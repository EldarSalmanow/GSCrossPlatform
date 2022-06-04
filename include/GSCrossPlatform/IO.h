#ifndef GSCROSSPLATFORM_IO_H
#define GSCROSSPLATFORM_IO_H

#include <iostream>

#include <GSCrossPlatform/UString.h>

inline LRef<std::istream> operator>>(LRef<std::istream> stream, LRef<UString> string) {
    while (true) {
        auto byte = StaticCast<U8>(stream.get());

        if (byte == '\n' || stream.eof()) {
            break;
        }

        auto symbolSize = UTF8Size(byte);

        Vector<U8> bytes;

        bytes.Append(byte);

        for (U64 i = 1; i < symbolSize; ++i) {
            byte = StaticCast<U8>(stream.get());

            bytes.Append(byte);
        }

        auto codePoint = FromUTF8(bytes);

        string.Append(USymbol(codePoint));
    }

    return stream;
}

inline LRef<std::ostream> operator<<(LRef<std::ostream> stream, ConstLRef<UString> string) {
    for (auto &symbol : string) {
        auto bytes = symbol.AsUTF8();

        for (auto &byte : bytes) {
            stream << byte;
        }
    }

    return stream;
}

inline Bool EnableUnicodeConsole();

static Bool IsEnabledUnicodeConsole = EnableUnicodeConsole();

#endif //GSCROSSPLATFORM_IO_H
