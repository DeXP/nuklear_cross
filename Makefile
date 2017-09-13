#
# Makefile for Nuklear+ Example and all available technologies
#
EMCC = emcc
WINCC = i686-w64-mingw32-gcc 
SOURCE = nuklear_cross.c
EXE = nkcexample
CFLAGS = -O2 -Wall -DNKC_EXAMPLE -DNDEBUG
LDFLAGS = -s -lm
STRICTFLAGS = -std=c89

LIBGLES = -lGLESv2
ifeq ($(OS),Windows_NT)
	BIN = .exe
	LIBGLEW = -lGLEW32
	LIBGL = -lopengl32
	LIBSDL = -lmingw32 -lSDL2main -lSDL2
	LIBGLFW = -lglfw3
	WINCC := $(CC)
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		BIN = .bin
		LIBGLEW = -lGLEW
		LIBGL = -framework OpenGL -framework Cocoa -framework IOKit
		LIBSDL = -lSDL2
		LIBGLFW = -lglfw3
	else
		BIN = .bin
		LIBGLEW := $(shell pkg-config --libs --cflags glew)
		LIBGL := $(shell pkg-config --libs --cflags gl)
		LIBSDL := $(shell pkg-config --libs --cflags sdl2)
		LIBGLFW := $(shell pkg-config --libs --cflags glfw3)
		MAKE_XLIB = $(UNAME_S)
	endif
endif

SDLBASE  = -DNKCD=NKC_SDL  $(LIBSDL)
GLFWBASE = -DNKCD=NKC_GLFW $(LIBGLFW)
XLIBBASE = -DNKCD=NKC_XLIB `pkg-config --libs --cflags x11`
RPIFLAGS = -DNKC_USE_OPENGL=NGL_ES2 -DNKC_RASPBERRY_PI -I/opt/vc/include -L/opt/vc/lib -lbcm_host -lbrcmGLESv2

COMP = $(CC) $(SOURCE) $(CFLAGS) $(LDFLAGS) $(STRICTFLAGS)
EMCOMP = $(EMCC) $(SOURCE) $(CFLAGS) $(STRICTFLAGS)



all: sdl glfw xlib emscripten gdip

sdl: sdl-gl2 sdl-gl3 sdl-gles2
sdl-gl2:
	$(COMP) $(SDLBASE) $(LIBGL) -o $(EXE)-sdl-gl2$(BIN)
sdl-gl3:
	$(COMP) $(SDLBASE) -DNKC_USE_OPENGL=3 $(LIBGL) $(LIBGLEW) -o $(EXE)-sdl-gl3$(BIN)
sdl-gles2:
	$(COMP) $(SDLBASE) -DNKC_USE_OPENGL=NGL_ES2 $(LIBGLES) -o $(EXE)-sdl-gles2$(BIN)

glfw: glfw-gl2 glfw-gl3
glfw-gl2:
	$(COMP) $(GLFWBASE) $(LIBGL) -o $(EXE)-glfw-gl2$(BIN)
glfw-gl3:
	$(COMP) $(GLFWBASE) -DNKC_USE_OPENGL=3 $(LIBGL) $(LIBGLEW) -o $(EXE)-glfw-gl3$(BIN)

ifdef MAKE_XLIB
xlib: xlib-gl2 xlib-gl3 xlib-pure
xlib-gl2:
	$(COMP) $(XLIBBASE) -DNKC_USE_OPENGL=2 $(LIBGL) -o $(EXE)-xlib-gl2$(BIN)
xlib-gl3:
	$(COMP) $(XLIBBASE) -DNKC_USE_OPENGL=3 $(LIBGL) $(LIBGLEW) -o $(EXE)-xlib-gl3$(BIN)
xlib-pure:
	$(COMP) $(XLIBBASE) -o $(EXE)-xlib-pure$(BIN)
else
xlib:
	echo "No Xlib on your system"
endif

emscripten: emscripten-glfw emscripten-sdl
emscripten-glfw:	
	$(EMCOMP) -s USE_GLFW=3 -DNKCD=NKC_GLFW -o $(EXE)-glfw.html
emscripten-sdl:	
	$(EMCOMP) -s USE_SDL=2  -DNKCD=NKC_SDL  -o $(EXE)-sdl.html

gdip:
	$(WINCC) -DNKCD=NKC_GDIP $(CFLAGS) $(LDFLAGS) $(SOURCE) -lgdiplus -lshlwapi -o $(EXE)-gdip.exe 

raspberry:
	$(CC) $(SOURCE) $(CFLAGS) $(LDFLAGS) $(SDLBASE) $(RPIFLAGS) -o $(EXE)-sdl-rasp$(BIN)


doc:
	( cat Doxyfile ; echo -e "INPUT=nuklear_cross.h\nPROJECT_NAME=Nuklear+\nGENERATE_LATEX=No" ) | doxygen -

clean:
	rm $(EXE)*
