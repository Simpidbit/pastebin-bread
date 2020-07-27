#include "http.h"


std::regex http::HttpMsg::host_reg
    = std::regex(".*://([A-Za-z\.]*):*[0-9]*/.*");
std::regex http::HttpMsg::port_reg
    = std::regex(".*://[A-Za-z\.]*:*([0-9]*)/.*");
std::regex http::HttpMsg::protocol_reg
    = std::regex("(.*)://.*");


http::HttpMsg::HttpMsg()
{
}

http::HttpMsg::HttpMsg(std::string argurl,
            std::vector<std::string> argheaders = {""},
            std::string argbody = "")
    : url(argurl), headers(argheaders), body(argbody)
{
}

int http::HttpMsg::initHostInfo()
{
    std::smatch result_host;
    std::smatch result_port;
    std::smatch result_protocol;
    
    /* Get Hostname */
    regex_match(this->url, result_host, http::HttpMsg::host_reg);
    /* Get Host Port */
    regex_match(this->url, result_port, http::HttpMsg::port_reg);
    /* Get Protocol (HTTP or HTTPS) */
    regex_match(this->url, result_protocol, http::HttpMsg::protocol_reg);

    if (result_port[1] == "") {
        if (result_protocol[1] == "http") {
            this->port = 80;        /* Default port 80 (HTTP) */
        }
        else if (result_protocol[1] == "https") {
            this->port = 443;       /* Default port 443 (HTTPS) */
        }
    }
    else {
        this->port = stoi(result_port[1]);
    }

    if (result_host[1] == "") {
        std::cout << "Host error" << std::endl;
        std::cout << result_host[1] << std::endl;
        return -1;
    }
    else {
        this->host = result_host[1];
    }
    if (result_protocol[1] == "") {
        std::cout << "Protocol error" << std::endl;
        return -1;
    }
    
    std::cout << "Host: " << this->host << std::endl;
    std::cout << "Port: " << this->port << std::endl;
    std::cout << "Protocol: " << result_protocol[1] << std::endl;

    return 0;
}


int main()
{
    http::HttpMsg msg("http://pastebin.com/ara/fuck/index.html");
    if (msg.initHostInfo() == -1) {
        std::cout << "Error" << std::endl;
    }
    return 0;
}
