#ifndef HTTP_H
#define HTTP_H

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <string>
#include <unordered_map>
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
 *
 * All of things above -> std::string whole_msg_
 *
 * 2020-7-27    Simpidbit
 */
class http::HttpMsg {
 public:
    std::string url;
    std::unordered_map<std::string, std::string> headers;
    std::string body;

 public:
    HttpMsg();
    HttpMsg(std::string,
            std::unordered_map<std::string, std::string>,
            std::string
            );

    std::string *wholeMsg();

 protected:
    std::string host;
    int port;
    static std::vector<std::unordered_map<std::string, std::string> > ipaddrs;
    static std::regex host_reg;
    static std::regex port_reg;
    static std::regex protocol_reg;

    /*
     * whole_msg_ is a whole HTTP/HTTPS message,
     * It can be sent to HTTP server.
     */
    std::string whole_msg_;

 public:
    int initHostInfo();
};


#endif
