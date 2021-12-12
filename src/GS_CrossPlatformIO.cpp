#include <GSCrossPlatform/GS_CrossPlatformString.h>

#include <GSCrossPlatform/GS_CrossPlatformIO.h>

#if defined(GS_OS_WINDOWS)
    #if defined(GS_COMPILER_MSVC)
        #include <Windows.h>
    #elif defined(GS_COMPILER_MINGW)
        #include <windows.h>
    #endif
#endif

namespace CrossPlatform {

    UDevice::~UDevice() = default;

    UStream::~UStream() = default;

    UFileDevice::UFileDevice(FILE *file)
            : _file(file) {}

    Byte UFileDevice::readByte() {
        return std::fgetc(_file);
    }

    Void UFileDevice::writeByte(Byte byte) {
        std::fputc(byte, _file);
    }

    UFileStream::UFileStream(UFileDevice *device)
            : _device(device) {}

    Byte UFileStream::readByte() {
        return _device->readByte();
    }

    Void UFileStream::writeByte(Byte byte) {
        _device->writeByte(byte);
    }

    CodePoint UFileStream::readCodePoint() {
        auto byte = _device->readByte();

        auto size = Conversions::UTF8SymbolSize(byte);

        if (!size) {
            return InvalidCodePoint;
        }

        Vector<Byte> bytes;

        bytes.emplace_back(byte);

        for (auto i = 1; i < size; ++i) {
            bytes.emplace_back(_device->readByte());
        }

        ConversionError error = ConversionError::NullError;

        auto codePoint = Conversions::Decode(bytes, Encoding::UTF8, error);

        if (error != ConversionError::NullError) {
            return InvalidCodePoint;
        }

        return codePoint;
    }

    Void UFileStream::writeCodePoint(CodePoint codePoint) {
        ConversionError error = ConversionError::NullError;

        auto bytes = Conversions::Encode(codePoint, Encoding::UTF8, error);

        if (error != ConversionError::NullError) {
            return;
        }

        for (auto &byte : bytes) {
            _device->writeByte(byte);
        }
    }

    UFileDevice *COutDevice;
    UFileDevice *CErrDevice;
    UFileDevice *CInDevice;

    UFileStream *COutStream;
    UFileStream *CErrStream;
    UFileStream *CInStream;

    class UIOInit {
    public:

        UIOInit() {
#if defined(GS_OS_WINDOWS)
            _codePage = GetConsoleCP();

            SetConsoleCP(CP_UTF8);
            SetConsoleOutputCP(CP_UTF8);
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
            SetConsoleOutputCP(_codePage);
            SetConsoleCP(_codePage);
#endif
        }

    private:

#if defined(GS_OS_WINDOWS)
        UINT _codePage;
#endif
    };

    UIOInit Init;

    UStream &COut() {
        return *COutStream;
    }

    UStream &CErr() {
        return *CErrStream;
    }

    UStream &CIn() {
        return *CInStream;
    }

}
