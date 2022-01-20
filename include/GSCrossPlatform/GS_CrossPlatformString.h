#ifndef GSCROSSPLATFORM_GS_CROSSPLATFORMSTRING_H
#define GSCROSSPLATFORM_GS_CROSSPLATFORMSTRING_H

#include <GSCrossPlatform/GS_CrossPlatformContainers.h>

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
        Bool isAlpha() const;

        /**
         * Is digit symbol
         * @return Is digit
         */
        Bool isDigit() const;

        /**
         * Is whitespace symbol
         * @return Is whitespace
         */
        Bool isWhitespace() const;

        /**
         * Is IDStart symbol
         * @return Is IDStart
         */
        Bool isIDStart() const;

        /**
         * Is IDContinue symbol
         * @return Is IDContinue
         */
        Bool isIDContinue() const;

    public:

        /**
         * Getter for codepoint
         * @return Codepoint
         */
        CodePoint getCodePoint() const;

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

    class UStringIterator;

    /**
     * Class for unicode string
     */
    class UString : public Iterable<UStringIterator> {
    public:

        using IteratorT = UStringIterator;

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
        Void append(ConstLRef<USymbol> symbol);

        /**
         * Size of unicode string
         * @return Size of string
         */
        U64 size() const;

        /**
         * Is empty unicode string
         * @return Is empty string
         */
        Bool empty();

        /**
         * Converting string to bytes
         * @return String bytes
         */
        Vector<Byte> asBytes() const;

        /**
         * Converting unicode string to standard string
         * @return Standard string
         */
        String asString() const;

        /**
         *
         * @return
         */
        Vector<Byte> asCStringBytes() const;

    public:

        /**
         * Getter for unicode symbols
         * @return Unicode symbols
         */
        Vector<USymbol> getSymbols() const;

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
        IteratorT begin() override;

        /**
         *
         * @return
         */
        IteratorT end() override;

    public:

        /**
         * Unicode symbols
         */
        Vector<USymbol> _symbols;
    };

    class UStringIterator : public Iterator<USymbol, UStringIterator> {
    public:

        explicit UStringIterator(USymbol *pointer)
                : _pointer(pointer) {}

    public:

        LRef<DataT> operator*() override {
            return *_pointer;
        }

        Ptr<DataT> operator->() override {
            return _pointer;
        }

        LRef<IteratorT> operator++() override {
            ++_pointer;

            return *this;
        }

        LRef<IteratorT> operator--() override {
            --_pointer;

            return *this;
        }

        Bool operator==(ConstLRef<IteratorT> iterator) const override {
            return _pointer == iterator._pointer;
        }

        Bool operator!=(ConstLRef<IteratorT> iterator) const override {
            return !(*this == iterator);
        }

    private:

        Ptr<USymbol> _pointer;
    };

}

#endif //GSCROSSPLATFORM_GS_CROSSPLATFORMSTRING_H
