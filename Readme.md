# Nuklear+
Nuklear+ (read as "Nuklear cross") is a front-end overlay for [Nuklear](https://github.com/vurtun/nuklear) GUI library.

Write one simple code, compile it for any supported frontend.


## Why?
[Nuklear](https://github.com/vurtun/nuklear) itself requires a lot of additional code to create OS window etc. Nuklear+ hide it all from programmer. Just write your code, do not think about OS!


## Docs
You can use [Doxygen docs](https://nuklear-cross.dexp.in). Or just have a look at [nuklear_cross.h](nuklear_cross.h) for all function descriptions.

## Complete Example
It's the same example as in [original Nuklear](https://github.com/vurtun/nuklear#example). The only difference - you need to add code in original example. This one is working out of the box.

```c
#include "nuklear_cross.h"
#include <stdio.h>

enum radioOptions {
    EASY,
    HARD
};

struct my_nkc_app {
    struct nkc* nkcHandle;

    /* some user data */
    float value;
    enum radioOptions op;
};

void mainLoop(void* loopArg){
    struct my_nkc_app* myapp = (struct my_nkc_app*)loopArg;
    struct nk_context *ctx = nkc_get_ctx(myapp->nkcHandle);

    union nkc_event e = nkc_poll_events(myapp->nkcHandle);
    if( (e.type == NKC_EWINDOW) && (e.window.param == NKC_EQUIT) ){
        nkc_stop_main_loop(myapp->nkcHandle);
    }

    /* Nuklear GUI code */
    if (nk_begin(ctx, "Show", nk_rect(50, 50, 220, 220),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE)) {
        /* fixed widget pixel width */
        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "button")) {
            /* event handling */
            printf("Button pressed\n");
        }

        /* fixed widget window ratio width */
        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_option_label(ctx, "easy", myapp->op == EASY)) myapp->op = EASY;
        if (nk_option_label(ctx, "hard", myapp->op == HARD)) myapp->op = HARD;

        /* custom widget pixel width */
        nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
        {
            nk_layout_row_push(ctx, 50);
            nk_label(ctx, "Volume:", NK_TEXT_LEFT);
            nk_layout_row_push(ctx, 110);
            nk_slider_float(ctx, 0, &(myapp->value), 1.0f, 0.1f);
        }
        nk_layout_row_end(ctx);
    }
    nk_end(ctx);
    /* End Nuklear GUI */

    nkc_render(myapp->nkcHandle, nk_rgb(40,40,40) );
}

int main(){
    struct my_nkc_app myapp;
    struct nkc nkcx; /* Allocate memory for Nuklear+ handle */
    myapp.nkcHandle = &nkcx;
    /* init some user data */
    myapp.value = 0.4;
    myapp.op = HARD;

    if( nkc_init( myapp.nkcHandle, "Nuklear+ Example", 640, 480, NKC_WIN_NORMAL ) ){
        printf("Successfull init. Starting 'infinite' main loop...\n");
        nkc_set_main_loop(myapp.nkcHandle, mainLoop, (void*)&myapp );
    } else {
        printf("Can't init NKC\n");
    }
    printf("Value after exit = %f\n", myapp.value);
    nkc_shutdown( myapp.nkcHandle );
    return 0;
}
```

![example](https://cloud.githubusercontent.com/assets/8057201/10187981/584ecd68-675c-11e5-897c-822ef534a876.png)


## More examples

- dxBin2h: https://github.com/DeXP/dxBin2h
- Nuklear Web Demo: https://github.com/DeXP/nuklear-webdemo



## How to use

The best way is using Git submodules. In your project's directory:

```
git submodule add https://github.com/DeXP/nuklear_cross
```

It will create `nuklear_cross` subdirectory and will fetch all content. When you will want to actualize content:

```
cd nuklear_cross
git checkout master
git pull
```


## Applications and games, made on Nuklear+

- Wordlase: [Steam](http://store.steampowered.com/app/602930/Wordlase/), [Web demo](https://wordlase.dexp.in/), [site](https://dexp.in/games/wordlase/)


## FAQ

- Are main loop function usage required?
- Only for Emscripten. You can organize main loop as you want if you do not plannig to make a web version.

## Updating Nuklear files
The library aims to use vanilla Nuklear.h and driver files from [demo](https://github.com/vurtun/nuklear/tree/master/demo) folder. So in general case you can just replace file by file from [Nuklear](https://github.com/vurtun/nuklear) repo. By the way, the API in demos can be changed. In that case frontend will stop work. Also, there can some functionality, not yet added to Nuklear's main repo. Also, drivers can need some small fixes. The path of `stb_image.h` in `nuklear_xlib.h` for example.

## Credits:
Developed by Dmitry Hrabrov a.k.a. DeXPeriX and every direct or indirect contributor to the GitHub.

## License:
This software is dual-licensed to the public domain and under the following license: you are granted a perpetual, irrevocable license to copy, modify, publish and distribute this file as you see fit
