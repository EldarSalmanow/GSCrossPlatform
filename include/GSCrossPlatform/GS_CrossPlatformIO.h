#ifndef GSCROSSPLATFORM_GS_CROSSPLATFORMIO_H
#define GSCROSSPLATFORM_GS_CROSSPLATFORMIO_H

#include <GSCrossPlatform/GS_CrossPlatformUnicodeConversions.h>

namespace CrossPlatform {

//    namespace New {

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

            static_assert(std::is_same_v<typename DataStream<T>::DataT, typename BufferedStream<T>::DataT>, "DataT DataStream and BufferedStream are different!");

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
        for (auto &symbol : string.getSymbols()) {
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

//    }

//    template<typename T>
//    class Source {
//    public:
//
//        using DataT = T;
//
//    public:
//
//        virtual ~Source();
//
//    public:
//
//        virtual DataT Get() = 0;
//
//        virtual Void Put(DataT data) = 0;
//    };
//
//    template<typename T>
//    class Stream {
//    public:
//
//        using DataT = T;
//
//    public:
//
//        virtual ~Stream();
//
//    public:
//
//        virtual DataT Get() = 0;
//
//        virtual Void Put(DataT data) = 0;
//
//    public:
//
//        virtual LRef<Stream<DataT>> operator>>(LRef<DataT> data) = 0;
//
//        virtual LRef<Stream<DataT>> operator<<(DataT data) = 0;
//    };
//
//    template<typename T>
//    class BasicSource : public Source<T> {
//    public:
//
//        using DataT = typename Source<T>::DataT;
//
//    public:
//
//        ~BasicSource() override;
//    };
//
//    template<typename T>
//    class BasicStream : public Stream<T> {
//    public:
//
//        using DataT = typename Stream<T>::DataT;
//
//    public:
//
//        explicit BasicStream(Ptr<BasicSource<DataT>> source);
//
//    public:
//
//        ~BasicStream() override;
//
//    public:
//
//        Ptr<BasicSource<DataT>> GetSource();
//
//    public:
//
//        DataT Get() override;
//
//        Void Put(DataT data) override;
//
//    public:
//
//        LRef<Stream<DataT>> operator>>(LRef<DataT> data) override;
//
//        LRef<Stream<DataT>> operator<<(DataT data) override;
//
//    private:
//
//        Ptr<BasicSource<T>> _source;
//    };
//
//    template<typename T>
//    class DataSource : public BasicSource<T> {
//    public:
//
//        ~DataSource() override;
//    };
//
//    template<typename T>
//    class DataStream : public BasicStream<T> {
//    public:
//
//        using DataT = typename BasicStream<T>::DataT;
//
//    public:
//
//        explicit DataStream(Ptr<DataSource<DataT>> source);
//
//    public:
//
//        Ptr<DataSource<DataT>> GetDataSource();
//    };
//
//    class ByteSource : public DataSource<Byte> {
//    public:
//
//        using DataT = DataSource<Byte>::DataT;
//    };
//
//    class ByteStream : public DataStream<Byte> {
//    public:
//
//        using DataT = DataStream<Byte>::DataT;
//
//    public:
//
//        explicit ByteStream(Ptr<ByteSource> source);
//
//    public:
//
//        Ptr<ByteSource> GetByteSource();
//    };
//
//    class UnicodeSource : public DataSource<USymbol> {
//    public:
//
//        using DataT = DataSource<USymbol>::DataT;
//    };
//
//    class UnicodeStream : public DataStream<USymbol> {
//    public:
//
//        using DataT = DataStream<USymbol>::DataT;
//
//    public:
//
//        explicit UnicodeStream(Ptr<UnicodeSource> source);
//
//    public:
//
//        Ptr<UnicodeSource> GetUnicodeSource();
//    };
//
//    class UStringSource : public UnicodeSource {
//    public:
//
//        using DataT = UnicodeSource::DataT;
//
//    public:
//
//        explicit UStringSource(ConstLRef<UString> string);
//
//    public:
//
//        DataT Get() override;
//
//        Void Put(DataT data) override;
//
//    private:
//
//        UString _string;
//
//        UString::IteratorT _iterator;
//    };
//
//    class UStringStream : public UnicodeStream {
//    public:
//
//        using DataT = UnicodeStream::DataT;
//
//    public:
//
//        explicit UStringStream(ConstLRef<UString> string);
//
//    public:
//
//        Ptr<UStringSource> GetUStringSource();
//    };
//
//    class FileImplementation;
//
//    enum class FilePositionPoint {
//        Current,
//        Begin,
//        End
//    };
//
//    using FilePositionOffset = unsigned long;
//
//    class FilePosition {
//    public:
//
//        FilePosition()
//                : _point(FilePositionPoint::Current), _offset(0) {}
//
//        FilePosition(FilePositionPoint point, FilePositionOffset offset)
//                : _point(point), _offset(offset) {}
//
//    public:
//
//        FilePositionPoint getPoint() {
//            return _point;
//        }
//
//        FilePositionOffset getOffset() {
//            return _offset;
//        }
//
//    private:
//
//        FilePositionPoint _point;
//
//        FilePositionOffset _offset;
//    };
//
//    /**
//     * File open mode type
//     */
//    using FileOpenMode = U8;
//
//    /**
//     * Input file open mode
//     */
//    inline Const<FileOpenMode> in_mode = 0x1;
//
//    /**
//     * Output file open mode
//     */
//    inline Const<FileOpenMode> out_mode = 0x2;
//
//    /**
//     * Binary file open mode
//     */
//    inline Const<FileOpenMode> bin_mode = 0x4;
//
//    class UFileSource : public UnicodeSource {
//    public:
//
//        UFileSource();
//
//        explicit UFileSource(Ptr<FileImplementation> implementation);
//
//    public:
//
//        ~UFileSource() override;
//
//    public:
//
//        Bool Open(ConstLRef<UString> name, ConstLRef<FileOpenMode> mode);
//
//        Bool Close();
//
//        Bool GetPosition(LRef<FilePosition> position);
//
//        Bool SetPosition(LRef<FilePosition> position);
//
//    public:
//
//        DataT Get() override;
//
//        Void Put(DataT data) override;
//
//    private:
//
//        Ptr<FileImplementation> _implementation;
//    };
//
//    class UFileStream : public UnicodeStream {
//    public:
//
//        UFileStream();
//
//        explicit UFileStream(Ptr<UFileSource> source);
//
//    public:
//
//        Bool Open(ConstLRef<UString> name, ConstLRef<FileOpenMode> mode);
//
//    public:
//
//        Ptr<UFileSource> GetUFileSource();
//    };
//
//    /**
//     * Reading unicode string from stream
//     * @param stream Stream
//     * @param string Unicode string
//     * @return Reference to stream
//     */
//    inline LRef<UnicodeStream> operator>>(LRef<UnicodeStream> stream, LRef<UString> string) {
//        auto codePoint = stream.Get();
//
//        while (codePoint != USymbol(StaticCast<CodePoint>(0xA))) {
//            string += codePoint;
//
//            codePoint = stream.Get();
//        }
//
//        return stream;
//    }
//
//    /**
//     * Writing unicode string to stream
//     * @param stream Stream
//     * @param string Unicode string
//     * @return Reference to stream
//     */
//    inline LRef<UnicodeStream> operator<<(LRef<UnicodeStream> stream, ConstLRef<UString> string) {
//        for (auto &symbol : string.getSymbols()) {
//            stream.Put(symbol.getCodePoint());
//        }
//
//        return stream;
//    }
//
//    /**
//     * Unicode console out stream
//     * @return Unicode console out stream
//     */
//    LRef<UnicodeStream> UCOut();
//
//    /**
//     * Unicode console error stream
//     * @return Unicode console error stream
//     */
//    LRef<UnicodeStream> UCErr();
//
//    /**
//     * Unicode console input stream
//     * @return Unicode console input stream
//     */
//    LRef<UnicodeStream> UCIn();

}

#endif //GSCROSSPLATFORM_GS_CROSSPLATFORMIO_H
