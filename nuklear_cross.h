/**
 * @file nuklear_cross.h
 * @version 0.70
 * @author Dmitry Hrabrov a.k.a. DeXPeriX
 * @date 2016-2017
 * @copyright public domain - no warrenty implied; use at your own risk.
 * @brief Nuklear+ (read as "Nuklear cross") is a front-end overlay for Nuklear GUI library. 
 * 
 * 
 * @mainpage Write one simple code, compile it for any supported frontend.
 * 
 * Nuklear+ (read as "Nuklear cross") is a front-end overlay for Nuklear GUI library.
 * 
 * Preprocessor constants:
 * * NKC_IMPLEMENTATION - define this constant in one C-file in your project, or use nuklear_cross.c
 * * NKC_DISABLE_DEFAULT_FONT - if set, the default Nuklear font will not be included. Size reduce
 * * NKC_DISABLE_IMAGES - do not include stb_image and images function. Size reduce
 * * NKC_USE_OPENGL=3 - use OpenGL 3 instead of 2 in OpenGL-based frontends
 * * NKCD=x - choose Nuklear+ fronend driver:
 * Frontend choose (with OpenGL 2/3):
 * * NKC_SDL - SDL2
 * * NKC_GLFW - GLFW3
 * * NKC_XLIB - X11/Xlib
 * Non-OpenGL frontend:
 * * NKC_GDIP - GDI+ (Windows only). The minimal size. Resulting picture differs from OpenGL!
 * * NKC_XLIB - X11/Xlib. No font loader!
 * 
 * Not all Window modes are implemented in each frontend.
 * @see nuklear_cross.h
 * @see https://github.com/DeXP/nuklear_cross
*/

#ifndef NUKLEAR_CROSS_H
#define NUKLEAR_CROSS_H

#define NKC_SDL 1
#define NKC_GLFW 2
#define NKC_XLIB 3
#define NKC_GDIP 4

#define NGL_ES2 20

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * @brief Main structure. Implementation depends on frontend
 * There always will be fields:
 *     struct nk_context *ctx;
 *     int nkcInited;
*/
struct nkc; 

/** 
 * @brief Window mode constants, passed to initialization 
 */
enum nkc_window_mode {
    NKC_WIN_NORMAL = 'w', /**< normal window mode, user can resize/maximize */
    NKC_WIN_MAXIMIZED = 'm', /**< like normal, but starts maximized */
    NKC_WIN_FIXED = 'x', /**< fixed size mode. User can't resize/maximize */
    NKC_WIN_FULLSCREEN = 'f', /**< real fullscreen. In almost all frontends changes the screen's resolution */
    NKC_WIN_FULLSCREEN_DESKTOP = 'd' /**< "virtual" fullscreen. Removes windows decorations, 
     * expands window to full size, changes window size */
};
#define NKC_INITED 1234  /**< Internal used constant @hideinitializer */


#define MAX_VERTEX_MEMORY 512 * 1024 /**< Internal used constant, OpenGL render @hideinitializer */
#define MAX_ELEMENT_MEMORY 128 * 1024 /**< Internal used constant, OpenGL render @hideinitializer */

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_STANDARD_IO
#if !defined(NKC_DISABLE_DEFAULT_FONT)
    #define NK_INCLUDE_DEFAULT_FONT
#endif

#if defined(NKC_IMPLEMENTATION) && !defined(NK_IMPLEMENTATION)
    #define NK_IMPLEMENTATION
#endif


#if defined(__EMSCRIPTEN__)
    /* GL ES systems */
    #undef NKC_OPENGL_VERSION
    #define NKC_OPENGL_VERSION NGL_ES2
#else
    #if defined(NKC_USE_OPENGL)
        #define NKC_OPENGL_VERSION NKC_USE_OPENGL
    #else
        #define NKC_OPENGL_VERSION 2
    #endif    
#endif

#include <stdio.h>
#include <string.h>

#include "nuklear.h"

/* Events system */
enum nkc_event_type {
    NKC_ENONE, /**< No event */
    NKC_EWINDOW, /**< Window event */
    NKC_EKEY, /**< Keyboard events */
    NKC_EQUIT /**< Quit from app event */
};

struct nkc_window_event {
    enum nkc_event_type type;
    int param;
};

struct nkc_key_event {
    enum nkc_event_type type;
    int code;
    int mod;
};
union nkc_event {
    enum nkc_event_type type;
    struct nkc_window_event window; 
    struct nkc_key_event key;
};
/* end Events */

#if defined(NKCD)
    #if NKCD==NKC_GDIP
        #include "nkc_frontend/nkc_gdip.h"
    #elif NKCD==NKC_SDL
        #include "nkc_frontend/nkc_sdl.h"
    #elif NKCD==NKC_GLFW
        #include "nkc_frontend/nkc_glfw.h"
    #elif NKCD==NKC_XLIB
        #include "nkc_frontend/nkc_xlib.h"
    #endif
#else
    /* if no value defined. Try to choose */
    #if defined(WIN32) && !defined(__EMSCRIPTEN__)
        #include "nkc_frontend/nkc_gdip.h"
    #else
        /* SDL if not windows */
        #include "nkc_frontend/nkc_sdl.h"
    #endif
#endif /* Frontend choose */





/** @defgroup init Initialization/finalizing, event loop
 *  @brief Functions, related to initialization
 *  @{
 */


/**
 * @brief Fatal error. Application exit. Die with message. Printf-like
 * @param fmt - format string
 */
NK_API void* nkc_rdie(const char *fmt, ...);

/**
 * @brief Initialize the library, create the operation system window
 * @param nkcHandle - pointer to struct nkc
 * @param title - window title
 * @param width - window width in pixels
 * @param height - window height in pixels
 * @param windowMode - one value from enum nkc_window_mode
 * @see enum nkc_window_mode
 * @return if error, than returns NULL
 */
NK_API struct nk_context *nkc_init(struct nkc* nkcHandle, const char* title, 
                            int width, int height, enum nkc_window_mode windowMode);

/**
 * @brief Poll window's events in a loop
 * @return union nkc_event
 * @see union nkc_event
 */
NK_API union nkc_event nkc_poll_events(struct nkc* nkcHandle);

/** @return Returns nkcHandle->ctx */
NK_API struct nk_context* nkc_get_ctx(struct nkc* nkcHandle);

/** @brief Finalizing */
NK_API void nkc_shutdown(struct nkc* nkcHandle);

/** @} */ /* end of init group */



/** @defgroup render Rendering
 *  @brief You can render GUI and BG separately.
 *  @{
 */
NK_API void nkc_render_bg(struct nkc* nkcHandle, struct nk_color bgColor);
NK_API void nkc_render_gui(struct nkc* nkcHandle);

/** Just calls nkc_render_bg than nkc_render_gui */
NK_API void nkc_render(struct nkc* nkcHandle, struct nk_color bgColor);
/** @} */ /* end of render group */




/** @defgroup font Font loading and handling
 *  @brief Loading TTF-font from file and memory
 *  @{
 */

/** Differs from nk_style_set_font only on checking font for NULL */
NK_API void nkc_style_set_font(struct nkc* nkcHandle, const struct nk_user_font* font);

/**
 * @brief Load font from TTF-file from disk
 * @param size - size of the rendered text in points (ex. 14pt) 
 * @param symbolsRange - will be given directly yo Nuklear
 * @return NULL if error
 */
NK_API struct nk_user_font* nkc_load_font_file(struct nkc* nkcHandle, const char* filename, float size, 
                              const nk_rune *symbolsRange);
NK_API struct nk_user_font* nkc_load_font_memory(struct nkc* nkcHandle, const void* membuf, int membufSize, 
                              float size, const nk_rune *symbolsRange);

/**
 * @brief Converts keyboard code to it's latin character (if have)
 * @param code - NK_KEY_ code
 */
NK_API char nkc_get_key_char(int code);
/** @} */ /* end of font group */




/** @defgroup image Images manipulating functions
 *  @brief Loading from file/memory and finalization
 *  @{
 */
#if !defined(NKC_DISABLE_IMAGES)
NK_API struct nk_image nkc_load_image_file(struct nkc* nkcHandle, const char* filename);
NK_API struct nk_image nkc_load_image_memory(struct nkc* nkcHandle, const void* membuf, int membufSize);
NK_API void nkc_image_free(struct nk_image* img);
#endif /* NKC_DISABLE_IMAGES */

/**
 * @brief Gets the desktop size in pixels. In browsers - draw area
 * @param width - desktop width, will be 0 if error
 * @param height - desktop height, will be 0 if error
 * @return nk_true if correct and nk_false if something wrong
 */
NK_API int nkc_get_desktop_size(struct nkc* nkcHandle, int* width, int* height);
/** @} */ /* end of image group */



/** @defgroup mainloop Main loop
 *  @brief Required for Emscripten
 *  @{
 */
 
/**
 * @brief Starts the 'infinite' main loop. Required for Emscipten only.
 * @param mainLoopFunc - pointer to the function, that will be called each loop iteration
 * @param loopArg - pointer to your data structer, that will be passed to mainLoopFunc function
 */
NK_API void nkc_set_main_loop(struct nkc* nkcHandle,
            void (*mainLoopFunc)(void* loopArg), void* loopArg);
/** Exit from main loop */
NK_API void nkc_stop_main_loop(struct nkc* nkcHandle);
/** @} */ /* end of mainloop group */





/** @defgroup file File functions
 *  @brief Not really related to GUI, but useful in most programs
 *  @{
 */
#include "nkc_frontend/helpers/nkc_file.h"

/** Checks if file exists on disk. nk_true if so. */
int nkc_file_exists(const char* filename);

/** Returns file size in bytes. */
size_t nkc_file_size(const char* filename);

/**
 * @brief Returns file size in bytes.
 * @param f - pointer to std FILE
 * @return File size in bytes
 */
size_t nkc_stdfile_size(FILE* f);


/**
 * @brief Mounts local storage folder for writing. Useful for Emscripten only
 * @param folder - path to the folder. "/save" for example
 */
void nkc_mount_write(const char* folder);

/** Reads local storage to memory. Usually call it one time only, after mount. Useful for Emscripten only. */
void nkc_file_pre_read();

/** Writes memory contents to local storage. Usually call it after all fclose */
void nkc_file_post_write();

/** @} */ /* end of file group */



#if defined(NKC_IMPLEMENTATION)
NK_API void nkc_render(struct nkc* nkcHandle, struct nk_color bgColor){
    nkc_render_bg(nkcHandle, bgColor);
    nkc_render_gui(nkcHandle);
}

NK_API struct nk_context* nkc_get_ctx(struct nkc* nkcHandle){
    return nkcHandle->ctx;
}

NK_API void nkc_style_set_font(struct nkc* nkcHandle, const struct nk_user_font* font){
    if(font) nk_style_set_font(nkcHandle->ctx, font);
}

#if !defined(__EMSCRIPTEN__)
NK_API void nkc_set_main_loop(struct nkc* nkcHandle,
            void (*mainLoopFunc)(void* loopArg), void* loopArg)
{
    nkcHandle->keepRunning = nk_true;
    while (nkcHandle->keepRunning)
        mainLoopFunc(loopArg);
}

NK_API void nkc_stop_main_loop(struct nkc* nkcHandle){
    nkcHandle->keepRunning = nk_false;
}
#endif /* __EMSCRIPTEN__ */

#endif /* NKC_IMPLEMENTATION */

#ifdef __cplusplus
}
#endif

#endif /* NUKLEAR_CROSS_H */
