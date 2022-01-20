#include <unicode/uchar.h>

#include <GSCrossPlatform/GS_CrossPlatformUnicodeConversions.h>

#include <GSCrossPlatform/GS_CrossPlatformString.h>

namespace CrossPlatform {

    USymbol::USymbol(ConstLRef<CodePoint> codePoint)
            : _codePoint(codePoint) {}

    USymbol::USymbol(ConstLRef<C32> symbol)
            : _codePoint(symbol) {}

    Bool USymbol::isAlpha() const {
        return u_isalpha(StaticCast<UChar32>(_codePoint));
    }

    Bool USymbol::isDigit() const {
        return u_isdigit(StaticCast<UChar32>(_codePoint));
    }

    Bool USymbol::isWhitespace() const {
        return u_isspace(StaticCast<UChar32>(_codePoint));
    }

    Bool USymbol::isIDStart() const {
        return u_isIDStart(StaticCast<UChar32>(_codePoint));
    }

    Bool USymbol::isIDContinue() const {
        return u_isIDPart(StaticCast<UChar32>(_codePoint));
    }

    CodePoint USymbol::getCodePoint() const {
        return _codePoint;
    }

    Bool USymbol::operator==(ConstLRef<USymbol> symbol) const {
        return _codePoint == symbol.getCodePoint();
    }

    UString::UString() = default;

    UString::UString(ConstPtr<C32> string) {
        for (U64 index = 0; string[index] != 0; ++index) {
            _symbols.emplace_back(CCast<CodePoint>(string[index]));
        }
    }

    UString::UString(ConstLRef<UString> string)
            : _symbols(string.getSymbols()) {}

    UString::UString(RRef<UString> string)
            : _symbols(string.getSymbols()) {}

    Void UString::append(ConstLRef<USymbol> symbol) {
        _symbols.emplace_back(symbol);
    }

    U64 UString::size() const {
        return _symbols.size();
    }

    Bool UString::empty() {
        return size() == 0;
    }

    Vector<Byte> UString::asBytes() const {
        Vector<Byte> bytes;

        for (auto &symbol : _symbols) {
            auto codePoint = symbol.getCodePoint();

            auto utf8bytes = Conversions::Encode(codePoint, Encoding::UTF8, ByteEndian::Unknown);

            for (auto &byte : utf8bytes) {
                bytes.emplace_back(byte);
            }
        }

        return bytes;
    }

    String UString::asString() const {
        String string;

        for (auto &byte : asBytes()) {
            string += StaticCast<StringCharType>(byte);
        }

        return string;
    }

    Vector<Byte> UString::asCStringBytes() const {
        auto bytes = asBytes();

        bytes.emplace_back(0);

        return bytes;
    }

    Vector<USymbol> UString::getSymbols() const {
        return _symbols;
    }

    LRef<UString> UString::operator=(ConstLRef<UString> string) {
        if (&string == this) {
            return *this;
        }

        _symbols = string.getSymbols();

        return *this;
    }

    LRef<UString> UString::operator=(RRef<UString> string) {
        if (&string == this) {
            return *this;
        }

        _symbols = string.getSymbols();

        return *this;
    }

    LRef<UString> UString::operator+=(ConstLRef<USymbol> symbol) {
        append(symbol);

        return *this;
    }

    LRef<UString> UString::operator+=(ConstLRef<UString> string) {
        if (&string == this) {
            return *this;
        }

        for (auto &symbol : string.getSymbols()) {
            append(symbol);
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
        if (size() != string.size()) {
            return false;
        }

        for (U64 index = 0; index < size(); ++index) {
            if (_symbols[index] != string[index]) {
                return false;
            }
        }

        return true;
    }

    auto UString::operator<=>(ConstLRef<UString> string) const {
        return size() <=> string.size();
    }

    UString::IteratorT UString::begin() {
        return UStringIterator(_symbols.data());
    }

    UString::IteratorT UString::end() {
        return UStringIterator(_symbols.data() + size());
    }

}
