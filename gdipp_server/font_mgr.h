#pragma once

#include "gdipp_server/os2_metrics.h"

namespace gdipp
{

#define buf_family_name(metric_buf) (reinterpret_cast<const wchar_t *>(metric_buf + reinterpret_cast<const UINT>((reinterpret_cast<const OUTLINETEXTMETRICW *>(metric_buf)->otmpFamilyName))))
#define buf_face_name(metric_buf) (reinterpret_cast<const wchar_t *>(metric_buf + reinterpret_cast<const UINT>((reinterpret_cast<const OUTLINETEXTMETRICW *>(metric_buf)->otmpFaceName))))
#define buf_style_name(metric_buf) (reinterpret_cast<const wchar_t *>(metric_buf + reinterpret_cast<const UINT>((reinterpret_cast<const OUTLINETEXTMETRICW *>(metric_buf)->otmpStyleName))))
#define metric_family_name(outline_metric) (reinterpret_cast<const wchar_t *>(reinterpret_cast<const BYTE *>(outline_metric) + reinterpret_cast<const UINT>(outline_metric->otmpFamilyName)))
#define metric_face_name(outline_metric) (reinterpret_cast<const wchar_t *>(reinterpret_cast<const BYTE *>(outline_metric) + reinterpret_cast<const UINT>(outline_metric->otmpFaceName)))
#define metric_style_name(outline_metric) (reinterpret_cast<const wchar_t *>(reinterpret_cast<const BYTE *>(outline_metric) + reinterpret_cast<const UINT>(outline_metric->otmpStyleName)))

class font_mgr
{
public:
	static DWORD get_font_size(HDC font_holder, DWORD *table_header);
	static ULONG get_ttc_face_index(HDC font_holder, DWORD ttc_file_size);
	
	void *register_font(const LOGFONTW *log_font, BYTE **outline_metrics_buf, unsigned long *outline_metrics_size, HDC hdc = NULL);
	HFONT select_font(void *font_id, HDC hdc) const;

	ULONG lookup_face_index(void *font_id) const;
	DWORD lookup_font_data(void *font_id, DWORD table, DWORD offset, LPVOID data_buf, DWORD buf_size, HDC hdc = NULL) const;
	DWORD lookup_glyph_indices(void *font_id, const wchar_t *str, int count, unsigned short *gi, HDC hdc = NULL) const;
	const os2_metrics *lookup_os2_metrics(void *font_id) const;
	FT_Stream lookup_stream(void *font_id) const;

private:
	struct font_entry
	{
		// all fields are font-specific invariants

		HFONT font_handle;
		os2_metrics os2;
		FT_StreamRec stream;

		// used to retrieve font data from GetFontData
		DWORD face_index;
		DWORD table_header;
	};

	static unsigned long get_dc_outline_metrics(HDC hdc, BYTE **outline_metrics_buf);
	static unsigned long stream_io(FT_Stream stream, unsigned long offset, unsigned char *buffer, unsigned long count);
	static void stream_close(FT_Stream stream);

	std::map<std::wstring, font_entry> _font_registry;
};

}
