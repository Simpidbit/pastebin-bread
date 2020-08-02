#ifndef W_H
#define W_H
#include <curl/curl.h>
#include <string>


struct UserData {
    size_t data_size;
    std::string data;
};

std::string sendPostMsg(std::string data, long optpost = 1, std::string url = "https://pastebin.com/api/api_post.php");

#endif // W_H
