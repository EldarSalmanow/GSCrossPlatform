#include <GSCrossPlatform/GS_CrossPlatformString.h>

#include <GSCrossPlatform/GS_CrossPlatformIO.h>

#if defined(GS_OS_WINDOWS)
    #if defined(GS_COMPILER_MSVC)
        #include <Windows.h>
    #elif defined(GS_COMPILER_MINGW)
        #include <windows.h>
    #endif
#endif

namespace CrossPlatform {

    template<typename T>
    Stream<T>::~Stream<T>() = default;

    template<typename T>
    BasicStream<T>::~BasicStream<T>() = default;

    template<typename T>
    typename BasicStream<T>::DataT BasicStream<T>::Get() {
        throw UException(U"BasicStream<T>::Get() not implemented!");
    }

    template<typename T>
    Void BasicStream<T>::Put(DataT data) {
        throw UException(U"BasicStream<T>::Put(DataT) not implemented!");
    }

    template<typename T>
    LRef<Stream<typename BasicStream<T>::DataT>> BasicStream<T>::operator>>(LRef<DataT> data) {
        data = Get();

        return *this;
    }

    template<typename T>
    LRef<Stream<typename BasicStream<T>::DataT>> BasicStream<T>::operator<<(DataT data) {
        Put(data);

        return *this;
    }

    template<typename T>
    DataStream<T>::~DataStream<T>() = default;

    StreamPosition::StreamPosition()
            : _seek(Seek::Current), _offset(0) {}

    StreamPosition::StreamPosition(Seek seek, PositionOffset offset)
            : _seek(seek), _offset(offset) {}

    Seek StreamPosition::getSeek() {
        return _seek;
    }

    PositionOffset StreamPosition::getOffset() {
        return _offset;
    }

    template<typename T>
    BufferedStream<T>::~BufferedStream<T>() = default;

    template<typename T>
    BufferedDataStream<T>::~BufferedDataStream<T>() = default;

    UnicodeStream::~UnicodeStream() = default;

    BufferedUnicodeStream::~BufferedUnicodeStream() = default;

    class FileImplementation {
    public:

        virtual ~FileImplementation() = default;

    public:

        virtual Bool Open(ConstLRef<UString> name, ConstLRef<FileOpenMode> mode) = 0;

        virtual Bool Close() = 0;

        virtual Bool Read(LRef<Byte> byte) = 0;

        virtual Bool Write(LRef<Byte> byte) = 0;

        virtual Bool GetPosition(LRef<StreamPosition> position) = 0;

        virtual Bool SetPosition(LRef<StreamPosition> position) = 0;

        virtual Bool IsEOF() = 0;
    };

    class WindowsFileImplementation : public FileImplementation {
    public:

        WindowsFileImplementation()
                : _fileDescriptor(INVALID_HANDLE_VALUE), _hasOwner(false), _isEOF(false) {};

        explicit WindowsFileImplementation(HANDLE handle, Bool hasOwner = false)
                : _fileDescriptor(handle), _hasOwner(hasOwner), _isEOF(false) {}

    public:

        ~WindowsFileImplementation() override {
            if (!_hasOwner) {
                WindowsFileImplementation::Close();
            }
        }

    public:

        Bool Open(ConstLRef<UString> name, ConstLRef<FileOpenMode> mode) override {
            DWORD desiredAccess = 0;

            if (mode & in_mode) {
                desiredAccess |= GENERIC_READ;
            }

            if (mode & out_mode) {
                desiredAccess |= GENERIC_WRITE;
            }

            _fileDescriptor = CreateFileA(
                    ReinterpretCast<ConstPtr<C8>>(name.asCStringBytes().data()),
                    desiredAccess,
                    0,
                    nullptr,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL,
                    nullptr);

            if (_fileDescriptor == INVALID_HANDLE_VALUE) {
                return false;
            }

            return true;
        }

        Bool Close() override {
            auto result = CloseHandle(_fileDescriptor);

            if (result == FALSE) {
                return false;
            }

            return true;
        }

        Bool Read(LRef<Byte> byte) override {
            DWORD read;

            auto result = ReadFile(_fileDescriptor, &byte, 1, &read, nullptr);

            if (result == FALSE && read == 0) {
                _isEOF = true;

                return false;
            }

            return true;
        }

        Bool Write(LRef<Byte> byte) override {
            DWORD written = 0;

            auto result = WriteFile(_fileDescriptor, &byte, 1, &written, nullptr);

            if (result == FALSE) {
                return false;
            }

            return true;
        }

        Bool GetPosition(LRef<StreamPosition> position) override {
            auto filePosition = SetFilePointer(_fileDescriptor, 0, nullptr, FILE_CURRENT);

            if (filePosition == INVALID_SET_FILE_POINTER) {
                return false;
            }

            position = StreamPosition(Seek::Current, filePosition);

            return true;
        }

        Bool SetPosition(LRef<StreamPosition> position) override {
            DWORD moveMethod;

            switch (position.getSeek()) {
                case Seek::Current:
                    moveMethod = FILE_CURRENT;

                    break;
                case Seek::Begin:
                    moveMethod = FILE_BEGIN;

                    break;
                case Seek::End:
                    moveMethod = FILE_END;

                    break;
                default:
                    return false;
            }

            auto filePosition = SetFilePointer(_fileDescriptor, StaticCast<LONG>(position.getOffset()), nullptr, moveMethod);

            if (filePosition == INVALID_SET_FILE_POINTER) {
                return false;
            }

            return true;
        }

        Bool IsEOF() override {
            return _isEOF;
        }

    private:

        HANDLE _fileDescriptor;

        Bool _hasOwner;

        Bool _isEOF;
    };

    UFileStream::UFileStream() {
#if defined(GS_OS_WINDOWS)
        _implementation = new WindowsFileImplementation();
#endif
    }

    UFileStream::UFileStream(Ptr<FileImplementation> implementation)
            : _implementation(implementation) {}

    UFileStream::~UFileStream() {
        delete _implementation;
    }

    Bool UFileStream::Open(ConstLRef<UString> name, ConstLRef<FileOpenMode> mode) {
        return _implementation->Open(name, mode);
    }

    Bool UFileStream::Close() {
        return _implementation->Close();
    }

    Bool UFileStream::IsEOF() {
        return _implementation->IsEOF();
    }

    UFileStream::DataT UFileStream::Get() {
        Vector<Byte> bytes;

        Byte byte;

        _implementation->Read(byte);

        bytes.emplace_back(byte);

        auto size = Conversions::UTF8SymbolSize(bytes[0]);

        if (!size) {
            throw UException(U"Invalid size!");
        }

        for (auto i = 1; i < size; ++i) {
            _implementation->Read(byte);

            bytes.emplace_back(byte);
        }

        return Conversions::Decode(bytes, Encoding::UTF8, ByteEndian::Unknown);
    }

    Void UFileStream::Put(DataT data) {
        for (auto &byte : Conversions::Encode(data.getCodePoint(), Encoding::UTF8, ByteEndian::Unknown)) {
            _implementation->Write(byte);
        }
    }

    Ptr<FileImplementation> COutFile;
    Ptr<FileImplementation> CErrFile;
    Ptr<FileImplementation> CInFile;

    Ptr<UFileStream> COutStream;
    Ptr<UFileStream> CErrStream;
    Ptr<UFileStream> CInStream;

    class UIOInit {
    public:

        UIOInit() {
#if defined(GS_OS_WINDOWS)
            _codePage = GetConsoleCP();

            SetConsoleCP(CP_UTF8);
            SetConsoleOutputCP(CP_UTF8);

            COutFile = new WindowsFileImplementation(GetStdHandle(STD_OUTPUT_HANDLE), true);
            CErrFile = new WindowsFileImplementation(GetStdHandle(STD_ERROR_HANDLE), true);
            CInFile = new WindowsFileImplementation(GetStdHandle(STD_INPUT_HANDLE), true);
#endif
            COutStream = new UFileStream(COutFile);
            CErrStream = new UFileStream(CErrFile);
            CInStream = new UFileStream(CInFile);
        }

    public:

        ~UIOInit() {
            delete COutStream;
            delete CErrStream;
            delete CInStream;

#if defined(GS_OS_WINDOWS)
            SetConsoleOutputCP(_codePage);
            SetConsoleCP(_codePage);
#endif
        }

    private:

#if defined(GS_OS_WINDOWS)
        UINT _codePage;
#endif
    };

    UIOInit Init;

    LRef<UnicodeStream> UCOut() {
        return *COutStream;
    }

    LRef<UnicodeStream> UCErr() {
        return *CErrStream;
    }

    LRef<UnicodeStream> UCIn() {
        return *CInStream;
    }

//    template<typename T>
//    Source<T>::~Source() = default;
//
//    template<typename T>
//    Stream<T>::~Stream() = default;
//
//    template<typename T>
//    BasicSource<T>::~BasicSource<T>() = default;
//
//    template<typename T>
//    BasicStream<T>::BasicStream(Ptr<BasicSource<DataT>> source)
//            : _source(source) {}
//
//    template<typename T>
//    BasicStream<T>::~BasicStream() {
//        delete GetSource();
//    }
//
//    template<typename T>
//    Ptr<BasicSource<typename BasicStream<T>::DataT>> BasicStream<T>::GetSource() {
//        return _source;
//    }
//
//    template<typename T>
//    typename BasicStream<T>::DataT BasicStream<T>::Get() {
//        return _source->Get();
//    }
//
//    template<typename T>
//    Void BasicStream<T>::Put(DataT data) {
//        _source->Put(data);
//    }
//
//    template<typename T>
//    LRef<Stream<typename BasicStream<T>::DataT>> BasicStream<T>::operator>>(LRef<DataT> data) {
//        data = Get();
//
//        return *this;
//    }
//
//    template<typename T>
//    LRef<Stream<typename BasicStream<T>::DataT>> BasicStream<T>::operator<<(DataT data) {
//        Put(data);
//
//        return *this;
//    }
//
//    template<typename T>
//    DataSource<T>::~DataSource<T>() = default;
//
//    template<typename T>
//    DataStream<T>::DataStream(Ptr<DataSource<DataT>> source)
//            : BasicStream<DataT>(source) {}
//
//    template<typename T>
//    Ptr<DataSource<typename DataStream<T>::DataT>> DataStream<T>::GetDataSource() {
//        return ReinterpretCast<Ptr<DataSource<DataT>>>(BasicStream<DataT>::GetSource());
//    }
//
//    ByteStream::ByteStream(Ptr<ByteSource> source)
//            : DataStream<DataT>(source) {}
//
//    Ptr<ByteSource> ByteStream::GetByteSource() {
//        return ReinterpretCast<Ptr<ByteSource>>(DataStream<DataT>::GetDataSource());
//    }
//
//    UnicodeStream::UnicodeStream(Ptr<UnicodeSource> source)
//            : DataStream<DataT>(source) {}
//
//    Ptr<UnicodeSource> UnicodeStream::GetUnicodeSource() {
//        return ReinterpretCast<Ptr<UnicodeSource>>(DataStream<DataT>::GetDataSource());
//    }
//
//    UStringSource::UStringSource(ConstLRef<UString> string)
//            : _string(string), _iterator(_string.begin()) {}
//
//    UStringSource::DataT UStringSource::Get() {
//        if (_iterator != _string.end()) {
//            auto symbol = *_iterator;
//
//            ++_iterator;
//
//            return symbol;
//        }
//
//        throw UException(U"String position out of range!");
//    }
//
//    Void UStringSource::Put(DataT data) {
//        if (_iterator != _string.end()) {
//            *_iterator = data;
//
//            ++_iterator;
//
//            return;
//        }
//
//        throw UException(U"String position out of range!");
//    }
//
//    UStringStream::UStringStream(ConstLRef<UString> string)
//            : UnicodeStream(new UStringSource(string)) {}
//
//    Ptr<UStringSource> UStringStream::GetUStringSource() {
//        return ReinterpretCast<Ptr<UStringSource>>(UnicodeStream::GetUnicodeSource());
//    }
//
//    class FileImplementation {
//    public:
//
//        virtual ~FileImplementation() = default;
//
//    public:
//
//        virtual Bool Open(ConstLRef<UString> name, ConstLRef<FileOpenMode> mode) = 0;
//
//        virtual Bool Close() = 0;
//
//        virtual Bool Read(LRef<Byte> byte) = 0;
//
//        virtual Bool Write(LRef<Byte> byte) = 0;
//
//        virtual Bool GetPosition(LRef<FilePosition> position) = 0;
//
//        virtual Bool SetPosition(LRef<FilePosition> position) = 0;
//    };
//
//    class WindowsFileImplementation : public FileImplementation {
//    public:
//
//        WindowsFileImplementation()
//                : _fileDescriptor(INVALID_HANDLE_VALUE), _hasOwner(false) {};
//
//        explicit WindowsFileImplementation(HANDLE handle, Bool hasOwner = false)
//                : _fileDescriptor(handle), _hasOwner(hasOwner) {}
//
//    public:
//
//        ~WindowsFileImplementation() override {
//            if (!_hasOwner) {
//                WindowsFileImplementation::Close();
//            }
//        }
//
//    public:
//
//        Bool Open(ConstLRef<UString> name, ConstLRef<FileOpenMode> mode) override {
//            DWORD desiredAccess = 0;
//
//            if (mode & in_mode) {
//                desiredAccess |= GENERIC_READ;
//            }
//
//            if (mode & out_mode) {
//                desiredAccess |= GENERIC_WRITE;
//            }
//
//            _fileDescriptor = CreateFileA(
//                    ReinterpretCast<ConstPtr<C8>>(name.asCStringBytes().data()),
//                    desiredAccess,
//                    0,
//                    nullptr,
//                    OPEN_EXISTING,
//                    FILE_ATTRIBUTE_NORMAL,
//                    nullptr);
//
//            if (_fileDescriptor == INVALID_HANDLE_VALUE) {
//                return false;
//            }
//
//            return true;
//        }
//
//        Bool Close() override {
//            auto result = CloseHandle(_fileDescriptor);
//
//            if (result == FALSE) {
//                return false;
//            }
//
//            return true;
//        }
//
//        Bool Read(LRef<Byte> byte) override {
//            DWORD read;
//
//            auto result = ReadFile(GetStdHandle(STD_INPUT_HANDLE), &byte, 1, &read, nullptr);
//
//            if (result == FALSE) {
//                return false;
//            }
//
//            return true;
//        }
//
//        Bool Write(LRef<Byte> byte) override {
//            DWORD written = 0;
//
//            auto result = WriteFile(_fileDescriptor, &byte, 1, &written, nullptr);
//
//            if (result == FALSE) {
//                return false;
//            }
//
//            return true;
//        }
//
//        Bool GetPosition(LRef<FilePosition> position) override {
//            auto filePosition = SetFilePointer(_fileDescriptor, 0, nullptr, FILE_CURRENT);
//
//            if (filePosition == INVALID_SET_FILE_POINTER) {
//                return false;
//            }
//
//            position = FilePosition(FilePositionPoint::Current, filePosition);
//
//            return true;
//        }
//
//        Bool SetPosition(LRef<FilePosition> position) override {
//            DWORD moveMethod;
//
//            switch (position.getPoint()) {
//                case FilePositionPoint::Current:
//                    moveMethod = FILE_CURRENT;
//
//                    break;
//                case FilePositionPoint::Begin:
//                    moveMethod = FILE_BEGIN;
//
//                    break;
//                case FilePositionPoint::End:
//                    moveMethod = FILE_END;
//
//                    break;
//                default:
//                    return false;
//            }
//
//            auto filePosition = SetFilePointer(_fileDescriptor, StaticCast<LONG>(position.getOffset()), nullptr, moveMethod);
//
//            if (filePosition == INVALID_SET_FILE_POINTER) {
//                return false;
//            }
//
//            return true;
//        }
//
//    private:
//
//        HANDLE _fileDescriptor;
//
//        Bool _hasOwner;
//    };
//
//    UFileSource::UFileSource() {
//#if defined(GS_OS_WINDOWS)
//        _implementation = new WindowsFileImplementation();
//#endif
//    }
//
//    UFileSource::UFileSource(Ptr<FileImplementation> implementation)
//            : _implementation(implementation) {}
//
//    UFileSource::~UFileSource() {
//        delete _implementation;
//    }
//
//    Bool UFileSource::Open(ConstLRef<UString> name, ConstLRef<FileOpenMode> mode) {
//        return _implementation->Open(name, mode);
//    }
//
//    Bool UFileSource::Close() {
//        return _implementation->Close();
//    }
//
//    Bool UFileSource::GetPosition(LRef<FilePosition> position) {
//        return _implementation->GetPosition(position);
//    }
//
//    Bool UFileSource::SetPosition(LRef<FilePosition> position) {
//        return _implementation->SetPosition(position);
//    }
//
//    UFileSource::DataT UFileSource::Get() {
//        Vector<Byte> bytes;
//
//        Byte byte;
//
//        _implementation->Read(byte);
//
//        bytes.emplace_back(byte);
//
//        auto size = Conversions::UTF8SymbolSize(bytes[0]);
//
//        if (!size) {
//            throw UException(U"Invalid size!");
//        }
//
//        for (auto i = 1; i < size; ++i) {
//            _implementation->Read(byte);
//
//            bytes.emplace_back(byte);
//        }
//
//        return Conversions::Decode(bytes, Encoding::UTF8, ByteEndian::Unknown);
//    }
//
//    Void UFileSource::Put(DataT data) {
//        for (auto &byte : Conversions::Encode(data.getCodePoint(), Encoding::UTF8, ByteEndian::Unknown)) {
//            _implementation->Write(byte);
//        }
//    }
//
//    UFileStream::UFileStream()
//            : UnicodeStream(new UFileSource()) {}
//
//    UFileStream::UFileStream(Ptr<UFileSource> source)
//            : UnicodeStream(source) {}
//
//    Bool UFileStream::Open(ConstLRef<UString> name, ConstLRef<FileOpenMode> mode) {
//        return GetUFileSource()->Open(name, mode);
//    }
//
//    Ptr<UFileSource> UFileStream::GetUFileSource() {
//        return ReinterpretCast<Ptr<UFileSource>>(UnicodeStream::GetUnicodeSource());
//    }
//
//    Ptr<FileImplementation> COutFile;
//    Ptr<FileImplementation> CErrFile;
//    Ptr<FileImplementation> CInFile;
//
//    Ptr<UFileSource> COutDevice;
//    Ptr<UFileSource> CErrDevice;
//    Ptr<UFileSource> CInDevice;
//
//    Ptr<UFileStream> COutStream;
//    Ptr<UFileStream> CErrStream;
//    Ptr<UFileStream> CInStream;
//
//    class UIOInit {
//    public:
//
//        UIOInit() {
//#if defined(GS_OS_WINDOWS)
//            _codePage = GetConsoleCP();
//
//            SetConsoleCP(CP_UTF8);
//            SetConsoleOutputCP(CP_UTF8);
//
//            COutFile = new WindowsFileImplementation(GetStdHandle(STD_OUTPUT_HANDLE), true);
//            CErrFile = new WindowsFileImplementation(GetStdHandle(STD_ERROR_HANDLE), true);
//            CInFile = new WindowsFileImplementation(GetStdHandle(STD_INPUT_HANDLE), true);
//#endif
//            COutDevice = new UFileSource(COutFile);
//            CErrDevice = new UFileSource(CErrFile);
//            CInDevice = new UFileSource(CInFile);
//
//            COutStream = new UFileStream(COutDevice);
//            CErrStream = new UFileStream(CErrDevice);
//            CInStream = new UFileStream(CInDevice);
//        }
//
//    public:
//
//        ~UIOInit() {
//            delete COutStream;
//            delete CErrStream;
//            delete CInStream;
//
//#if defined(GS_OS_WINDOWS)
//            SetConsoleOutputCP(_codePage);
//            SetConsoleCP(_codePage);
//#endif
//        }
//
//    private:
//
//#if defined(GS_OS_WINDOWS)
//        UINT _codePage;
//#endif
//    };
//
//    UIOInit Init;
//
//    LRef<UnicodeStream> UCOut() {
//        return *COutStream;
//    }
//
//    LRef<UnicodeStream> UCErr() {
//        return *CErrStream;
//    }
//
//    LRef<UnicodeStream> UCIn() {
//        return *CInStream;
//    }

}
