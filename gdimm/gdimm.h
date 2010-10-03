#pragma once

#include "font_link.h"
#include "font_store.h"
#include "gamma.h"
#include "glyph_cache.h"
#include "hook.h"
#include "setting_cache.h"

extern HMODULE h_self;
extern bool os_support_directwrite;

extern gdimm_font_link font_link_instance;
extern gdimm_font_store font_store_instance;
extern gdimm_gamma gamma_instance;
extern gdimm_glyph_cache glyph_cache_instance;
extern gdimm_hook hook_instance;
extern gdimm_setting_cache setting_cache_instance;

extern sqlite3 *glyph_cache_db;
extern sqlite3 *glyph_run_cache_db;