#ifndef GSCROSSPLATFORM_GS_CROSSPLATFORMTYPES_H
#define GSCROSSPLATFORM_GS_CROSSPLATFORMTYPES_H

#include <vector>
#include <map>
#include <any>
#include <memory>
#include <string>
#include <sstream>

#if defined(GS_USE_BOOST_NOWIDE)
    #include <boost/nowide/iostream.hpp>
    #include <boost/nowide/fstream.hpp>
#else
    #include <iostream>
    #include <fstream>
#endif

#include <GSCrossPlatform/GS_CrossPlatformDefines.h>

/**
 * Integer types
 */

/**
 * One byte signed type
 */
using I8  = std::int8_t;

/**
 * One byte unsigned type
 */
using U8  = std::uint8_t;

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

#if defined(GS_USE_BOOST_NOWIDE)
    /**
     * Output stream type
     */
    using OStream = boost::nowide::detail::winconsole_ostream;

    /**
     * Input stream type
     */
    using IStream = boost::nowide::detail::winconsole_istream;

    /**
     * Output file stream type
     */
    using OFStream = boost::nowide::basic_ofstream<StreamCharType>;

    /**
     * Input file stream type
     */
    using IFStream = boost::nowide::basic_ifstream<StreamCharType>;

    /**
     * Console output stream
     */
    inline OStream &COut = boost::nowide::cout;

    /**
     * Console output error stream
     */
    inline OStream &CErr = boost::nowide::cerr;

    /**
     * Console output log stream
     */
    inline OStream &CLog = boost::nowide::clog;

    /**
     * Console input stream
     */
    inline IStream &CIn = boost::nowide::cin;
#else
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
#endif

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
 * Any type
 */
using Any = std::any;

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

#endif //GSCROSSPLATFORM_GS_CROSSPLATFORMTYPES_H
