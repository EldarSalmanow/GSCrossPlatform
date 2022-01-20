#ifndef GSCROSSPLATFORM_GS_CROSSPLATFORMDEFINES_H
#define GSCROSSPLATFORM_GS_CROSSPLATFORMDEFINES_H

/**
 * Checking for Windows operation system
 */
#if defined(WIN32) || defined(WIN64)
    #define GS_OS_DETECTED

    #define GS_OS_WINDOWS
#endif

/**
 * Checking for MSVC compiler
 */
#if defined(_MSC_VER)
    #define GS_COMPILER_DETECTED

    #define GS_COMPILER_MSVC
#endif

/**
 * Checking for MinGW compiler
 */
#if defined(__MINGW32__) || defined(__MINGW64__)
    #define GS_COMPILER_DETECTED

    #define GS_COMPILER_MINGW
#endif

/**
 * Checking OS detecting
 */
#if !defined(GS_OS_DETECTED)
    #warning "Unsupported operation system!"
#endif

/**
 * Checking compiler detecting
 */
#if !defined(GS_COMPILER_DETECTED)
    #warning "Unsupported compiler!"
#endif

/**
 * Cross platform entry point function defining
 */
#define GS_MAIN int main(int argc, char **argv)

#endif //GSCROSSPLATFORM_GS_CROSSPLATFORMDEFINES_H
