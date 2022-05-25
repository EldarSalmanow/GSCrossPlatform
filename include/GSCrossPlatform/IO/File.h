#ifndef FEATURESTESTING_IOSTREAM_H
#define FEATURESTESTING_IOSTREAM_H

#include <GSCrossPlatform/Containers.h>

namespace CrossPlatform {

//    /**
//     * File open mode type
//     */
//    using OpenMode = U8;
//
//    /**
//     * Input file open mode
//     */
//    inline Const<OpenMode> InMode = 0x1;
//
//    /**
//     * Output file open mode
//     */
//    inline Const<OpenMode> OutMode = 0x2;
//
//    /**
//     * Class for working with file descriptors
//     */
//    class File {
//    private:
//
//        /**
//         * Constructor for file
//         * @param fileDescriptor File descriptor
//         */
//        explicit File(Ptr<FILE> fileDescriptor);
//
//    public:
//
//        /**
//         * File destructor
//         */
//        ~File();
//
//    public:
//
//        /**
//         * Create file
//         * @return File with null ptr descriptor
//         */
//        static UniquePtr<File> Create();
//
//        /**
//         * Create file
//         * @param fileDescriptor Native file descriptor
//         * @return File ptr
//         */
//        static UniquePtr<File> Create(Ptr<FILE> fileDescriptor);
//
//        /**
//         * Create file
//         * @param name Name
//         * @param mode Mode
//         * @return File ptr
//         */
//        static UniquePtr<File> Create(ConstLRef<UString> name, ConstLRef<OpenMode> mode);
//
//    public:
//
//        /**
//         * Reading symbol
//         * @return Symbol
//         */
//        USymbol ReadSymbol();
//
//        /**
//         * Writing symbol
//         * @param symbol Symbol
//         * @return
//         */
//        Void WriteSymbol(USymbol symbol);
//
//        /**
//         * Read string while symbol is not delimiter
//         * @param delimiter Delimiter symbol
//         * @return String
//         */
//        UString Read(USymbol delimiter = U'\n');
//
//        /**
//         * Read data from file as strings
//         * @return Text from file
//         */
//        Vector<UString> ReadText();
//
//        /**
//         * Read data from file as one string
//         * @return String from file
//         */
//        UString ReadInput();
//
//        /**
//         * Write to file
//         * @param string String
//         * @return
//         */
//        Void Write(ConstLRef<UString> string);
//
//        /**
//         * Open file
//         * @param name Name
//         * @param mode Mode
//         * @return Is opened
//         */
//        Bool Open(ConstLRef<UString> name, ConstLRef<OpenMode> mode);
//
//        /**
//         * Close file
//         * @return
//         */
//        Void Close();
//
//        /**
//         * Is EOF
//         * @return Is EOF
//         */
//        Bool IsEOF();
//
//    public:
//
//        /**
//         * Stream input operator
//         * @param string String
//         * @return File without data
//         */
//        LRef<File> operator>>(LRef<UString> string);
//
//        /**
//         * Stream output operator
//         * @param string String
//         * @return File with data
//         */
//        LRef<File> operator<<(ConstLRef<UString> string);
//
//    private:
//
//        /**
//         * File descriptor
//         */
//        Ptr<FILE> _fileDescriptor;
//    };
//
//    /**
//     * Unicode console output
//     * @return Unicode console output descriptor
//     */
//    LRef<File> UCOut();
//
//    /**
//     * Unicode console error
//     * @return Unicode console error descriptor
//     */
//    LRef<File> UCErr();
//
//    /**
//     * Unicode console input
//     * @return Unicode console input descriptor
//     */
//    LRef<File> UCIn();
//
//    /**
//     * Class for manipulating with console code page
//     */
//    class CodePage {
//    public:
//
//        /**
//         * Getting code page
//         * @return Code page
//         */
//        static U32 GetCodePage();
//
//        /**
//         * Setting code page
//         * @param codePage Code page
//         * @return
//         */
//        static Void SetCodePage(U32 codePage);
//    };

    Bool EnableUnicodeConsole();

    static Bool IsEnabledUnicodeConsole = EnableUnicodeConsole();

}

#endif //FEATURESTESTING_IOSTREAM_H
