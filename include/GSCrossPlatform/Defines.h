#ifndef GSCROSSPLATFORM_DEFINES_H
#define GSCROSSPLATFORM_DEFINES_H

/**
 * Checking for Windows OS
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
 * Enabling or disabling OS and compiler checks
 */
#if !defined(GS_NOT_OS_AND_COMPILER_CHECKS)

    /**
     * Checking OS detecting
     */
    #if !defined(GS_OS_DETECTED)
        #error "Unsupported operation system!"
    #endif

    /**
     * Checking compiler detecting
     */
    #if !defined(GS_COMPILER_DETECTED)
        #error "Unsupported compiler!"
    #endif

#endif

/**
 * Attribute macro
 */
#define GS_ATTRIBUTE(name) [[name]]

/**
 * Attribute 'noreturn'
 */
#define GS_NORETURN GS_ATTRIBUTE(noreturn)

/**
 * Cross platform entry point function defining
 */
#define GS_MAIN int main(int argc, char **argv)

/**
 * Is OS Windows
 * @return Is OS Windows
 */
inline constexpr bool IsOSWindows() {
#if defined(GS_OS_WINDOWS)

    return true;

#else

    return false;

#endif
}

/**
 * Is compiler MSVC
 * @return Is compiler MSVC
 */
inline constexpr bool IsCompilerMSVC() {
#if defined(GS_COMPILER_MSVC)

    return true;

#else

    return false;

#endif
}

/**
 * Is compiler MinGW
 * @return Is compiler MinGW
 */
inline constexpr bool IsCompilerMinGW() {
#if defined(GS_COMPILER_MINGW)

    return true;

#else

    return false;

#endif
}

#endif //GSCROSSPLATFORM_DEFINES_H
