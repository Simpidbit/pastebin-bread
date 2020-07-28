#include "http.h"

/*
 * For initPyLib() and clearPyLib(), whether python lib inited or not.
 */
libStatus PYLIBSTATUS = uninited;

http::HttpMsg::HttpMsg()
{
}

http::HttpMsg::HttpMsg(std::string argurl,
            std::unordered_map<std::string, std::string> argdata
            )
    : url(argurl), data(argdata)
{
}



std::string http::pySendMsg(HttpMsg &msg)
{
    initPyLib();
    PyObject *pArgs_sendPostMsg = PyTuple_New(2);

    PyObject *pDictData = PyDict_New();
    for (auto iter = msg.data.begin();
            iter != msg.data.end(); iter++) {
        PyDict_SetItemString(pDictData, iter->first.c_str(), Py_BuildValue("s", iter->second.c_str()));
    }
    PyTuple_SetItem(pArgs_sendPostMsg, 0, Py_BuildValue("s", msg.url.c_str()));
    PyTuple_SetItem(pArgs_sendPostMsg, 1, pDictData);

    PyObject *pRetval = PyEval_CallObject(pyruntime::pFunc_sendPostMsg, pArgs_sendPostMsg);
    char *pRetstr = nullptr;
    PyArg_Parse(pRetval, "s", &pRetstr);
    std::string sendret = pRetstr;
    return sendret;
}

void initPyLib()
{
    if (PYLIBSTATUS == uninited) {
        PYLIBSTATUS = inited;
        Py_Initialize();

        std::string chdir_cmd = "sys.path.append('./')";
        const char* cstr_cmd = chdir_cmd.c_str();
        PyRun_SimpleString("import sys");
        PyRun_SimpleString(cstr_cmd);


        pyruntime::pModule = PyImport_ImportModule("reqapi");
        pyruntime::pFunc_sendPostMsg = PyObject_GetAttrString(pyruntime::pModule, "sendPostMsg");
    }
}

void clearPyLib()
{
    if (PYLIBSTATUS == inited) {
        PYLIBSTATUS = uninited;
        Py_DECREF(pyruntime::pModule);
        Py_DECREF(pyruntime::pFunc_sendPostMsg);
        Py_Finalize();
    }
}

/* Do not use this main() function */
int main()
{
    http::HttpMsg msg("https://pastebin.com/api/api_post.php",
            { 
                {"api_dev_key", "_oEOdQg9gJEe786KEgIyH5ssC0v4l7ij"},
                {"api_option", "paste"},
                {"api_paste_code", "Hello, Dear Pastebin.com~~~~~"}
            }
        );
    std::string r = http::pySendMsg(msg);
    std::cout << r << std::endl;
    return 0;
}
