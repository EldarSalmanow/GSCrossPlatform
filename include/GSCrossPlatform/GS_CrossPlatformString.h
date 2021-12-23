#ifndef GSCROSSPLATFORM_GS_CROSSPLATFORMSTRING_H
#define GSCROSSPLATFORM_GS_CROSSPLATFORMSTRING_H

#include <GSCrossPlatform/GS_CrossPlatformTypes.h>

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

    public:

        /**
         * Getter for codepoint
         * @return Codepoint
         */
        CodePoint getCodePoint() const;

    private:

        /**
         * Unicode codepoint
         */
        CodePoint _codePoint;
    };

    /**
     * Is digit symbol
     * @param symbol Symbol
     * @return Is digit
     */
    Bool IsDigit(ConstLRef<USymbol> symbol);

    /**
     * Is alpha symbol
     * @param symbol Symbol
     * @return Is alpha
     */
    Bool IsAlpha(ConstLRef<USymbol> symbol);

    /**
     * Is starting symbol
     * @param symbol Symbol
     * @return Is starting
     */
    Bool IsIDStart(ConstLRef<USymbol> symbol);

    /**
     * Is continue symbol
     * @param symbol Symbol
     * @return Is continue
     */
    Bool IsIDContinue(ConstLRef<USymbol> symbol);

    /**
     * Class for unicode string
     */
    class UString {
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
         * Appending one unicode symbol to string
         * @param symbol Unicode symbol
         * @return
         */
        Void append(ConstLRef<USymbol> symbol);

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

    public:

        /**
         * Getter for unicode symbols
         * @return Unicode symbols
         */
        Vector<USymbol> getSymbols() const;

    public:

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
         * Unicode symbols
         */
        Vector<USymbol> _symbols;
    };

    /**
     * Unicode encodings
     */
    enum class Encoding {
        UTF8,
        UTF16,
        UTF32
    };

    /**
     * Byte endian
     */
    enum class ByteEndian {
        BigEndian,
        LittleEndian
    };

    /**
     * Conversion errors
     */
    enum class ConversionError {
        NullError,
        UnknownEncodingError,
        InvalidCodePointError,
        InvalidBytesError
    };

    /**
     * Class for supporting unicode conversions
     */
    class Conversions {
    public:

        /**
         * Encode unicode symbol
         * @param codePoint Codepoint
         * @param encoding Encoding
         * @param byteEndian Byte endian
         * @param conversionError Conversion error
         * @return Unicode symbol bytes
         */
        inline static Vector<Byte> Encode(ConstLRef<CodePoint> codePoint, ConstLRef<Encoding> encoding, ConstLRef<ByteEndian> byteEndian, LRef<ConversionError> conversionError) {
            switch (encoding) {
                case Encoding::UTF8:
                    return EncodeUTF8(codePoint, conversionError);
                case Encoding::UTF16:
                    return EncodeUTF16(codePoint, byteEndian, conversionError);
                case Encoding::UTF32:
                    return EncodeUTF32(codePoint, byteEndian, conversionError);
                default:
                    conversionError = ConversionError::UnknownEncodingError;
            }

            return InvalidBytes;
        }

        /**
         * Decode unicode symbol
         * @param bytes Unicode symbol bytes
         * @param encoding Encoding
         * @param byteEndian Byte endian
         * @param conversionError Conversion error
         * @return Codepoint
         */
        inline static CodePoint Decode(ConstLRef<Vector<Byte>> bytes, ConstLRef<Encoding> encoding, ConstLRef<ByteEndian> byteEndian, LRef<ConversionError> conversionError) {
            switch (encoding) {
                case Encoding::UTF8:
                    return DecodeUTF8(bytes, conversionError);
                case Encoding::UTF16:
                    return DecodeUTF16(bytes, byteEndian, conversionError);
                case Encoding::UTF32:
                    return DecodeUTF32(bytes, byteEndian, conversionError);
                default:
                    conversionError = ConversionError::UnknownEncodingError;
            }

            return InvalidCodePoint;
        }

        /**
         * Encoding UTF8 symbol
         * @param codePoint Codepoint
         * @param conversionError Conversion error
         * @return UTF8 symbol bytes
         */
        inline static Vector<Byte> EncodeUTF8(ConstLRef<CodePoint> codePoint, LRef<ConversionError> conversionError) {
            auto size = UTF8SymbolSize(codePoint);

            if (!size) {
                conversionError = ConversionError::InvalidCodePointError;

                return InvalidBytes;
            }

            Vector<Byte> bytes;

            if (size == 1) {
                bytes.emplace_back(static_cast<Byte>(codePoint));
            } else if (size == 2) {
                bytes.emplace_back(static_cast<Byte>(codePoint >> 6) | 0xC0);
                bytes.emplace_back(static_cast<Byte>(codePoint & 0x3F) | 0x80);
            } else if (size == 3) {
                bytes.emplace_back(static_cast<Byte>(codePoint >> 12) | 0xE0);
                bytes.emplace_back(static_cast<Byte>((codePoint >> 6) & 0x3F) | 0x80);
                bytes.emplace_back(static_cast<Byte>(codePoint & 0x3F) | 0x80);
            } else if (size == 4) {
                bytes.emplace_back(static_cast<Byte>(codePoint >> 18) | 0xF0);
                bytes.emplace_back(static_cast<Byte>((codePoint >> 12) & 0x3F) | 0x80);
                bytes.emplace_back(static_cast<Byte>((codePoint >> 6) & 0x3F) | 0x80);
                bytes.emplace_back(static_cast<Byte>(codePoint & 0x3F) | 0x80);
            }

            return bytes;
        }

        /**
         * Decoding UTF8 symbol
         * @param bytes UTF8 symbol bytes
         * @param conversionError Conversion error
         * @return Codepoint
         */
        inline static CodePoint DecodeUTF8(ConstLRef<Vector<Byte>> bytes, LRef<ConversionError> conversionError) {
            auto size = UTF8SymbolSize(bytes[0]);

            if (!size) {
                conversionError = ConversionError::InvalidBytesError;

                return InvalidCodePoint;
            }

            CodePoint codePoint;

            if (size == 1) {
                codePoint = bytes[0];
            } else if (size == 2) {
                codePoint = (static_cast<CodePoint>((bytes[0] & 0x1f)) << 6)
                            | static_cast<CodePoint>((bytes[1] & 0x3f));
            } else if (size == 3) {
                codePoint = (static_cast<CodePoint>((bytes[0] & 0x0f) << 12))
                            | static_cast<CodePoint>(((bytes[1] & 0x3f) << 6))
                            | static_cast<CodePoint>((bytes[2] & 0x3f));
            } else if (size == 4) {
                codePoint = (static_cast<CodePoint>((bytes[0] & 0x07) << 18))
                            | static_cast<CodePoint>(((bytes[1] & 0x3f) << 12))
                            | static_cast<CodePoint>(((bytes[2] & 0x3f) << 6))
                            | static_cast<CodePoint>((bytes[3] & 0x3f));
            }

            return codePoint;
        }

        /**
         * Encoding UTF16 symbol
         * @param codePoint Codepoint
         * @param byteEndian Byte endian
         * @param conversionError Conversion error
         * @return UTF16 symbol bytes
         */
        inline static Vector<Byte> EncodeUTF16(ConstLRef<CodePoint> codePoint, ConstLRef<ByteEndian> byteEndian, LRef<ConversionError> conversionError) {
            // TODO add supporting UTF-16 encoding

            return InvalidBytes;
        }

        /**
         * Decoding UTF16 symbol
         * @param bytes UTF16 symbol bytes
         * @param byteEndian Byte endian
         * @param conversionError Conversion error
         * @return Codepoint
         */
        inline static CodePoint DecodeUTF16(ConstLRef<Vector<Byte>> bytes, ConstLRef<ByteEndian> byteEndian, LRef<ConversionError> conversionError) {
            // TODO add supporting UTF-16 decoding

            return InvalidCodePoint;
        }

        /**
         * Encoding UTF32 symbol
         * @param codePoint Codepoint
         * @param byteEndian Byte endian
         * @param conversionError Conversion error
         * @return UTF32 symbol bytes
         */
        inline static Vector<Byte> EncodeUTF32(ConstLRef<CodePoint> codePoint, ConstLRef<ByteEndian> byteEndian, LRef<ConversionError> conversionError) {
            // TODO add supporting UTF-32 encoding

            return InvalidBytes;
        }

        /**
         * Decoding UTF32 symbol
         * @param bytes UTF32 symbol bytes
         * @param byteEndian Byte endian
         * @param conversionError Conversion error
         * @return Codepoint
         */
        inline static CodePoint DecodeUTF32(ConstLRef<Vector<Byte>> bytes, ConstLRef<ByteEndian> byteEndian, LRef<ConversionError> conversionError) {
            // TODO add supporting UTF-32 decoding

            return InvalidCodePoint;
        }

        /**
         * UTF8 symbol size
         * @param codePoint Codepoint
         * @return UTF8 symbol size
         */
        inline static U8 UTF8SymbolSize(ConstLRef<CodePoint> codePoint) {
            U8 size = 0;

            if (codePoint <= 0x7F) {
                size = 1;
            } else if (codePoint <= 0x7FF) {
                size = 2;
            } else if (codePoint <= 0xFFFF) {
                size = 3;
            } else if (codePoint <= 0x10FFFF) {
                size = 4;
            }

            return size;
        }

        /**
         * UTF8 symbol size
         * @param byte First symbol byte
         * @return UTF8 symbol size
         */
        inline static U8 UTF8SymbolSize(ConstLRef<Byte> byte) {
            U8 size = 0;

            if (byte <= 0x7F) {
                size = 1;
            } else if (byte <= 0xDF) {
                size = 2;
            } else if (byte <= 0xEF) {
                size = 3;
            } else if (byte <= 0xF4) {
                size = 4;
            }

            return size;
        }
    };

}

#endif //GSCROSSPLATFORM_GS_CROSSPLATFORMSTRING_H
