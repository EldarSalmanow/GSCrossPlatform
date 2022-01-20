#include <GSCrossPlatform/GS_CrossPlatformException.h>

namespace CrossPlatform {

    UException::UException(ConstLRef<UString> message)
            : _message(message), _stringMessage(_message.asString()) {}

    ConstPtr<C8> UException::what() const {
        return _stringMessage.c_str();
    }
}
