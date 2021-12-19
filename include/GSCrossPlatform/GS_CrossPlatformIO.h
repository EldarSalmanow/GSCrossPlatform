#ifndef GSCROSSPLATFORM_GS_CROSSPLATFORMIO_H
#define GSCROSSPLATFORM_GS_CROSSPLATFORMIO_H

#include <GSCrossPlatform/GS_CrossPlatformString.h>

namespace CrossPlatform {

    /**
     * Unicode device
     */
    class UDevice {
    public:

        /**
         * Virtual destructor
         */
        virtual ~UDevice();

    public:

        /**
         * Reading byte from device
         * @return Byte
         */
        virtual Byte readByte() = 0;

        /**
         * Writing byte to device
         * @param byte Byte
         * @return
         */
        virtual Void writeByte(Byte byte) = 0;
    };

    /**
     * Unicode stream
     */
    class UStream {
    public:

        /**
         * Constructor for UStream
         * @param device Ptr to unicode device
         */
        UStream(Ptr<UDevice> device);

    public:

        /**
         * Virtual destructor
         */
        virtual ~UStream();

    public:

        /**
         * Getter for ptr to unicode device
         * @return Ptr to unicode device
         */
        Ptr<UDevice> getDevice();

    public:

        /**
         * Reading byte from stream
         * @return Byte
         */
        virtual Byte readByte() = 0;

        /**
         * Writing byte to stream
         * @param byte Byte
         * @return
         */
        virtual Void writeByte(Byte byte) = 0;

        /**
         * Reading codepoint from stream
         * @return Codepoint
         */
        virtual CodePoint readCodePoint() = 0;

        /**
         * Writing codepoint to stream
         * @param codePoint Codepoint
         * @return
         */
        virtual Void writeCodePoint(CodePoint codePoint) = 0;

    public:

        /**
         * Reading byte from stream
         * @param byte Byte
         * @return Reference to stream
         */
        virtual LRef<UStream> operator>>(LRef<Byte> byte);

        /**
         * Writing byte to stream
         * @param byte Byte
         * @return Reference to stream
         */
        virtual LRef<UStream> operator<<(Byte byte);

        /**
         * Reading codepoint from stream
         * @param codePoint Codepoint
         * @return Reference to stream
         */
        virtual LRef<UStream> operator>>(LRef<CodePoint> codePoint);

        /**
         * Writing codepoint to stream
         * @param codePoint Codepoint
         * @return Reference to stream
         */
        virtual LRef<UStream> operator<<(CodePoint codePoint);

    private:

        /**
         * Ptr to device
         */
        Ptr<UDevice> _device;
    };

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

    /**
     * Binary file open mode
     */
    inline Const<FileOpenMode> bin_mode = 0x4;

    /**
     * Unicode file device
     */
    class UFileDevice : public UDevice {
    public:

        /**
         * Constructor for UFileDevice
         * @param file Ptr to file
         */
        UFileDevice(Ptr<FILE> file);

    public:

        /**
         * Open file device
         * @param name Filename
         * @param mode File open mode
         * @return Is opened
         */
        Bool open(ConstLRef<UString> name, ConstLRef<FileOpenMode> mode);

    public:

        /**
         * Reading byte from file
         * @return Byte
         */
        Byte readByte() override;

        /**
         * Writing byte to file
         * @param byte Byte
         * @return
         */
        Void writeByte(Byte byte) override;

    private:

        /**
         * Ptr to file
         */
        Ptr<FILE> _file;
    };

    /**
     * Unicode file stream
     */
    class UFileStream : public UStream {
    public:

        /**
         * Constructor for UFileStream
         * @param device Ptr to file device
         */
        UFileStream(Ptr<UFileDevice> device);

        /**
         * Constructor for UFileStream
         * @param fileName Filename
         * @param mode File open mode
         */
        UFileStream(ConstLRef<UString> fileName, ConstLRef<FileOpenMode> mode);

    public:

        /**
         * Opening file stream
         * @param fileName Filename
         * @param mode File open mode
         * @return Is opened
         */
        Bool open(ConstLRef<UString> fileName, ConstLRef<FileOpenMode> mode);

    public:

        /**
         * Reading byte from file
         * @return Byte
         */
        Byte readByte() override;

        /**
         * Writing byte to file
         * @param byte Byte
         * @return
         */
        Void writeByte(Byte byte) override;

        /**
         * Reading codepoint from file
         * @return Codepoint
         */
        CodePoint readCodePoint() override;

        /**
         * Writing codepoint to file
         * @param codePoint Codepoint
         * @return
         */
        Void writeCodePoint(CodePoint codePoint) override;

    private:

        /**
         * File device
         */
        UFileDevice _file;
    };

    /**
     * Reading unicode string from stream
     * @param stream Stream
     * @param string Unicode string
     * @return Reference to stream
     */
    inline LRef<UStream> operator>>(LRef<UStream> stream, LRef<UString> string) {
        auto codePoint = stream.readCodePoint();

        while (codePoint != '\n') {
            string += codePoint;

            codePoint = stream.readCodePoint();
        }

        return stream;
    }

    /**
     * Writing unicode string to stream
     * @param stream Stream
     * @param string Unicode string
     * @return Reference to stream
     */
    inline LRef<UStream> operator<<(LRef<UStream> stream, ConstLRef<UString> string) {
        for (auto &symbol : string.getSymbols()) {
            stream << symbol.getCodePoint();
        }

        return stream;
    }

    /**
     * Unicode console out stream
     * @return Unicode console out stream
     */
    LRef<UStream> UCOut();

    /**
     * Unicode console error stream
     * @return Unicode console error stream
     */
    LRef<UStream> UCErr();

    /**
     * Unicode console input stream
     * @return Unicode console input stream
     */
    LRef<UStream> UCIn();

}

#endif //GSCROSSPLATFORM_GS_CROSSPLATFORMIO_H
