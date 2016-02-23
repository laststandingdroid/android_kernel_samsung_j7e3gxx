#ifndef __MDNIE_TABLE_H__
#define __MDNIE_TABLE_H__

/* 2015.02.16 */

static struct mdnie_scr_info scr_info = {
	.index = 2,
	.color_blind = 1,	/* ASCR_WIDE_CR[7:0] */
	.white_r = 19,		/* ASCR_WIDE_WR[7:0] */
	.white_g = 21,		/* ASCR_WIDE_WG[7:0] */
	.white_b = 23		/* ASCR_WIDE_WB[7:0] */
};

static inline int color_offset_f1(int x, int y)
{
	return ((y << 10) - (((x << 10) * 99) / 91) - (6 << 10)) >> 10;
}
static inline int color_offset_f2(int x, int y)
{
	return ((y << 10) - (((x << 10) * 164) / 157) - (8 << 10)) >> 10;
}
static inline int color_offset_f3(int x, int y)
{
	return ((y << 10) + (((x << 10) * 218) / 39) - (20166 << 10)) >> 10;
}
static inline int color_offset_f4(int x, int y)
{
	return ((y << 10) + (((x << 10) * 23) / 8) - (11610 << 10)) >> 10;
}

/* color coordination order is WR, WG, WB */
static unsigned char coordinate_data_1[] = {
	0xff, 0xff, 0xff, /* dummy */
	0xff, 0xf8, 0xf9, /* Tune_1 */
	0xff, 0xfa, 0xfe, /* Tune_2 */
	0xfb, 0xf9, 0xff, /* Tune_3 */
	0xff, 0xfe, 0xfb, /* Tune_4 */
	0xff, 0xff, 0xff, /* Tune_5 */
	0xf9, 0xfb, 0xff, /* Tune_6 */
	0xfc, 0xff, 0xf9, /* Tune_7 */
	0xfb, 0xff, 0xfb, /* Tune_8 */
	0xfa, 0xff, 0xff, /* Tune_9 */
};

static unsigned char *coordinate_data[MODE_MAX] = {
	coordinate_data_1,
	coordinate_data_1,
	coordinate_data_1,
	coordinate_data_1,
	coordinate_data_1,
	coordinate_data_1,
};

static unsigned char LEVEL_UNLOCK[] = {
	0xF0,
	0x5A, 0x5A
};

static unsigned char LEVEL_LOCK[] = {
	0xF0,
	0xA5, 0xA5
};

static unsigned char BYPASS_1[] ={
	0xE8,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned char BYPASS_2[] ={
	0xE9,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0x00
};

static unsigned char BYPASS_3[] ={
	0xEA,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20
};

static unsigned char BYPASS_4[] ={
	0xEB,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0xFF
};

static unsigned char BYPASS_5[] ={
	0xEC,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00
};

static unsigned char BYPASS_6[] ={
	0xE7,
	0x00, 0x00, 0x02, 0xD0, 0x05, 0x00, 0x00
};

static unsigned char NEGATIVE_1[] ={
	0xE8,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned char NEGATIVE_2[] ={
	0xE9,
	0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00,
	0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF,
	0x00, 0xFF, 0x00, 0xFF
};

static unsigned char NEGATIVE_3[] ={
	0xEA,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20
};

static unsigned char NEGATIVE_4[] ={
	0xEB,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0xFF
};

static unsigned char NEGATIVE_5[] ={
	0xEC,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00
};

static unsigned char NEGATIVE_6[] ={
	0xE7,
	0x08, 0x30, 0x02, 0xD0, 0x05, 0x00, 0x00
};

static unsigned char GRAYSCALE_1[] ={
	0xE8,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned char GRAYSCALE_2[] ={
	0xE9,
	0xE2, 0x1D, 0xE2, 0x1D, 0xE2, 0x1D, 0x69, 0x96, 0x69, 0x96,
	0x69, 0x96, 0xB3, 0x4C, 0xB3, 0x4C, 0xB3, 0x4C, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0x00
};

static unsigned char GRAYSCALE_3[] ={
	0xEA,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20
};

static unsigned char GRAYSCALE_4[] ={
	0xEB,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0xFF
};

static unsigned char GRAYSCALE_5[] ={
	0xEC,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00
};

static unsigned char GRAYSCALE_6[] ={
	0xE7,
	0x08, 0x30, 0x02, 0xD0, 0x05, 0x00, 0x00
};

static unsigned char GRAYSCALE_NEGATIVE_1[] ={
	0xE8,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned char GRAYSCALE_NEGATIVE_2[] ={
	0xE9,
	0x1D, 0xE2, 0x1D, 0xE2, 0x1D, 0xE2, 0x96, 0x69, 0x96, 0x69,
	0x96, 0x69, 0x4C, 0xB3, 0x4C, 0xB3, 0x4C, 0xB3, 0x00, 0xFF,
	0x00, 0xFF, 0x00, 0xFF
};

static unsigned char GRAYSCALE_NEGATIVE_3[] ={
	0xEA,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20
};

static unsigned char GRAYSCALE_NEGATIVE_4[] ={
	0xEB,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0xFF
};

static unsigned char GRAYSCALE_NEGATIVE_5[] ={
	0xEC,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00
};

static unsigned char GRAYSCALE_NEGATIVE_6[] ={
	0xE7,
	0x08, 0x30, 0x02, 0xD0, 0x05, 0x00, 0x00
};

static unsigned char UI_1[] ={
	0xE8,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned char UI_2[] ={
	0xE9,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0x00
};

static unsigned char UI_3[] ={
	0xEA,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20
};

static unsigned char UI_4[] = {
	0xEB,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0xFF
};

static unsigned char UI_5[] ={
	0xEC,
	0x04, 0x88, 0x1F, 0xA6, 0x1F, 0xD2, 0x1F, 0xEE, 0x04, 0x3F,
	0x1F, 0xD2, 0x1F, 0xEE, 0x1F, 0xA6, 0x04, 0x6C
};

static unsigned char UI_6[] ={
	0xE7,
	0x08, 0x03, 0x02, 0xD0, 0x05, 0x00, 0x02
};

static unsigned char VIDEO_1[] ={
	0xE8,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned char VIDEO_2[] = {
	0xE9,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0x00
};

static unsigned char VIDEO_3[] ={
	0xEA,
	0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C,
	0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C,
	0x00, 0x1C, 0x00, 0x1C
};

static unsigned char VIDEO_4[] = {
	0xEB,
	0x00, 0x1C, 0x0D, 0xA4, 0x0D, 0xA4, 0x0D, 0xA4, 0x0D, 0xA4,
	0x0D, 0xA4, 0x0D, 0xA4, 0x0D, 0xA4, 0x0D, 0xA4, 0x25, 0x1C,
	0x4A, 0x17, 0x00, 0xFF
};

static unsigned char VIDEO_5[] ={
	0xEC,
	0x04, 0x88, 0x1F, 0xA6, 0x1F, 0xD2, 0x1F, 0xEE, 0x04, 0x3F,
	0x1F, 0xD2, 0x1F, 0xEE, 0x1F, 0xA6, 0x04, 0x6C
};

static unsigned char VIDEO_6[] = {
	0xE7, 0x08, 0x03, 0x02, 0xD0, 0x05, 0x00, 0x07
};

static unsigned char CAMERA_1[] ={
	0xE8,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned char CAMERA_2[] ={
	0xE9,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0x00
};

static unsigned char CAMERA_3[] ={
	0xEA,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20
};

static unsigned char CAMERA_4[] ={
	0xEB,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0xFF
};

static unsigned char CAMERA_5[] ={
	0xEC,
	0x04, 0x88, 0x1F, 0xA6, 0x1F, 0xD2, 0x1F, 0xEE, 0x04, 0x3F,
	0x1F, 0xD2, 0x1F, 0xEE, 0x1F, 0xA6, 0x04, 0x6C
};

static unsigned char CAMERA_6[] ={
	0xE7,
	0x08, 0x03, 0x02, 0xD0, 0x05, 0x00, 0x02
};

static unsigned char GALLERY_1[] ={
	0xE8,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned char GALLERY_2[] = {
	0xE9,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0x00
};

static unsigned char GALLERY_3[] = {
	0xEA,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20
};

static unsigned char GALLERY_4[] ={
	0xEB,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0xFF
};

static unsigned char GALLERY_5[] = {
	0xEC,
	0x04, 0x88, 0x1F, 0xA6, 0x1F, 0xD2, 0x1F, 0xEE, 0x04, 0x3F,
	0x1F, 0xD2, 0x1F, 0xEE, 0x1F, 0xA6, 0x04, 0x6C
};

static unsigned char GALLERY_6[] = {
	0xE7,
	0x08, 0x03, 0x02, 0xD0, 0x05, 0x00, 0x02
};

static unsigned char VT_1[] = {
	0xE8,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned char VT_2[] = {
	0xE9,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0x00
};

static unsigned char VT_3[] = {
	0xEA,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20
};

static unsigned char VT_4[] = {
	0xEB,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0xFF
};

static unsigned char VT_5[] = {
	0xEC,
	0x04, 0x88, 0x1F, 0xA6, 0x1F, 0xD2, 0x1F, 0xEE, 0x04, 0x3F,
	0x1F, 0xD2, 0x1F, 0xEE, 0x1F, 0xA6, 0x04, 0x6C
};

static unsigned char VT_6[] = {
	0xE7,
	0x08, 0x03, 0x02, 0xD0, 0x05, 0x00, 0x06
};

static unsigned char BROWSER_1[] = {
	0xE8,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned char BROWSER_2[] = {
	0xE9,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0x00
};

static unsigned char BROWSER_3[] = {
	0xEA,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20
};

static unsigned char BROWSER_4[] = {
	0xEB,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0xFF
};

static unsigned char BROWSER_5[] = {
	0xEC,
	0x04, 0x88, 0x1F, 0xA6, 0x1F, 0xD2, 0x1F, 0xEE, 0x04, 0x3F,
	0x1F, 0xD2, 0x1F, 0xEE, 0x1F, 0xA6, 0x04, 0x6C
};

static unsigned char BROWSER_6[] = {
	0xE7,
	0x08, 0x33, 0x02, 0xD0, 0x05, 0x00, 0x02
};

static unsigned char EBOOK_UI_1[] = {
	0xE8,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned char EBOOK_UI_2[] = {
	0xE9,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xD6, 0x00,
	0xEA, 0x00, 0xFF, 0x00
};

static unsigned char EBOOK_UI_3[] = {
	0xEA,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20
};

static unsigned char EBOOK_UI_4[] = {
	0xEB,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0xFF
};

static unsigned char EBOOK_UI_5[] = {
	0xEC,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00
};

static unsigned char EBOOK_UI_6[] = {
	0xE7,
	0x08, 0x30, 0x02, 0xD0, 0x05, 0x00, 0x00
};

static unsigned char EMAIL_1[] = {
	0xE8,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned char EMAIL_2[] = {
	0xE9,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0xF7, 0x00
};

static unsigned char EMAIL_3[] = {
	0xEA,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20
};

static unsigned char EMAIL_4[] = {
	0xEB,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0xFF
};

static unsigned char EMAIL_5[] = {
	0xEC,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00
};

static unsigned char EMAIL_6[] = {
	0xE7,
	0x08, 0x30, 0x02, 0xD0, 0x05, 0x00, 0x00
};

static char OUTDOOR_MDNIE_1[] ={
	0xE8,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static char OUTDOOR_MDNIE_2[] ={
	0xE9,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0x00
};

static char OUTDOOR_MDNIE_3[] ={
	0xEA,
	0x00, 0x7B, 0x03, 0x48, 0x08, 0x32, 0x08, 0x32, 0x08, 0x32,
	0x08, 0x32, 0x08, 0x32, 0x10, 0x28, 0x10, 0x28, 0x10, 0x28,
	0x10, 0x28, 0x10, 0x28
};

static char OUTDOOR_MDNIE_4[] ={
	0xEB,
	0x19, 0x22, 0x19, 0x22, 0x19, 0x22, 0x19, 0x22, 0x19, 0x22,
	0x19, 0x22, 0x23, 0x1E, 0x2E, 0x1B, 0x33, 0x1A, 0x40, 0x18,
	0x48, 0x17, 0x00, 0xFF
};

static char OUTDOOR_MDNIE_5[] ={
	0xEC,
	0x04, 0x88, 0x1F, 0xA6, 0x1F, 0xD2, 0x1F, 0xEE, 0x04, 0x3F,
	0x1F, 0xD2, 0x1F, 0xEE, 0x1F, 0xA6, 0x04, 0x6C
};

static char OUTDOOR_MDNIE_6[] ={
	0xE7,
	0x08, 0x03, 0x02, 0xD0, 0x05, 0x00, 0x03
};

static char COLOR_ADJUSTMENT_MDNIE_1[] ={
	0xE8,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static char COLOR_ADJUSTMENT_MDNIE_2[] ={
	0xE9,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0x00
};

static char COLOR_ADJUSTMENT_MDNIE_3[] ={
	0xEA,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20
};

static char COLOR_ADJUSTMENT_MDNIE_4[] ={
	0xEB,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20,
	0x00, 0x20, 0x00, 0xFF
};

static char COLOR_ADJUSTMENT_MDNIE_5[] ={
	0xEC,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00
};

static char COLOR_ADJUSTMENT_MDNIE_6[] ={
	0xE7,
	0x08, 0x30, 0x02, 0xD0, 0x05, 0x00, 0x00
};

#define MDNIE_SET(id)	\
{							\
	.name		= #id,				\
	.update_flag	= {0, 1, 2, 3, 4, 5, 6, 0},			\
	.seq		= {				\
		{	.cmd = LEVEL_UNLOCK,	.len = ARRAY_SIZE(LEVEL_UNLOCK),	.sleep = 0,},	\
		{	.cmd = id##_1,		.len = ARRAY_SIZE(id##_1),		.sleep = 0,},	\
		{	.cmd = id##_2,		.len = ARRAY_SIZE(id##_2),		.sleep = 0,},	\
		{	.cmd = id##_3,		.len = ARRAY_SIZE(id##_3),		.sleep = 0,},	\
		{	.cmd = id##_4,		.len = ARRAY_SIZE(id##_4),		.sleep = 0,},	\
		{	.cmd = id##_5,		.len = ARRAY_SIZE(id##_5),		.sleep = 0,},	\
		{	.cmd = id##_6,		.len = ARRAY_SIZE(id##_6),		.sleep = 0,},	\
		{	.cmd = LEVEL_LOCK,	.len = ARRAY_SIZE(LEVEL_LOCK),		.sleep = 0,},	\
	}	\
}

struct mdnie_table bypass_table[BYPASS_MAX] = {
	[BYPASS_ON] = MDNIE_SET(BYPASS)
};

struct mdnie_table accessibility_table[ACCESSIBILITY_MAX] = {
	[NEGATIVE] = MDNIE_SET(NEGATIVE),
	MDNIE_SET(COLOR_ADJUSTMENT_MDNIE),
	MDNIE_SET(UI),
	MDNIE_SET(GRAYSCALE),
	MDNIE_SET(GRAYSCALE_NEGATIVE)
};


struct mdnie_table hbm_table[HBM_MAX] = {
	[HBM_ON] = 	MDNIE_SET(OUTDOOR_MDNIE),
	MDNIE_SET(OUTDOOR_MDNIE),
};

struct mdnie_table main_table[SCENARIO_MAX][MODE_MAX] = {
	{
		MDNIE_SET(UI),
		MDNIE_SET(UI),
		MDNIE_SET(UI),
		MDNIE_SET(UI),
		MDNIE_SET(EBOOK_UI),
		MDNIE_SET(UI),
	}, {
		MDNIE_SET(VIDEO),
		MDNIE_SET(VIDEO),
		MDNIE_SET(VIDEO),
		MDNIE_SET(VIDEO),
		MDNIE_SET(EBOOK_UI),
		MDNIE_SET(VIDEO),
	},
	[CAMERA_MODE] = {
		MDNIE_SET(CAMERA),
		MDNIE_SET(CAMERA),
		MDNIE_SET(CAMERA),
		MDNIE_SET(CAMERA),
		MDNIE_SET(EBOOK_UI),
		MDNIE_SET(CAMERA),
	},
	[GALLERY_MODE] = {
		MDNIE_SET(GALLERY),
		MDNIE_SET(GALLERY),
		MDNIE_SET(GALLERY),
		MDNIE_SET(GALLERY),
		MDNIE_SET(EBOOK_UI),
		MDNIE_SET(GALLERY),
	}, {
		MDNIE_SET(VT),
		MDNIE_SET(VT),
		MDNIE_SET(VT),
		MDNIE_SET(VT),
		MDNIE_SET(EBOOK_UI),
		MDNIE_SET(VT),
	}, {
		MDNIE_SET(BROWSER),
		MDNIE_SET(BROWSER),
		MDNIE_SET(BROWSER),
		MDNIE_SET(BROWSER),
		MDNIE_SET(EBOOK_UI),
		MDNIE_SET(BROWSER),
	}, {
		MDNIE_SET(EBOOK_UI),
		MDNIE_SET(EBOOK_UI),
		MDNIE_SET(EBOOK_UI),
		MDNIE_SET(EBOOK_UI),
		MDNIE_SET(EBOOK_UI),
		MDNIE_SET(EBOOK_UI),
	}, {
		MDNIE_SET(EMAIL),
		MDNIE_SET(EMAIL),
		MDNIE_SET(EMAIL),
		MDNIE_SET(EMAIL),
		MDNIE_SET(EBOOK_UI),
		MDNIE_SET(EMAIL),
	}
};
#undef MDNIE_SET

static struct mdnie_tune tune_info = {
	.bypass_table = bypass_table,
	.accessibility_table = accessibility_table,
	.hbm_table = hbm_table,
	.main_table = main_table,

	.coordinate_table = coordinate_data,
	.scr_info = &scr_info,
	.color_offset = {color_offset_f1, color_offset_f2, color_offset_f3, color_offset_f4}
};

#endif