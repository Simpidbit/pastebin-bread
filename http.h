#ifndef HTTP_H
#define HTTP_H

#include <string>
#include <unordered_map>
#include <iostream>

#include <python3.8/Python.h>

#include "version.h"


namespace http {
    class HttpMsg;
    std::string pySendMsg(HttpMsg &msg);
}

namespace pyruntime {
    PyObject *pModule = nullptr;
    PyObject *pFunc_sendPostMsg = nullptr;
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
    std::unordered_map<std::string, std::string> data;

 public:
    HttpMsg();
    HttpMsg(std::string,
            std::unordered_map<std::string, std::string>
            );
};

enum libStatus {
    uninited = 0, inited = 1
};

void initPyLib();
void clearPyLib();

#endif
