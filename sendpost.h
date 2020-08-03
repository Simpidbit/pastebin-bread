#ifndef W_H
#define W_H
#include <curl/curl.h>
#include <string>
#include <unordered_map>


struct UserData {
    size_t data_size;
    std::string data;
};

std::string sendPostMsg(std::string data, long optpost = 1, std::string url = "https://pastebin.com/api/api_post.php");

class PostData {
 public:
    PostData(std::unordered_map<std::string, std::string>);
    PostData();

    std::string datasToStr();
    std::unordered_map<std::string, std::string> datas;
};

#endif // W_H
