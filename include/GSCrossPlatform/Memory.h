#ifndef GSCROSSPLATFORM_MEMORY_H
#define GSCROSSPLATFORM_MEMORY_H

#include <GSCrossPlatform/Types.h>

template<typename ValueT>
class UniquePtr {
public:

    using ValueType = ValueT;

public:

    constexpr UniquePtr()
            : _pointer(nullptr) {}

    constexpr UniquePtr(Ptr<ValueType> pointer)
            : _pointer(pointer) {}

public:

    constexpr UniquePtr(ConstLRef<UniquePtr<ValueType>> uniquePtr) = delete;

    constexpr UniquePtr(RRef<UniquePtr<ValueType>> uniquePtr) noexcept {
        if (this == &uniquePtr) {
            return *this;
        }

        _pointer = uniquePtr._pointer;

        uniquePtr._pointer = nullptr;
    }

public:

    constexpr ~UniquePtr() {
        delete _pointer;
    }

public:

    inline constexpr LRef<UniquePtr<ValueType>> operator=(ConstLRef<UniquePtr<ValueType>> uniquePtr) = delete;

    inline constexpr LRef<UniquePtr<ValueType>> operator=(RRef<UniquePtr<ValueType>> uniquePtr) {
        if (this == &uniquePtr) {
            return *this;
        }

       _pointer = uniquePtr._pointer;

       uniquePtr._pointer = nullptr;

       return *this;
    }

    inline constexpr LRef<ValueType> operator*() {
        return *_pointer;
    }

    inline constexpr Ptr<ValueType> operator->() {
        return _pointer;
    }

private:

    Ptr<ValueType> _pointer;
};

#endif //GSCROSSPLATFORM_MEMORY_H
