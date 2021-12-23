#include <GSCrossPlatform/GS_CrossPlatformString.h>

#include <GSCrossPlatform/GS_CrossPlatformIO.h>

namespace Windows {

#if defined(GS_OS_WINDOWS)
    #if defined(GS_COMPILER_MSVC)
        #include <Windows.h>
    #elif defined(GS_COMPILER_MINGW)
        #include <windows.h>
    #endif
#endif

}

namespace CrossPlatform {

    UDevice::~UDevice() = default;

    UStream::~UStream() = default;

    UFileDevice::UFileDevice(Ptr<FILE> file)
            : _file(file) {}

    Bool UFileDevice::open(ConstLRef<UString> name, ConstLRef<FileOpenMode> mode) {
        UString stringMode;

        if (mode & in_mode && mode & out_mode) {
            return false;
        }

        if (mode & in_mode) {
            stringMode += U'r';
        }

        if (mode & out_mode) {
            stringMode += U'w';
        }

        if (mode & bin_mode) {
            stringMode += U'b';
        }

        _file = std::fopen(name.asString().data(), stringMode.asString().data());

        return true;
    }

    CodePoint UFileDevice::readCodePoint() {
        auto byte = StaticCast<Byte>(std::fgetc(_file));

        auto size = Conversions::UTF8SymbolSize(byte);

        if (!size) {
            return InvalidCodePoint;
        }

        Vector<Byte> bytes;

        bytes.emplace_back(byte);

        for (auto i = 1; i < size; ++i) {
            bytes.emplace_back(std::fgetc(_file));
        }

        auto error = ConversionError::NullError;

        auto codePoint = Conversions::DecodeUTF8(bytes, error);

        if (error != ConversionError::NullError) {
            return InvalidCodePoint;
        }

        return codePoint;
    }

    Void UFileDevice::writeCodePoint(CodePoint codePoint) {
        auto error = ConversionError::NullError;

        auto bytes = Conversions::EncodeUTF8(codePoint, error);

        if (error != ConversionError::NullError) {
            return;
        }

        for (auto &byte : bytes) {
            std::fputc(byte, _file);
        }
    }

    UFileStream::UFileStream(Ptr<UFileDevice> device)
            : _file(*device) {}

    UFileStream::UFileStream(ConstLRef<UString> fileName, ConstLRef<FileOpenMode> mode)
            : _file(nullptr) {
        _file.open(fileName, mode);
    }

    Bool UFileStream::open(ConstLRef<UString> fileName, ConstLRef<FileOpenMode> mode) {
        return _file.open(fileName, mode);
    }

    CodePoint UFileStream::readCodePoint() {
        return _file.readCodePoint();
    }

    Void UFileStream::writeCodePoint(CodePoint codePoint) {
        _file.writeCodePoint(codePoint);
    }

    LRef<UStream> UFileStream::operator>>(LRef<CodePoint> codePoint) {
        codePoint = readCodePoint();

        return *this;
    }

    LRef<UStream> UFileStream::operator<<(CodePoint codePoint) {
        writeCodePoint(codePoint);

        return *this;
    }

    Ptr<UFileDevice> COutDevice;
    Ptr<UFileDevice> CErrDevice;
    Ptr<UFileDevice> CInDevice;

    Ptr<UFileStream> COutStream;
    Ptr<UFileStream> CErrStream;
    Ptr<UFileStream> CInStream;

    class UIOInit {
    public:

        UIOInit() {
#if defined(GS_OS_WINDOWS)
            _codePage = Windows::GetConsoleCP();

            Windows::SetConsoleCP(CP_UTF8);
            Windows::SetConsoleOutputCP(CP_UTF8);
#endif
            COutDevice = new UFileDevice(stdout);
            CErrDevice = new UFileDevice(stderr);
            CInDevice = new UFileDevice(stdin);

            COutStream = new UFileStream(COutDevice);
            CErrStream = new UFileStream(CErrDevice);
            CInStream = new UFileStream(CInDevice);
        }

    public:

        ~UIOInit() {
            delete COutStream;
            delete CErrStream;
            delete CInStream;

            delete COutDevice;
            delete CErrDevice;
            delete CInDevice;

#if defined(GS_OS_WINDOWS)
            Windows::SetConsoleOutputCP(_codePage);
            Windows::SetConsoleCP(_codePage);
#endif
        }

    private:

#if defined(GS_OS_WINDOWS)
        Windows::UINT _codePage;
#endif
    };

    UIOInit Init;

    LRef<UStream> UCOut() {
        return *COutStream;
    }

    LRef<UStream> UCErr() {
        return *CErrStream;
    }

    LRef<UStream> UCIn() {
        return *CInStream;
    }
}
