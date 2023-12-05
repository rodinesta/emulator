#pragma once

#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <iostream>
#include <filesystem>
#include <cstring>
#include <event2/event_struct.h>
#include "tinyxml2.h"

class server {
public:
    server(struct event_base* base);
    ~server();

    void start();

private:
    static void handle_info_request(struct evhttp_request* req, void* arg);

    struct evhttp* http_server_;
};