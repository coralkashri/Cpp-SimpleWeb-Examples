
#ifndef SERVER0311_SPEC_SERVER_H
#define SERVER0311_SPEC_SERVER_H

#include "../simple_web/server_classes.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <dirent.h>
#include <boost/filesystem.hpp>
#include <condition_variable>

class my_server {
public:

    explicit my_server(SimpleWeb::Server<SimpleWeb::HTTP> &server, std::atomic_bool &is_running, std::condition_variable_any& cv, std::mutex &mtx);

    void start();

    void stop();


private:
    typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;

    HttpServer &server;
    std::atomic_bool &is_running;
    std::condition_variable_any &cv;
    std::mutex &mtx;
    std::thread server_thread;

    void init();
    void init_routes();
};
#endif //SERVER0311_SPEC_SERVER_H