#ifndef GSCROSSPLATFORM_UNICODEENCODINGS_H
#define GSCROSSPLATFORM_UNICODEENCODINGS_H

#include <GSCrossPlatform/Utils.h>

namespace CrossPlatform {

    /**
     * Unicode encodings
     */
    enum class Encoding {
        UTF8,
        UTF16,
        UTF32
    };

    /**
     * Conversion errors
     */
    enum class ConversionError {
        NullError,
        InvalidCodePointError,
        InvalidBytesError
    };

    /**
     * Class for supporting unicode conversions
     */
    class Conversions {
    public:

        /**
         * Decode unicode symbol
         * @param bytes Unicode symbol bytes
         * @param encoding Encoding
         * @return Codepoint
         */
        inline static Vector<Byte> Encode(ConstLRef<CodePoint> codePoint, ConstLRef<Encoding> encoding) {
            auto conversionError = ConversionError::NullError;

            auto bytes = Encode(codePoint, encoding, conversionError);

            if (conversionError != ConversionError::NullError) {
                auto errorMessage = U"Conversion Error: "_us;

                switch (conversionError) {
                    case ConversionError::InvalidCodePointError:
                        errorMessage += U"Invalid Unicode codepoint!";

                        break;
                    case ConversionError::InvalidBytesError:
                        errorMessage += U"Invalid Unicode bytes!";

                        break;
                }

                throw UException(errorMessage);
            }

            return bytes;
        }

        /**
         * Decode unicode symbol
         * @param bytes Unicode symbol bytes
         * @param encoding Encoding
         * @return Codepoint
         */
        inline static CodePoint Decode(ConstLRef<Vector<Byte>> bytes, ConstLRef<Encoding> encoding) {
            auto conversionError = ConversionError::NullError;

            auto codePoint = Decode(bytes, encoding, conversionError);

            if (conversionError != ConversionError::NullError) {
                auto errorMessage = U"Conversion Error: "_us;

                switch (conversionError) {
                    case ConversionError::InvalidCodePointError:
                        errorMessage += U"Invalid Unicode codepoint!";

                        break;
                    case ConversionError::InvalidBytesError:
                        errorMessage += U"Invalid Unicode bytes!";

                        break;
                }

                throw UException(errorMessage);
            }

            return codePoint;
        }

        /**
         * Encode unicode symbol
         * @param codePoint Codepoint
         * @param encoding Encoding
         * @param conversionError Conversion error
         * @return Unicode symbol bytes
         */
        inline static Vector<Byte> Encode(ConstLRef<CodePoint> codePoint, ConstLRef<Encoding> encoding, LRef<ConversionError> conversionError) {
            auto bytes = InvalidBytes;

            switch (encoding) {
                case Encoding::UTF8:
                    bytes = EncodeUTF8(codePoint, conversionError);

                    break;
                case Encoding::UTF16:
                    bytes = EncodeUTF16(codePoint, conversionError);

                    break;
                case Encoding::UTF32:
                    bytes = EncodeUTF32(codePoint, conversionError);

                    break;
            }

            return bytes;
        }

        /**
         * Decode unicode symbol
         * @param bytes Unicode symbol bytes
         * @param encoding Encoding
         * @param conversionError Conversion error
         * @return Codepoint
         */
        inline static CodePoint Decode(ConstLRef<Vector<Byte>> bytes, ConstLRef<Encoding> encoding, LRef<ConversionError> conversionError) {
            auto codePoint = InvalidCodePoint;

            switch (encoding) {
                case Encoding::UTF8:
                    codePoint = DecodeUTF8(bytes, conversionError);

                    break;
                case Encoding::UTF16:
                    codePoint = DecodeUTF16(bytes, conversionError);

                    break;
                case Encoding::UTF32:
                    codePoint = DecodeUTF32(bytes, conversionError);

                    break;
            }

            return codePoint;
        }

        /**
         * Encoding UTF8 symbol
         * @param codePoint Codepoint
         * @param conversionError Conversion error
         * @return UTF8 symbol bytes
         */
        inline static Vector<Byte> EncodeUTF8(ConstLRef<CodePoint> codePoint, LRef<ConversionError> conversionError) {
            auto bytes = InvalidBytes;

            auto size = SymbolSizeUTF8(codePoint);

            if (!size) {
                conversionError = ConversionError::InvalidCodePointError;

                return bytes;
            }

            if (size == 1) {
                bytes.emplace_back(StaticCast<Byte>(codePoint & 0xFF));
            } else if (size == 2) {
                bytes.emplace_back(StaticCast<Byte>(0xC0 | ((codePoint >> 6)  & 0xFF)));
                bytes.emplace_back(StaticCast<Byte>(0x80 | ((codePoint        & 0x3F))));
            } else if (size == 3) {
                bytes.emplace_back(StaticCast<Byte>(0xE0 | ((codePoint >> 12) & 0xFF)));
                bytes.emplace_back(StaticCast<Byte>(0x80 | ((codePoint >> 6)  & 0x3F)));
                bytes.emplace_back(StaticCast<Byte>(0x80 | (codePoint         & 0x3F)));
            } else if (size == 4) {
                bytes.emplace_back(StaticCast<Byte>(0xF0 | ((codePoint >> 18) & 0xFF)));
                bytes.emplace_back(StaticCast<Byte>(0x80 | ((codePoint >> 12) & 0x3F)));
                bytes.emplace_back(StaticCast<Byte>(0x80 | ((codePoint >> 6)  & 0x3F)));
                bytes.emplace_back(StaticCast<Byte>(0x80 | (codePoint         & 0x3F)));
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
            auto codePoint = InvalidCodePoint;

            auto size = SymbolSizeUTF8(bytes[0]);

            if (!size) {
                conversionError = ConversionError::InvalidBytesError;

                return codePoint;
            }

            if (size == 1) {
                codePoint = bytes[0];
            } else if (size == 2) {
                codePoint = (StaticCast<CodePoint>((bytes[0] & 0x1f)) << 6)
                           | StaticCast<CodePoint>((bytes[1] & 0x3f)      );
            } else if (size == 3) {
                codePoint = (StaticCast<CodePoint>((bytes[0] & 0x0f) << 12)
                           | StaticCast<CodePoint>((bytes[1] & 0x3f) << 6 )
                           | StaticCast<CodePoint>((bytes[2] & 0x3f)      ));
            } else if (size == 4) {
                codePoint = (StaticCast<CodePoint>((bytes[0] & 0x07) << 18)
                           | StaticCast<CodePoint>((bytes[1] & 0x3f) << 12)
                           | StaticCast<CodePoint>((bytes[2] & 0x3f) << 6 )
                           | StaticCast<CodePoint>((bytes[3] & 0x3f)      ));
            }

            return codePoint;
        }

        /**
         * Encoding UTF16 symbol
         * @param codePoint Codepoint
         * @param conversionError Conversion error
         * @return UTF16 symbol bytes
         */
        inline static Vector<Byte> EncodeUTF16(ConstLRef<CodePoint> codePoint, LRef<ConversionError> conversionError) {
            // TODO add supporting UTF-16 encoding

            return InvalidBytes;
        }

        /**
         * Decoding UTF16 symbol
         * @param bytes UTF16 symbol bytes
         * @param conversionError Conversion error
         * @return Codepoint
         */
        inline static CodePoint DecodeUTF16(ConstLRef<Vector<Byte>> bytes, LRef<ConversionError> conversionError) {
            // TODO add supporting UTF-16 decoding

            return InvalidCodePoint;
        }

        /**
         * Encoding UTF32 symbol
         * @param codePoint Codepoint
         * @param conversionError Conversion error
         * @return UTF32 symbol bytes
         */
        inline static Vector<Byte> EncodeUTF32(ConstLRef<CodePoint> codePoint, LRef<ConversionError> conversionError) {
            // TODO add supporting UTF-32 encoding

            return InvalidBytes;
        }

        /**
         * Decoding UTF32 symbol
         * @param bytes UTF32 symbol bytes
         * @param conversionError Conversion error
         * @return Codepoint
         */
        inline static CodePoint DecodeUTF32(ConstLRef<Vector<Byte>> bytes, LRef<ConversionError> conversionError) {
            // TODO add supporting UTF-32 decoding

            return InvalidCodePoint;
        }

        /**
         * UTF8 symbol size
         * @param codePoint Codepoint
         * @return UTF8 symbol size
         */
        inline static U8 SymbolSizeUTF8(ConstLRef<CodePoint> codePoint) {
            auto size = 0;

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
        inline static U8 SymbolSizeUTF8(ConstLRef<Byte> byte) {
            auto size = 0;

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

#endif //GSCROSSPLATFORM_UNICODEENCODINGS_H
