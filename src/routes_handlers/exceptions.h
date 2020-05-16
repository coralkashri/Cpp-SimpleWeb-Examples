#ifndef CPPSIMPLEWEBEXAMPLES_EXCEPTIONS_H
#define CPPSIMPLEWEBEXAMPLES_EXCEPTIONS_H

#include <iostream>
#include "../simple_web/status_code.hpp"

namespace handlers {
    class RequestException : std::exception {
    public:
        SimpleWeb::StatusCode status_code;
        std::string message;

        explicit RequestException(SimpleWeb::StatusCode status_code, std::string message)
        : status_code(status_code), message(std::move(message)) {

        }

        const char* what() {
            return message.c_str();
        }
    };
}

#endif //CPPSIMPLEWEBEXAMPLES_EXCEPTIONS_H