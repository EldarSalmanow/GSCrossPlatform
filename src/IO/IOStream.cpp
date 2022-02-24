#include <GSCrossPlatform/IO/IOStream.h>

namespace CrossPlatform {

#if defined(GS_OS_WINDOWS)

    static UnicodeFileStream COut(FileHandle(GetStdHandle(STD_OUTPUT_HANDLE)));

    static UnicodeFileStream CIn(FileHandle(GetStdHandle(STD_INPUT_HANDLE)));

    static UnicodeFileStream CErr(FileHandle(GetStdHandle(STD_ERROR_HANDLE)));

#endif

    LRef<UnicodeFileStream> UCOut() {
        return COut;
    }

    LRef<UnicodeFileStream> UCIn() {
        return CIn;
    }

    LRef<UnicodeFileStream> UCErr() {
        return CErr;
    }

}
