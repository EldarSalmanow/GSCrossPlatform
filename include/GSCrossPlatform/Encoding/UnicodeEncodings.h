#ifndef GSCROSSPLATFORM_UNICODEENCODINGS_H
#define GSCROSSPLATFORM_UNICODEENCODINGS_H

#include <GSCrossPlatform/Utils.h>

namespace CrossPlatform {

    inline constexpr CodePoint InvalidCodePoint = 0x10FFFF + 1;

    inline Vector<Byte> InvalidBytes = {};

    inline constexpr U8 UTF8Size(ConstLRef<CodePoint> codePoint) {
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

    inline constexpr U8 UTF8Size(ConstLRef<Byte> byte) {
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

    inline Vector<Byte> ToUTF8(ConstLRef<CodePoint> codePoint) {
        auto bytes = InvalidBytes;

        auto size = UTF8Size(codePoint);

        if (size == 1) {
            bytes.emplace_back(StaticCast<Byte>(codePoint));
        } else if (size == 2) {
            bytes.emplace_back(0xC0 + (codePoint  >> 6));
            bytes.emplace_back(0x80 + (codePoint         & 0x3F));
        } else if (size == 3) {
            bytes.emplace_back(0xE0 + (codePoint  >> 12));
            bytes.emplace_back(0x80 + ((codePoint >> 6)  & 0x3F));
            bytes.emplace_back(0x80 + (codePoint         & 0x3F));
        } else if (size == 4) {
            bytes.emplace_back(0xF0 + (codePoint  >> 18));
            bytes.emplace_back(0x80 + ((codePoint >> 12) & 0x3F));
            bytes.emplace_back(0x80 + ((codePoint >> 6)  & 0x3F));
            bytes.emplace_back(0x80 + (codePoint         & 0x3F));
        }

        return bytes;
    }

    inline CodePoint FromUTF8(ConstLRef<Vector<Byte>> bytes) {
        auto codePoint = InvalidCodePoint;

        auto size = UTF8Size(bytes[0]);

        if (size == 1) {
            codePoint = bytes[0];
        } else if (size == 2) {
            codePoint = ((bytes[0] & 0x1F) << 6)
                      +  (bytes[1] & 0x3F);
        } else if (size == 3) {
            codePoint = ((bytes[0] & 0x0F) << 12)
                      + ((bytes[1] & 0x3F) << 6)
                      +  (bytes[2] & 0x3F);
        } else if (size == 4) {
            codePoint = ((bytes[0] & 0x07) << 18)
                      + ((bytes[1] & 0x3F) << 12)
                      + ((bytes[2] & 0x3F) << 6)
                      +  (bytes[3] & 0x3F);
        }

        return codePoint;
    }

    // TODO add supporting UTF-16

    inline Vector<Byte> ToUTF16(ConstLRef<CodePoint> codePoint) {
        auto bytes = InvalidBytes;

//        if (codePoint <= 0xD7FF || (codePoint >= 0xE000 && codePoint <= 0xFFFF)) {
//            bytes.emplace_back(codePoint >> 8);
//            bytes.emplace_back(codePoint & 0xFF);
//        } else {
//            uint16_t high = ((codePoint - 0x10000) >> 10)  + 0xD800;
//            uint16_t low = ((codePoint - 0x10000) & 0x3FF) + 0xDC00;
//            bytes.emplace_back(high >> 8);
//            bytes.emplace_back(high & 0xFF);
//            bytes.emplace_back(low >> 8);
//            bytes.emplace_back(low & 0xFF);
//        }

        return bytes;
    }

    inline CodePoint FrmUTF16(ConstLRef<Vector<Byte>> bytes) {
        auto codePoint = InvalidCodePoint;

//        auto size = utf16_size();
//
//        if (size == 2) {
//            codePoint = (bytes[0] << 8)
//                       + bytes[1];
//        }
//        if (size == 4) {
//            codePoint = 0x10000 + ((((bytes[0] << 8) + bytes[1]) - 0xD800) << 10)
//                    + (((bytes[2] << 8) + bytes[3]) - 0xDC00);
//        }

        return codePoint;
    }

    inline Vector<Byte> ToUTF32(ConstLRef<CodePoint> codePoint) {
        auto bytes = InvalidBytes;

        bytes.emplace_back(codePoint  >> 24);
        bytes.emplace_back((codePoint >> 16) & 0xFF);
        bytes.emplace_back((codePoint >> 8)  & 0xFF);
        bytes.emplace_back(codePoint         & 0xFF);

        return bytes;
    }

    inline CodePoint FromUTF32(ConstLRef<Vector<Byte>> bytes) {
        auto codePoint = InvalidCodePoint;

        codePoint = (bytes[0] << 24)
                  + (bytes[1] << 16)
                  + (bytes[2] << 8)
                  + bytes[3];

        return codePoint;
    }

    inline std::u16string UTF8ToUTF16(ConstLRef<std::string> string) {
        std::u16string u16string;

        return u16string;
    }

    inline std::u32string UTF8ToUTF32(ConstLRef<std::string> string) {
        std::u32string u32string;

        for (U64 index = 0; index < string.size(); ++index) {
            auto byte = StaticCast<Byte>(string[index]);

            auto symbolSize = UTF8Size(byte);

            Vector<Byte> bytes;

            bytes.emplace_back(byte);

            for (U64 i = 1; i < symbolSize; ++i) {
                ++index;

                byte = StaticCast<Byte>(string[index]);

                bytes.emplace_back(byte);
            }

            auto codePoint = FromUTF8(bytes);

            u32string += StaticCast<char32_t>(codePoint);
        }

        return u32string;
    }

#if defined(__cpp_lib_char8_t)

    inline std::u16string UTF8ToUTF16(ConstLRef<std::u8string> string) {
        std::u16string u16string;

        return u16string;
    }

    inline std::u32string UTF8ToUTF32(ConstLRef<std::u8string> string) {
        std::u32string u32string;

        return u32string;
    }

#endif

    inline std::string UTF16ToUTF8(ConstLRef<std::u16string> u16string) {
        std::string string;

        return string;
    }

    inline std::u32string UTF16ToUTF32(ConstLRef<std::u16string> u16string) {
        std::u32string u32string;

        return u32string;
    }

    inline std::string UTF32ToUTF8(ConstLRef<std::u32string> u32string) {
        std::string string;

        return string;
    }

    inline std::u16string UTF32ToUTF16(ConstLRef<std::u32string> u32string) {
        std::u16string u16string;

        return u16string;
    }

}

#endif //GSCROSSPLATFORM_UNICODEENCODINGS_H
