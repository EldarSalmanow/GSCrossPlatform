#include <GSCrossPlatform/IO.h>

#if defined(GS_OS_WINDOWS)

    #include <Windows.h>

#endif

Bool EnableUnicodeConsole() {
#if defined(GS_OS_WINDOWS)

    if (SetConsoleCP(CP_UTF8) == TRUE && SetConsoleOutputCP(CP_UTF8) == TRUE) {
        return true;
    }

#endif

    return false;
}
