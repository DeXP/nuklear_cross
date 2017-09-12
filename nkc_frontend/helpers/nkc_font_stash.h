/**
 * Nuklear+ (read as "Nuklear cross") is a front-end overlay for Nuklear GUI library. 
 * Write one simple code, compile it for any supported frontend.
 *
 * License: public domain
 * no warrenty implied; use at your own risk.
 * authored from 2016-2017 by Dmitry Hrabrov a.k.a. DeXPeriX
 */

#ifndef NKC_FONT_STASH_LOADER

#include "nkc_file.h"

#define NKC_FONT_STASH_LOADER(NKC_STASH_FRONTEND) \
\
NK_API struct nk_user_font* nkc_load_font_file(struct nkc* nkcHandle, const char* filename, float size, \
                              const nk_rune *symbolsRange) \
{ \
    struct nk_font_atlas *atlas; \
    struct nk_font_config config = nk_font_config(size); \
    config.oversample_h = 1; \
    config.oversample_v = 1; \
    if(symbolsRange != NULL) config.range = symbolsRange; \
        else config.range = nk_font_default_glyph_ranges(); \
    if( !nkc_file_exists(filename) ) return NULL; \
    nk_##NKC_STASH_FRONTEND##_font_stash_begin(&atlas); \
    struct nk_font *loadedFont = nk_font_atlas_add_from_file(atlas, filename, size, &config); \
    nk_##NKC_STASH_FRONTEND##_font_stash_end(); \
    if( loadedFont ){ \
        nk_style_set_font(nkcHandle->ctx, &loadedFont->handle); \
        return &loadedFont->handle; \
    } else return NULL; \
} \
\
NK_API struct nk_user_font* nkc_load_font_memory(struct nkc* nkcHandle, const void* membuf, int membufSize, \
                                float size, const nk_rune *symbolsRange) \
{ \
    struct nk_font_atlas *atlas; \
    struct nk_font_config config = nk_font_config(size); \
    config.oversample_h = 1; \
    config.oversample_v = 1; \
    if(symbolsRange != NULL) config.range = symbolsRange; \
        else config.range = nk_font_default_glyph_ranges(); \
    nk_##NKC_STASH_FRONTEND##_font_stash_begin(&atlas); \
    struct nk_font *memfont = nk_font_atlas_add_from_memory(atlas, (void*)membuf, membufSize, size, &config); \
    nk_##NKC_STASH_FRONTEND##_font_stash_end(); \
    if( memfont ){ \
        nk_style_set_font(nkcHandle->ctx, &memfont->handle); \
        return &memfont->handle; \
    } else return NULL; \
}

#endif