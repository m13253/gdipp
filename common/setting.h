#pragma once

#include "global.h"
#include <pugixml.hpp>
#include <list>
#include <map>
#include <set>
using namespace pugi;
using namespace std;

#define COMMON_BRANCH_NAME "common"

class _gdimm_setting
{
public:
	struct gamma_setting
	{
		double gray;
		double red;
		double green;
		double blue;

		gamma_setting();
	};

	struct shadow_setting
	{
		LONG offset_x;
		LONG offset_y;
		BYTE alpha;

		shadow_setting();
	};

	struct setting_items
	{
		bool auto_hinting;
		bool embedded_bitmap;
		float embolden;
		bool freetype_loader;
		gamma_setting gamma;
		bool hinting;
		BYTE lcd_filter;
		bool light_mode;
		LONG max_height;
		bool render_mono;
		bool render_non_aa;
		shadow_setting shadow;
		bool subpixel_render;
		bool zero_alpha;

		setting_items();
	};

private:
	// map keys are case-insensitive
	typedef map<const wstring, setting_items, string_ci_less> setting_map;

	setting_map _setting_branchs;
	set<const wstring, string_ci_less> _exclude_names;
	WCHAR _process_name[MAX_PATH];

	template <typename T>
	void evaluate_to_number(const xml_node &context_node, const char *expression, const T &default_value, T &out_value)
	{
		xpath_query query(expression);
		if (query.evaluate_boolean(context_node))
			out_value = (T) query.evaluate_number(context_node);
		else
			out_value = default_value;
	}

	void load_settings(const xml_node &context_node, const setting_items &default_items, setting_items &settings);
	void load_common(const xml_node &context_node);
	void load_branchs(const xml_node &context_node, const setting_items &default_items, const char *xpath);
	void load_exclude(const xml_node &context_node);

public:
	_gdimm_setting();
	bool init(HMODULE h_module);
	bool is_name_excluded(const WCHAR *name) const;

	const setting_items &get_setting_items(const WCHAR *font_family = TEXT(COMMON_BRANCH_NAME)) const;
};

typedef singleton<_gdimm_setting> gdimm_setting;