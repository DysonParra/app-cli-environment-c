#ifndef ENVIRONMENT_H_

/* Includes for the header file */

#define ENVIRONMENT_H_

#if defined __cplusplus
#define LANGUAGE extern "C"
#elif defined __GNUC__
#define LANGUAGE extern
#endif

#if defined ENVIRONMENT_STATIC_
#define DLLIMPORT
#elif defined BUILDING
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT __declspec(dllimport)
#endif

#define CALLING __cdecl
//#define CALLING __stdcall

/* Macros and definitions for the source file. */
#if defined ENVIRONMENT_DEFINITIONS_
#define elif else if
#define null NULL
#endif

#if !defined BUILDING
#undef LANGUAGE
#undef DLLIMPORT
#undef CALLING
#endif

#endif