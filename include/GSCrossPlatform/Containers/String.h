#ifndef GSCROSSPLATFORM_STRING_H
#define GSCROSSPLATFORM_STRING_H

#include <GSCrossPlatform/Utils/Types.h>

//#include <GSCrossPlatform/Containers/Iterator.h>

namespace CrossPlatform {

//    /**
//     * Invalid unicode codepoint
//     */
//    inline Const<CodePoint> InvalidCodePoint = 0x10FFFF + 1;
//
//    /**
//     * Invalid unicode bytes
//     */
//    inline Const<Vector<Byte>> InvalidBytes = {};
//
//    /**
//     * Class for unicode symbol
//     */
//    class USymbol {
//    public:
//
//        /**
//         * Constructor for unicode symbol
//         * @param codePoint Unicode codepoint
//         */
//        USymbol(ConstLRef<CodePoint> codePoint);
//
//        /**
//         * Constructor for unicode symbol
//         * @param symbol Symbol
//         */
//        USymbol(ConstLRef<C32> symbol);
//
//    public:
//
//        /**
//         * Is alpha symbol
//         * @return Is alpha
//         */
//        Bool IsAlpha() const;
//
//        /**
//         * Is digit symbol
//         * @return Is digit
//         */
//        Bool IsDigit() const;
//
//        /**
//         * Is whitespace symbol
//         * @return Is whitespace
//         */
//        Bool IsWhitespace() const;
//
//        /**
//         * Is IDStart symbol
//         * @return Is IDStart
//         */
//        Bool IsIDStart() const;
//
//        /**
//         * Is IDContinue symbol
//         * @return Is IDContinue
//         */
//        Bool IsIDContinue() const;
//
//    public:
//
//        /**
//         * Getter for codepoint
//         * @return Codepoint
//         */
//        CodePoint GetCodePoint() const;
//
//    public:
//
//        /**
//         * Is equals symbols
//         * @param symbol Symbol
//         * @return Is equals
//         */
//        Bool operator==(ConstLRef<USymbol> symbol) const;
//
//    private:
//
//        /**
//         * Unicode codepoint
//         */
//        CodePoint _codePoint;
//    };

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

        using Iterator = Vector<USymbol>::iterator;

        using ConstIterator = Vector<USymbol>::const_iterator;

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

//    /**
//     * Defining UStringIterator
//     */
//    class UStringIterator;
//
//    /**
//     * Class for unicode string
//     */
//    class UString : public Iterable<UStringIterator> {
//    public:
//
//        /**
//         * Iterator type
//         */
//        using Iterator = typename Iterable<UStringIterator>::Iterator;
//
//    public:
//
//        /**
//         * Default unicode string constructor
//         */
//        UString();
//
//        /**
//         * Constructor for unicode string
//         * @param symbols Symbols
//         */
//        UString(Vector<USymbol> symbols);
//
//        /**
//         * Constructor for unicode string
//         * @param bytes Bytes
//         */
//        UString(Vector<Byte> bytes);
//
//        /**
//         * Constructor for unicode string
//         * @param string String
//         */
//        UString(ConstPtr<C32> string);
//
//        /**
//         * Constructor for unicode string
//         * @param string String
//         */
//        UString(ConstPtr<C8> string);
//
//        /**
//         * Constructor for unicode string
//         * @param string String
//         */
//        UString(String string);
//
//    public:
//
//        /**
//         * Copy constructor for unicode string
//         * @param string String
//         */
//        UString(ConstLRef<UString> string);
//
//        /**
//         * Move copy constructor for unicode string
//         * @param string String
//         */
//        UString(RRef<UString> string);
//
//    public:
//
//        /**
//         * Appending one unicode symbol to string
//         * @param symbol Unicode symbol
//         * @return
//         */
//        Void Append(ConstLRef<USymbol> symbol);
//
//        /**
//         * Size of unicode string
//         * @return Size of string
//         */
//        U64 Size() const;
//
//        /**
//         * Is empty unicode string
//         * @return Is empty string
//         */
//        Bool Empty();
//
//        /**
//         * Converting string to bytes
//         * @return String bytes
//         */
//        Vector<Byte> AsBytes() const;
//
//        /**
//         * Converting unicode string to standard string
//         * @return Standard string
//         */
//        String AsString() const;
//
//        /**
//         *
//         * @return
//         */
//        Vector<Byte> AsCStringBytes() const;
//
//    public:
//
//        /**
//         * Getter for unicode symbols
//         * @return Unicode symbols
//         */
//        Vector<USymbol> GetSymbols() const;
//
//    public:
//
//        /**
//         * Assignment operator for UString
//         * @param string String
//         * @return String
//         */
//        LRef<UString> operator=(ConstLRef<UString> string);
//
//        /**
//         * Move assignment operator for UString
//         * @param string String
//         * @return String
//         */
//        LRef<UString> operator=(RRef<UString> string);
//
//        /**
//         * Appending symbol to string
//         * @param symbol Symbol
//         * @return String
//         */
//        LRef<UString> operator+=(ConstLRef<USymbol> symbol);
//
//        /**
//         * Appending string to string
//         * @param string String
//         * @return String
//         */
//        LRef<UString> operator+=(ConstLRef<UString> string);
//
//        /**
//         * Adding string with string
//         * @param string String
//         * @return String
//         */
//        UString operator+(ConstLRef<UString> string);
//
//        /**
//         * Index string operator
//         * @param index Index
//         * @return Symbol at index
//         */
//        LRef<USymbol> operator[](ConstLRef<U64> index);
//
//        /**
//         * Index string operator
//         * @param index Index
//         * @return Symbol at index
//         */
//        ConstLRef<USymbol> operator[](ConstLRef<U64> index) const;
//
//        /**
//         * Is equals strings
//         * @param string String
//         * @return Is equals strings
//         */
//        Bool operator==(ConstLRef<UString> string) const;
//
//        /**
//         * Support for comparing strings
//         * @param string String
//         * @return Is true comparing
//         */
//        auto operator<=>(ConstLRef<UString> string) const;
//
//    public:
//
//        /**
//         * Begin string iterator
//         * @return Begin iterator
//         */
//        Iterator begin() override;
//
//        /**
//         * End string iterator
//         * @return End iterator
//         */
//        Iterator end() override;
//
//    public:
//
//        /**
//         * Unicode symbols
//         */
//        Vector<USymbol> _symbols;
//    };
//
//    /**
//     * Unicode string iterator
//     */
//    class UStringIterator : public Iterator<USymbol, UStringIterator> {
//    public:
//
//        /**
//         * Constructor for unicode string iterator
//         * @param pointer Pointer to unicode symbol
//         */
//        explicit UStringIterator(Ptr<USymbol> pointer)
//                : _pointer(pointer) {}
//
//    public:
//
//        /**
//         * Dereference operator
//         * @return Data
//         */
//        LRef<Data> operator*() override {
//            return *_pointer;
//        }
//
//        /**
//         * Member access operator
//         * @return Pointer to data
//         */
//        Ptr<Data> operator->() override {
//            return _pointer;
//        }
//
//        /**
//         * Increment operator
//         * @return Incremented iterator
//         */
//        LRef<ChildIterator> operator++() override {
//            ++_pointer;
//
//            return *this;
//        }
//
//        /**
//         * Decrement operator
//         * @return Decremented iterator
//         */
//        LRef<ChildIterator> operator--() override {
//            --_pointer;
//
//            return *this;
//        }
//
//        /**
//         * Comparing operator
//         * @param iterator Iterator for comparing
//         * @return Is equals
//         */
//        Bool operator==(ConstLRef<ChildIterator> iterator) const override {
//            return _pointer == iterator._pointer;
//        }
//
//        /**
//         * Not comparing operator
//         * @param iterator Iterator for comparing
//         * @return Is not equals
//         */
//        Bool operator!=(ConstLRef<ChildIterator> iterator) const override {
//            return !(*this == iterator);
//        }
//
//    private:
//
//        /**
//         * Pointer to unicode symbol
//         */
//        Ptr<USymbol> _pointer;
//    };
//
//    /**
//     * Unicode string operator
//     * @param text Text
//     * @param size Size of text
//     * @return Unicode string
//     */
//    inline UString operator""_us(ConstPtr<C32> text, U64 size) {
//        return UString(text);
//    }
//
//    /**
//     * Unicode string operator
//     * @param text Text
//     * @param size Size of text
//     * @return Unicode string
//     */
//    inline UString operator""_us(ConstPtr<C8> text, U64 size) {
//        return UString(text);
//    }

}

#endif //GSCROSSPLATFORM_STRING_H
