/**
 * Nuklear+ (read as "Nuklear cross") is a front-end overlay for Nuklear GUI library. 
 * Write one simple code, compile it for any supported frontend.
 *
 * License: public domain
 * no warrenty implied; use at your own risk.
 * authored from 2016-2017 by Dmitry Hrabrov a.k.a. DeXPeriX
 */

#ifndef NKC_XLIB_H
#define NKC_XLIB_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <stdarg.h>
    #include <string.h>
    #include <math.h>
    #include <assert.h>
    #include <math.h>
    #include <time.h>
    #include <limits.h>
    
    #define GL_GLEXT_PROTOTYPES
    #if defined(NKC_USE_OPENGL)
        #if NKC_USE_OPENGL > 2
            #if defined(NKC_IMPLEMENTATION)
                #define NK_XLIB_GL3_IMPLEMENTATION
            #endif
            /*#define NK_XLIB_LOAD_OPENGL_EXTENSIONS*/
            #include "../nuklear_drivers/nuklear_xlib_gl3.h"
        #else
            #if defined(NKC_IMPLEMENTATION)
                #define NK_XLIB_GL2_IMPLEMENTATION
            #endif
            #include "../nuklear_drivers/nuklear_xlib_gl2.h"
        #endif
        
        #include <GL/gl.h>
        #include <GL/glx.h>
        #include <GL/glxext.h>
    #else
        /* Pure Xlib */
        #if defined(NKC_IMPLEMENTATION)
                #define NK_XLIB_IMPLEMENTATION
                #define NK_XLIB_INCLUDE_STB_IMAGE
                #define NK_XLIB_IMPLEMENT_STB_IMAGE
            #endif
        #include "../nuklear_drivers/nuklear_xlib.h"
    #endif
    
    
    #include <X11/Xutil.h>
    
    
    struct nkc {
        int nkcInited;
        struct nk_context *ctx;
        int keepRunning;

        Display *dpy;
        Window win;
        
        Colormap cmap;
        XSetWindowAttributes swa;
        XWindowAttributes attr;
        int width, height;
        Atom wm_delete_window;
        const char* winTitle;
        int screen;
        #if defined(NKC_USE_OPENGL)
            XVisualInfo *vis;
            GLXFBConfig fbc;
            GLXContext glContext;
        #else
            Visual *vis;
            XFont *font;
            Window root;
            
            struct nk_color bgColor;
        #endif
    };

/* Constants */
#define NKC_KEY_ESCAPE XK_Escape
#define NKC_KEY_SPACE XK_space
#define NKC_KEY_BACKSPACE XK_BackSpace
#define NKC_KEY_DELETE XK_Delete
#define NKC_KEY_TAB XK_Tab
#define NKC_KEY_CTRL XK_Control_L
#define NKC_KEY_SHIFT XK_Shift_L
#define NKC_KEY_ALT XK_Alt_L
#define NKC_KEY_WIN XK_Win_L
#define NKC_KEY_LEFTBRACKET XK_bracketleft
#define NKC_KEY_RIGHTBRACKET XK_bracketright
#define NKC_KEY_SEMICOLON XK_semicolon
#define NKC_KEY_APOSTROPHE XK_apostrophe
#define NKC_KEY_COMMA XK_comma
#define NKC_KEY_PERIOD XK_period
#define NKC_KEY_GRAVE XK_grave
#define NKC_KEY_SLASH XK_slash
#define NKC_KEY_BACKSLASH XK_backslash
#define NKC_KEY_INSERT XK_Insert
#define NKC_KEY_HOME XK_Home
#define NKC_KEY_END XK_End
#define NKC_KEY_PGUP XK_Page_Up
#define NKC_KEY_PGDOWN XK_Page_Down
#define NKC_KEY_A XK_a
#define NKC_KEY_B XK_b
#define NKC_KEY_C XK_c
#define NKC_KEY_D XK_d
#define NKC_KEY_E XK_e
#define NKC_KEY_F XK_f
#define NKC_KEY_G XK_g
#define NKC_KEY_H XK_h
#define NKC_KEY_I XK_i
#define NKC_KEY_J XK_j
#define NKC_KEY_K XK_k
#define NKC_KEY_L XK_l
#define NKC_KEY_M XK_m
#define NKC_KEY_N XK_n
#define NKC_KEY_O XK_o
#define NKC_KEY_P XK_p
#define NKC_KEY_Q XK_q
#define NKC_KEY_R XK_r
#define NKC_KEY_S XK_s
#define NKC_KEY_T XK_t
#define NKC_KEY_U XK_u
#define NKC_KEY_V XK_v
#define NKC_KEY_W XK_w
#define NKC_KEY_X XK_x
#define NKC_KEY_Y XK_y
#define NKC_KEY_Z XK_z
#define NKC_KEY_0 XK_0
#define NKC_KEY_1 XK_1
#define NKC_KEY_2 XK_2
#define NKC_KEY_3 XK_3
#define NKC_KEY_4 XK_4
#define NKC_KEY_5 XK_5
#define NKC_KEY_6 XK_6
#define NKC_KEY_7 XK_7
#define NKC_KEY_8 XK_8
#define NKC_KEY_9 XK_9
#define NKC_KEY_F1 XK_F1
#define NKC_KEY_F2 XK_F2
#define NKC_KEY_F3 XK_F3
#define NKC_KEY_F4 XK_F4
#define NKC_KEY_F5 XK_F5
#define NKC_KEY_F6 XK_F6
#define NKC_KEY_F7 XK_F7
#define NKC_KEY_F8 XK_F8
#define NKC_KEY_F9 XK_F9
#define NKC_KEY_F10 XK_F10
#define NKC_KEY_F11 XK_F11
#define NKC_KEY_F12 XK_F12

#if defined(NKC_IMPLEMENTATION)

NK_API void* nkc_rdie(const char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputs("\n", stderr);
    return NULL;
}

#if defined(NKC_USE_OPENGL)
    static int gl_err = nk_false;
    static int gl_error_handler(Display *dpy, XErrorEvent *ev)
    {(void)dpy;(void)ev; gl_err = nk_true;return 0;}


    static int
    has_extension(const char *string, const char *ext)
    {
        const char *start, *where, *term;
        where = strchr(ext, ' ');
        if (where || *ext == '\0')
            return nk_false;

        for (start = string;;) {
            where = strstr((const char*)start, ext);
            if (!where) break;
            term = where + strlen(ext);
            if (where == start || *(where - 1) == ' ') {
                if (*term == ' ' || *term == '\0')
                    return nk_true;
            }
            start = term;
        }
        return nk_false;
    }
#endif /* OpenGL */


void nkc_x11_fullscreen(Display* dpy, Window wid) {
    XWindowAttributes xwa;
    XGetWindowAttributes( dpy, wid, &xwa );
 
    XEvent e;
    e.xclient.type = ClientMessage;
    e.xclient.message_type = XInternAtom( dpy, "_NET_WM_STATE", nk_false );
    e.xclient.display = dpy;
    e.xclient.window = wid;
    e.xclient.format = 32;
    e.xclient.data.l[0] = 1;
    e.xclient.data.l[1] = XInternAtom( dpy, "_NET_WM_STATE_FULLSCREEN", nk_false );
    e.xclient.data.l[2] = 0;
    e.xclient.data.l[3] = 0;
    e.xclient.data.l[4] = 0;
    XSendEvent( dpy, xwa.root,
        nk_false, SubstructureNotifyMask | SubstructureRedirectMask, &e );
    XFlush(dpy);
}

#if defined(NKC_USE_OPENGL)
NK_API struct nk_context *nkc_init(struct nkc* nkcHandle, const char* title, 
                        int width, int height, enum nkc_window_mode windowMode)
{
    memset(nkcHandle, 0, sizeof(struct nkc));
    nkcHandle->winTitle = title;
    nkcHandle->dpy = XOpenDisplay(NULL);
    if (!nkcHandle->dpy) return nkc_rdie("Failed to open X display\n");
    {
        /* check glx version */
        int glx_major, glx_minor;
        if (!glXQueryVersion(nkcHandle->dpy, &glx_major, &glx_minor))
            return nkc_rdie("[X11]: Error: Failed to query OpenGL version\n");
        if ((glx_major == 1 && glx_minor < 3) || (glx_major < 1))
            return nkc_rdie("[X11]: Error: Invalid GLX version!\n");
    }
    {
        /* find and pick matching framebuffer visual */
        int fb_count;
        static GLint attr[] = {
            GLX_X_RENDERABLE,   True,
            GLX_DRAWABLE_TYPE,  GLX_WINDOW_BIT,
            GLX_RENDER_TYPE,    GLX_RGBA_BIT,
            GLX_X_VISUAL_TYPE,  GLX_TRUE_COLOR,
            GLX_RED_SIZE,       8,
            GLX_GREEN_SIZE,     8,
            GLX_BLUE_SIZE,      8,
            GLX_ALPHA_SIZE,     8,
            GLX_DEPTH_SIZE,     24,
            GLX_STENCIL_SIZE,   8,
            GLX_DOUBLEBUFFER,   True,
            None
        };
        GLXFBConfig *fbc;
        fbc = glXChooseFBConfig(nkcHandle->dpy, DefaultScreen(nkcHandle->dpy), attr, &fb_count);
        if (!fbc) return nkc_rdie("[X11]: Error: failed to retrieve framebuffer configuration\n");
        {
            /* pick framebuffer with most samples per pixel */
            int i;
            int fb_best = -1, best_num_samples = -1;
            for (i = 0; i < fb_count; ++i) {
                XVisualInfo *vi = glXGetVisualFromFBConfig(nkcHandle->dpy, fbc[i]);
                if (vi) {
                    int sample_buffer, samples;
                    glXGetFBConfigAttrib(nkcHandle->dpy, fbc[i], GLX_SAMPLE_BUFFERS, &sample_buffer);
                    glXGetFBConfigAttrib(nkcHandle->dpy, fbc[i], GLX_SAMPLES, &samples);
                    if ((fb_best < 0) || (sample_buffer && samples > best_num_samples)){
                        fb_best = i; best_num_samples = samples;
                        
                    }
                }
            }
            nkcHandle->fbc = fbc[fb_best];
            XFree(fbc);
            nkcHandle->vis = glXGetVisualFromFBConfig(nkcHandle->dpy, nkcHandle->fbc);
        }
    } 
    {
        /* create window */
        nkcHandle->cmap = XCreateColormap(nkcHandle->dpy, RootWindow(nkcHandle->dpy, nkcHandle->vis->screen), 
           nkcHandle->vis->visual, AllocNone);
        nkcHandle->swa.colormap =  nkcHandle->cmap;
        nkcHandle->swa.background_pixmap = None;
        nkcHandle->swa.border_pixel = 0;
        nkcHandle->swa.event_mask =
            ExposureMask | KeyPressMask | KeyReleaseMask | ClientMessage |
            ButtonPress | ButtonReleaseMask| ButtonMotionMask |
            Button1MotionMask | Button3MotionMask | Button4MotionMask | Button5MotionMask|
            PointerMotionMask| StructureNotifyMask;
        nkcHandle->win = XCreateWindow(nkcHandle->dpy, RootWindow(nkcHandle->dpy, nkcHandle->vis->screen),
            0, 0, width, height, 0, nkcHandle->vis->depth, InputOutput, nkcHandle->vis->visual, 
            CWBorderPixel|CWColormap|CWEventMask, &(nkcHandle->swa) );
        if (!nkcHandle->win) return nkc_rdie("[X11]: Failed to create window\n");
        XFree(nkcHandle->vis);
        XStoreName(nkcHandle->dpy, nkcHandle->win, nkcHandle->winTitle);
        XMapWindow(nkcHandle->dpy, nkcHandle->win);
        nkcHandle->wm_delete_window = XInternAtom(nkcHandle->dpy, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(nkcHandle->dpy, nkcHandle->win, &(nkcHandle->wm_delete_window), 1);
    }
    {
        if( windowMode == NKC_WIN_FULLSCREEN ) nkc_x11_fullscreen(nkcHandle->dpy, nkcHandle->win);
        if( windowMode == NKC_WIN_FULLSCREEN_DESKTOP ) nkc_x11_fullscreen(nkcHandle->dpy, nkcHandle->win);
    }
    {
        /* create opengl context */
        typedef GLXContext(*glxCreateContext)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
        int(*old_handler)(Display*, XErrorEvent*) = XSetErrorHandler(gl_error_handler);
        const char *extensions_str = glXQueryExtensionsString(nkcHandle->dpy, DefaultScreen(nkcHandle->dpy));
        glxCreateContext create_context = (glxCreateContext)
            glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB");

        gl_err = nk_false;
        if (!has_extension(extensions_str, "GLX_ARB_create_context") || !create_context) {
            fprintf(stdout, "[X11]: glXCreateContextAttribARB() not found...\n");
            fprintf(stdout, "[X11]: ... using old-style GLX context\n");
            nkcHandle->glContext = glXCreateNewContext(nkcHandle->dpy, nkcHandle->fbc, GLX_RGBA_TYPE, 0, True);
        } else {
            GLint attr[] = {
                GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
                GLX_CONTEXT_MINOR_VERSION_ARB, 0,
                None
            };
            nkcHandle->glContext = create_context(nkcHandle->dpy, nkcHandle->fbc, 0, True, attr);
            XSync(nkcHandle->dpy, False);
            if (gl_err || !(nkcHandle->glContext) ) {
                /* Could not create GL 3.0 context. Fallback to old 2.x context.
                 * If a version below 3.0 is requested, implementations will
                 * return the newest context version compatible with OpenGL
                 * version less than version 3.0.*/
                attr[1] = 1; attr[3] = 0;
                gl_err = nk_false;
                fprintf(stdout, "[X11] Failed to create OpenGL 3.0 context\n");
                fprintf(stdout, "[X11] ... using old-style GLX context!\n");
                nkcHandle->glContext = create_context(nkcHandle->dpy, nkcHandle->fbc, 0, True, attr);
            }
        }
        XSync(nkcHandle->dpy, False);
        XSetErrorHandler(old_handler);
        if (gl_err || !nkcHandle->glContext)
            return nkc_rdie("[X11]: Failed to create an OpenGL context\n");
        glXMakeCurrent(nkcHandle->dpy, nkcHandle->win, nkcHandle->glContext);
    }
    
    nkcHandle->ctx = nk_x11_init(nkcHandle->dpy, nkcHandle->win);
    /* Load Fonts: if none of these are loaded a default font will be used  */
    {
        struct nk_font_atlas *atlas;
        nk_x11_font_stash_begin(&atlas);
        nk_x11_font_stash_end();
    }
    glEnable(GL_TEXTURE_2D);
    nkcHandle->nkcInited = NKC_INITED;
    return nkcHandle->ctx;
}
#else
NK_API struct nk_context *nkc_init(struct nkc* xw, const char* title, 
                        int width, int height, enum nkc_window_mode windowMode)
{
    memset(xw, 0, sizeof(struct nkc));
    xw->winTitle = title;
    xw->dpy = XOpenDisplay(NULL);
    if (!xw->dpy) return nkc_rdie("Failed to open X display\n");
    
    xw->root = DefaultRootWindow(xw->dpy);
    xw->screen = XDefaultScreen(xw->dpy);
    xw->vis = XDefaultVisual(xw->dpy, xw->screen);
    xw->cmap = XCreateColormap(xw->dpy,xw->root,xw->vis,AllocNone);

    xw->swa.colormap = xw->cmap;
    xw->swa.event_mask =
        ExposureMask | KeyPressMask | KeyReleaseMask |
        ButtonPress | ButtonReleaseMask| ButtonMotionMask |
        Button1MotionMask | Button3MotionMask | Button4MotionMask | Button5MotionMask|
        PointerMotionMask | KeymapStateMask;
    xw->win = XCreateWindow(xw->dpy, xw->root, 0, 0, width, height, 0,
        XDefaultDepth(xw->dpy, xw->screen), InputOutput,
        xw->vis, CWEventMask | CWColormap, &xw->swa);

    XStoreName(xw->dpy, xw->win, xw->winTitle);
    XMapWindow(xw->dpy, xw->win);
    xw->wm_delete_window = XInternAtom(xw->dpy, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(xw->dpy, xw->win, &xw->wm_delete_window, 1);
    XGetWindowAttributes(xw->dpy, xw->win, &xw->attr);
    xw->width = (unsigned int)xw->attr.width;
    xw->height = (unsigned int)xw->attr.height;
    
    {
        if( windowMode == NKC_WIN_FULLSCREEN ) nkc_x11_fullscreen(xw->dpy, xw->win);
        if( windowMode == NKC_WIN_FULLSCREEN_DESKTOP ) nkc_x11_fullscreen(xw->dpy, xw->win);
    }
    
    xw->font = nk_xfont_create(xw->dpy, "fixed");
    xw->ctx = nk_xlib_init(xw->font, xw->dpy, xw->screen, xw->win, xw->width, xw->height);
    xw->bgColor = nk_rgb(0, 0, 0);
    return xw->ctx;
}
#endif /* OpenGL */

NK_API void nkc_shutdown(struct nkc* nkcHandle){
    #if defined(NKC_USE_OPENGL)
        nk_x11_shutdown();
        glXMakeCurrent(nkcHandle->dpy, 0, 0);
        glXDestroyContext(nkcHandle->dpy, nkcHandle->glContext);
    #else
        nk_xlib_shutdown();
    #endif /* OpenGL */
    XUnmapWindow(nkcHandle->dpy, nkcHandle->win);
    XFreeColormap(nkcHandle->dpy, nkcHandle->cmap);
    XDestroyWindow(nkcHandle->dpy, nkcHandle->win);
    XCloseDisplay(nkcHandle->dpy);
}

NK_API union nkc_event nkc_poll_events(struct nkc* nkcHandle){
    /* Input */
    XEvent evt;
    union nkc_event ne;
    ne.type = NKC_ENONE;
    nk_input_begin(nkcHandle->ctx);
    while (XPending(nkcHandle->dpy)) {
        XNextEvent(nkcHandle->dpy, &evt);
        if (evt.type == ClientMessage){
            ne.type = NKC_EWINDOW;
            ne.window.param = NKC_EQUIT;
        }
        if (evt.type == KeyPress){
            int ret = 0;
            KeySym *code = XGetKeyboardMapping(nkcHandle->dpy, (KeyCode)evt.xkey.keycode, 1, &ret);
            ne.type = NKC_EKEY;
            ne.key.code = (int)*code;
        }
        if (XFilterEvent(&evt, nkcHandle->win)) continue;
        
        #if defined(NKC_USE_OPENGL)
            nk_x11_handle_event(&evt);
        #else
            nk_xlib_handle_event(nkcHandle->dpy, DefaultScreen(nkcHandle->dpy), nkcHandle->win, &evt);
        #endif
    }
    nk_input_end(nkcHandle->ctx);
    return ne;
}

NK_API char nkc_get_key_char(int code){
    /*char* str = XKeysymToString( (KeySym)code );
    printf("key %d = '%s' = '%c'\n", code, str, code);
    return str[0];*/
    return (char)code;
}

NK_API void nkc_render_bg(struct nkc* nkcHandle, struct nk_color bgColor){
    float bg[4];
    nk_color_fv(bg, bgColor);
    #if defined(NKC_USE_OPENGL)
        /*XGetWindowAttributes(nkcHandle->dpy, nkcHandle->win, &(nkcHandle->attr) );
        glViewport(0, 0, nkcHandle->width, nkcHandle->height);*/
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(bg[0], bg[1], bg[2], bg[3]);
    #else
        nkcHandle->bgColor = bgColor;
    #endif
}

NK_API void nkc_render_gui(struct nkc* nkcHandle){
    /* IMPORTANT: `nk_x11_render` modifies some global OpenGL state
     * with blending, scissor, face culling, depth test and viewport and
     * defaults everything back into a default state.
     * Make sure to either a.) save and restore or b.) reset your own state after
     * rendering the UI. */
    #if defined(NKC_USE_OPENGL)
        nk_x11_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
        glXSwapBuffers(nkcHandle->dpy, nkcHandle->win);
    #else
        nk_xlib_render(nkcHandle->win, nkcHandle->bgColor );
    #endif
}

NK_API int nkc_get_desktop_size(struct nkc* nkcHandle, int* width, int* height){
    Screen* scrn = DefaultScreenOfDisplay( XOpenDisplay(NULL) );
    if( scrn == NULL ) return 0;
    (void)nkcHandle;
    *height = scrn->height;
    *width  = scrn->width;
    return 1;
}

#if defined(NKC_USE_OPENGL)
    #include "helpers/nkc_stb_image.h"
    #include "helpers/nkc_font_stash.h"
    NKC_FONT_STASH_LOADER(x11);
#else
    /* pure Xlib */
    NK_API struct nk_image nkc_load_image_memory(struct nkc* nkcHandle, const void* membuf, int membufSize){
        (void)nkcHandle;
        return nk_xsurf_load_image_from_memory(membuf, membufSize);
    }
    
    NK_API struct nk_image nkc_load_image_file(struct nkc* nkcHandle, const char* filename){
        (void)nkcHandle;
        return nk_xsurf_load_image_from_file(filename);
    }
    
    NK_API void nkc_image_free(struct nk_image* img){
        nk_xsurf_image_free(img);
        #include "helpers/nkc_stbi_unused.h"
    }
    
    NK_API struct nk_user_font* nkc_load_font_file(struct nkc* nkcHandle, const char* filename, float size,
                              const nk_rune *symbolsRange)
    {
        return NULL;
    }
    
    NK_API struct nk_user_font* nkc_load_font_memory(struct nkc* nkcHandle, const void* membuf, int membufSize,
                                float size, const nk_rune *symbolsRange)
    {
        return NULL;
    }
#endif /* NKC_USE_OPENGL */

#endif /* NKC_IMPLEMENTATION */

#endif /* NKC_XLIB_H */