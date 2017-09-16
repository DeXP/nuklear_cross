/**
 * Nuklear+ (read as "Nuklear cross") is a front-end overlay for Nuklear GUI library. 
 * Write one simple code, compile it for any supported frontend.
 *
 * License: public domain
 * no warrenty implied; use at your own risk.
 * authored from 2016-2017 by Dmitry Hrabrov a.k.a. DeXPeriX
 */

#ifndef NKC_SDL_H
#define NKC_SDL_H

    #define GL_GLEXT_PROTOTYPES 1
    #if NKC_OPENGL_VERSION == 3
        #include <GL/glew.h>
    #endif
    
    #if defined(NKC_RASPBERRY_PI)
        #include "bcm_host.h"
    #endif
    

    #include <SDL2/SDL.h>
    
    #if defined(NKC_OPENGL_VERSION) && (NKC_OPENGL_VERSION == NGL_ES2)
        /*#define GL_VERSION_1_5
        #include <SDL2/SDL_opengles2.h>*/
        #include <GLES2/gl2.h>
    #else
        #include <SDL2/SDL_opengl.h>
    #endif

    struct nkc {
        int nkcInited;
        struct nk_context *ctx;
        int keepRunning;

        SDL_Window *window;
        SDL_GLContext glContext;
        int win_width;
        int win_height;
    };

    #if defined(NKC_OPENGL_VERSION) && (NKC_OPENGL_VERSION == NGL_ES2)      
        #if defined(NKC_IMPLEMENTATION)
            #define NK_SDL_GLES2_IMPLEMENTATION
        #endif
        
        #define _OPENGL_ES_  NGL_ES2
        #include "../nuklear_drivers/nuklear_sdl_gles2.h"
    #else
        #if defined(NKC_OPENGL_VERSION) && (NKC_OPENGL_VERSION == 3)
            #if defined(NKC_IMPLEMENTATION)
                #define NK_SDL_GL3_IMPLEMENTATION
            #endif
            #include "../nuklear_drivers/nuklear_sdl_gl3.h"
        #else
            #if defined(NKC_IMPLEMENTATION)
                #define NK_SDL_GL2_IMPLEMENTATION
            #endif
            #include "../nuklear_drivers/nuklear_sdl_gl2.h"
        #endif
    #endif

    
/* Constants */
#define NKC_KEY_ESCAPE SDL_SCANCODE_ESCAPE
#define NKC_KEY_SPACE SDL_SCANCODE_SPACE
#define NKC_KEY_BACKSPACE SDL_SCANCODE_BACKSPACE
#define NKC_KEY_DELETE SDL_SCANCODE_DELETE
#define NKC_KEY_TAB SDL_SCANCODE_TAB
#define NKC_KEY_CTRL SDL_SCANCODE_LCTRL
#define NKC_KEY_SHIFT SDL_SCANCODE_LSHIFT
#define NKC_KEY_ALT SDL_SCANCODE_LALT
#define NKC_KEY_WIN SDL_SCANCODE_LGUI
#define NKC_KEY_LEFTBRACKET SDL_SCANCODE_LEFTBRACKET
#define NKC_KEY_RIGHTBRACKET SDL_SCANCODE_RIGHTBRACKET
#define NKC_KEY_SEMICOLON SDL_SCANCODE_SEMICOLON
#define NKC_KEY_APOSTROPHE SDL_SCANCODE_APOSTROPHE
#define NKC_KEY_COMMA SDL_SCANCODE_COMMA
#define NKC_KEY_PERIOD SDL_SCANCODE_PERIOD
#define NKC_KEY_GRAVE SDL_SCANCODE_GRAVE
#define NKC_KEY_SLASH SDL_SCANCODE_SLASH
#define NKC_KEY_BACKSLASH SDL_SCANCODE_BACKSLASH
#define NKC_KEY_INSERT SDL_SCANCODE_INSERT
#define NKC_KEY_HOME SDL_SCANCODE_HOME
#define NKC_KEY_END SDL_SCANCODE_END
#define NKC_KEY_PGUP SDL_SCANCODE_PAGEUP
#define NKC_KEY_PGDOWN SDL_SCANCODE_PAGEDOWN
#define NKC_KEY_A SDL_SCANCODE_A
#define NKC_KEY_B SDL_SCANCODE_B
#define NKC_KEY_C SDL_SCANCODE_C
#define NKC_KEY_D SDL_SCANCODE_D
#define NKC_KEY_E SDL_SCANCODE_E
#define NKC_KEY_F SDL_SCANCODE_F
#define NKC_KEY_G SDL_SCANCODE_G
#define NKC_KEY_H SDL_SCANCODE_H
#define NKC_KEY_I SDL_SCANCODE_I
#define NKC_KEY_J SDL_SCANCODE_J
#define NKC_KEY_K SDL_SCANCODE_K
#define NKC_KEY_L SDL_SCANCODE_L
#define NKC_KEY_M SDL_SCANCODE_M
#define NKC_KEY_N SDL_SCANCODE_N
#define NKC_KEY_O SDL_SCANCODE_O
#define NKC_KEY_P SDL_SCANCODE_P
#define NKC_KEY_Q SDL_SCANCODE_Q
#define NKC_KEY_R SDL_SCANCODE_R
#define NKC_KEY_S SDL_SCANCODE_S
#define NKC_KEY_T SDL_SCANCODE_T
#define NKC_KEY_U SDL_SCANCODE_U
#define NKC_KEY_V SDL_SCANCODE_V
#define NKC_KEY_W SDL_SCANCODE_W
#define NKC_KEY_X SDL_SCANCODE_X
#define NKC_KEY_Y SDL_SCANCODE_Y
#define NKC_KEY_Z SDL_SCANCODE_Z
#define NKC_KEY_0 SDL_SCANCODE_0
#define NKC_KEY_1 SDL_SCANCODE_1
#define NKC_KEY_2 SDL_SCANCODE_2
#define NKC_KEY_3 SDL_SCANCODE_3
#define NKC_KEY_4 SDL_SCANCODE_4
#define NKC_KEY_5 SDL_SCANCODE_5
#define NKC_KEY_6 SDL_SCANCODE_6
#define NKC_KEY_7 SDL_SCANCODE_7
#define NKC_KEY_8 SDL_SCANCODE_8
#define NKC_KEY_9 SDL_SCANCODE_9
#define NKC_KEY_F1 SDL_SCANCODE_F1
#define NKC_KEY_F2 SDL_SCANCODE_F2
#define NKC_KEY_F3 SDL_SCANCODE_F3
#define NKC_KEY_F4 SDL_SCANCODE_F4
#define NKC_KEY_F5 SDL_SCANCODE_F5
#define NKC_KEY_F6 SDL_SCANCODE_F6
#define NKC_KEY_F7 SDL_SCANCODE_F7
#define NKC_KEY_F8 SDL_SCANCODE_F8
#define NKC_KEY_F9 SDL_SCANCODE_F9
#define NKC_KEY_F10 SDL_SCANCODE_F10
#define NKC_KEY_F11 SDL_SCANCODE_F11
#define NKC_KEY_F12 SDL_SCANCODE_F12

    #include "helpers/nkc_emscripten.h"


#if defined(NKC_IMPLEMENTATION)
NK_API struct nk_context *nkc_init(struct nkc* nkcHandle, const char* title, 
                        int width, int height, enum nkc_window_mode windowMode)
{
    struct nk_font_atlas *atlas;
    #if defined(NKC_RASPBERRY_PI)
        bcm_host_init();
    #endif
    /* SDL setup */
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    /*#if !defined(__EMSCRIPTEN__)
        SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS);
    #endif*/
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    #if (NKC_OPENGL_VERSION == 2) || (NKC_OPENGL_VERSION == 3)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, NKC_OPENGL_VERSION);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, NKC_OPENGL_VERSION);
    #elif (NKC_OPENGL_VERSION == NGL_ES2)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2); 
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0); 
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES); 
    #endif
    
    #if defined(NKC_USE_OPENGL) && (NKC_USE_OPENGL == 3)
        SDL_GL_SetAttribute (SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    #endif
    nkcHandle->window = SDL_CreateWindow(title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 
        SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);
    nkcHandle->glContext = SDL_GL_CreateContext(nkcHandle->window);
    
    #if !defined(__EMSCRIPTEN__)
    if( windowMode == NKC_WIN_FULLSCREEN )
        SDL_SetWindowFullscreen(nkcHandle->window, SDL_WINDOW_FULLSCREEN);
    if( windowMode == NKC_WIN_FULLSCREEN_DESKTOP )
        SDL_SetWindowFullscreen(nkcHandle->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    #endif


    #if NKC_OPENGL_VERSION == 3
        glewExperimental = 1;
        if (glewInit() != GLEW_OK) {
            return NULL;
        }
    #endif /* OpenGL version */
    nkcHandle->ctx = nk_sdl_init(nkcHandle->window);
    /* load default font */
    nk_sdl_font_stash_begin(&atlas);
    nk_sdl_font_stash_end();
    glEnable(GL_TEXTURE_2D);
    
    #if defined(__EMSCRIPTEN__)
    if( windowMode == NKC_WIN_FULLSCREEN ) nkc_fullscreen_enter(nkcHandle);
    #endif
    
    nkcHandle->nkcInited = NKC_INITED;
    return nkcHandle->ctx;
}

NK_API void nkc_shutdown(struct nkc* nkcHandle){
    nk_sdl_shutdown();
    SDL_GL_DeleteContext(nkcHandle->glContext);
    SDL_DestroyWindow(nkcHandle->window);
    SDL_Quit();
}

NK_API union nkc_event nkc_poll_events(struct nkc* nkcHandle){
    SDL_Event evt;
    union nkc_event ne;
    ne.type = NKC_ENONE;
    nk_input_begin(nkcHandle->ctx);
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_QUIT){
            ne.type = NKC_EWINDOW;
            ne.window.param = NKC_EQUIT;
        }
        if (evt.type == SDL_KEYDOWN){
            ne.type = NKC_EKEY;
            ne.key.code = evt.key.keysym.scancode;
        }
        nk_sdl_handle_event(&evt);
    }
    nk_input_end(nkcHandle->ctx);
    return ne;
}

NK_API void nkc_render_bg(struct nkc* nkcHandle, struct nk_color bgColor){
    float bg[4];
    nk_color_fv(bg, bgColor);
    /*SDL_GetWindowSize(nkcHandle->window, &(nkcHandle->win_width), &(nkcHandle->win_height) );
    glViewport(0, 0, nkcHandle->win_width, nkcHandle->win_height);*/
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(bg[0], bg[1], bg[2], bg[3]);
}

NK_API void nkc_render_gui(struct nkc* nkcHandle){
    #if NKC_OPENGL_VERSION > 2
        nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
    #else
        nk_sdl_render(NK_ANTI_ALIASING_ON);
    #endif
    SDL_GL_SwapWindow(nkcHandle->window);
}


#if !defined(__EMSCRIPTEN__)

NK_API void* nkc_rdie(const char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputs("\n", stderr);
    return NULL;
}

NK_API int nkc_get_desktop_size(struct nkc* nkcHandle, int* width, int* height){
    SDL_DisplayMode dm;
    (void)nkcHandle;
    if( !(SDL_WasInit(SDL_INIT_EVERYTHING) & SDL_INIT_VIDEO) )
        SDL_Init(SDL_INIT_VIDEO);
    int ret = SDL_GetDesktopDisplayMode(0, &dm);
    if( ret != 0 ){
        /*SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());*/
        return 0;
    }
    *width = dm.w;
    *height = dm.h;
    return 1;
}

NK_API char nkc_get_key_char(int code){
    const char* name = SDL_GetScancodeName(code);
    if( strlen(name) == 1 ){
        if( (name[0]>='A') && (name[0]<='Z') ){
            return name[0] - 'A' + 'a'; /* 'a' for NKC_KEY_A */
        } else return name[0];
    }
    return 0; 
}
#endif /* __EMSCRIPTEN__ */

#include "helpers/nkc_stb_image.h"
#include "helpers/nkc_font_stash.h"
NKC_FONT_STASH_LOADER(sdl)

#endif /* NKC_IMPLEMENTATION */

#endif /* NKC_SDL_H */