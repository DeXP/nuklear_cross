/**
 * Nuklear+ (read as "Nuklear cross") is a front-end overlay for Nuklear GUI library. 
 * Write one simple code, compile it for any supported frontend.
 *
 * License: public domain
 * no warrenty implied; use at your own risk.
 * authored from 2016-2017 by Dmitry Hrabrov a.k.a. DeXPeriX
 */

#if !defined(NKC_STB_IMAGE_LOADER) && !defined(NKC_DISABLE_IMAGES)
#define NKC_STB_IMAGE_LOADER


#if defined(NKC_IMPLEMENTATION)
    #define STB_IMAGE_IMPLEMENTATION
#endif
#include "../../stb_image.h"

#define NKC_IS_POWER_OF_2(value) ((value & (value - 1)) == 0)


NK_API struct nk_image nkc_load_image_gl(unsigned char *data, int x, int y, int n){
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    #if (defined(NKC_USE_OPENGL) && (NKC_USE_OPENGL == NGL_ES2)) || defined(__EMSCRIPTEN__)
        /* WebGL via Emscripten */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        
        if (NKC_IS_POWER_OF_2(x) && NKC_IS_POWER_OF_2(y)){
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
    #else
        /* Desktop OpenGL */
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        
        #if !defined(GL_GENERATE_MIPMAP)
            /* from GLEW.h, OpenGL 1.4 only! */
            #define GL_GENERATE_MIPMAP 0x8191
        #endif
            
        #if defined(NKC_USE_OPENGL) && (NKC_USE_OPENGL > 2)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        #else
            glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); 
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        #endif

    #endif /* EMSCRIPTEN */
    
    stbi_image_free(data);
    return nk_image_id((int)tex);
}

NK_API struct nk_image nkc_load_image_memory(struct nkc* nkcHandle, const void* membuf, int membufSize){
    int x,y,n;    
    unsigned char *data = stbi_load_from_memory(membuf, membufSize, &x, &y, &n, 0);
    return nkc_load_image_gl(data, x, y, n);
}

NK_API struct nk_image nkc_load_image_file(struct nkc* nkcHandle, const char* filename){
    int x,y,n;
    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
    return nkc_load_image_gl(data, x, y, n);
}

NK_API void nkc_image_free(struct nk_image* img){
    if( img != NULL ){
        glDeleteTextures(1,(const GLuint*)&(img->handle.id) );
        img->w = 0;
        img->h = 0;
        img = NULL;
    }
    #include "nkc_stbi_unused.h"
}

#endif 