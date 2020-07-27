#ifndef HTTP_H
#define HTTP_H

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string>
#include <vector>
#include <list>
#include <regex>
#include <iostream>


namespace http {
    class HttpMsg;
}


/*
 * URL -> host & port -> ip-address & port
 * headers
 * body
 */
class http::HttpMsg {
 public:
    std::string url;
    std::vector<std::string> headers;
    std::string body;

 public:
    HttpMsg();
    HttpMsg(std::string,
            std::vector<std::string>,
            std::string
            );

    std::string *wholeMsg();

 protected:
    std::string host;
    int port;
    std::string whole_msg_;
    static std::regex host_reg;
    static std::regex port_reg;
    static std::regex protocol_reg;

 public:
    int initHostInfo();
};


#endif
