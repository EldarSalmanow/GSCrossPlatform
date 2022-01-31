#ifndef GSCROSSPLATFORM_GS_CROSSPLATFORMIO_H
#define GSCROSSPLATFORM_GS_CROSSPLATFORMIO_H

#include <GSCrossPlatform/GS_CrossPlatformUnicodeConversions.h>

namespace CrossPlatform {

    template<typename T>
    class Stream {
    public:

        using DataT = T;

    public:

        virtual ~Stream();

    public:

        virtual DataT Get() = 0;

        virtual Void Put(DataT data) = 0;

    public:

        virtual LRef<Stream<DataT>> operator>>(LRef<DataT> data) = 0;

        virtual LRef<Stream<DataT>> operator<<(DataT data) = 0;
    };

    template<typename T>
    class BasicStream : public Stream<T> {
    public:

        using DataT = typename Stream<T>::DataT;

    public:

        ~BasicStream() override;

    public:

        DataT Get() override;

        Void Put(DataT data) override;

    public:

        LRef<Stream<DataT>> operator>>(LRef<DataT> data) override;

        LRef<Stream<DataT>> operator<<(DataT data) override;
    };

    template<typename T>
    class DataStream : virtual public BasicStream<T> {
    public:

        using DataT = typename BasicStream<T>::DataT;

    public:

        ~DataStream() override;
    };

    enum class Seek {
        Begin,
        Current,
        End
    };

    using PositionOffset = I64;

    class StreamPosition {
    public:

        StreamPosition();

        StreamPosition(Seek seek, PositionOffset offset);

    public:

        Seek getSeek();

        PositionOffset getOffset();

    private:

        Seek _seek;

        PositionOffset _offset;
    };

    template<typename T>
    class BufferedStream : virtual public BasicStream<T> {
    public:

        using DataT = typename BasicStream<T>::DataT;

    public:

        ~BufferedStream() override;

    public:

        virtual StreamPosition GetPosition() = 0;

        virtual Bool SetPosition(StreamPosition position) = 0;
    };

    template<typename T>
    class BufferedDataStream : public DataStream<T>, public BufferedStream<T> {
    public:

        static_assert(std::is_same_v<typename DataStream<T>::DataT, typename BufferedStream<T>::DataT>,
                      "DataT DataStream and BufferedStream are different!");

        using DataT = typename DataStream<T>::DataT;

    public:

        ~BufferedDataStream() override;
    };

    template<typename T>
    class StreamCursor {
    public:

        using DataT = typename BufferedDataStream<T>::DataT;

    public:

        explicit StreamCursor(Ptr<BufferedDataStream<T>> stream)
                : _stream(stream) {}

    public:

        DataT Current() {
            auto data = _stream->Get();

            Prev();

            return data;
        }

        Void Next() {
            StreamPosition position(Seek::Current, 1);

            _stream->SetPosition(position);
        }

        Void Prev() {
            StreamPosition position(Seek::Current, -1);

            _stream->SetPosition(position);
        }

    private:

        Ptr<BufferedDataStream<T>> _stream;
    };

    class UnicodeStream : public DataStream<USymbol> {
    public:

        using DataT = DataStream<USymbol>::DataT;

    public:

        ~UnicodeStream() override;
    };

    class BufferedUnicodeStream : public BufferedDataStream<UnicodeStream::DataT> {
    public:

        ~BufferedUnicodeStream() override;
    };

    class FileImplementation;

    /**
    * File open mode type
    */
    using FileOpenMode = U8;

    /**
     * Input file open mode
     */
    inline Const<FileOpenMode> in_mode = 0x1;

    /**
     * Output file open mode
     */
    inline Const<FileOpenMode> out_mode = 0x2;

    class UFileStream : public UnicodeStream {
    public:

        using DataT = BufferedUnicodeStream::DataT;

    public:

        UFileStream();

        explicit UFileStream(Ptr<FileImplementation> implementation);

    public:

        ~UFileStream() override;

    public:

        Bool Open(ConstLRef<UString> name, ConstLRef<FileOpenMode> mode);

        Bool Close();

        Bool IsEOF();

    public:

        DataT Get() override;

        Void Put(DataT data) override;

    private:

        Ptr<FileImplementation> _implementation;
    };

    /**
     * Reading unicode string from stream
     * @param stream Stream
     * @param string Unicode string
     * @return Reference to stream
     */
    inline LRef<UnicodeStream> operator>>(LRef<UnicodeStream> stream, LRef<UString> string) {
        auto codePoint = stream.Get();

        while (codePoint != USymbol(StaticCast<CodePoint>(0xA))) {
            string += codePoint;

            codePoint = stream.Get();
        }

        return stream;
    }

    /**
     * Writing unicode string to stream
     * @param stream Stream
     * @param string Unicode string
     * @return Reference to stream
     */
    inline LRef<UnicodeStream> operator<<(LRef<UnicodeStream> stream, ConstLRef<UString> string) {
        for (auto &symbol: string.getSymbols()) {
            stream.Put(symbol.getCodePoint());
        }

        return stream;
    }

    /**
     * Unicode console out stream
     * @return Unicode console out stream
     */
    LRef<UnicodeStream> UCOut();

    /**
     * Unicode console error stream
     * @return Unicode console error stream
     */
    LRef<UnicodeStream> UCErr();

    /**
     * Unicode console input stream
     * @return Unicode console input stream
     */
    LRef<UnicodeStream> UCIn();

}

#endif //GSCROSSPLATFORM_GS_CROSSPLATFORMIO_H
