#include <unicode/uchar.h>

#include <GSCrossPlatform/Encoding.h>

#include <GSCrossPlatform/Containers/String.h>

namespace CrossPlatform {

    USymbol::USymbol(ConstLRef<CodePoint> codePoint)
            : _codePoint(codePoint) {}

    USymbol::USymbol(ConstLRef<C32> symbol)
            : _codePoint(symbol) {}

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

    CodePoint USymbol::GetCodePoint() const {
        return _codePoint;
    }

    Bool USymbol::operator==(ConstLRef<USymbol> symbol) const {
        return _codePoint == symbol.GetCodePoint();
    }

    UString::UString() = default;

    UString::UString(ConstPtr<C32> string) {
        for (U64 index = 0; string[index] != 0; ++index) {
            _symbols.emplace_back(CCast<CodePoint>(string[index]));
        }
    }

    UString::UString(ConstPtr<C32> string, U64 size) {
        for (U64 index = 0; index < size && string[index] != 0; ++index) {
            _symbols.emplace_back(CCast<CodePoint>(string[index]));
        }
    }

    UString::UString(ConstLRef<UString> string)
            : _symbols(string.GetSymbols()) {}

    UString::UString(RRef<UString> string)
            : _symbols(string.GetSymbols()) {}

    Void UString::Append(ConstLRef<USymbol> symbol) {
        _symbols.emplace_back(symbol);
    }

    U64 UString::Size() const {
        return _symbols.size();
    }

    Bool UString::Empty() {
        return Size() == 0;
    }

    Vector<Byte> UString::AsBytes() const {
        Vector<Byte> bytes;

        for (auto &symbol : _symbols) {
            auto codePoint = symbol.GetCodePoint();

            for (auto &byte : Conversions::Encode(codePoint, Encoding::UTF8)) {
                bytes.emplace_back(byte);
            }
        }

        return bytes;
    }

    String UString::AsString() const {
        String string;

        for (auto &byte : AsBytes()) {
            string += StaticCast<StringCharType>(byte);
        }

        return string;
    }

    Vector<Byte> UString::AsCStringBytes() const {
        auto bytes = AsBytes();

        bytes.emplace_back(0);

        return bytes;
    }

    Vector<USymbol> UString::GetSymbols() const {
        return _symbols;
    }

    LRef<UString> UString::operator=(ConstLRef<UString> string) {
        if (&string == this) {
            return *this;
        }

        _symbols = string.GetSymbols();

        return *this;
    }

    LRef<UString> UString::operator=(RRef<UString> string) {
        if (&string == this) {
            return *this;
        }

        _symbols = string.GetSymbols();

        return *this;
    }

    LRef<UString> UString::operator+=(ConstLRef<USymbol> symbol) {
        Append(symbol);

        return *this;
    }

    LRef<UString> UString::operator+=(ConstLRef<UString> string) {
        if (&string == this) {
            return *this;
        }

        for (auto &symbol : string.GetSymbols()) {
            Append(symbol);
        }

        return *this;
    }

    LRef<UString> UString::operator+(ConstLRef<UString> string) {
        for (auto &symbol : string.GetSymbols()) {
            Append(symbol);
        }

        return *this;
    }

    LRef<USymbol> UString::operator[](ConstLRef<U64> index) {
        return _symbols[index];
    }

    ConstLRef<USymbol> UString::operator[](ConstLRef<U64> index) const {
        return _symbols[index];
    }

    Bool UString::operator==(ConstLRef<UString> string) const {
        if (Size() != string.Size()) {
            return false;
        }

        for (U64 index = 0; index < Size(); ++index) {
            if (_symbols[index] != string[index]) {
                return false;
            }
        }

        return true;
    }

    auto UString::operator<=>(ConstLRef<UString> string) const {
        return Size() <=> string.Size();
    }

    UString::Iterator UString::begin() {
        return UStringIterator(_symbols.data());
    }

    UString::Iterator UString::end() {
        return UStringIterator(_symbols.data() + Size());
    }

}
