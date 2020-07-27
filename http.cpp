#include "http.h"

/*
 * Here is some regex for getting host info
 *                               (host, port, protocol and so on)
 *
 * 2020-7-27    Simpidbit
 */
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
            std::unordered_map<std::string, std::string> argheaders = { {"User-Agent", "C++ socket in Linux"} },
            std::string argbody = "")
    : url(argurl), headers(argheaders), body(argbody)
{
}


/*
 * Maybe the regex has something wrong.
 * Return -1 on error or return 0 on success.
 *
 * 2020-7-27 Simpidbit
 */
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

    /*
     *    If result_port[1] is empty, there is no port in URL,
     * so we can get port by protocol at the front of the URL,
     * it means that get port from protocols' default port
     *
     *    For example:
     *      HTTP protocol's default port is 80.
     *      if there is no port in URL but the protocol is HTTP,
     *      set the port to 80(HTTP default)
     *
     */
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
    
    /* Maybe the regex has something wrong. */
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

    /*
     * Look for ipaddress from std::vector<...> ipaddrs first,
     * if there is no any ipaddress of the hostname,
     * get ipaddress from DNS.
     */
    std::cout << "Host: " << this->host << std::endl;
    std::cout << "Port: " << this->port << std::endl;
    std::cout << "Protocol: " << result_protocol[1] << std::endl;

    return 0;
}

/* Do not use this main() function */
int main()
{
    http::HttpMsg msg("http://pastebin.com/ara/fuck/index.html");
    if (msg.initHostInfo() == -1) {
        std::cout << "Error" << std::endl;
    }
    return 0;
}
