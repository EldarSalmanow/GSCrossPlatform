#ifndef GSCROSSPLATFORM_ITERATOR_H
#define GSCROSSPLATFORM_ITERATOR_H

#include <GSCrossPlatform/Utils/Types.h>

namespace CrossPlatform {

    template<typename IteratorT>
    class Iterable {
    public:

        using Iterator = IteratorT;

    public:

        virtual ~Iterable() = default;

    public:

        virtual Iterator begin() = 0;

        virtual Iterator end() = 0;
    };

    template<typename DataT, typename IteratorT>
    class Iterator {
    public:

        using Data = DataT;

        using ChildIterator = IteratorT;

    public:

        virtual ~Iterator() = default;

    public:

        virtual LRef<Data> operator*() = 0;

        virtual Ptr<Data> operator->() = 0;

        virtual LRef<ChildIterator> operator++() = 0;

        virtual LRef<ChildIterator> operator--() = 0;

        virtual Bool operator==(ConstLRef<ChildIterator> iterator) const = 0;

        virtual Bool operator!=(ConstLRef<ChildIterator> iterator) const = 0;
    };

}

#endif //GSCROSSPLATFORM_ITERATOR_H
