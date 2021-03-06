#pragma once

#include "gdipp_config/render_config_static.h"

namespace gdipp
{

const double pi = acos(-1.0);

// convert 26.6 fixed float type to 16.16 fixed point
FIXED fixed_from_26dot6(signed long x);

// convert 16.16 fixed point to 26.6 format
signed long fixed_to_26dot6(const FIXED &x);

// convert floating point to 16.16 format
signed long float_to_16dot16(double x);

// convert 16.16 fixed float type to integer
LONG int_from_16dot16(signed long x);

// convert 26.6 fixed float type to integer
LONG int_from_26dot6(signed long x);

DWORD create_tls_index();
BOOL free_tls_index(DWORD tls_index);

// high-performance division method to approximate number * numerator / 255
//BYTE division_by_255(short number, short numerator);

uint128_t generate_render_trait(const LOGFONTW *logfont, int render_mode);

// apply alignment on the reference point and use it to calculate the baseline
POINT get_baseline(UINT alignment, int x, int y, int width, int ascent, int descent);

// for given bitmap width and bit count, compute the bitmap pitch
int get_bmp_pitch(int width, WORD bpp);

// retrieve BITMAPINFOHEADER from the selected bitmap of the given DC
bool get_dc_bmp_header(HDC hdc, BITMAPINFOHEADER &dc_dc_bmp_header);

// get outline metrics of the DC
OUTLINETEXTMETRICW *get_dc_metrics(HDC hdc, std::vector<BYTE> &metric_buf);

int get_glyph_bmp_width(const FT_Bitmap &bitmap);

//LONG get_glyph_run_width(const glyph_run *a_glyph_run, bool is_control_width);

LOGFONTW get_log_font(HDC hdc);

// return true and fill the corresponding FT_Glyph_To_Bitmap render mode if find an appropriate render mode
// otherwise, return false
bool get_render_mode(const render_config_static::render_mode_static &render_mode_conf, WORD dc_bmp_bpp, BYTE font_quality, FT_Render_Mode *render_mode);

bool operator<(const LOGFONTW &lf1, const LOGFONTW &lf2);

//const FT_Glyph make_empty_outline_glyph();

//bool mb_to_wc(const char *multi_byte_str, int count, std::wstring &wide_char_str);

BOOL paint_background(HDC hdc, const RECT *bg_rect, COLORREF bg_color);

}
