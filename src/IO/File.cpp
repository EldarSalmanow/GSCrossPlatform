#include <GSCrossPlatform/Encoding.h>

#include <GSCrossPlatform/IO/File.h>

#if defined(GS_OS_WINDOWS)

    #include <Windows.h>

#endif

namespace CrossPlatform {

    File::File(Ptr<FILE> fileDescriptor)
            : _fileDescriptor(fileDescriptor) {}

    File::~File() {
        Close();
    }

    UniquePtr<File> File::Create() {
        return File::Create(nullptr);
    }

    UniquePtr<File> File::Create(Ptr<FILE> fileDescriptor) {
        auto file = new File(fileDescriptor);

        return std::unique_ptr<File>(file);
    }

    UniquePtr<File> File::Create(ConstLRef<UString> name, ConstLRef<OpenMode> mode) {
        UString stringOpenMode;

        if (mode & InMode) {
            stringOpenMode += U"r"_us;
        }

        if (mode & OutMode) {
            stringOpenMode += U"w"_us;
        }

        auto fileDescriptor = std::fopen(name.AsString().c_str(), stringOpenMode.AsString().c_str());

        if (!fileDescriptor) {
            return nullptr;
        }

        return File::Create(fileDescriptor);
    }

    USymbol File::ReadSymbol() {
        auto byte = StaticCast<Byte>(std::fgetc(_fileDescriptor));

        auto size = Conversions::SymbolSizeUTF8(byte);

        Vector<Byte> bytes;

        bytes.emplace_back(byte);

        for (auto i = 1; i < size; ++i) {
            bytes.emplace_back(StaticCast<Byte>(std::fgetc(_fileDescriptor)));
        }

        ConversionError error = ConversionError::NullError;

        return Conversions::Decode(bytes, Encoding::UTF8, error);
    }

    Void File::WriteSymbol(USymbol symbol) {
        ConversionError error = ConversionError::NullError;

        auto bytes = Conversions::Encode(symbol.GetCodePoint(), Encoding::UTF8, error);

        for (auto &byte : bytes) {
            std::fputc(byte, _fileDescriptor);
        }
    }

    UString File::Read(USymbol delimiter) {
        UString string;

        auto symbol = ReadSymbol();

        while (symbol != delimiter && !IsEOF()) {
            string += symbol;

            symbol = ReadSymbol();
        }

        return string;
    }

    Vector<UString> File::ReadText() {
        Vector<UString> text;

        while (!IsEOF()) {
            auto string = Read();

            text.emplace_back(string);
        }

        return text;
    }

    UString File::ReadInput() {
        UString input;

        while (!IsEOF()) {
            auto string = Read();

            string += U'\n';

            input += string;
        }

        return input;
    }

    Void File::Write(ConstLRef<UString> string) {
        for (auto &symbol : string.GetSymbols()) {
            WriteSymbol(symbol);
        }
    }

    Void File::Close() {
        if (_fileDescriptor) {
            std::fclose(_fileDescriptor);
        }
    }

    Bool File::IsEOF() {
        if (!std::feof(_fileDescriptor)) {
            return false;
        }

        return true;
    }

    LRef<File> File::operator>>(LRef<UString> string) {
        string = Read();

        return *this;
    }

    LRef<File> File::operator<<(ConstLRef<UString> string) {
        Write(string);

        return *this;
    }

    UniquePtr<File> _UCOut;
    UniquePtr<File> _UCErr;
    UniquePtr<File> _UCIn;

    LRef<File> UCOut() {
        return *_UCOut;
    }

    LRef<File> UCErr() {
        return *_UCErr;
    }

    LRef<File> UCIn() {
        return *_UCIn;
    }

    U32 CodePage::GetCodePage() {
#if defined(GS_OS_WINDOWS)

        return GetConsoleOutputCP();

#else

        return 0;

#endif
    }

    Void CodePage::SetCodePage(U32 codePage) {
#if defined(GS_OS_WINDOWS)

        SetConsoleOutputCP(codePage);

#endif
    }

    class IOInit {
    public:

        IOInit() {
            _UCOut = File::Create(stdout);
            _UCErr = File::Create(stderr);
            _UCIn = File::Create(stdin);

            _codePage = CodePage::GetCodePage();

#if defined(GS_OS_WINDOWS)

            CodePage::SetCodePage(CP_UTF8);

#endif
        }

    public:

        ~IOInit() {
            CodePage::SetCodePage(_codePage);

            _UCOut.reset();
            _UCErr.reset();
            _UCIn.reset();
        }

    private:

        U32 _codePage;
    };

    static IOInit Init;

}
