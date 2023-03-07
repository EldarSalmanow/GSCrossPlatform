#ifndef GSCROSSPLATFORM_IO_H
#define GSCROSSPLATFORM_IO_H

#include <iostream>

#include <GSCrossPlatform/UString.h>

inline LRef<std::istream> operator>>(LRef<std::istream> stream, LRef<USymbol> symbol) {
    auto byte = StaticCast<U8>(stream.get());

    if (stream.eof()) {
        return stream;
    }

    auto symbolSize = UTF8Size(byte);

    Vector<U8> bytes;

    bytes.Append(byte);

    for (U64 i = 1; i < symbolSize; ++i) {
        byte = StaticCast<U8>(stream.get());

        bytes.Append(byte);
    }

    auto codePoint = FromUTF8(bytes);

    symbol = USymbol(codePoint);

    return stream;
}

inline LRef<std::ostream> operator<<(LRef<std::ostream> stream, ConstLRef<USymbol> symbol) {
    auto bytes = ToUTF8(symbol.CodePoint());

    for (auto &byte : bytes) {
        stream.put(StaticCast<C>(byte));
    }

    return stream;
}

inline LRef<std::istream> operator>>(LRef<std::istream> stream, LRef<UString> string) {
    while (true) {
        USymbol symbol;

        stream >> symbol;

        if (symbol == '\n' || stream.eof()) {
            break;
        }

        string.Append(symbol);
    }

    return stream;
}

inline LRef<std::ostream> operator<<(LRef<std::ostream> stream, ConstLRef<UString> string) {
    for (auto &symbol : string) {
        stream << symbol;
    }

    return stream;
}

Bool EnableUnicodeConsole();

static Bool IsEnabledUnicodeConsole = EnableUnicodeConsole();

#endif //GSCROSSPLATFORM_IO_H
