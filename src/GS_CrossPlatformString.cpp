#include <GSCrossPlatform/GS_CrossPlatformUtils.h>

#include <GSCrossPlatform/GS_CrossPlatformString.h>

namespace CrossPlatform {

    USymbol::USymbol(CodePoint codePoint)
            : _codePoint(codePoint) {}

    CodePoint USymbol::getCodePoint() {
        return _codePoint;
    }

    UString::UString() = default;

    UString::UString(const C32 *string) {
        for (U64 index = 0; string[index] != 0; ++index) {
            _symbols.emplace_back(USymbol((I32) string[index]));
        }
    }

    Void UString::append(USymbol symbol) {
        _symbols.emplace_back(symbol);
    }

    Vector<Byte> UString::asBytes() {
        Vector<Byte> bytes;

        for (auto &symbol : _symbols) {
            auto codePoint = symbol.getCodePoint();

            ConversionError error = ConversionError::NullError;

            auto utf8bytes = Conversions::EncodeUTF8(codePoint, error);

            if (error != ConversionError::NullError) {
                return InvalidBytes;
            }

            for (auto &byte : utf8bytes) {
                bytes.emplace_back(byte);
            }
        }

        bytes.emplace_back(0);

        return bytes;
    }

    Vector<USymbol> UString::getSymbols() {
        return _symbols;
    }

}
