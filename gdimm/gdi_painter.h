#pragma once

#include "painter.h"

using namespace std;

class gdimm_gdi_painter : public gdimm_painter
{
	struct text_bbox
	{
		/*
		extent and baseline determine the bounding box before clipping
		visible rectangle is the visible part after clipping
		they are identical if no clipping happens
		the area of visible rectangle is always less or equal to the extent
		*/
		SIZE extent;
		POINT baseline;
		RECT visible_rect;
	};

	HDC _hdc_canvas;
	RGBQUAD _text_rgb_gamma;

	static INT adjust_glyph_bbox(bool is_pdy, UINT count, CONST INT *lpDx, glyph_run &a_glyph_run);

	void set_mono_mask_bits(const FT_BitmapGlyph glyph,
		const RECT &src_rect,
		BYTE *dest_bits,
		const RECT &dest_rect,
		int dest_pitch,
		bool project_bottom) const;
	void set_gray_text_bits(const FT_BitmapGlyph glyph,
		const RECT &src_rect,
		BYTE *dest_bits,
		const RECT &dest_rect,
		int dest_pitch,
		bool project_bottom) const;
	void set_lcd_text_bits(const FT_BitmapGlyph glyph,
		const RECT &src_rect,
		BYTE *dest_bits,
		const RECT &dest_rect,
		int dest_pitch,
		bool project_bottom,
		BYTE alpha) const;

	BOOL paint_mono(UINT options, CONST RECT *lprect, const glyph_run &a_glyph_run, const text_bbox &bbox) const;
	BOOL paint_gray(UINT options, CONST RECT *lprect, const glyph_run &a_glyph_run, const text_bbox &bbox) const;
	BOOL paint_lcd(UINT options, CONST RECT *lprect, const glyph_run &a_glyph_run, const text_bbox &bbox) const;
	BOOL paint_glyph_run(UINT options, CONST RECT *lprect, const glyph_run &a_glyph_run, INT max_glyph_distance = 0);

public:
	bool begin(const dc_context *context, FT_Render_Mode render_mode);
	void end();
	bool paint(int x, int y, UINT options, CONST RECT *lprect, const void *text, UINT c, CONST INT *lpDx);
};