#include <unicode/uchar.h>

#include <GSCrossPlatform/GS_CrossPlatformString.h>

namespace CrossPlatform {

    USymbol::USymbol(ConstLRef<CodePoint> codePoint)
            : _codePoint(codePoint) {}

    CodePoint USymbol::getCodePoint() const {
        return _codePoint;
    }

    Bool IsDigit(ConstLRef<USymbol> symbol) {
        return u_isdigit(StaticCast<UChar32>(symbol.getCodePoint()));
    }

    Bool IsAlpha(ConstLRef<USymbol> symbol) {
        return u_isalpha(StaticCast<UChar32>(symbol.getCodePoint()));
    }

    Bool IsIDStart(ConstLRef<USymbol> symbol) {
        return u_isIDStart(StaticCast<UChar32>(symbol.getCodePoint()));
    }

    Bool IsIDContinue(ConstLRef<USymbol> symbol) {
        return u_isIDPart(StaticCast<UChar32>(symbol.getCodePoint()));
    }

    UString::UString() = default;

    UString::UString(ConstPtr<C32> string) {
        for (U64 index = 0; string[index] != 0; ++index) {
            _symbols.emplace_back(CCast<CodePoint>(string[index]));
        }
    }

    Void UString::append(ConstLRef<USymbol> symbol) {
        _symbols.emplace_back(symbol);
    }

    Vector<Byte> UString::asBytes() const {
        Vector<Byte> bytes;

        for (auto &symbol : _symbols) {
            auto codePoint = symbol.getCodePoint();

            auto error = ConversionError::NullError;

            auto utf8bytes = Conversions::EncodeUTF8(codePoint, error);

            if (error != ConversionError::NullError) {
                return InvalidBytes;
            }

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

    Vector<USymbol> UString::getSymbols() const {
        return _symbols;
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

    Bool UString::operator==(ConstLRef<UString> string) const {
        return _symbols.size() == string.getSymbols().size();
    }

    auto UString::operator<=>(ConstLRef<UString> string) const {
        return _symbols.size() <=> string.getSymbols().size();
    }

}
