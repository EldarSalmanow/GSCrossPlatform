#ifndef GSCROSSPLATFORM_ARRAY_H
#define GSCROSSPLATFORM_ARRAY_H

#include <stdexcept>

#include <GSCrossPlatform/Types.h>

template<typename ValueT, auto SizeV>
class Array {
public:

    using ValueType = ValueT;

    using SizeType = decltype(SizeV);

    inline static constexpr Const<SizeType> SizeValue = SizeV;

public:

    using Iterator = Ptr<ValueType>;

    using ConstIterator = ConstPtr<ValueType>;

public:

    constexpr Array() = default;

    constexpr Array(std::initializer_list<ValueType> initializerList) {
        if (initializerList.size() > SizeValue) {
            throw std::runtime_error("Array::Array(std::initializer_list<ValueType>): Initializer list bigger than array Size!");
        }

        for (U64 index = 0; auto &value : initializerList) {
            _data[index] = value;

            ++index;
        }
    }

    constexpr Array(ConstLRef<Array<ValueType, SizeValue>> array) {
        if (this == &array) {
            return;
        }

        for (U64 index = 0; auto &value : array) {
            _data[index] = value;

            ++index;
        }
    }

    constexpr Array(RRef<Array<ValueType, SizeValue>> array) noexcept {
        if (this == &array) {
            return;
        }

        for (U64 index = 0; auto &value : array) {
            _data[index] = value;

            ++index;
        }
    }

public:

    inline constexpr Ptr<ValueType> Data() {
        return _data;
    }

    inline constexpr SizeType Size() const {
        return SizeValue;
    }

public:

    inline constexpr Iterator begin() {
        return _data;
    }

    inline constexpr Iterator end() {
        return _data + SizeValue;
    }

    inline constexpr ConstIterator begin() const {
        return _data;
    }

    inline constexpr ConstIterator end() const {
        return _data + SizeValue;
    }

public:

    inline constexpr LRef<Array<ValueType, SizeValue>> operator=(ConstLRef<Array<ValueType, SizeValue>> array) {
        if (this == &array) {
            return *this;
        }

        for (U64 index = 0; auto &value : array) {
            _data[index] = value;

            ++index;
        }

        return *this;
    }

    inline constexpr LRef<Array<ValueType, SizeValue>> operator=(RRef<Array<ValueType, SizeValue>> array) noexcept {
        if (this == &array) {
            return *this;
        }

        for (U64 index = 0; auto &value : array) {
            _data[index] = value;

            ++index;
        }

        return *this;
    }

    inline constexpr Bool operator==(ConstLRef<Array<ValueType, SizeValue>> array) const {
        for (U64 index = 0; auto &value : array) {
            if (_data[index] != value) {
                return false;
            }

            ++index;
        }

        return true;
    }

    inline constexpr Bool operator!=(ConstLRef<Array<ValueType, SizeValue>> array) const {
        return !(*this == array);
    }

    inline constexpr LRef<ValueType> operator[](ConstLRef<U64> index) {
        if (index >= 0 && index < SizeValue) {
            return _data[index];
        }

        throw std::runtime_error("Array::operator[](ConstLRef<U64>): Index out of range!");
    }

    inline constexpr ConstLRef<ValueType> operator[](ConstLRef<U64> index) const {
        if (index >= 0 && index < SizeValue) {
            return _data[index];
        }

        throw std::runtime_error("Array::operator[](ConstLRef<U64>) const: Index out of range!");
    }

private:

    ValueType _data[SizeValue];
};

template<typename ValueT, auto SizeV>
inline constexpr Array<ValueT, SizeV> make_array() {
    return Array<ValueT, SizeV>();
}

template<typename ValueT, auto SizeV>
inline constexpr Array<ValueT, SizeV> make_array(std::initializer_list<ValueT> initializerList) {
    return Array<ValueT, SizeV>(initializerList);
}

template<typename ValueT, auto SizeV>
inline constexpr Array<ValueT, SizeV> make_array(ConstLRef<Array<ValueT, SizeV>> array) {
    return Array<ValueT, SizeV>(array);
}

template<typename ValueT, auto SizeV>
inline constexpr Array<ValueT, SizeV> make_array(RRef<Array<ValueT, SizeV>> array) {
    return Array<ValueT, SizeV>(array);
}

namespace std {

    template<typename ValueT, auto SizeV>
    constexpr size_t size(ConstLRef<Array<ValueT, SizeV>> array) noexcept {
        return array.Size();
    }

    template<typename ValueT, auto SizeV>
    constexpr auto data(LRef<Array<ValueT, SizeV>> array) {
        return array.Data();
    }

}

#endif //GSCROSSPLATFORM_ARRAY_H
