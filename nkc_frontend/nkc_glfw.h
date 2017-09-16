/**
 * Nuklear+ (read as "Nuklear cross") is a front-end overlay for Nuklear GUI library. 
 * Write one simple code, compile it for any supported frontend.
 *
 * License: public domain
 * no warrenty implied; use at your own risk.
 * authored from 2016-2017 by Dmitry Hrabrov a.k.a. DeXPeriX
 */

#ifndef NKC_GLFW_H
#define NKC_GLFW_H

    
    #define GLFW_INCLUDE_GLEXT
    #define GL_GLEXT_PROTOTYPES
    #if defined(NKC_USE_OPENGL) && (NKC_USE_OPENGL == 3)
        #include <GL/glew.h>
    #endif
    #include <GLFW/glfw3.h>
    #include <string.h>
    #include <stdarg.h>


    struct nkc {
        int nkcInited;
        struct nk_context *ctx;
        int keepRunning;

        GLFWwindow *window;
        int width;
        int height;
    };

    #if defined(__EMSCRIPTEN__)
        #undef NKC_USE_OPENGL
        #define NKC_USE_OPENGL 3
        
        #if defined(NKC_IMPLEMENTATION)
            #define NK_GLFW_GL3_IMPLEMENTATION
        #endif
        
        #include "../nuklear_drivers/nuklear_glfw_emscripten.h"
    #else
        #if defined(NKC_USE_OPENGL) && (NKC_USE_OPENGL > 2)
            #if defined(NKC_IMPLEMENTATION)
                #define NK_GLFW_GL3_IMPLEMENTATION
            #endif
            
            #include "../nuklear_drivers/nuklear_glfw_gl3.h"
        #else
            #if defined(NKC_IMPLEMENTATION)
                #define NK_GLFW_GL2_IMPLEMENTATION
            #endif
            #include "../nuklear_drivers/nuklear_glfw_gl2.h"
        #endif
        
        #if defined(NKC_USE_OPENGL)
            #define NKC_OPENGL_VERSION NKC_USE_OPENGL
        #else
            #define NKC_OPENGL_VERSION 2
        #endif
    #endif
    

/* Constants */
#define NKC_KEY_ESCAPE GLFW_KEY_ESCAPE
#define NKC_KEY_SPACE GLFW_KEY_SPACE
#define NKC_KEY_BACKSPACE GLFW_KEY_BACKSPACE
#define NKC_KEY_DELETE GLFW_KEY_DELETE
#define NKC_KEY_TAB GLFW_KEY_TAB
#define NKC_KEY_CTRL GLFW_KEY_LEFT_CONTROL
#define NKC_KEY_SHIFT GLFW_KEY_LEFT_SHIFT
#define NKC_KEY_ALT GLFW_KEY_LEFT_ALT
#define NKC_KEY_WIN GLFW_KEY_LEFT_SUPER
#define NKC_KEY_LEFTBRACKET GLFW_KEY_LEFT_BRACKET 
#define NKC_KEY_RIGHTBRACKET GLFW_KEY_RIGHT_BRACKET
#define NKC_KEY_SEMICOLON GLFW_KEY_SEMICOLON
#define NKC_KEY_APOSTROPHE GLFW_KEY_APOSTROPHE
#define NKC_KEY_COMMA GLFW_KEY_COMMA
#define NKC_KEY_PERIOD GLFW_KEY_PERIOD
#define NKC_KEY_GRAVE GLFW_KEY_GRAVE_ACCENT
#define NKC_KEY_SLASH GLFW_KEY_SLASH
#define NKC_KEY_BACKSLASH GLFW_KEY_BACKSLASH
#define NKC_KEY_INSERT GLFW_KEY_INSERT
#define NKC_KEY_HOME GLFW_KEY_HOME
#define NKC_KEY_END GLFW_KEY_END
#define NKC_KEY_PGUP GLFW_KEY_PAGE_UP
#define NKC_KEY_PGDOWN GLFW_KEY_PAGE_DOWN
#define NKC_KEY_A GLFW_KEY_A
#define NKC_KEY_B GLFW_KEY_B
#define NKC_KEY_C GLFW_KEY_C
#define NKC_KEY_D GLFW_KEY_D
#define NKC_KEY_E GLFW_KEY_E
#define NKC_KEY_F GLFW_KEY_F
#define NKC_KEY_G GLFW_KEY_G
#define NKC_KEY_H GLFW_KEY_H
#define NKC_KEY_I GLFW_KEY_I
#define NKC_KEY_J GLFW_KEY_J
#define NKC_KEY_K GLFW_KEY_K
#define NKC_KEY_L GLFW_KEY_L
#define NKC_KEY_M GLFW_KEY_M
#define NKC_KEY_N GLFW_KEY_N
#define NKC_KEY_O GLFW_KEY_O
#define NKC_KEY_P GLFW_KEY_P
#define NKC_KEY_Q GLFW_KEY_Q
#define NKC_KEY_R GLFW_KEY_R
#define NKC_KEY_S GLFW_KEY_S
#define NKC_KEY_T GLFW_KEY_T
#define NKC_KEY_U GLFW_KEY_U
#define NKC_KEY_V GLFW_KEY_V
#define NKC_KEY_W GLFW_KEY_W
#define NKC_KEY_X GLFW_KEY_X
#define NKC_KEY_Y GLFW_KEY_Y
#define NKC_KEY_Z GLFW_KEY_Z
#define NKC_KEY_0 GLFW_KEY_0
#define NKC_KEY_1 GLFW_KEY_1
#define NKC_KEY_2 GLFW_KEY_2
#define NKC_KEY_3 GLFW_KEY_3
#define NKC_KEY_4 GLFW_KEY_4
#define NKC_KEY_5 GLFW_KEY_5
#define NKC_KEY_6 GLFW_KEY_6
#define NKC_KEY_7 GLFW_KEY_7
#define NKC_KEY_8 GLFW_KEY_8
#define NKC_KEY_9 GLFW_KEY_9
#define NKC_KEY_F1 GLFW_KEY_F1
#define NKC_KEY_F2 GLFW_KEY_F2
#define NKC_KEY_F3 GLFW_KEY_F3
#define NKC_KEY_F4 GLFW_KEY_F4
#define NKC_KEY_F5 GLFW_KEY_F5
#define NKC_KEY_F6 GLFW_KEY_F6
#define NKC_KEY_F7 GLFW_KEY_F7
#define NKC_KEY_F8 GLFW_KEY_F8
#define NKC_KEY_F9 GLFW_KEY_F9
#define NKC_KEY_F10 GLFW_KEY_F10
#define NKC_KEY_F11 GLFW_KEY_F11
#define NKC_KEY_F12 GLFW_KEY_F12

    #include "helpers/nkc_emscripten.h"


#if defined(NKC_IMPLEMENTATION)
static void nkc_glfw_error_callback(int e, const char *d)
{printf("Error %d: %s\n", e, d);}


void nkc_fullscreen_enter(struct nkc* nkcHandle);
NK_API void* nkc_rdie(const char *fmt, ...);

NK_API struct nk_context *nkc_init(struct nkc* nkcHandle, const char* title, 
                        int width, int height, enum nkc_window_mode windowMode)
{
    struct nk_font_atlas *atlas;
    GLFWmonitor* monitor = NULL;
    int winWidth = width;
    int winHeight = height;
    /* GLFW */
    glfwSetErrorCallback(nkc_glfw_error_callback);
    if (!glfwInit()) return nkc_rdie("[GFLW] failed to init!");
    #if NKC_OPENGL_VERSION > 2
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, NKC_OPENGL_VERSION);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, NKC_OPENGL_VERSION);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
    #endif
    #if !defined(__EMSCRIPTEN__)
    if( (windowMode == NKC_WIN_FULLSCREEN) ||
        (windowMode == NKC_WIN_FULLSCREEN_DESKTOP ) ){
            monitor = glfwGetPrimaryMonitor();
        }
    if( windowMode == NKC_WIN_FULLSCREEN_DESKTOP ){
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        winWidth = mode->width;
        winHeight = mode->height;
    }
    #endif

    nkcHandle->window = glfwCreateWindow(winWidth, winHeight, title, monitor, NULL);
    if( !nkcHandle->window ) return nkc_rdie("[GLFW] Window was not created!");
    if( windowMode == NKC_WIN_FIXED ) 
        glfwSetWindowSizeLimits(nkcHandle->window, width, height, width, height);
        
    glfwMakeContextCurrent(nkcHandle->window);
    /*glfwGetWindowSize(nkcHandle->window, &nkcHandle->width, &nkcHandle->height);
    nkcHandle->width = width;
    nkcHandle->height = height;
    nkcHandle->width = winWidth;
    nkcHandle->height = winHeight;

    glViewport(0, 0, nkcHandle->width, nkcHandle->height);*/
    #if (NKC_OPENGL_VERSION == 3) && !defined(__EMSCRIPTEN__)
        glewExperimental = 1;
        if (glewInit() != GLEW_OK) return nkc_rdie("[GLFW] Failed to setup GLEW");
    #endif
    
    nkcHandle->ctx = nk_glfw3_init(nkcHandle->window, NK_GLFW3_INSTALL_CALLBACKS);
    
    nk_glfw3_font_stash_begin(&atlas);
    nk_glfw3_font_stash_end();
    
    #if defined(__EMSCRIPTEN__)
    if( windowMode == NKC_WIN_FULLSCREEN ) nkc_fullscreen_enter(nkcHandle);
    #endif
    
    glEnable(GL_TEXTURE_2D);
    glfwSwapInterval(1);
    nkcHandle->nkcInited = NKC_INITED;
    return nkcHandle->ctx;
}

NK_API void nkc_shutdown(struct nkc* nkcHandle){
    nk_glfw3_shutdown();
    glfwTerminate();
}


/*NK_API void nkc_set_main_loop(struct nkc* nkcHandle, 
            void (*renderProcedure)(void* nkcHandleVoided) )
{
#if defined(__EMSCRIPTEN__)
    emscripten_set_main_loop_arg(renderProcedure, nkcHandle, 0, 1);
#else
    int doExit = 0;
    while (!doExit) 
      renderProcedure((void*)nkcHandle);
#endif
}*/

NK_API union nkc_event nkc_poll_events(struct nkc* nkcHandle){
    static char keyOnce[GLFW_KEY_LAST + 1];
    #define glfwGetKeyOnce(WINDOW, KEY) \
        (glfwGetKey(WINDOW, KEY) ? \
        (keyOnce[KEY] ? nk_false : (keyOnce[KEY] = nk_true)) : \
        (keyOnce[KEY] = nk_false))
    #include "helpers/nkc_keyboard.h"
    int i;
    union nkc_event ne;
    ne.type = NKC_ENONE;
    glfwPollEvents();
    nk_glfw3_new_frame();
    if( glfwWindowShouldClose(nkcHandle->window) ){
        ne.type = NKC_EWINDOW;
        ne.window.param = NKC_EQUIT;
    }
    for(i=0; i<sizeof(nkc_suported_keys)/sizeof(nkc_suported_keys[0]); i++){
        int key = nkc_suported_keys[i];
        if( glfwGetKeyOnce(nkcHandle->window, key) == GLFW_PRESS ){
            ne.type = NKC_EKEY;
            ne.key.code = key;
        }
    }
    return ne;
}

NK_API void nkc_render_bg(struct nkc* nkcHandle, struct nk_color bgColor){
    float bg[4];
    nk_color_fv(bg, bgColor);
    /*glfwGetWindowSize(nkcHandle->window, &(nkcHandle->width), &(nkcHandle->height) );
    glViewport(0, 0, nkcHandle->width, nkcHandle->height);
    printf("Viewport: %dx%d\n", nkcHandle->width, nkcHandle->height);*/
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(bg[0], bg[1], bg[2], bg[3]);
}

NK_API void nkc_render_gui(struct nkc* nkcHandle){
    /* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
     * with blending, scissor, face culling, depth test and viewport and
     * defaults everything back into a default state.
     * Make sure to either a.) save and restore or b.) reset your own state after
     * rendering the UI. */
    #if NKC_USE_OPENGL > 2
        nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
    #else
        nk_glfw3_render(NK_ANTI_ALIASING_ON);
    #endif
    glfwSwapBuffers(nkcHandle->window);
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
    const GLFWvidmode* mode;
    if( nkcHandle->nkcInited != NKC_INITED ) glfwInit();
    mode = glfwGetVideoMode( glfwGetPrimaryMonitor() );
    if( mode == NULL ) return 0;
    *width = mode->width;
    *height = mode->height;
    return 1;
}

NK_API char nkc_get_key_char(int code){
    const char* name = glfwGetKeyName(code, 0);
    if( name == NULL ) return 0;
    if( strlen(name) == 1 ){
        if( (name[0]>='A') && (name[0]<='Z') ){
            return name[0] - 'A' + 'a'; /* 'a' for NKC_KEY_A */
        } else return name[0];
    }
    return 0;
}

int nkc_is_fullscreen(struct nkc* g){
    return !!glfwGetWindowMonitor(g->window);
}

void nkc_fullscreen_exit(struct nkc* g){
    glfwSetWindowMonitor(g->window, NULL, 0, 0, g->width, g->height, GLFW_DONT_CARE);
}

void nkc_fullscreen_enter(struct nkc* g){
    /*glfwGetWindowPos(g->window, &g->window_xpos, &g->window_ypos);*/
    glfwGetWindowSize(g->window, &g->width, &g->height);
    glfwSetWindowMonitor(g->window, glfwGetPrimaryMonitor(), 0, 0, g->width, g->height, GLFW_DONT_CARE);
}

#endif /* EMSCRIPTEN */


#include "helpers/nkc_stb_image.h"
#include "helpers/nkc_font_stash.h"
NKC_FONT_STASH_LOADER(glfw3)

#endif /* NKC_IMPLEMENTATION */

#endif /* NKC_GLFW_H */