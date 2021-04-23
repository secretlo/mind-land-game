#include <iostream>
#include <string>

#include <cpp_httplib/httplib.h>
#include <json/json.hpp>
using namespace httplib;
using json = nlohmann::json;

#include <File/File.h>
#include <tools/getParam.h>
#include <tools/response.h>

namespace RouteLogin {
   extern std::string pwd;

   void Handler(const Request& req, Response& res);
} // RouteLogin

#include "login.cpp"