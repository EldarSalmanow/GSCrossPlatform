#ifndef GSCROSSPLATFORM_STRING_H
#define GSCROSSPLATFORM_STRING_H

#include <GSCrossPlatform/Containers/Iterator.h>

namespace CrossPlatform {

    /**
     * Invalid unicode codepoint
     */
    inline Const<CodePoint> InvalidCodePoint = 0x10FFFF + 1;

    /**
     * Invalid unicode bytes
     */
    inline Const<Vector<Byte>> InvalidBytes = {};

    /**
     * Class for unicode symbol
     */
    class USymbol {
    public:

        /**
         * Constructor for USymbol
         * @param codePoint Unicode codepoint
         */
        USymbol(ConstLRef<CodePoint> codePoint);

        /**
         * Constructor for USymbol
         * @param symbol Symbol
         */
        USymbol(ConstLRef<C32> symbol);

    public:

        /**
         * Is alpha symbol
         * @return Is alpha
         */
        Bool IsAlpha() const;

        /**
         * Is digit symbol
         * @return Is digit
         */
        Bool IsDigit() const;

        /**
         * Is whitespace symbol
         * @return Is whitespace
         */
        Bool IsWhitespace() const;

        /**
         * Is IDStart symbol
         * @return Is IDStart
         */
        Bool IsIDStart() const;

        /**
         * Is IDContinue symbol
         * @return Is IDContinue
         */
        Bool IsIDContinue() const;

    public:

        /**
         * Getter for codepoint
         * @return Codepoint
         */
        CodePoint GetCodePoint() const;

    public:

        /**
         * Is equals symbols
         * @param symbol Symbol
         * @return Is equals
         */
        Bool operator==(ConstLRef<USymbol> symbol) const;

    private:

        /**
         * Unicode codepoint
         */
        CodePoint _codePoint;
    };

    /**
     * Defining UStringIterator
     */
    class UStringIterator;

    /**
     * Class for unicode string
     */
    class UString : public Iterable<UStringIterator> {
    public:

        /**
         * Iterator type
         */
        using Iterator = typename Iterable<UStringIterator>::Iterator;

    public:

        /**
         * Default UString constructor
         */
        UString();

        /**
         * Constructor for UString
         * @param string String
         */
        UString(ConstPtr<C32> string);

        /**
         * Constructor for UString
         * @param string String
         * @param size Size
         */
        UString(ConstPtr<C32> string, U64 size);

    public:

        /**
         * Copy constructor for UString
         * @param string String
         */
        UString(ConstLRef<UString> string);

        /**
         * Move copy constructor for UString
         * @param string String
         */
        UString(RRef<UString> string);

    public:

        /**
         * Appending one unicode symbol to string
         * @param symbol Unicode symbol
         * @return
         */
        Void Append(ConstLRef<USymbol> symbol);

        /**
         * Size of unicode string
         * @return Size of string
         */
        U64 Size() const;

        /**
         * Is empty unicode string
         * @return Is empty string
         */
        Bool Empty();

        /**
         * Converting string to bytes
         * @return String bytes
         */
        Vector<Byte> AsBytes() const;

        /**
         * Converting unicode string to standard string
         * @return Standard string
         */
        String AsString() const;

        /**
         *
         * @return
         */
        Vector<Byte> AsCStringBytes() const;

    public:

        /**
         * Getter for unicode symbols
         * @return Unicode symbols
         */
        Vector<USymbol> GetSymbols() const;

    public:

        /**
         * Assignment operator for UString
         * @param string String
         * @return String
         */
        LRef<UString> operator=(ConstLRef<UString> string);

        /**
         * Move assignment operator for UString
         * @param string String
         * @return String
         */
        LRef<UString> operator=(RRef<UString> string);

        /**
         * Appending symbol to string
         * @param symbol Symbol
         * @return String
         */
        LRef<UString> operator+=(ConstLRef<USymbol> symbol);

        /**
         * Appending string to string
         * @param string String
         * @return String
         */
        LRef<UString> operator+=(ConstLRef<UString> string);

        /**
         * Adding string with string
         * @param string String
         * @return String
         */
        LRef<UString> operator+(ConstLRef<UString> string);

        /**
         * Index string operator
         * @param index Index
         * @return Symbol at index
         */
        LRef<USymbol> operator[](ConstLRef<U64> index);

        /**
         * Index string operator
         * @param index Index
         * @return Symbol at index
         */
        ConstLRef<USymbol> operator[](ConstLRef<U64> index) const;

        /**
         * Is equals strings
         * @param string String
         * @return Is equals strings
         */
        Bool operator==(ConstLRef<UString> string) const;

        /**
         * Support for comparing strings
         * @param string String
         * @return Is true comparing
         */
        auto operator<=>(ConstLRef<UString> string) const;

    public:

        /**
         *
         * @return
         */
        Iterator begin() override;

        /**
         *
         * @return
         */
        Iterator end() override;

    public:

        /**
         * Unicode symbols
         */
        Vector<USymbol> _symbols;
    };

    class UStringIterator : public Iterator<USymbol, UStringIterator> {
    public:

        explicit UStringIterator(Ptr<USymbol> pointer)
                : _pointer(pointer) {}

    public:

        LRef<Data> operator*() override {
            return *_pointer;
        }

        Ptr<Data> operator->() override {
            return _pointer;
        }

        LRef<ChildIterator> operator++() override {
            ++_pointer;

            return *this;
        }

        LRef<ChildIterator> operator--() override {
            --_pointer;

            return *this;
        }

        Bool operator==(ConstLRef<ChildIterator> iterator) const override {
            return _pointer == iterator._pointer;
        }

        Bool operator!=(ConstLRef<ChildIterator> iterator) const override {
            return !(*this == iterator);
        }

    private:

        Ptr<USymbol> _pointer;
    };

    inline UString operator""_us(ConstPtr<C32> text, U64 size) {
        return UString(text, size);
    }

}

#endif //GSCROSSPLATFORM_STRING_H
