#include <linux/module.h>

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/slab.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/workqueue.h>
#include <linux/gpio.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of.h>
#include <linux/spinlock.h>
#include <linux/wakelock.h>
#include <linux/input/flip_cover.h>

struct device *sec_device_create(void *drvdata, const char *fmt);

struct hall_drvdata {
	struct input_dev *input;
	int gpio_flip_cover;
	int irq_flip_cover;
	struct work_struct work;
	struct delayed_work flip_cover_dwork;
	struct wake_lock flip_wake_lock;
#ifdef CONFIG_SENSORS_HALL_IRQ_CTRL
	struct mutex irq_lock;
	bool gsm_area;
	bool irq_state;
	bool cover_state;
	bool wa_enable;
#endif
};

static bool flip_cover = 1;

/* WorkAround for K3G Hall IRQ Problem */
#ifdef CONFIG_SENSORS_HALL_IRQ_CTRL
struct hall_drvdata *g_drvdata;

#define enable_hall_irq() \
	do { \
		if (g_drvdata->irq_state == false) { \
			g_drvdata->irq_state = true; \
			enable_irq(g_drvdata->irq_flip_cover); \
			pr_info("%s():irq is enabled\n", __func__);\
		} else { \
			pr_info("%s():irq is already enabled\n",\
					__func__);\
		}\
	} while (0)

#define disable_hall_irq() \
	do { \
		if (g_drvdata->irq_state == true) { \
			g_drvdata->irq_state = false; \
			disable_irq(g_drvdata->irq_flip_cover); \
			pr_info("%s():irq is disabled\n", __func__);\
		} else { \
			pr_info("%s():irq is already disabled\n",\
					__func__);\
		}\
	} while (0)

void hall_irq_set(int state, bool auth_changed)
{
	if (auth_changed)
		g_drvdata->cover_state = state;

	pr_info("%s: gsm: %d, cover: %d, irq: %d, state: %d, auth: %d\n",
			__func__, g_drvdata->gsm_area, g_drvdata->cover_state,
			g_drvdata->irq_state, state, auth_changed);

	if (g_drvdata->gsm_area) {
		mutex_lock(&g_drvdata->irq_lock);

		if (state)
			enable_hall_irq();
		else
			disable_hall_irq();

		mutex_unlock(&g_drvdata->irq_lock);
	}
}

static ssize_t hall_irq_ctrl_store(struct device *dev,
		struct device_attribute *attr, const char *buf,
		size_t count)
{
	pr_info("%s: %s\n", __func__, buf);

	if (!g_drvdata->wa_enable)
		return count;

	if (!strncasecmp(buf, "ON", 2)) {
		g_drvdata->gsm_area = true;
		if (!g_drvdata->cover_state)
			hall_irq_set(disable, false);
	} else if (!strncasecmp(buf, "OFF", 3)) {
		hall_irq_set(enable, false);
		g_drvdata->gsm_area = false;
	} else {
		pr_info("%s: Wrong command, current state %s\n",
				__func__, g_drvdata->gsm_area?"ON":"OFF");
	}

	return count;
}

static DEVICE_ATTR(hall_irq_ctrl, 0664, NULL, hall_irq_ctrl_store);
#endif

static ssize_t hall_detect_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (flip_cover) {
		sprintf(buf, "OPEN");
	} else {
		sprintf(buf, "CLOSE");
	}

	return strlen(buf);
}
static DEVICE_ATTR(hall_detect, 0664, hall_detect_show, NULL);

static struct attribute *hall_attrs[] = {
	&dev_attr_hall_detect.attr,
/* WorkAround for K3G Hall IRQ Problem */
#ifdef CONFIG_SENSORS_HALL_IRQ_CTRL
	&dev_attr_hall_irq_ctrl.attr,
#endif
	NULL,
};

static struct attribute_group hall_attr_group = {
	.attrs = hall_attrs,
};

#ifdef CONFIG_SEC_FACTORY
static void flip_cover_work(struct work_struct *work)
{
	bool first,second;
	struct hall_drvdata *ddata =
		container_of(work, struct hall_drvdata,
				flip_cover_dwork.work);

	first = gpio_get_value_cansleep(ddata->gpio_flip_cover);

	printk("keys:%s #1 : %d\n", __func__, first);

	msleep(50);

	second = gpio_get_value_cansleep(ddata->gpio_flip_cover);

	printk("keys:%s #2 : %d\n", __func__, second);

	if(first == second) {
		flip_cover = first;
		input_report_switch(ddata->input, SW_LID, !flip_cover);
		input_sync(ddata->input);
	}
}
#else
static void flip_cover_work(struct work_struct *work)
{
	bool first;
#ifdef CONFIG_SENSORS_HALL_IRQ_CTRL
	bool second;
#endif
	struct hall_drvdata *ddata =
		container_of(work, struct hall_drvdata,
				flip_cover_dwork.work);

	first = gpio_get_value_cansleep(ddata->gpio_flip_cover);

	printk("keys:%s #1 : %d\n", __func__, first);

/* WorkAround for K3G Hall IRQ Problem */
#ifdef CONFIG_SENSORS_HALL_IRQ_CTRL
	if (g_drvdata->gsm_area) {
		pr_info("%s: NDT\n", __func__);
		mdelay(7);
		second = gpio_get_value_cansleep(ddata->gpio_flip_cover);
		if (first != second) {
			pr_info("%s: NDT, not stable value\n", __func__);
			return;
		}
	}
#endif
	flip_cover = first;
	input_report_switch(ddata->input,
			SW_LID, !flip_cover);
	input_sync(ddata->input);
}
#endif

static void __flip_cover_detect(struct hall_drvdata *ddata, bool flip_status)
{
	cancel_delayed_work_sync(&ddata->flip_cover_dwork);
#ifdef CONFIG_SEC_FACTORY
	schedule_delayed_work(&ddata->flip_cover_dwork, HZ / 20);
#else
	if(flip_status)	{
		wake_lock_timeout(&ddata->flip_wake_lock, HZ * 5 / 100); /* 50ms */
		schedule_delayed_work(&ddata->flip_cover_dwork, HZ * 1 / 100); /* 10ms */
	} else {
		wake_unlock(&ddata->flip_wake_lock);
		schedule_delayed_work(&ddata->flip_cover_dwork, 0);
	}
#endif
}

static irqreturn_t flip_cover_detect(int irq, void *dev_id)
{
	bool flip_status;
	struct hall_drvdata *ddata = dev_id;

	flip_status = gpio_get_value_cansleep(ddata->gpio_flip_cover);

	printk(KERN_DEBUG "keys:%s flip_status : %d\n",
		 __func__, flip_status);

	__flip_cover_detect(ddata, flip_status);

	return IRQ_HANDLED;
}

static int hall_open(struct input_dev *input)
{
	struct hall_drvdata *ddata = input_get_drvdata(input);
	/* update the current status */
	schedule_delayed_work(&ddata->flip_cover_dwork, HZ / 2);
	/* Report current state of buttons that are connected to GPIOs */
	input_sync(input);

	return 0;
}

static void hall_close(struct input_dev *input)
{
}


static void init_hall_ic_irq(struct input_dev *input)
{
	struct hall_drvdata *ddata = input_get_drvdata(input);

	int ret = 0;
	int irq = ddata->irq_flip_cover;

	flip_cover = gpio_get_value_cansleep(ddata->gpio_flip_cover);

	INIT_DELAYED_WORK(&ddata->flip_cover_dwork, flip_cover_work);

	ret =
		request_threaded_irq(
		irq, NULL,
		flip_cover_detect,
		IRQF_DISABLED | IRQF_TRIGGER_RISING |
		IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
		"flip_cover", ddata);
	if (ret < 0) {
		printk(KERN_ERR
		"keys: failed to request flip cover irq %d gpio %d\n",
		irq, ddata->gpio_flip_cover);
	} else {
		pr_info("%s : success\n", __func__);
#ifdef CONFIG_SENSORS_HALL_IRQ_CTRL
		g_drvdata->irq_state = true;
#endif
	}
}

#ifdef CONFIG_OF
static int of_hall_data_parsing_dt(struct hall_drvdata *ddata)
{
	struct device_node *np_haptic;
	int gpio;
	enum of_gpio_flags flags;
#ifdef CONFIG_SENSORS_HALL_IRQ_CTRL
	u32 temp;
	int ret;
#endif

	np_haptic = of_find_node_by_path("/hall");
	if (np_haptic == NULL) {
		printk("%s : error to get dt node\n", __func__);
		return -EINVAL;
	}

	gpio = of_get_named_gpio_flags(np_haptic, "hall,gpio_flip_cover", 0, &flags);
	if (gpio < 0) {
		pr_info("%s: fail to get flip_cover \n", __func__ );
		return -EINVAL;
	}
	ddata->gpio_flip_cover = gpio;

	gpio = gpio_to_irq(gpio);
	if (gpio < 0) {
		pr_info("%s: fail to return irq corresponding gpio \n", __func__ );
		return -EINVAL;
	}
	ddata->irq_flip_cover = gpio;

#ifdef CONFIG_SENSORS_HALL_IRQ_CTRL
	ret = of_property_read_u32(np_haptic, "hall,gsm_wa", &temp);
	if (ret) {
		pr_info("%s: No property about WA\n", __func__);
		ddata->wa_enable = false;
	} else {
		pr_info("%s: get the wa property\n", __func__);
		ddata->wa_enable = temp;
	}
#endif

	return 0;
}
#endif

static int hall_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hall_drvdata *ddata;
	struct input_dev *input;
	int error;
	int wakeup = 0;

	ddata = kzalloc(sizeof(struct hall_drvdata), GFP_KERNEL);
	if (!ddata) {
		dev_err(dev, "failed to allocate state\n");
		return -ENOMEM;
	}

#ifdef CONFIG_OF
	if(dev->of_node) {
		error = of_hall_data_parsing_dt(ddata);
		if (error < 0) {
			pr_info("%s : fail to get the dt (HALL)\n", __func__);
			goto fail1;
		}
	}
#endif

	input = input_allocate_device();
	if (!input) {
		dev_err(dev, "failed to allocate state\n");
		error = -ENOMEM;
		goto fail1;
	}

	ddata->input = input;

	wake_lock_init(&ddata->flip_wake_lock, WAKE_LOCK_SUSPEND,
		"flip wake lock");

	platform_set_drvdata(pdev, ddata);
	input_set_drvdata(input, ddata);

	input->name = "hall";
	input->phys = "hall";
	input->dev.parent = &pdev->dev;

	input->evbit[0] |= BIT_MASK(EV_SW);
	input_set_capability(input, EV_SW, SW_LID);

	input->open = hall_open;
	input->close = hall_close;

	/* Enable auto repeat feature of Linux input subsystem */
	__set_bit(EV_REP, input->evbit);

#ifdef CONFIG_SENSORS_HALL_IRQ_CTRL
	mutex_init(&ddata->irq_lock);

	ddata->gsm_area = false;
	ddata->cover_state = false;
	g_drvdata = ddata;
#endif

	init_hall_ic_irq(input);

	error = sysfs_create_group(&sec_key->kobj, &hall_attr_group);
	if (error) {
		dev_err(dev, "Unable to export keys/switches, error: %d\n",
			error);
		goto fail2;
	}

	error = input_register_device(input);
	if (error) {
		dev_err(dev, "Unable to register input device, error: %d\n",
			error);
		goto fail3;
	}

	device_init_wakeup(&pdev->dev, wakeup);

	return 0;

 fail3:
	sysfs_remove_group(&pdev->dev.kobj, &hall_attr_group);
 fail2:
	platform_set_drvdata(pdev, NULL);
	wake_lock_destroy(&ddata->flip_wake_lock);
	input_free_device(input);
 fail1:
	kfree(ddata);

	return error;
}

static int hall_remove(struct platform_device *pdev)
{
	struct hall_drvdata *ddata = platform_get_drvdata(pdev);
	struct input_dev *input = ddata->input;

	printk("%s start\n", __func__);
	sysfs_remove_group(&pdev->dev.kobj, &hall_attr_group);

	device_init_wakeup(&pdev->dev, 0);

	input_unregister_device(input);

	wake_lock_destroy(&ddata->flip_wake_lock);

	kfree(ddata);

	return 0;
}

#if defined(CONFIG_OF)
static struct of_device_id hall_dt_ids[] = {
	{ .compatible = "hall" },
	{ },
};
MODULE_DEVICE_TABLE(of, hall_dt_ids);
#endif /* CONFIG_OF */

#ifdef CONFIG_PM_SLEEP
static int hall_suspend(struct device *dev)
{
	struct hall_drvdata *ddata = dev_get_drvdata(dev);
	struct input_dev *input = ddata->input;

	printk("%s start\n", __func__);

/* need to be change */
/* Without below one line, it is not able to get the irq during freezing */
#ifdef CONFIG_SENSORS_HALL_IRQ_CTRL
	/* gsm_area can be controlled only in hall_irq_set */
	if (!g_drvdata->cover_state && g_drvdata->gsm_area)
		disable_irq_wake(ddata->irq_flip_cover);
	else
		enable_irq_wake(ddata->irq_flip_cover);
#else
	enable_irq_wake(ddata->irq_flip_cover);
#endif

	if (device_may_wakeup(dev)) {
		enable_irq_wake(ddata->irq_flip_cover);
	} else {
		mutex_lock(&input->mutex);
		if (input->users)
			hall_close(input);
		mutex_unlock(&input->mutex);
	}

	return 0;
}

static int hall_resume(struct device *dev)
{
	struct hall_drvdata *ddata = dev_get_drvdata(dev);
	struct input_dev *input = ddata->input;

	printk("%s start\n", __func__);
	input_report_switch(ddata->input, SW_FLIP,
			gpio_get_value_cansleep(ddata->gpio_flip_cover));
	input_sync(input);
#ifdef CONFIG_SENSORS_HALL_IRQ_CTRL
	/* gsm_area can be controlled only in hall_irq_set */
	if (g_drvdata->cover_state && g_drvdata->gsm_area)
		hall_irq_set(enable, false);
#endif
	return 0;
}
#endif

static SIMPLE_DEV_PM_OPS(hall_pm_ops, hall_suspend, hall_resume);

static struct platform_driver hall_device_driver = {
	.probe		= hall_probe,
	.remove		= hall_remove,
	.driver		= {
		.name	= "hall",
		.owner	= THIS_MODULE,
		.pm	= &hall_pm_ops,
#if defined(CONFIG_OF)
		.of_match_table	= hall_dt_ids,
#endif /* CONFIG_OF */
	}
};

static int __init hall_init(void)
{
	printk("%s start\n", __func__);
	return platform_driver_register(&hall_device_driver);
}

static void __exit hall_exit(void)
{
	printk("%s start\n", __func__);
	platform_driver_unregister(&hall_device_driver);
}

late_initcall(hall_init);
module_exit(hall_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Phil Blundell <pb@handhelds.org>");
MODULE_DESCRIPTION("Keyboard driver for GPIOs");
MODULE_ALIAS("platform:gpio-keys");
