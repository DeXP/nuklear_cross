/**
 * Nuklear+ (read as "Nuklear cross") is a front-end overlay for Nuklear GUI library. 
 * Write one simple code, compile it for any supported frontend.
 *
 * License: public domain
 * no warrenty implied; use at your own risk.
 * authored from 2016-2017 by Dmitry Hrabrov a.k.a. DeXPeriX
 */

#ifndef NKC_GDIP_H
#define NKC_GDIP_H
    #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0500
    #endif
    #include <windows.h>

    #if defined(NKC_IMPLEMENTATION)
        #define NK_GDIP_IMPLEMENTATION
    #endif

    #include "../nuklear_drivers/nuklear_gdip.h"
    
    #define NKC_WINTITSIZE 128
    /*#define NKC_MAX_PATH 256*/

    struct nkc {
        int nkcInited;
        struct nk_context *ctx;
        int keepRunning;
        
        GdipFont* font;
        HWND window;
        wchar_t winTitle[NKC_WINTITSIZE];
        int needs_refresh;
    };
        

/* Constants */
#define NKC_KEY_ESCAPE VK_ESCAPE
#define NKC_KEY_SPACE VK_SPACE
#define NKC_KEY_BACKSPACE VK_BACK
#define NKC_KEY_DELETE VK_DELETE
#define NKC_KEY_TAB VK_TAB
#define NKC_KEY_CTRL VK_CONTROL
#define NKC_KEY_SHIFT VK_SHIFT
#define NKC_KEY_ALT VK_MENU
#define NKC_KEY_WIN VK_LWIN
#define NKC_KEY_LEFTBRACKET VK_OEM_4 
#define NKC_KEY_RIGHTBRACKET VK_OEM_6
#define NKC_KEY_SEMICOLON VK_OEM_1
#define NKC_KEY_APOSTROPHE VK_OEM_3
#define NKC_KEY_COMMA VK_OEM_COMMA
#define NKC_KEY_PERIOD VK_OEM_PERIOD
#define NKC_KEY_GRAVE VK_OEM_3
#define NKC_KEY_SLASH VK_OEM_2
#define NKC_KEY_BACKSLASH VK_OEM_5
#define NKC_KEY_INSERT VK_INSERT
#define NKC_KEY_HOME VK_HOME
#define NKC_KEY_END VK_END
#define NKC_KEY_PGUP VK_PRIOR
#define NKC_KEY_PGDOWN VK_NEXT
#define NKC_KEY_A 0x41
#define NKC_KEY_B 0x42
#define NKC_KEY_C 0x43
#define NKC_KEY_D 0x44
#define NKC_KEY_E 0x45
#define NKC_KEY_F 0x46
#define NKC_KEY_G 0x47
#define NKC_KEY_H 0x48
#define NKC_KEY_I 0x49
#define NKC_KEY_J 0x4A
#define NKC_KEY_K 0x4B
#define NKC_KEY_L 0x4C
#define NKC_KEY_M 0x4D
#define NKC_KEY_N 0x4E
#define NKC_KEY_O 0x4F
#define NKC_KEY_P 0x50
#define NKC_KEY_Q 0x51
#define NKC_KEY_R 0x52
#define NKC_KEY_S 0x53
#define NKC_KEY_T 0x54
#define NKC_KEY_U 0x55
#define NKC_KEY_V 0x56
#define NKC_KEY_W 0x57
#define NKC_KEY_X 0x58
#define NKC_KEY_Y 0x59
#define NKC_KEY_Z 0x5A
#define NKC_KEY_0 0x30
#define NKC_KEY_1 0x31
#define NKC_KEY_2 0x32
#define NKC_KEY_3 0x33
#define NKC_KEY_4 0x34
#define NKC_KEY_5 0x35
#define NKC_KEY_6 0x36
#define NKC_KEY_7 0x37
#define NKC_KEY_8 0x38
#define NKC_KEY_9 0x39
#define NKC_KEY_F1 VK_F1
#define NKC_KEY_F2 VK_F2
#define NKC_KEY_F3 VK_F3
#define NKC_KEY_F4 VK_F4
#define NKC_KEY_F5 VK_F5
#define NKC_KEY_F6 VK_F6
#define NKC_KEY_F7 VK_F7
#define NKC_KEY_F8 VK_F8
#define NKC_KEY_F9 VK_F9
#define NKC_KEY_F10 VK_F10
#define NKC_KEY_F11 VK_F11
#define NKC_KEY_F12 VK_F12

#if defined(NKC_IMPLEMENTATION)
/* https://msdn.microsoft.com/en-us/library/windows/desktop/ms534038(v=vs.85).aspx */
GpStatus WINGDIPAPI GdipGetDpiX(GpGraphics *graphics, REAL* dpi);

static struct {
    int winWidth;
    int winHeight;
    int origWidth;
    int origHeight;
    enum nkc_window_mode winMode;
} nkcg;


NK_API void* nkc_rdie(const char *fmt, ...){
    char buffer[1024];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);
    va_end(ap);

    MessageBoxA(NULL, buffer, "Error", MB_ICONERROR | MB_OK);
    return NULL;
}

LRESULT CALLBACK WindowProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam){
    WORD lo, hi;
    if( msg == WM_DESTROY ){
        PostQuitMessage(0);
        return 0;
    }
    
    if(nkcg.winMode == NKC_WIN_FULLSCREEN_DESKTOP){
        switch (msg){
        /*case WM_DESTROY:
            PostQuitMessage(0);
            return 0;*/
        case WM_SIZE: return 0;
        
        case WM_MOUSEMOVE: 
        case WM_LBUTTONDOWN: case WM_LBUTTONUP: case WM_LBUTTONDBLCLK:
        case WM_RBUTTONDOWN: case WM_RBUTTONUP: case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDOWN: case WM_MBUTTONUP: case WM_MBUTTONDBLCLK:
            lo = LOWORD(lparam) * nkcg.origWidth / nkcg.winWidth;
            hi = HIWORD(lparam) * nkcg.origHeight / nkcg.winHeight;
            lparam = MAKELPARAM(lo, hi);
        }
    }
    if (nk_gdip_handle_event(wnd, msg, wparam, lparam)) return 0;
    return DefWindowProcW(wnd, msg, wparam, lparam);
}

/* https://stackoverflow.com/questions/34462445/fullscreen-vs-borderless-window */
NK_API int nkc_get_desktop_size(struct nkc* nkcHandle, int* width, int* height){
    /*MONITORINFO info;
    HMONITOR monitor = MonitorFromWindow( GetDesktopWindow(), MONITOR_DEFAULTTONEAREST);
    info.cbSize = sizeof(MONITORINFO);
    if( !GetMonitorInfo(monitor, &info) ) return 0;
    *width = info.rcMonitor.right - info.rcMonitor.left;
    *height = info.rcMonitor.bottom - info.rcMonitor.top;*/
    *width = GetSystemMetrics(SM_CXSCREEN);
    *height = GetSystemMetrics(SM_CYSCREEN);
    (void)nkcHandle;
    return 1;
}

/* https://www.gamedev.net/forums/topic/536958-win32-api-fullscreen-mode/ */
int GoRealFullscreen(struct nkc* nkcHandle, HWND m_hWindow, int width, int height){
    DEVMODE newSettings;
    long result;
    SetWindowRgn(m_hWindow, 0, nk_false);

    EnumDisplaySettings(0, 0, &newSettings);
    newSettings.dmPelsWidth  = width;
    newSettings.dmPelsHeight = height;
    newSettings.dmBitsPerPel = 32;
    newSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    result = ChangeDisplaySettings(&newSettings, CDS_FULLSCREEN);

    if ( result != DISP_CHANGE_SUCCESSFUL ) return nk_false;
    else {
        /* switch off the title bar */
        DWORD dwstyle = GetWindowLong(m_hWindow, GWL_STYLE);
        dwstyle &= ~WS_CAPTION;
        SetWindowLong(m_hWindow, GWL_STYLE, dwstyle);

        /* move the window to (0,0) */
        SetWindowPos(m_hWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        InvalidateRect(m_hWindow, 0, nk_true);
        return nk_true;
    }
}

int GoRealWindowedMode(struct nkc* nkcHandle, HWND m_hWindow){
    DWORD dwstyle = GetWindowLong(m_hWindow, GWL_STYLE);
    ChangeDisplaySettings(0, 0);
    /* replace the title bar */
    dwstyle = dwstyle | WS_CAPTION;
    SetWindowLong(m_hWindow, GWL_STYLE, dwstyle);
    /* move the window back to its old position
    SetWindowPos(m_hWindow, 0, m_oldLoc.x, m_oldLoc.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    InvalidateRect(m_hWindow, 0, true);*/
    return nk_true;
}

NK_API struct nk_context *nkc_init(struct nkc* nkcHandle, const char* title, 
                        int width, int height, enum nkc_window_mode windowMode)
{
    int descWidth = 0;
    int descHeight = 0;
    WNDCLASSW wc;
    RECT rect = { 0, 0, width, height };
    RECT deskRect;
    LONG centerLeft, centerTop, curWidth, curHeight;
    DWORD style = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX;
    DWORD exstyle = WS_EX_APPWINDOW;
    MultiByteToWideChar(CP_ACP, 0, title, strlen(title)+1, nkcHandle->winTitle, NKC_WINTITSIZE);

    nkcg.winMode = windowMode;
    nkcg.origWidth = width;
    nkcg.origHeight = height;
    if( windowMode == NKC_WIN_NORMAL ) style = WS_OVERLAPPEDWINDOW;
    if( (windowMode == NKC_WIN_FULLSCREEN_DESKTOP) && nkc_get_desktop_size(nkcHandle, &descWidth, &descHeight) ){
        /* ok, go to fullscreen */
        /*style &= ~(WS_CAPTION | WS_THICKFRAME);
        exstyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);*/
        /*style = WS_POPUP | WS_VISIBLE;
        exstyle = WS_EX_APPWINDOW | WS_EX_TOPMOST;*/
        style = WS_POPUP;
        rect.right = descWidth;
        rect.bottom = descHeight;
        /*printf("desktop width = %d height = %d\n", descWidth, descHeight);*/
    }
    nkcg.winWidth = rect.right;
    nkcg.winHeight = rect.bottom;
    
    ZeroMemory(&wc, sizeof(wc));
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandleW(0);
    wc.hIcon = LoadIcon(wc.hInstance, MAKEINTRESOURCE(101));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"Nuklear-Cross";
    RegisterClassW(&wc);
        
    AdjustWindowRectEx(&rect, style, FALSE, exstyle);
    curWidth = rect.right - rect.left;
    curHeight = rect.bottom - rect.top;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &deskRect, 0);
    centerLeft = (deskRect.right - curWidth) / 2;
    centerTop = (deskRect.bottom - curHeight ) / 2;

    nkcHandle->window = CreateWindowExW(exstyle, wc.lpszClassName, nkcHandle->winTitle,
            style | WS_VISIBLE, centerLeft, centerTop, curWidth, curHeight,
            NULL, NULL, wc.hInstance, NULL);
    
    if( nkcg.winMode == NKC_WIN_FULLSCREEN_DESKTOP ) 
        SetWindowPos(nkcHandle->window, HWND_TOP, 0, 0, descWidth, descHeight, SWP_FRAMECHANGED);
    if( nkcg.winMode == NKC_WIN_FULLSCREEN )
        GoRealFullscreen(nkcHandle, nkcHandle->window, width, height);
    nkcHandle->needs_refresh = 1;
    
    nkcHandle->ctx = nk_gdip_init(nkcHandle->window, width, height);
    nkcHandle->font = nk_gdipfont_create("Arial", 12);
    nk_gdip_set_font(nkcHandle->font);
    
    nkcHandle->nkcInited = NKC_INITED;
    return nkcHandle->ctx;
}

NK_API void nkc_shutdown(struct nkc* nkcHandle){
    nk_gdipfont_del(nkcHandle->font);
    nk_gdip_shutdown();
    UnregisterClassW( nkcHandle->winTitle, GetModuleHandleW(0) );
}

NK_API union nkc_event nkc_poll_events(struct nkc* nkcHandle){
    struct nk_context *ctx = nkcHandle->ctx;
    MSG msg;
    union nkc_event ne;
    ne.type = NKC_ENONE;
    /* Input */
    nk_input_begin(ctx);
    if (nkcHandle->needs_refresh == 0){
        if (GetMessageW(&msg, NULL, 0, 0) <= 0){
            ne.type = NKC_EWINDOW;
            ne.window.param = NKC_EQUIT;
        } else {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        nkcHandle->needs_refresh = 1;
    } else {
        nkcHandle->needs_refresh = 0;
    }
    while ( PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)){
        switch(msg.message){
            case WM_QUIT:
                ne.type = NKC_EWINDOW;
                ne.window.param = NKC_EQUIT;
            break;
            case WM_KEYDOWN:
                ne.type = NKC_EKEY;
                ne.key.code = msg.wParam;
            break;
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
        nkcHandle->needs_refresh = 1;
    }
    nk_input_end(ctx);
    return ne;
}

NK_API char nkc_get_key_char(int code){
    char ret = MapVirtualKey(code, 2); /* MAPVK_VK_TO_CHAR = 2 */
    if( (ret>='A') && (ret<='Z') ) ret = ret - 'A' + 'a';
    return ret;
}

NK_API void nkc_render_bg(struct nkc* nkcHandle, struct nk_color bgColor){
    nk_gdip_clear(bgColor);
}

NK_API void nkc_render_gui(struct nkc* nkcHandle){
    nk_gdip_prerender_gui(NK_ANTI_ALIASING_ON);
    if(nkcg.winMode == NKC_WIN_FULLSCREEN_DESKTOP){
        GdipDrawImageRectI(gdip.window, gdip.bitmap, 0, 0, nkcg.winWidth, nkcg.winHeight);
    } else {
        nk_gdip_blit(gdip.window);
    }
    nk_clear(nkcHandle->ctx);
}


WCHAR* nkc_char_to_wchar(const char* str){
    int wsize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
    WCHAR* widestr = (WCHAR*)malloc((wsize + 1) * sizeof(WCHAR));
    MultiByteToWideChar(CP_ACP, 0, str, -1, widestr, wsize);
    widestr[wsize] = 0;
    return widestr;
}


int gdip_fontSizeCorrect(int ptSize){
    /*return ptSize*1;*/
    return ptSize*0.87;
    /*REAL dpi;
    GdipGetDpiX(gdip.memory, &dpi);
    return ptSize * 72 / dpi + 1;*/ /* pixels to points convert */
}

NK_API struct nk_user_font* nkc_load_font_file(struct nkc* nkcHandle, const char* filename, float size, const nk_rune *symbolsRange){
    WCHAR* wfile = nkc_char_to_wchar(filename);
    (void)symbolsRange;

    nkcHandle->font = nk_gdipfont_create_from_file(wfile, gdip_fontSizeCorrect(size) );
    if( nkcHandle->font ) nk_gdip_set_font(nkcHandle->font);
    free(wfile);
    if( nkcHandle->font ) return &nkcHandle->font->nk;
        else return NULL;
}

NK_API struct nk_user_font* nkc_load_font_memory(struct nkc* nkcHandle, const void* membuf, int membufSize, 
                                float size, const nk_rune *symbolsRange)
{
    (void)symbolsRange;
    nkcHandle->font = nk_gdipfont_create_from_memory(membuf, membufSize, gdip_fontSizeCorrect(size) );
    if( nkcHandle->font ){
        nk_gdip_set_font(nkcHandle->font);
        return &nkcHandle->font->nk;
    } else return NULL;
}

NK_API struct nk_image nkc_load_image_file(struct nkc* nkcHandle, const char* filename){
    struct nk_image img;
    WCHAR* wfile = nkc_char_to_wchar(filename);
    img = nk_gdip_load_image_from_file(wfile);
    free(wfile);
    return img;
}

NK_API struct nk_image nkc_load_image_memory(struct nkc* nkcHandle, const void* membuf, int membufSize){
    (void)nkcHandle;
    return nk_gdip_load_image_from_memory(membuf, membufSize);
}

NK_API void nkc_image_free(struct nk_image* img){
    /*GdipDisposeImage(img->handle.ptr);*/
    nk_gdip_image_free(*img);
    img->w = 0;
    img->h = 0;
    img = NULL;
}
#endif /* NKC_IMPLEMENTATION */

#endif /* NKC_GDIP_H */