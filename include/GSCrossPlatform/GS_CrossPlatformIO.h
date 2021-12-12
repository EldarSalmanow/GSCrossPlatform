#ifndef GSCROSSPLATFORM_GS_CROSSPLATFORMIO_H
#define GSCROSSPLATFORM_GS_CROSSPLATFORMIO_H

#include <GSCrossPlatform/GS_CrossPlatformString.h>

namespace CrossPlatform {

    class UDevice {
    public:

        virtual ~UDevice();

    public:

        virtual Byte readByte() = 0;

        virtual Void writeByte(Byte byte) = 0;
    };

    class UStream {
    public:

        virtual ~UStream();

    public:

        virtual Byte readByte() = 0;

        virtual Void writeByte(Byte byte) = 0;

        virtual CodePoint readCodePoint() = 0;

        virtual Void writeCodePoint(CodePoint codePoint) = 0;
    };

    class UFileDevice : public UDevice {
    public:

        UFileDevice(FILE *file);

    public:

        Byte readByte() override;

        Void writeByte(Byte byte) override;

    private:

        FILE *_file;
    };

    class UFileStream : public UStream {
    public:

        UFileStream(UFileDevice *device);

    public:

        Byte readByte() override;

        Void writeByte(Byte byte) override;

        CodePoint readCodePoint() override;

        Void writeCodePoint(CodePoint codePoint) override;

    private:

        UFileDevice *_device;
    };

    UStream &COut();

    UStream &CErr();

    UStream &CIn();

}

#endif //GSCROSSPLATFORM_GS_CROSSPLATFORMIO_H
