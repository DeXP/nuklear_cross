/**
 * Nuklear+ (read as "Nuklear cross") is a front-end overlay for Nuklear GUI library. 
 * Write one simple code, compile it for any supported frontend.
 *
 * License: public domain
 * no warrenty implied; use at your own risk.
 * authored from 2016-2017 by Dmitry Hrabrov a.k.a. DeXPeriX
 */
 
#if defined(__EMSCRIPTEN__)

#include <emscripten.h>
#include <emscripten/html5.h>

#include "nkc_keyboard.h"



#if defined(NKC_IMPLEMENTATION)

NK_API void* nkc_rdie(const char *fmt, ...){
    char scriptbuf[1024];
    char buffer[1024];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);
    va_end(ap);
    
    sprintf(scriptbuf, "alert('%s')", buffer);
    emscripten_run_script(scriptbuf);
    return NULL;
}

NK_API int nkc_get_desktop_size(struct nkc* nkcHandle, int* width, int* height){
    *width = EM_ASM_INT_V(return window.innerWidth 
        || document.documentElement.clientWidth 
        || document.body.clientWidth
    );
    *height = EM_ASM_INT_V(return window.innerHeight
        || document.documentElement.clientHeight
        || document.body.clientHeight
    );
    return 1;
}

NK_API char nkc_get_key_char(int code){
    if( (code>=NKC_KEY_A) && (code<=NKC_KEY_Z) ) return code - NKC_KEY_A + 'a';
    if( (code>=NKC_KEY_1) && (code<=NKC_KEY_9) ) return code - NKC_KEY_1 + '1';
    switch(code){
        case NKC_KEY_0: return '0';
        case NKC_KEY_LEFTBRACKET: return '[';
        case NKC_KEY_RIGHTBRACKET: return ']';
        case NKC_KEY_SEMICOLON: return ';';
        case NKC_KEY_APOSTROPHE: return '\'';
        case NKC_KEY_COMMA: return ',';
        case NKC_KEY_PERIOD: return '.';
        case NKC_KEY_GRAVE: return '`';
        case NKC_KEY_SLASH: return '/';
        case NKC_KEY_BACKSLASH: return '\\';
    }
    return code;
}

NK_API void nkc_set_main_loop(struct nkc* nkcHandle,
            void (*mainLoopFunc)(void* loopArg), void* loopArg )
{
    emscripten_set_main_loop_arg(mainLoopFunc, loopArg, 0, 1);
}

NK_API void nkc_stop_main_loop(struct nkc* nkcHandle){
    emscripten_cancel_main_loop();
}

int nkc_is_fullscreen(struct nkc* nkcHandle) {
    (void)nkcHandle;
    EmscriptenFullscreenChangeEvent fsce;
    emscripten_get_fullscreen_status(&fsce);
    return fsce.isFullscreen;
}

void nkc_fullscreen_exit(struct nkc* nkcHandle){ emscripten_exit_fullscreen(); }

void nkc_fullscreen_enter(struct nkc* nkcHandle){
    emscripten_exit_soft_fullscreen();

    /* Workaround https://github.com/kripken/emscripten/issues/5124#issuecomment-292849872 */
    EM_ASM(JSEvents.inEventHandler = true);
    EM_ASM(JSEvents.currentEventHandler = {allowsDeferredCalls:true});

    EmscriptenFullscreenStrategy strategy = {
        .scaleMode = EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH,
        .canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_NONE,
        .filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT,
        .canvasResizedCallback = NULL,
        .canvasResizedCallbackUserData = NULL
    };
    /*emscripten_request_fullscreen_strategy(NULL, EM_TRUE, &strategy);*/
    emscripten_enter_soft_fullscreen(NULL, &strategy);
}
#endif /* NKC_IMPLEMENTATION */

#endif /* __EMSCRIPTEN__ */