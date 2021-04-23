#include <iostream>
#include <string>
#include <cpp_httplib/httplib.h>

namespace httplib {
   std::string getParam(const Request& req, std::string paramName);
}