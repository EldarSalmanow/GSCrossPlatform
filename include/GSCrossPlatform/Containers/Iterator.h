#ifndef GSCROSSPLATFORM_ITERATOR_H
#define GSCROSSPLATFORM_ITERATOR_H

#include <GSCrossPlatform/Utils.h>

namespace CrossPlatform {

    template<typename T>
    class Iterable {
    public:

        using IteratorT = T;

    public:

        virtual ~Iterable() = default;

    public:

        virtual IteratorT begin() = 0;

        virtual IteratorT end() = 0;
    };

    template<typename T, typename R>
    class Iterator {
    public:

        using DataT = T;

        using IteratorT = R;

    public:

        virtual ~Iterator() = default;

    public:

        virtual LRef<DataT> operator*() = 0;

        virtual Ptr<DataT> operator->() = 0;

        virtual LRef<IteratorT> operator++() = 0;

        virtual LRef<IteratorT> operator--() = 0;

        virtual Bool operator==(ConstLRef<IteratorT> iterator) const = 0;

        virtual Bool operator!=(ConstLRef<IteratorT> iterator) const = 0;
    };

}

#endif //GSCROSSPLATFORM_ITERATOR_H
