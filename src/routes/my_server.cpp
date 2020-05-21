#include "my_server.h"
#include "../simple_web_utils/responses.h"
#include "../routes_handlers/handlers.h"
#include "../routes_handlers/exceptions.h"

my_server::my_server(SimpleWeb::Server<SimpleWeb::HTTP> &server, std::atomic_bool &is_running, std::condition_variable_any& cv, std::mutex &mtx)
        :server(server), is_running(is_running), cv(cv), mtx(mtx) {
    init();
}

void my_server::start() {
    is_running.store(true);
    std::thread([this]() { server.start(); }).detach();
    std::cout << "Server is running" << std::endl;
}

void my_server::stop() {
    server.stop();
    {
        std::lock_guard<std::mutex> lck(mtx);
        is_running.store(false);
    }
    std::cout << "Server is stopped" << std::endl;
    std::cout << "Server thread is stopped" << std::endl;
    cv.notify_one();
}

void my_server::init() {
    is_running.store(false);
    init_routes();
}

void my_server::init_routes() {
    server.resource["^/SuccessExample$"]["POST"] = [](HttpServer::Response &response, std::shared_ptr<HttpServer::Request> request) {
        std::string res = handlers::simple_success_example();
        responses::generate_response(response, SimpleWeb::StatusCode::success_ok, res);
    };

    server.resource["^/SuccessExample$"]["GET"] = [](HttpServer::Response &response, std::shared_ptr<HttpServer::Request> request) {
        std::string res = handlers::simple_success_example();
        responses::generate_response(response, SimpleWeb::StatusCode::success_ok, res);
    };

    server.resource["^/BadRequest$"]["GET"] = [](HttpServer::Response &response, std::shared_ptr<HttpServer::Request> request) {
        try {
            std::string res = handlers::simple_bad_request_example();
            responses::generate_response(response, SimpleWeb::StatusCode::success_ok, res);
        } catch (handlers::RequestException &e) {
            responses::generate_response(response, e.status_code, e.what());
        } catch (std::exception &e) {
            responses::generate_response(response, SimpleWeb::StatusCode::server_error_bad_gateway, e.what());
        }
    };

    server.resource["^/GeneralError$"]["POST"] = [](HttpServer::Response &response, std::shared_ptr<HttpServer::Request> request) {
        try {
            std::string res = handlers::simple_general_error_example();
            responses::generate_response(response, SimpleWeb::StatusCode::success_ok, res);
        } catch (handlers::RequestException &e) {
            responses::generate_response(response, e.status_code, e.what());
        } catch (std::exception &e) {
            responses::generate_response(response, SimpleWeb::StatusCode::server_error_bad_gateway, e.what());
        }
    };

    server.resource["^/CloseServer$"]["POST"] = [this](HttpServer::Response &response, std::shared_ptr<HttpServer::Request> request) {
        responses::generate_response(response, SimpleWeb::StatusCode::success_ok, "Server successfully stopped");
        stop();
    };
}