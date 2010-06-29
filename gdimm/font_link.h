#pragma once

#include <gdipp_common.h>
using namespace std;

struct font_link_info
{
	wstring font_family;
	double scaling;
};

/*
only the constructor changes internal state
all public functions are read-only
therefore it is thread-safe
*/
class gdimm_font_link
{
	typedef map<wstring, vector<font_link_info>, wstring_ci_less> link_map;

	link_map _link_table;

public:
	gdimm_font_link();
	const font_link_info *lookup_link(const wchar_t *font_name, size_t index) const;
	size_t get_link_count(const wchar_t *font_name) const;
};