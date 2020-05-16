#include <iostream>
#include <condition_variable>
#include "simple_web/server_classes.hpp"
#include "routes/my_server.h"

using namespace SimpleWeb;
typedef Server<HTTP> HttpServer;

int main() {
    std::atomic_bool is_running;
    unsigned short port = 8080;
    size_t threads_count = 1;

    std::condition_variable_any cv;
    std::mutex mtx;
    std::unique_lock<std::mutex> lck(mtx);

    HttpServer server(port, threads_count);

    my_server ms(server, is_running, cv, mtx);
    ms.start();

    while (is_running) {
        cv.wait_for(lck, std::chrono::seconds(1), [&is_running]() -> bool { return is_running; });
    }

    std::cout << "Program successfully ended" << std::endl;

    return EXIT_SUCCESS;
}