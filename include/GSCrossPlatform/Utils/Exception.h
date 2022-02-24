#ifndef GSCROSSPLATFORM_EXCEPTION_H
#define GSCROSSPLATFORM_EXCEPTION_H

#include <GSCrossPlatform/Containers.h>

namespace CrossPlatform {

    /**
     * Class for supporting unicode exceptions
     */
    class UException : public std::exception {
    public:

        explicit UException(ConstLRef<UString> message);

    public:

        UString getMessage() const;

    public:

        ConstPtr<C8> what() const override;

    private:

        UString _message;

        String _stringMessage;
    };

}

#endif //GSCROSSPLATFORM_EXCEPTION_H
