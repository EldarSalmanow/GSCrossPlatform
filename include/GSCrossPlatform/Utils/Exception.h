#ifndef GSCROSSPLATFORM_EXCEPTION_H
#define GSCROSSPLATFORM_EXCEPTION_H

#include <GSCrossPlatform/Containers.h>

namespace CrossPlatform {

    /**
     * Class for supporting unicode exceptions
     */
    class UException : public Exception {
    public:

        /**
         * Constructor for unicode exception
         * @param message Message
         */
        explicit UException(ConstLRef<UString> message);

    public:

        /**
         * Getter for exception message
         * @return Exception message
         */
        UString GetMessage() const;

    public:

        /**
         * Getting message as const symbol pointer
         * @return Const symbol pointer
         */
        ConstPtr<C8> what() const override;

    private:

        /**
         * Unicode string message
         */
        UString _message;

        /**
         * Standard string message
         */
        String _stringMessage;
    };

}

#endif //GSCROSSPLATFORM_EXCEPTION_H
