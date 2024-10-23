#pragma once

#include <QString>
#include <regex>

namespace validation {
    bool isEmailInvalid(const QString& email);
    int isPasswdInvalid(const QString& passwd);
    //int isLicenseValid(const QString& license);

    namespace invalidPasswd {
        enum {
            TOO_SHORT   = 1,
            NO_LOWER    = 2,
            NO_UPPER    = 3,
            NO_DIGIT    = 4,
            NO_SPECIAL  = 5
        };
        
        namespace detail {
            const QString TOO_SHORT_MSG = "Password must be at least 8 characters long.";
            const QString NO_LOWER_MSG = "Password must contain at least one lowercase letter.";
            const QString NO_UPPER_MSG = "Password must contain at least one uppercase letter.";
            const QString NO_DIGIT_MSG = "Password must contain at least one digit.";
            const QString NO_SPECIAL_MSG = "Password must contain at least one special character.";
        }
    }
}

