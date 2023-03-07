#include <unicode/uchar.h>

#include <GSCrossPlatform/IO.h>

Bool USymbol::IsAlpha() const {
    return u_isalpha(StaticCast<UChar32>(_codePoint));
}

Bool USymbol::IsDigit() const {
    return u_isdigit(StaticCast<UChar32>(_codePoint));
}

Bool USymbol::IsWhitespace() const {
    return u_isspace(StaticCast<UChar32>(_codePoint));
}

Bool USymbol::IsIDStart() const {
    return u_isIDStart(StaticCast<UChar32>(_codePoint));
}

Bool USymbol::IsIDContinue() const {
    return u_isIDPart(StaticCast<UChar32>(_codePoint));
}
