#include <GSCrossPlatform/GS_CrossPlatformString.h>

namespace CrossPlatform {

    String createString(const StringCharType *text) {
        return { text };
    }

}
