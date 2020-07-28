#include "http.h"

http::HttpMsg::HttpMsg()
{
}

http::HttpMsg::HttpMsg(std::string argurl,
            std::unordered_map<std::string, std::string> argdata,
            std::unordered_map<std::string, std::string> argheaders = { {"User-Agent", (std::string)"pastebin-bread Client Version " + VERSION} }
            )
    : url(argurl), data(argdata), headers(argheaders)
{
}

/* Do not use this main() function */
int main()
{
    return 0;
}
