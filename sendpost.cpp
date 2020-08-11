#include "sendpost.h"

#include <QDebug>
#include <curl/curl.h>

static size_t sendPostMsg_writeFunc(char *ptr, size_t size, size_t nmemb, void *userp)
{
    struct UserData *retdata = (struct UserData *)userp;
    retdata->data_size = size;
    char *p = ptr;
    while (*p != '\0') {
        retdata->data += *p;
        p++;
    }
    return size * nmemb;
}

std::string sendPostMsg(std::string data, long optpost, std::string url)
{
    CURL *curl = curl_easy_init();

    if (curl) {
        struct UserData retdata_struct;
        curl_easy_setopt(curl, CURLOPT_URL, &url.front());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&retdata_struct);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, sendPostMsg_writeFunc);
        curl_easy_setopt(curl, CURLOPT_POST, optpost);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, &data.front());
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        return retdata_struct.data;
    } else {
        return "Error: CURL* curl == NULL";
    }
}


PostData::PostData(std::unordered_map<std::string, std::string> datas_)
    : datas(datas_)
{
}

PostData::PostData()
{
}

std::string PostData::datasToStr() {
    std::string data_str;
    for (auto iter_pair = this->datas.begin(); iter_pair != this->datas.end(); iter_pair++) {
        data_str += iter_pair->first + "=" + iter_pair->second + "&";
    }
    data_str.erase(data_str.end() - 1);
    return data_str;
}
