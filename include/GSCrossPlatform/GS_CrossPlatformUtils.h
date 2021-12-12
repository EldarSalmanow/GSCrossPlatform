#ifndef GSCROSSPLATFORM_GS_CROSSPLATFORMUTILS_H
#define GSCROSSPLATFORM_GS_CROSSPLATFORMUTILS_H

#include <GSCrossPlatform/GS_CrossPlatformTypes.h>

namespace CrossPlatform {

    /**
     * Struct for converting values to and from bytes
     * @tparam T Type
     */
    template<typename T>
    struct ByteConverter {

        /**
         * Converting value to bytes
         * @param value Value
         * @return Value bytes
         */
        inline static Vector<Byte> toBytes(T value) {
            union {
                unsigned char unionBytes[sizeof(T)];
                T unionValue;
            };

            unionValue = value;

            Vector<Byte> bytes;

            for (U64 index = 0; index < sizeof(T); ++index) {
                bytes.emplace_back(unionBytes[index]);
            }

            return bytes;
        }

        /**
         * Converting bytes to value
         * @param bytes Bytes
         * @return Value
         */
        inline static T fromBytes(Vector<Byte> bytes) {
            union {
                unsigned char unionBytes[sizeof(T)];
                T unionValue;
            };

            for (U64 index = 0; index < sizeof(T); ++index) {
                unionBytes[index] = bytes[index];
            }

            return unionValue;
        }
    };

}

#endif //GSCROSSPLATFORM_GS_CROSSPLATFORMUTILS_H
