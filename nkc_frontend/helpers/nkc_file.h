/**
 * Nuklear+ (read as "Nuklear cross") is a front-end overlay for Nuklear GUI library. 
 * Write one simple code, compile it for any supported frontend.
 *
 * License: public domain
 * no warrenty implied; use at your own risk.
 * authored from 2016-2017 by Dmitry Hrabrov a.k.a. DeXPeriX
 */

#ifndef NKC_FILE_H
#define NKC_FILE_H

#include <stdio.h>
#include <string.h>

int nkc_file_exists(const char* filename);
size_t nkc_stdfile_size(FILE* f);
size_t nkc_file_size(const char* filename);
void nkc_file_pre_read();
void nkc_file_post_write();
void nkc_mount_write(const char* folder);


#if defined(NKC_IMPLEMENTATION)
int nkc_file_exists(const char* filename){
    FILE* f = fopen(filename, "r");
    if (f) {
        fclose(f);
        return nk_true;
    } else {
        return nk_false;
    }   
}

size_t nkc_stdfile_size(FILE* f){
    size_t fileSize;
    if(!f) return 0;
    fseek(f, 0, SEEK_END);
    fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);
    return fileSize;
}

size_t nkc_file_size(const char* filename){
    size_t fileSize;
    FILE* f = fopen(filename, "rb");
    fileSize = nkc_stdfile_size(f);
    fclose(f);
    return fileSize;
}

void nkc_file_pre_read(){
    #if defined(__EMSCRIPTEN__)
        EM_ASM(
            /* sync from persisted state into memory */
            FS.syncfs(true, function (err) {
              assert(!err);
            });
        );
    #endif
}

void nkc_file_post_write(){
    #if defined(__EMSCRIPTEN__)
        EM_ASM(
            FS.syncfs(false, function (err) {
              assert(!err);
            });
        );
    #endif
}

void nkc_mount_write(const char* folder){
    #if defined(__EMSCRIPTEN__)
        char buf[1024];
        sprintf(buf, "FS.mkdir('%s'); FS.mount(IDBFS, {}, '%s');", folder, folder);
        emscripten_run_script(buf);
    #else
        (void)folder;
    #endif
}
#endif /* NKC_IMPLEMENTATION */

#endif /* NKC_FILE_H */