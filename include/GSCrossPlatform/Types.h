#ifndef GSCROSSPLATFORM_TYPES_H
#define GSCROSSPLATFORM_TYPES_H

#include <cstdint>

#include <GSCrossPlatform/Defines.h>

using Void = void;

using Bool = bool;

using C = char;

#if defined(__cpp_lib_char8_t)

using C8 = char8_t;

#endif

using C16 = char16_t;

using C32 = char32_t;

using I8 = std::int8_t;

using U8 = std::uint8_t;

using I16 = std::int16_t;

using U16 = std::uint16_t;

using I32 = std::int32_t;

using U32 = std::uint32_t;

using I64 = std::int64_t;

using U64 = std::uint64_t;

template<typename T>
using Ptr = T *;

template<typename T>
using LRef = T &;

template<typename T>
using RRef = T &&;

template<typename T>
using Const = const T;

template<typename T>
using ConstPtr = const T *;

template<typename T>
using ConstLRef = const T &;

template<typename T>
using ConstRRef = const T &&;

template<typename T, typename R>
inline constexpr T StaticCast(R value) {
    return static_cast<T>(value);
}

template<typename T, typename R>
inline constexpr T ReinterpretCast(R value) {
    return reinterpret_cast<T>(value);
}

template<typename T, typename R>
inline constexpr T ConstCast(R value) {
    return const_cast<T>(value);
}

template<typename T, typename R>
inline constexpr T DynamicCast(R value) {
    return dynamic_cast<T>(value);
}

#endif //GSCROSSPLATFORM_TYPES_H
