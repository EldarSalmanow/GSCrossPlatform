#ifndef FEATURESTESTING_IOSTREAM_H
#define FEATURESTESTING_IOSTREAM_H

#include <GSCrossPlatform/Containers.h>

namespace CrossPlatform {

    using OpenMode = U8;

    inline Const<OpenMode> InMode = 0x1;

    inline Const<OpenMode> OutMode = 0x2;

    class File {
    private:

        explicit File(Ptr<FILE> fileDescriptor);

    public:

        ~File();

    public:

        static UniquePtr<File> Create();

        static UniquePtr<File> Create(Ptr<FILE> fileDescriptor);

        static UniquePtr<File> Create(ConstLRef<UString> name, ConstLRef<OpenMode> mode);

    public:

        USymbol ReadSymbol();

        Void WriteSymbol(USymbol symbol);

        UString Read(USymbol delimiter = U'\n');

        Vector<UString> ReadText();

        UString ReadInput();

        Void Write(ConstLRef<UString> string);

        Bool Open(ConstLRef<UString> name, ConstLRef<OpenMode> mode);

        Void Close();

        Bool IsEOF();

    public:

        LRef<File> operator>>(LRef<UString> string);

        LRef<File> operator<<(ConstLRef<UString> string);

    private:

        Ptr<FILE> _fileDescriptor;
    };

    LRef<File> COut();

    LRef<File> CErr();

    LRef<File> CIn();

    class CodePage {
    public:

        /**
         * Getting code page
         * @return Code page
         */
        static U32 GetCodePage();

        /**
         * Setting code page
         * @param codePage Code page
         * @return
         */
        static Void SetCodePage(U32 codePage);
    };

}

#endif //FEATURESTESTING_IOSTREAM_H
