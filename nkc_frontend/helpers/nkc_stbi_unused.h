/**
 * Nuklear+ (read as "Nuklear cross") is a front-end overlay for Nuklear GUI library. 
 * Write one simple code, compile it for any supported frontend.
 *
 * License: public domain
 * no warrenty implied; use at your own risk.
 * authored from 2016-2017 by Dmitry Hrabrov a.k.a. DeXPeriX
 */

#if defined(STBI_ONLY_PNG)
    /* Use unused functions. Reduce compiler warnings */
    {
        stbi__context s;
        s.io.read = 0;
        stbi__at_eof(&s);
    }
    #if !defined(WIN32) && defined(STBI_SSE2)
        stbi__sse2_available();
    #endif
#endif