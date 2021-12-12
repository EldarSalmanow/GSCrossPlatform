#ifndef GSCROSSPLATFORM_GS_CROSSPLATFORMSTRING_H
#define GSCROSSPLATFORM_GS_CROSSPLATFORMSTRING_H

#include <GSCrossPlatform/GS_CrossPlatformTypes.h>

namespace CrossPlatform {

    inline const CodePoint InvalidCodePoint = 0x10FFFF + 1;

    inline const Vector<Byte> InvalidBytes = {};

    /**
     * Class for unicode symbol
     */
    class USymbol {
    public:

        /**
         * Constructor for USymbol
         * @param codePoint Unicode codepoint
         */
        USymbol(CodePoint codePoint);

    public:

        /**
         * Getter for codepoint
         * @return Codepoint
         */
        CodePoint getCodePoint();

    private:

        /**
         * Unicode codepoint
         */
        CodePoint _codePoint;
    };

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
        UString(const C32 *string);

    public:

        /**
         * appending one unicode symbol to string
         * @param symbol Unicode symbol
         * @return
         */
        Void append(USymbol symbol);

        /**
         * Converting string to bytes
         * @return String bytes
         */
        Vector<Byte> asBytes();

    public:

        /**
         * Getter for unicode symbols
         * @return Unicode symbols
         */
        Vector<USymbol> getSymbols();

    public:

        /**
         * Unicode symbols
         */
        Vector<USymbol> _symbols;
    };

    enum class Encoding {
        UTF8,
        UTF16LE,
        UTF16BE,
        UTF32LE,
        UTF32BE
    };

    enum class ConversionError {
        NullError,
        UnknownEncodingError,
        InvalidCodePointError,
        InvalidBytesError
    };

    class Conversions {
    public:

        inline static Vector<Byte> Encode(CodePoint codePoint, Encoding encoding, ConversionError &conversionError) {
            switch (encoding) {
                case Encoding::UTF8:
                    return EncodeUTF8(codePoint, conversionError);
                case Encoding::UTF16LE:
                    return EncodeUTF16(codePoint, conversionError);
                case Encoding::UTF16BE:
                    return EncodeUTF16(codePoint, conversionError, true);
                case Encoding::UTF32LE:
                    return EncodeUTF32(codePoint, conversionError);
                case Encoding::UTF32BE:
                    return EncodeUTF32(codePoint, conversionError, true);
                default:
                    conversionError = ConversionError::UnknownEncodingError;
            }

            return InvalidBytes;
        }

        inline static CodePoint Decode(Vector<Byte> bytes, Encoding encoding, ConversionError &conversionError) {
            switch (encoding) {
                case Encoding::UTF8:
                    return DecodeUTF8(std::move(bytes), conversionError);
                case Encoding::UTF16LE:
                    return DecodeUTF16(std::move(bytes), conversionError);
                case Encoding::UTF16BE:
                    return DecodeUTF16(std::move(bytes), conversionError, true);
                case Encoding::UTF32LE:
                    return DecodeUTF32(std::move(bytes), conversionError);
                case Encoding::UTF32BE:
                    return DecodeUTF32(std::move(bytes), conversionError, true);
                default:
                    conversionError = ConversionError::UnknownEncodingError;
            }

            return InvalidCodePoint;
        }

        inline static Vector<Byte> EncodeUTF8(CodePoint codePoint, ConversionError &conversionError) {
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

        inline static CodePoint DecodeUTF8(Vector<Byte> bytes, ConversionError &conversionError, Bool isBE = false) {
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

        inline static Vector<Byte>
        EncodeUTF16(CodePoint codePoint, ConversionError &conversionError, Bool isBE = false) {
            // TODO add supporting UTF-16 encoding

            return InvalidBytes;
        }

        inline static CodePoint DecodeUTF16(Vector<Byte> bytes, ConversionError &conversionError, Bool isBE = false) {
            // TODO add supporting UTF-16 decoding

            return InvalidCodePoint;
        }

        inline static Vector<Byte>
        EncodeUTF32(CodePoint codePoint, ConversionError &conversionError, Bool isBE = false) {
            // TODO add supporting UTF-32 encoding

            return InvalidBytes;
        }

        inline static CodePoint DecodeUTF32(Vector<Byte> bytes, ConversionError &conversionError, Bool isBE = false) {
            // TODO add supporting UTF-32 decoding

            return InvalidCodePoint;
        }

        inline static U8 UTF8SymbolSize(CodePoint codePoint) {
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

        inline static U8 UTF8SymbolSize(Byte byte) {
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
