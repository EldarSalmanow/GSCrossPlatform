#ifndef GSCROSSPLATFORM_UEXCEPTION_H
#define GSCROSSPLATFORM_UEXCEPTION_H

#include <GSCrossPlatform/UString.h>

class UException : public std::exception {
public:

    explicit UException(UString string)
            : _string(std::move(string)), _utf8String(_string.AsUTF8()) {}

public:

    inline constexpr UString Message() const {
        return _string;
    }

public:

    ConstPtr<C> what() const override {
        return _utf8String.c_str();
    }

private:

    UString _string;

    std::string _utf8String;
};

enum class Result : I32 {
    Ok  = 0,
    Err = 1
};

inline constexpr I32 ToExitCode(Result result) {
    return StaticCast<I32>(result);
}

#endif //GSCROSSPLATFORM_UEXCEPTION_H
