#ifndef CPPSIMPLEWEBEXAMPLES_RESPONSES_H
#define CPPSIMPLEWEBEXAMPLES_RESPONSES_H

#include <iostream>
#include "../simple_web/server_classes.hpp"
#include "../simple_web/status_code.hpp"

namespace responses {
    void generate_response(SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const SimpleWeb::StatusCode &status_code, std::string response_content);
};


#endif //CPPSIMPLEWEBEXAMPLES_RESPONSES_H