#ifndef FEATURESTESTING_HANDLE_H
#define FEATURESTESTING_HANDLE_H

#include <GSCrossPlatform/Containers.h>

#include <GSCrossPlatform/IO/HandleTraits.h>

namespace CrossPlatform {

    template<typename HandleT, typename TraitsT>
    class IHandleBase {
    public:

        using NativeHandle = HandleT;

        using Traits       = TraitsT;

    public:

        virtual ~IHandleBase() = default;

    public:

        virtual NativeHandle GetNativeHandle() = 0;

        virtual Bool SetNativeHandle(NativeHandle handle) = 0;
    };

    template<typename HandleT, typename TraitsT>
    class HandleBase : public IHandleBase<HandleT, TraitsT> {
    public:

        using Traits       = typename IHandleBase<HandleT, TraitsT>::Traits;

        using NativeHandle = typename Traits::NativeHandle;

    public:

        HandleBase()
                : _handle(Traits::InvalidNativeHandle) {}

        explicit HandleBase(NativeHandle handle)
                : _handle(handle) {}

    public:

        NativeHandle GetNativeHandle() override {
            return this->_handle;
        }

        bool SetNativeHandle(NativeHandle handle) override {
            this->_handle = handle;

            return true;
        }

    private:

        NativeHandle _handle;
    };

    using OpenMode                   = std::uint8_t;

    inline Const<OpenMode> InMode    = 0x1;

    inline Const<OpenMode> OutMode   = 0x2;

    inline Const<OpenMode> InOutMode = InMode | OutMode;

    template<typename HandleT, typename TraitsT>
    class FileHandleBase : public HandleBase<HandleT, TraitsT> {
    public:

        using Traits         = typename HandleBase<HandleT, TraitsT>::Traits;

        using NativeHandle   = typename Traits::NativeHandle;

    public:

        FileHandleBase() = default;

        explicit FileHandleBase(NativeHandle handle) {
            this->SetNativeHandle(handle);
        }

        explicit FileHandleBase(ConstLRef<UString> name)
                : FileHandleBase(name, InOutMode) {}

        FileHandleBase(ConstLRef<UString> name, ConstLRef<OpenMode> mode) {
            this->Open(name, mode);
        }

    public:

        ~FileHandleBase() override {
            this->Close();
        }

    public:

        Byte ReadByte() {
            throw UException(U"FileHandle<HandleT, TraitsT>::ReadByte() not specialized!"_us);
        }

        Void WriteByte(ConstLRef<Byte> byte) {
            throw UException(U"FileHandle<HandleT, TraitsT>::WriteByte(ConstLRef<Byte>) not specialized!"_us);
        }

    public:

        Bool Open(ConstLRef<UString> name, ConstLRef<OpenMode> mode) {
            throw UException(U"FileHandle<HandleT, TraitsT>::Open(ConstLRef<UString>, ConstLRef<OpenMode>) not specialized!"_us);
        }

        Bool Close() {
            throw UException(U"FileHandle<HandleT, TraitsT>::Close() not specialized!"_us);
        }
    };

    template<typename TraitsT>
    class FileHandleBase<Windows::NativeHandle, TraitsT> : public HandleBase<Windows::NativeHandle, TraitsT> {
    public:

        using Traits         = typename HandleBase<Windows::NativeHandle, TraitsT>::Traits;

        using NativeHandle   = typename Traits::NativeHandle;

    public:

        FileHandleBase() = default;

        explicit FileHandleBase(NativeHandle handle) {
            this->SetNativeHandle(handle);
        }

        explicit FileHandleBase(ConstLRef<UString> name)
                : FileHandleBase(name, InOutMode) {}

        FileHandleBase(ConstLRef<UString> name, ConstLRef<OpenMode> mode) {
            this->Open(name, mode);
        }

    public:

        ~FileHandleBase() override {
            this->Close();
        }

    public:

        Byte ReadByte() {
            Byte byte;

            DWORD read;

            auto result = ReadFile(this->GetNativeHandle(), &byte, 1, &read, nullptr);

            if (result != TRUE) {
                throw UException(U"Can`t read byte from file handle!"_us);
            }

            return byte;
        }

        Void WriteByte(ConstLRef<Byte> byte) {
            DWORD writen;

            auto result = WriteFile(this->GetNativeHandle(), &byte, 1, &writen, nullptr);

            if (result != TRUE) {
                throw UException(U"Can`t write byte to file handle!"_us);
            }
        }

    public:

        Bool Open(ConstLRef<UString> name, ConstLRef<OpenMode> mode) {
            Close();

            auto fileName = name.asCStringBytes();

            DWORD fileOpenMode;

            if (mode & InMode) {
                fileOpenMode |= GENERIC_READ;
            }

            if (mode & OutMode) {
                fileOpenMode |= GENERIC_WRITE;
            }

            auto handle = CreateFileA(ReinterpretCast<Ptr<C8>>(fileName.data()), fileOpenMode, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

            this->SetNativeHandle(handle);

            if (handle == Traits::InvalidNativeHandle) {
                return false;
            }

            return true;
        }

        Void Close() {
            return CloseHandle(this->GetNativeHandle());
        }
    };

    using IHandle = IHandleBase<NativeHandle, HandleTraits<NativeHandle>>;

    using Handle = HandleBase<NativeHandle, HandleTraits<NativeHandle>>;

    using FileHandle = FileHandleBase<NativeHandle, FileHandleTraits<NativeHandle>>;

}

#endif //FEATURESTESTING_HANDLE_H
