#include "server.h"

server::server(struct event_base* base) {

    http_server_ = evhttp_new(base);

    evhttp_set_cb(http_server_, "/", handle_info_request, nullptr);
}

server::~server() {
    std::cout << "Server destructed" << std::endl;
}

void server::start() {
    evhttp_bind_socket(http_server_, "127.0.0.1", 49160);
    std::cout << "Server started on port: 49160" << std::endl;
}

void server::handle_info_request(struct evhttp_request* req, void* arg) {

    std::string hellostr = "Hello World!";

    struct evbuffer* response_buffer = evbuffer_new();

    evhttp_add_header(evhttp_request_get_output_headers(req), "Content-Type", "application/text" );
    evbuffer_add(response_buffer, hellostr.c_str(), hellostr.length());

    evhttp_send_reply(req, HTTP_OK, "OK", response_buffer);

    evbuffer_free(response_buffer);
}