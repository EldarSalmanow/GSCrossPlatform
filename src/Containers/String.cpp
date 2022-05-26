#include <unicode/uchar.h>

#include <GSCrossPlatform/Encoding.h>

#include <GSCrossPlatform/Containers/String.h>

namespace CrossPlatform {

//    USymbol::USymbol(ConstLRef<CodePoint> codePoint)
//            : _codePoint(codePoint) {}
//
//    USymbol::USymbol(ConstLRef<C32> symbol)
//            : _codePoint(symbol) {}
//
//    Bool USymbol::IsAlpha() const {
//        return u_isalpha(StaticCast<UChar32>(_codePoint));
//    }
//
//    Bool USymbol::IsDigit() const {
//        return u_isdigit(StaticCast<UChar32>(_codePoint));
//    }
//
//    Bool USymbol::IsWhitespace() const {
//        return u_isspace(StaticCast<UChar32>(_codePoint));
//    }
//
//    Bool USymbol::IsIDStart() const {
//        return u_isIDStart(StaticCast<UChar32>(_codePoint));
//    }
//
//    Bool USymbol::IsIDContinue() const {
//        return u_isIDPart(StaticCast<UChar32>(_codePoint));
//    }
//
//    CodePoint USymbol::GetCodePoint() const {
//        return _codePoint;
//    }
//
//    Bool USymbol::operator==(ConstLRef<USymbol> symbol) const {
//        return _codePoint == symbol.GetCodePoint();
//    }

    USymbol::USymbol()
            : _codePoint(InvalidCodePoint) {}

    USymbol::USymbol(ConstLRef<CodePoint> codePoint)
            : _codePoint(codePoint) {}

    USymbol::USymbol(ConstLRef<USymbol> symbol)
            : _codePoint(symbol._codePoint) {}

    USymbol::USymbol(RRef<USymbol> symbol) noexcept
            : _codePoint(symbol._codePoint) {}

    Bool USymbol::IsAlpha() const {
        return u_isalpha(StaticCast<UChar32>(_codePoint));
    }

    Bool USymbol::IsDigit() const {
        return u_isdigit(StaticCast<UChar32>(_codePoint));
    }

    Bool USymbol::IsWhitespace() const {
        return u_isspace(StaticCast<UChar32>(_codePoint));
    }

    Bool USymbol::IsIDStart() const {
        return u_isIDStart(StaticCast<UChar32>(_codePoint));
    }

    Bool USymbol::IsIDContinue() const {
        return u_isIDPart(StaticCast<UChar32>(_codePoint));
    }

    Vector<Byte> USymbol::AsUTF8() const {
        auto bytes = ToUTF8(_codePoint);

        return bytes;
    }

    Vector<Byte> USymbol::AsUTF16() const {
        auto bytes = ToUTF16(_codePoint);

        return bytes;
    }

    Vector<Byte> USymbol::AsUTF32() const {
        auto bytes = ToUTF32(_codePoint);

        return bytes;
    }

    CodePoint USymbol::GetCodePoint() const {
        return _codePoint;
    }

    LRef<USymbol> USymbol::operator=(ConstLRef<USymbol> symbol) {
        if (this == &symbol) {
            return *this;
        }

        _codePoint = symbol._codePoint;

        return *this;
    }

    LRef<USymbol> USymbol::operator=(RRef<USymbol> symbol) noexcept {
        if (this == &symbol) {
            return *this;
        }

        _codePoint = symbol._codePoint;

        return *this;
    }

    Bool USymbol::operator==(ConstLRef<USymbol> symbol) const {
        return GetCodePoint() == symbol.GetCodePoint();
    }

    Bool USymbol::operator!=(ConstLRef<USymbol> symbol) const {
        return !(*this == symbol);
    }

    auto USymbol::operator<=>(ConstLRef<USymbol> symbol) const {
        return _codePoint <=> symbol.GetCodePoint();
    }

    UString::UString() = default;

    UString::UString(Vector<USymbol> symbols)
            : _symbols(std::move(symbols)) {}

    UString::UString(ConstPtr<char> string) {
        for (U64 index = 0; string[index] != 0; ++index) {
            auto byte = StaticCast<Byte>(string[index]);

            auto symbolSize = UTF8Size(byte);

            Vector<Byte> bytes;

            bytes.emplace_back(byte);

            for (U64 i = 1; i < symbolSize; ++i) {
                ++index;

                byte = StaticCast<Byte>(string[index]);

                bytes.emplace_back(byte);
            }

            auto codePoint = FromUTF8(bytes);

            _symbols.emplace_back(USymbol(codePoint));
        }
    }

#if defined(__cpp_lib_char8_t)

    UString::UString(ConstPtr<char8_t> string)
            : UString(ReinterpretCast<ConstPtr<char>>(string)) {}

#endif

    UString::UString(ConstPtr<char16_t> string) {
        // TODO add supporting UTF-16 strings
    }

    UString::UString(ConstPtr<char32_t> string) {
        for (U64 index = 0; string[index] != 0; ++index) {
            _symbols.emplace_back(USymbol(StaticCast<CodePoint>(string[index])));
        }
    }

    UString::UString(ConstLRef<std::string> string)
            : UString(string.c_str()) {}

#if defined(__cpp_lib_char8_t)

    UString::UString(ConstLRef<std::u8string> string)
                : UString(string.c_str()) {}

#endif

    UString::UString(ConstLRef<std::u16string> string)
            : UString(string.c_str()) {}

    UString::UString(ConstLRef<std::u32string> string)
            : UString(string.c_str()) {}

    UString::UString(ConstLRef<UString> string)
            : _symbols(string._symbols) {}

    UString::UString(RRef<UString> string) noexcept
            : _symbols(std::move(string._symbols)) {}

    LRef<UString> UString::Append(ConstLRef<USymbol> symbol) {
        _symbols.emplace_back(symbol);

        return *this;
    }

    U64 UString::Size() const {
        return _symbols.size();
    }

    Bool UString::Empty() const {
        return _symbols.empty();
    }

    std::string UString::AsUTF8String() const {
        std::string string;

        for (auto &symbol : *this) {
            auto codePoint = symbol.GetCodePoint();

            for (auto &byte : ToUTF8(codePoint)) {
                string += StaticCast<char>(byte);
            }
        }

        return string;
    }

    std::u16string UString::AsUTF16String() const {
        std::u16string u16string;

        // ...

        return u16string;
    }

    std::u32string UString::AsUTF32String() const {
        std::u32string u32string;

        for (auto &symbol : *this) {
            auto codePoint = symbol.GetCodePoint();

            u32string += StaticCast<char32_t>(codePoint);
        }

        return u32string;
    }

    Vector<USymbol> UString::GetSymbols() const {
        return _symbols;
    }

    UString::Iterator UString::begin() {
        return _symbols.begin();
    }

    UString::Iterator UString::end() {
        return _symbols.end();
    }

    UString::ConstIterator UString::begin() const {
        return _symbols.begin();
    }

    UString::ConstIterator UString::end() const {
        return _symbols.end();
    }

    LRef<UString> UString::operator=(ConstLRef<UString> string) {
        if (this == &string) {
            return *this;
        }

        _symbols = string._symbols;

        return *this;
    }

    LRef<UString> UString::operator=(RRef<UString> string) noexcept {
        if (this == &string) {
            return *this;
        }

        _symbols = std::move(string._symbols);

        return *this;
    }

    LRef<UString> UString::operator+=(ConstLRef<USymbol> symbol) {
        _symbols.emplace_back(symbol);

        return *this;
    }

    LRef<UString> UString::operator+=(ConstLRef<UString> string) {
        for (auto &symbol : string) {
            _symbols.emplace_back(symbol);
        }

        return *this;
    }

    UString UString::operator+(ConstLRef<USymbol> symbol) const {
        UString outputString;

        outputString += *this;

        outputString += symbol;

        return outputString;
    }

    UString UString::operator+(ConstLRef<UString> string) const {
        UString outputString;

        outputString += *this;

        outputString += string;

        return outputString;
    }

    Bool UString::operator==(ConstLRef<UString> string) const {
        if (Size() != string.Size()) {
            return false;
        }

        for (U64 index = 0; index < Size(); ++index) {
            if ((*this)[index] != string[index]) {
                return false;
            }
        }

        return true;
    }

    Bool UString::operator!=(ConstLRef<UString> string) const {
        return !(*this == string);
    }

    auto UString::operator<=>(ConstLRef<UString> string) const {
        return Size() <=> string.Size();
    }

    LRef<USymbol> UString::operator[](ConstLRef<U64> index) {
        return _symbols[index];
    }

    ConstLRef<USymbol> UString::operator[](ConstLRef<U64> index) const {
        return _symbols[index];
    }

    LRef<std::istream> operator>>(LRef<std::istream> stream, LRef<UString> string) {
        while (true) {
            auto byte = StaticCast<Byte>(stream.get());

            if (byte == '\n' || stream.eof()) {
                break;
            }

            auto symbolSize = UTF8Size(byte);

            Vector<Byte> bytes;

            bytes.emplace_back(byte);

            for (U64 i = 1; i < symbolSize; ++i) {
                byte = StaticCast<Byte>(stream.get());

                bytes.emplace_back(byte);
            }

            auto codePoint = FromUTF8(bytes);

            string.Append(USymbol(codePoint));
        }

        return stream;
    }

    LRef<std::ostream> operator<<(LRef<std::ostream> stream, ConstLRef<UString> string) {
        for (auto &symbol : string) {
            auto bytes = symbol.AsUTF8();

            for (auto &byte : bytes) {
                stream << byte;
            }
        }

        return stream;
    }

//    UString::UString() = default;
//
//    UString::UString(Vector<USymbol> symbols)
//            : _symbols(std::move(symbols)) {}
//
//    UString::UString(Vector<Byte> bytes) {
//        for (U64 index = 0; index < bytes.size(); ++index) {
//            Vector<Byte> symbolBytes;
//
//            auto byte = bytes[index];
//
//            auto size = Conversions::SymbolSizeUTF8(byte);
//
//            symbolBytes.emplace_back(byte);
//
//            for (U64 i = 1; i < size; ++i, ++index) {
//                symbolBytes.emplace_back(bytes[index]);
//            }
//
//            auto codePoint = Conversions::Decode(symbolBytes, Encoding::UTF8);
//
//            _symbols.emplace_back(codePoint);
//        }
//    }
//
//    UString::UString(ConstPtr<C32> string) {
//        for (U64 index = 0; string[index] != 0; ++index) {
//            _symbols.emplace_back(CCast<CodePoint>(string[index]));
//        }
//    }
//
//    UString::UString(ConstPtr<C8> string) {
//        Vector<Byte> bytes;
//
//        for (U64 index = 0; string[index] != 0; ++index) {
//            bytes.emplace_back(string[index]);
//        }
//
//        for (U64 index = 0; index < bytes.size(); ++index) {
//            Vector<Byte> symbolBytes;
//
//            auto byte = bytes[index];
//
//            auto size = Conversions::SymbolSizeUTF8(byte);
//
//            symbolBytes.emplace_back(byte);
//
//            for (U64 i = 1; i < size; ++i, ++index) {
//                symbolBytes.emplace_back(bytes[index]);
//            }
//
//            auto codePoint = Conversions::Decode(symbolBytes, Encoding::UTF8);
//
//            _symbols.emplace_back(codePoint);
//        }
//    }
//
//    UString::UString(String string)
//            : UString(string.data()) {}
//
//    UString::UString(ConstLRef<UString> string)
//            : _symbols(string.GetSymbols()) {}
//
//    UString::UString(RRef<UString> string)
//            : _symbols(string.GetSymbols()) {}
//
//    Void UString::Append(ConstLRef<USymbol> symbol) {
//        _symbols.emplace_back(symbol);
//    }
//
//    U64 UString::Size() const {
//        return _symbols.size();
//    }
//
//    Bool UString::Empty() {
//        return Size() == 0;
//    }
//
//    Vector<Byte> UString::AsBytes() const {
//        Vector<Byte> bytes;
//
//        for (auto &symbol : _symbols) {
//            auto codePoint = symbol.GetCodePoint();
//
//            for (auto &byte : Conversions::Encode(codePoint, Encoding::UTF8)) {
//                bytes.emplace_back(byte);
//            }
//        }
//
//        return bytes;
//    }
//
//    String UString::AsString() const {
//        String string;
//
//        for (auto &byte : AsBytes()) {
//            string += StaticCast<StringCharType>(byte);
//        }
//
//        return string;
//    }
//
//    Vector<Byte> UString::AsCStringBytes() const {
//        auto bytes = AsBytes();
//
//        bytes.emplace_back(0);
//
//        return bytes;
//    }
//
//    Vector<USymbol> UString::GetSymbols() const {
//        return _symbols;
//    }
//
//    LRef<UString> UString::operator=(ConstLRef<UString> string) {
//        if (&string == this) {
//            return *this;
//        }
//
//        _symbols = string.GetSymbols();
//
//        return *this;
//    }
//
//    LRef<UString> UString::operator=(RRef<UString> string) {
//        if (&string == this) {
//            return *this;
//        }
//
//        _symbols = string.GetSymbols();
//
//        return *this;
//    }
//
//    LRef<UString> UString::operator+=(ConstLRef<USymbol> symbol) {
//        Append(symbol);
//
//        return *this;
//    }
//
//    LRef<UString> UString::operator+=(ConstLRef<UString> string) {
//        if (&string == this) {
//            return *this;
//        }
//
//        for (auto &symbol : string.GetSymbols()) {
//            Append(symbol);
//        }
//
//        return *this;
//    }
//
//    UString UString::operator+(ConstLRef<UString> string) {
//        UString newString(*this);
//
//        for (auto &symbol : string.GetSymbols()) {
//            newString.Append(symbol);
//        }
//
//        return newString;
//    }
//
//    LRef<USymbol> UString::operator[](ConstLRef<U64> index) {
//        return _symbols[index];
//    }
//
//    ConstLRef<USymbol> UString::operator[](ConstLRef<U64> index) const {
//        return _symbols[index];
//    }
//
//    Bool UString::operator==(ConstLRef<UString> string) const {
//        if (Size() != string.Size()) {
//            return false;
//        }
//
//        for (U64 index = 0; index < Size(); ++index) {
//            if (_symbols[index] != string[index]) {
//                return false;
//            }
//        }
//
//        return true;
//    }
//
//    auto UString::operator<=>(ConstLRef<UString> string) const {
//        return Size() <=> string.Size();
//    }
//
//    UString::Iterator UString::begin() {
//        return UStringIterator(_symbols.data());
//    }
//
//    UString::Iterator UString::end() {
//        return UStringIterator(_symbols.data() + Size());
//    }

}
