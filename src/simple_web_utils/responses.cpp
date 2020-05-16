#include "responses.h"

namespace responses {
    void generate_response(SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const SimpleWeb::StatusCode &status_code, std::string response_content) {
        response << "HTTP/1.1 " << SimpleWeb::status_code(status_code) <<
                 "\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *" <<
                 "\r\nContent-Length: " << response_content.length() <<
                 "\r\n\r\n" << response_content;
    }
};