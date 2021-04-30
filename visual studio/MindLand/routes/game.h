#include <iostream>
#include <string>

#include <cpp_httplib/httplib.h>
#include <json/json.hpp>
using namespace httplib;
using json = nlohmann::json;

#include <File/File.h>
#include <tools/getParam.h>
#include <tools/response.h>

// Random
#include <cstdlib>

namespace RouteGame {
   extern std::string pwd;
   
   int randint(int min, int max);
   size_t getMinGid(json games);
   
   void sendAll(size_t gid, size_t senderId, std::string action, json data);

   void Handler(const Request& req, Response& res);
} // RouteGame

#include "game.cpp"