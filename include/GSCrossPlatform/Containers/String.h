#ifndef GSCROSSPLATFORM_STRING_H
#define GSCROSSPLATFORM_STRING_H

#include <GSCrossPlatform/Utils/Types.h>

//#include <GSCrossPlatform/Containers/Iterator.h>

namespace CrossPlatform {

    class USymbol {
    public:

        USymbol();

        USymbol(ConstLRef<CodePoint> codePoint);

    public:

        USymbol(ConstLRef<USymbol> symbol);

        USymbol(RRef<USymbol> symbol) noexcept;

    public:

        Bool IsAlpha() const;

        Bool IsDigit() const;

        Bool IsWhitespace() const;

        Bool IsIDStart() const;

        Bool IsIDContinue() const;

    public:

        Vector<Byte> AsUTF8() const;

        Vector<Byte> AsUTF16() const;

        Vector<Byte> AsUTF32() const;

    public:

        CodePoint GetCodePoint() const;

    public:

        LRef<USymbol> operator=(ConstLRef<USymbol> symbol);

        LRef<USymbol> operator=(RRef<USymbol> symbol) noexcept;

        Bool operator==(ConstLRef<USymbol> symbol) const;

        Bool operator!=(ConstLRef<USymbol> symbol) const;

        auto operator<=>(ConstLRef<USymbol> symbol) const;

    private:

        CodePoint _codePoint;
    };

    class UString {
    public:

        using Iterator = Vector<USymbol>::const_iterator;

        using ConstIterator = Vector<USymbol>::iterator;

    public:

        using iterator = Iterator;

        using const_iterator = ConstIterator;

    public:

        UString();

        UString(Vector<USymbol> symbols);

        UString(ConstPtr<char> string);

#if defined(__cpp_lib_char8_t)

        UString(ConstPtr<char8_t> string);

#endif

        UString(ConstPtr<char16_t> string);

        UString(ConstPtr<char32_t> string);

        UString(ConstLRef<std::string> string);

#if defined(__cpp_lib_char8_t)

        UString(ConstLRef<std::u8string> string);

#endif

        UString(ConstLRef<std::u16string> string);

        UString(ConstLRef<std::u32string> string);

    public:

        UString(ConstLRef<UString> string);

        UString(RRef<UString> string) noexcept;

    public:

        LRef<UString> Append(ConstLRef<USymbol> symbol);

    public:

        U64 Size() const;

        Bool Empty() const;

    public:

        std::string AsUTF8String() const;

        std::u16string AsUTF16String() const;

        std::u32string AsUTF32String() const;

    public:

        Vector<USymbol> GetSymbols() const;

    public:

        Iterator begin();

        Iterator end();

        ConstIterator begin() const;

        ConstIterator end() const;

    public:

        LRef<UString> operator=(ConstLRef<UString> string);

        LRef<UString> operator=(RRef<UString> string) noexcept;

        LRef<UString> operator+=(ConstLRef<USymbol> symbol);

        LRef<UString> operator+=(ConstLRef<UString> string);

        UString operator+(ConstLRef<USymbol> symbol) const;

        UString operator+(ConstLRef<UString> string) const;

        Bool operator==(ConstLRef<UString> string) const;

        Bool operator!=(ConstLRef<UString> string) const;

        auto operator<=>(ConstLRef<UString> string) const;

        LRef<USymbol> operator[](ConstLRef<U64> index);

        ConstLRef<USymbol> operator[](ConstLRef<U64> index) const;

    private:

        Vector<USymbol> _symbols;
    };

    inline UString operator""_us(ConstPtr<char> text, U64 size) {
        return UString(text);
    }

#if defined(__cpp_lib_char8_t)

    inline UString operator""_us(ConstPtr<char8_t> text, U64 size) {
        return UString(text);
    }

#endif

    inline UString operator""_us(ConstPtr<char16_t> text, U64 size) {
        return UString(text);
    }

    inline UString operator""_us(ConstPtr<char32_t> text, U64 size) {
        return UString(text);
    }

    LRef<std::istream> operator>>(LRef<std::istream> stream, LRef<UString> string);

    LRef<std::ostream> operator<<(LRef<std::ostream> stream, ConstLRef<UString> string);

}

#endif //GSCROSSPLATFORM_STRING_H
