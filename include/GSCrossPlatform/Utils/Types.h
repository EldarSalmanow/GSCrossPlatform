#ifndef GSCROSSPLATFORM_TYPES_H
#define GSCROSSPLATFORM_TYPES_H

#include <vector>
#include <map>
#include <deque>
#include <stack>
#include <any>
#include <exception>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <GSCrossPlatform/Utils/Defines.h>

/**
 * Integer types
 */

/**
 * One byte signed type
 */
using I8 = std::int8_t;

/**
 * One byte unsigned type
 */
using U8 = std::uint8_t;

/**
 * Two bytes signed type
 */
using I16 = std::int16_t;

/**
 * Two bytes unsigned type
 */
using U16 = std::uint16_t;

/**
 * Four bytes signed type
 */
using I32 = std::int32_t;

/**
 * Four bytes unsigned type
 */
using U32 = std::uint32_t;

/**
 * Eight bytes signed type
 */
using I64 = std::int64_t;

/**
 * Eight bytes unsigned type
 */
using U64 = std::uint64_t;

/**
 * Number with point types
 */

/**
 * Four bytes type with point
 */
using F32 = float;

/**
 * Eight bytes type with point
 */
using F64 = double;

/**
 * Char types
 */

/**
 * One byte char type
 */
using C8 = char;

/**
 * Two bytes char type
 */
using C16 = char16_t;

/**
 * Four bytes char type
 */
using C32 = char32_t;

/**
 * Wide bytes char type
 */
using WC = wchar_t;

/**
 * Char type for string and streams
 */
using CharType = C8;

/**
 * String types
 */

/**
 * String char type
 */
using StringCharType = CharType;

/**
 * String with support unicode
 */
using String = std::basic_string<StringCharType>;

/**
 * String with support unicode iterator
 */
using StringIterator = String::iterator;

/**
 * Stream types
 */

/**
 * Stream char type
 */
using StreamCharType = CharType;

/**
 * Output stream type
 */
using OStream = std::basic_ostream<StreamCharType>;

/**
 * Input stream type
 */
using IStream = std::basic_istream<StreamCharType>;

/**
 * Output file stream type
 */
using OFStream = std::basic_ofstream<StreamCharType>;

/**
 * Input file stream type
 */
using IFStream = std::basic_ifstream<StreamCharType>;

/**
 * Console output stream
 */
inline OStream &COut = std::cout;

/**
 * Console output error stream
 */
inline OStream &CErr = std::cerr;

/**
 * Console output log stream
 */
inline OStream &CLog = std::clog;

/**
 * Console input stream
 */
inline IStream &CIn = std::cin;

/**
 * Container types
 */

/**
 * Vector type
 */
template<typename T>
using Vector = std::vector<T>;

/**
 * Vector iterator type
 */
template<typename T>
using VectorIterator = typename Vector<T>::iterator;

/**
 * Map type
 */
template<typename T, typename R>
using Map = std::map<T, R>;

/**
 * Map iterator type
 */
template<typename T, typename R>
using MapIterator = typename Map<T, R>::iterator;

/**
 * Deque type
 */
template<typename T>
using Deque = std::deque<T>;

/**
 * Deque iterator type
 */
template<typename T>
using DequeIterator = typename Deque<T>::iterator;

/**
 * Stack type
 */
template<typename T>
using Stack = std::stack<T>;

/**
 * Any type
 */
using Any = std::any;

/**
 * Exception type
 */
using Exception = std::exception;

/**
 * Memory types
 */

/**
 * Shared ptr type
 */
template<typename T>
using SharedPtr = std::shared_ptr<T>;

/**
 * Unique ptr type
 */
template<typename T>
using UniquePtr = std::unique_ptr<T>;

/**
 * Special types
 */

/**
 * Void type
 */
using Void = void;

/**
 * Boolean type
 */
using Bool = bool;

/**
 * Byte type
 */
using Byte = U8;

/**
 * Unicode types
 */

/**
 * Unicode codepoint type
 */
using CodePoint = U32;

/**
 * Modifier types
 */

/**
 * Const type
 */
template<typename T>
using Const = const T;

/**
 * Pointer type
 */
template<typename T>
using Ptr = T *;

/**
 * Lvalue reference type
 */
template<typename T>
using LRef = T &;

/**
 * Rvalue reference type
 */
template<typename T>
using RRef = T &&;

/**
 * Const pointer type
 */
template<typename T>
using ConstPtr = const T *;

/**
 * Const lvalue reference type
 */
template<typename T>
using ConstLRef = const T &;

/**
 * Const rvalue reference type
 */
template<typename T>
using ConstRRef = const T &&;

/**
 * Type cast functions
 */

/**
 * C style cast
 * @tparam T Out type
 * @tparam R In type
 * @param value Value
 * @return Casted value
 */
template<typename T, typename R>
inline T CCast(R value) {
    return (T) value;
}

/**
 * Reinterpret cast
 * @tparam T Out type
 * @tparam R In type
 * @param value Value
 * @return Casted value
 */
template<typename T, typename R>
inline T ReinterpretCast(R value) {
    return reinterpret_cast<T>(value);
}

/**
 * Static cast
 * @tparam T Out type
 * @tparam R In type
 * @param value Value
 * @return Casted value
 */
template<typename T, typename R>
inline T StaticCast(R value) {
    return static_cast<T>(value);
}

/**
 * Const cast
 * @tparam T Out type
 * @tparam R In type
 * @param value Value
 * @return Casted value
 */
template<typename T, typename R>
inline T ConstCast(R value) {
    return const_cast<T>(value);
}

/**
 * Dynamic cast
 * @tparam T Out type
 * @tparam R In type
 * @param value Value
 * @return Casted value
 */
template<typename T, typename R>
inline T DynamicCast(R value) {
    return dynamic_cast<T>(value);
}

#endif //GSCROSSPLATFORM_TYPES_H
