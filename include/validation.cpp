#include "validation.hpp"

namespace validation {
    bool isEmailInvalid(const QString& email) {
        std::regex emailPattern(R"(^[\w\.-]+@([\w\.-]+\.)+[\w\-]{2,4}$)");
        return !std::regex_match(email.toStdString(), emailPattern);
    }

    int isPasswdInvalid(const QString& passwd) {
        if (passwd.toStdString().length() < 8) {
            return invalidPasswd::TOO_SHORT; //"Password must be at least 8 characters long.";
        }
        if (!std::regex_search(passwd.toStdString(), std::regex("[a-z]"))) {
            return invalidPasswd::NO_LOWER; //"Password must contain at least one lowercase letter.";
        }
        if (!std::regex_search(passwd.toStdString(), std::regex("[A-Z]"))) {
            return invalidPasswd::NO_UPPER; //"Password must contain at least one uppercase letter.";
        }
        if (!std::regex_search(passwd.toStdString(), std::regex("\\d"))) {
            return invalidPasswd::NO_DIGIT; //"Password must contain at least one digit.";
        }
        if (!std::regex_search(passwd.toStdString(), std::regex("[\\W_]"))) {
            return invalidPasswd::NO_SPECIAL; //"Password must contain at least one special character.";
        }
        return 0; //"Password is valid.";
    }
}
