#ifndef GSCROSSPLATFORM_USTRING_H
#define GSCROSSPLATFORM_USTRING_H

#include <unicode/uchar.h>

#include <GSCrossPlatform/Encoding.h>

class USymbol {
public:

    constexpr USymbol()
            : _codePoint(InvalidCodePoint) {}

    constexpr USymbol(ConstLRef<U32> codePoint)
            : _codePoint(codePoint) {}

public:

    constexpr USymbol(ConstLRef<USymbol> symbol)
            : _codePoint(symbol._codePoint) {}

    constexpr USymbol(RRef<USymbol> symbol) noexcept
            : _codePoint(symbol._codePoint) {}

public:

    inline Bool IsAlpha() const {
        return u_isalpha(StaticCast<UChar32>(_codePoint));
    }

    inline Bool IsDigit() const {
        return u_isdigit(StaticCast<UChar32>(_codePoint));
    }

    inline Bool IsWhitespace() const {
        return u_isspace(StaticCast<UChar32>(_codePoint));
    }

    inline Bool IsIDStart() const {
        return u_isIDStart(StaticCast<UChar32>(_codePoint));
    }

    inline Bool IsIDContinue() const {
        return u_isIDPart(StaticCast<UChar32>(_codePoint));
    }

public:

    inline constexpr Vector<U8> AsUTF8() const {
        auto bytes = ToUTF8(_codePoint);

        return bytes;
    }

    inline constexpr Vector<U8> AsUTF16() const {
        auto bytes = ToUTF16(_codePoint);

        return bytes;
    }

    inline constexpr Vector<U8> AsUTF32() const {
        auto bytes = ToUTF32(_codePoint);

        return bytes;
    }

public:

    inline constexpr U32 CodePoint() const {
        return _codePoint;
    }

public:

    inline constexpr LRef<USymbol> operator=(ConstLRef<USymbol> symbol) {
        if (this == &symbol) {
            return *this;
        }

        _codePoint = symbol._codePoint;

        return *this;
    }

    inline constexpr LRef<USymbol> operator=(RRef<USymbol> symbol) noexcept {
        if (this == &symbol) {
            return *this;
        }

        _codePoint = symbol._codePoint;

        return *this;
    }

    inline constexpr Bool operator==(ConstLRef<USymbol> symbol) const {
        return _codePoint == symbol._codePoint;
    }

    inline constexpr Bool operator!=(ConstLRef<USymbol> symbol) const {
        return !(*this == symbol);
    }

private:

    U32 _codePoint;
};

class UString {
public:

    using Iterator = Vector<USymbol>::Iterator;

    using ConstIterator = Vector<USymbol>::ConstIterator;

public:

    constexpr UString() = default;

    constexpr UString(Vector<USymbol> symbols)
            : _symbols(std::move(symbols)) {}

    constexpr UString(ConstPtr<C> string) {
        for (U64 index = 0; string[index] != 0; ++index) {
            auto byte = StaticCast<U8>(string[index]);

            auto symbolSize = UTF8Size(byte);

            Vector<U8> bytes;

            bytes.Append(byte);

            for (U64 i = 1; i < symbolSize; ++i) {
                ++index;

                byte = StaticCast<U8>(string[index]);

                bytes.Append(byte);
            }

            auto codePoint = FromUTF8(bytes);

            _symbols.Append(USymbol(codePoint));
        }
    }

#if defined(__cpp_lib_char8_t)

    constexpr UString(ConstPtr<C8> string)
            : UString(ReinterpretCast<ConstPtr<C>>(string)) {}

#endif

    // TODO add supporting UTF-16 strings
    constexpr UString(ConstPtr<C16> string);

    constexpr UString(ConstPtr<C32> string) {
        for (U64 index = 0; string[index] != 0; ++index) {
            _symbols.Append(USymbol(StaticCast<U32>(string[index])));
        }
    }

    constexpr UString(ConstLRef<std::string> string)
            : UString(string.c_str()) {}

#if defined(__cpp_lib_char8_t)

    constexpr UString(ConstLRef<std::u8string> string)
            : UString(string.c_str()) {}

#endif

    constexpr UString(ConstLRef<std::u16string> string)
            : UString(string.c_str()) {}

    constexpr UString(ConstLRef<std::u32string> string)
            : UString(string.c_str()) {}

public:

    constexpr UString(ConstLRef<UString> string)
            : _symbols(string._symbols) {}

    constexpr UString(RRef<UString> string) noexcept
            : _symbols(std::move(string._symbols)) {}

public:

    inline constexpr LRef<UString> Append(ConstLRef<USymbol> symbol) {
        _symbols.Append(symbol);

        return *this;
    }

    inline constexpr Void Clear() {
        _symbols.Clear();
    }

public:

    inline constexpr U64 Size() const {
        return _symbols.Size();
    }

    inline constexpr Bool Empty() const {
        return _symbols.Empty();
    }

public:

    inline std::string AsUTF8() const {
        std::string string;

        for (auto &symbol : _symbols) {
            for (auto &byte : ToUTF8(symbol.CodePoint())) {
                string += StaticCast<C>(byte);
            }
        }

        return string;
    }

    inline std::u16string AsUTF16() const {
        std::u16string u16string;

        // ...

        return u16string;
    }

    inline std::u32string AsUTF32() const {
        std::u32string u32string;

        for (auto &symbol : _symbols) {
            u32string += StaticCast<C32>(symbol.CodePoint());
        }

        return u32string;
    }

public:

    inline constexpr Iterator begin() {
        return _symbols.begin();
    }

    inline constexpr Iterator end() {
        return _symbols.end();
    }

    inline constexpr ConstIterator begin() const {
        return _symbols.begin();
    }

    inline constexpr ConstIterator end() const {
        return _symbols.end();
    }

public:

    inline constexpr LRef<UString> operator=(ConstLRef<UString> string) {
        if (this == &string) {
            return *this;
        }

        _symbols = string._symbols;

        return *this;
    }

    inline constexpr LRef<UString> operator=(RRef<UString> string) noexcept {
        if (this == &string) {
            return *this;
        }

        _symbols = std::move(string._symbols);

        return *this;
    }

    inline constexpr LRef<UString> operator+=(ConstLRef<USymbol> symbol) {
        _symbols.Append(symbol);

        return *this;
    }

    inline constexpr LRef<UString> operator+=(ConstLRef<UString> string) {
        for (auto &symbol : string) {
            _symbols.Append(symbol);
        }

        return *this;
    }

    inline constexpr UString operator+(ConstLRef<USymbol> symbol) const {
        UString outputString;

        outputString += *this;

        outputString += symbol;

        return outputString;
    }

    inline constexpr UString operator+(ConstLRef<UString> string) const {
        UString outputString;

        outputString += *this;

        outputString += string;

        return outputString;
    }

    inline constexpr Bool operator==(ConstLRef<UString> string) const {
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

    inline constexpr Bool operator!=(ConstLRef<UString> string) const {
        return !(*this == string);
    }

    inline constexpr auto operator<=>(ConstLRef<UString> string) const {
        return Size() <=> string.Size();
    }

    inline constexpr LRef<USymbol> operator[](ConstLRef<U64> index) {
        return _symbols[index];
    }

    inline constexpr ConstLRef<USymbol> operator[](ConstLRef<U64> index) const {
        return _symbols[index];
    }

private:

    Vector<USymbol> _symbols;
};

inline constexpr UString operator""_us(ConstPtr<C> string, U64 size) {
    return UString(string);
}

#if defined(__cpp_lib_char8_t)

inline constexpr UString operator""_us(ConstPtr<C8> string, U64 size) {
    return UString(string);
}

#endif

inline constexpr UString operator""_us(ConstPtr<C16> string, U64 size) {
    return UString(string);
}

inline constexpr UString operator""_us(ConstPtr<C32> string, U64 size) {
    return UString(string);
}

#endif //GSCROSSPLATFORM_USTRING_H
