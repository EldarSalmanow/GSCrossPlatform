#ifndef FEATURESTESTING_IOSTREAMTRAITS_H
#define FEATURESTESTING_IOSTREAMTRAITS_H

#include <GSCrossPlatform/IO/Handle.h>

namespace CrossPlatform {

    template<typename ValueT>
    class StreamTraitsBase {
    public:

        using Value = ValueT;
    };

    template<typename ValueT, typename HandleT>
    class HandleStreamTraitsBase : public StreamTraitsBase<ValueT> {
    public:

        using Value  = typename StreamTraitsBase<ValueT>::Value;

        using Handle = HandleT;
    };

    template<typename ValueT, typename HandleT>
    class FileStreamTraitsBase : public HandleStreamTraitsBase<ValueT, HandleT> {
    public:

        using Value  = typename HandleStreamTraitsBase<ValueT, HandleT>::Value;

        using Handle = typename HandleStreamTraitsBase<ValueT, HandleT>::Handle;
    };

    template<typename ValueT>
    using StreamTraits = StreamTraitsBase<ValueT>;

    template<typename ValueT, typename HandleT>
    using HandleStreamTraits = HandleStreamTraitsBase<ValueT, HandleT>;

    template<typename ValueT, typename HandleT>
    using FileStreamTraits = FileStreamTraitsBase<ValueT, HandleT>;

}

#endif //FEATURESTESTING_IOSTREAMTRAITS_H
