#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <cpp_httplib/httplib.h>
#include <json/json.hpp>
using namespace httplib;
using json = nlohmann::json;

#include <File/File.h>
#include <tools/getParam.h>
#include <tools/response.h>

// Random
#include <cstdlib>

namespace RouteLeaders {
   extern std::string pwd;
   
   void Handler(const Request& req, Response& res);
} // RouteLeaders

#include "leaders.cpp"