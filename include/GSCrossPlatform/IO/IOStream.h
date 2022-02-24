#ifndef FEATURESTESTING_IOSTREAM_H
#define FEATURESTESTING_IOSTREAM_H

#include <GSCrossPlatform/Encoding.h>

#include <GSCrossPlatform/IO/IOStreamTraits.h>

namespace CrossPlatform {

    template<typename ValueT, typename TraitsT>
    class IStreamBase {
    public:

        using Traits = TraitsT;

        using Value  = typename Traits::Value;

    public:

        virtual ~IStreamBase() = default;

    public:

        virtual Value Read() = 0;

        virtual Void Write(Value value) = 0;
    };

    template<typename ValueT, typename TraitsT>
    class StreamBase : public IStreamBase<ValueT, TraitsT> {
    public:

        using Traits = typename IStreamBase<ValueT, TraitsT>::Traits;

        using Value  = typename Traits::Value;
    };

    template<typename ValueT, typename TraitsT>
    class HandleStreamBase : public StreamBase<ValueT, TraitsT> {
    public:

        using Traits = typename StreamBase<ValueT, TraitsT>::Traits;

        using Value  = typename Traits::Value;

        using Handle = typename Traits::Handle;

    public:

        HandleStreamBase() = default;

        explicit HandleStreamBase(ConstLRef<Handle> handle)
                : _handle(handle) {}

    public:

        LRef<Handle> GetHandle() {
            return _handle;
        }

    private:

        Handle _handle;
    };

    template<typename ValueT, typename TraitsT>
    class FileStreamBase : public HandleStreamBase<ValueT, TraitsT> {
    public:

        using Traits = typename HandleStreamBase<ValueT, TraitsT>::Traits;

        using Value  = typename Traits::Value;

        using Handle = typename Traits::Handle;

    public:

        FileStreamBase() = default;

        explicit FileStreamBase(ConstLRef<Handle> handle)
                : HandleStreamBase<ValueT, TraitsT>(handle) {}

        explicit FileStreamBase(ConstLRef<UString> name)
                : FileStreamBase(name, InOutMode) {}

        FileStreamBase(ConstLRef<UString> name, ConstLRef<OpenMode> mode) {
            if (!Open(name, mode)) {
                throw UException(U"Can`t open file \'"_us + name + U"\'!"_us);
            }
        }

    public:

        ~FileStreamBase() override {
            Close();
        }

    public:

        Bool Open(ConstLRef<UString> name, ConstLRef<OpenMode> mode) {
            return this->GetHandle().Open(name, mode);
        }

        Void Close() {
            return this->GetHandle().Close();
        }

    public:

        Value Read() override {
            return StaticCast<Value>(this->GetHandle().ReadByte());
        }

        Void Write(Value value) override {
            return this->GetHandle().WriteByte(StaticCast<Byte>(value));
        }
    };

    template<typename TraitsT>
    class FileStreamBase<CodePoint, TraitsT> : public HandleStreamBase<CodePoint, TraitsT> {
    public:

        using Traits = typename HandleStreamBase<CodePoint, TraitsT>::Traits;

        using Value  = typename Traits::Value;

        using Handle = typename Traits::Handle;

    public:

        FileStreamBase() = default;

        explicit FileStreamBase(ConstLRef<Handle> handle)
                : HandleStreamBase<CodePoint, TraitsT>(handle) {}

        explicit FileStreamBase(ConstLRef<UString> name)
                : FileStreamBase(name, InOutMode) {}

        FileStreamBase(ConstLRef<UString> name, ConstLRef<OpenMode> mode) {
            if (!Open(name, mode)) {
                throw UException(U"Can`t open file \'"_us + name + U"\'!"_us);
            }
        }

    public:

        ~FileStreamBase() override {
            Close();
        }

    public:

        Bool Open(ConstLRef<UString> name, ConstLRef<OpenMode> mode) {
            return this->GetHandle().Open(name, mode);
        }

        Void Close() {
            return this->GetHandle().Close();
        }

    public:

        Value Read() override {
            auto byte = this->GetHandle().ReadByte();

            auto size = Conversions::SymbolSizeUTF8(byte);

            Vector<Byte> bytes;

            bytes.emplace_back(byte);

            for (auto i = 1; i < size; ++i) {
                bytes.emplace_back(this->GetHandle().ReadByte());
            }

            return Conversions::Decode(bytes, Encoding::UTF8);
        }

        Void Write(Value value) override {
            for (auto &byte : Conversions::Encode(value, Encoding::UTF8)) {
                this->GetHandle().WriteByte(byte);
            }
        }
    };

    template<typename ValueT>
    using IStream = IStreamBase<ValueT, StreamTraits<ValueT>>;

    template<typename ValueT>
    using Stream = StreamBase<ValueT, StreamTraits<ValueT>>;

    template<typename ValueT>
    using HandleStream = HandleStreamBase<ValueT, HandleStreamTraits<ValueT, Handle>>;

    template<typename ValueT>
    using FileStream = FileStreamBase<ValueT, FileStreamTraits<ValueT, FileHandle>>;

    using ByteFileStream = FileStream<Byte>;

    using UnicodeFileStream = FileStream<CodePoint>;

    LRef<UnicodeFileStream> UCOut();

    LRef<UnicodeFileStream> UCIn();

    LRef<UnicodeFileStream> UCErr();

}

#endif //FEATURESTESTING_IOSTREAM_H
