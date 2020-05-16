#include "handlers.h"
#include "exceptions.h"

namespace handlers {
    std::string simple_success_example() {
        return "Successful request";
    }

    std::string simple_bad_request_example() {
        throw RequestException(SimpleWeb::StatusCode::client_error_bad_request, "Bad request, please fix your params.");
    }

    std::string simple_general_error_example() {
        throw std::runtime_error("Something broke, please try again.");
    }
};