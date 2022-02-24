#ifndef FEATURESTESTING_HANDLETRAITS_H
#define FEATURESTESTING_HANDLETRAITS_H

#include <GSCrossPlatform/Utils.h>

#if defined(GS_OS_WINDOWS)

    #include <Windows.h>

#endif

namespace CrossPlatform {

    namespace Windows {

#if defined(GS_OS_WINDOWS)

        using NativeHandle = HANDLE;

        inline Const<NativeHandle> InvalidNativeHandle = INVALID_HANDLE_VALUE;

#endif

    }

#if defined(GS_OS_WINDOWS)

    using NativeHandle = Windows::NativeHandle;

#endif

    template<typename HandleT>
    class HandleTraitsBase {
    public:

        using NativeHandle = HandleT;

    public:

        inline static Const<NativeHandle> InvalidNativeHandle = 0;
    };

    template<>
    class HandleTraitsBase<Windows::NativeHandle> {
    public:

        using NativeHandle = Windows::NativeHandle;

    public:

        inline static Const<NativeHandle> InvalidNativeHandle = Windows::InvalidNativeHandle;
    };

    template<typename HandleT>
    class FileHandleTraitsBase : public HandleTraitsBase<HandleT> {
    public:

        using NativeHandle = typename HandleTraitsBase<HandleT>::NativeHandle;
    };

    template<typename HandleT>
    using HandleTraits = HandleTraitsBase<HandleT>;

    template<typename HandleT>
    using FileHandleTraits = FileHandleTraitsBase<HandleT>;

}

#endif //FEATURESTESTING_HANDLETRAITS_H
