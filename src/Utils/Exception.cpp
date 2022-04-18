#include <GSCrossPlatform/Utils/Exception.h>

namespace CrossPlatform {

    UException::UException(ConstLRef<UString> message)
            : _message(message), _stringMessage(_message.AsString()) {}

    UString UException::GetMessage() const {
        return _message;
    }

    ConstPtr<C8> UException::what() const {
        return _stringMessage.c_str();
    }
}
