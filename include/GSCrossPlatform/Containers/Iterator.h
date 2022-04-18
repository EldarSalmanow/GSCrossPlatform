#ifndef GSCROSSPLATFORM_ITERATOR_H
#define GSCROSSPLATFORM_ITERATOR_H

#include <GSCrossPlatform/Utils/Types.h>

namespace CrossPlatform {

    /**
     * Interface for realise Iterator programming pattern
     * @tparam IteratorT Iterator type
     */
    template<typename IteratorT>
    class Iterable {
    public:

        /**
         * Iterator type
         */
        using Iterator = IteratorT;

    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~Iterable() = default;

    public:

        /**
         * Getting begin iterator of iterable object
         * @return Begin iterator
         */
        virtual Iterator begin() = 0;

        /**
         * Getting end iterator for iterable object
         * @return End iterator
         */
        virtual Iterator end() = 0;
    };

    /**
     * Base class for iterators
     * @tparam DataT Piece of data type which realise Iterable interface
     * @tparam IteratorT Child iterator type which realise this interface
     */
    template<typename DataT, typename IteratorT>
    class Iterator {
    public:

        /**
         * Piece of iterable data type
         */
        using Data = DataT;

        /**
         * Child iterator type
         */
        using ChildIterator = IteratorT;

    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~Iterator() = default;

    public:

        /**
         * Dereference operator
         * @return Data
         */
        virtual LRef<Data> operator*() = 0;

        /**
         * Member access operator
         * @return Pointer to data
         */
        virtual Ptr<Data> operator->() = 0;

        /**
         * Increment operator
         * @return Incremented iterator
         */
        virtual LRef<ChildIterator> operator++() = 0;

        /**
         * Decrement operator
         * @return Decremented iterator
         */
        virtual LRef<ChildIterator> operator--() = 0;

        /**
         * Comparing operator
         * @param iterator Iterator for comparing
         * @return Is equals
         */
        virtual Bool operator==(ConstLRef<ChildIterator> iterator) const = 0;

        /**
         * Not comparing operator
         * @param iterator Iterator for comparing
         * @return Is not equals
         */
        virtual Bool operator!=(ConstLRef<ChildIterator> iterator) const = 0;
    };

}

#endif //GSCROSSPLATFORM_ITERATOR_H
