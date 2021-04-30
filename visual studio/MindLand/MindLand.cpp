#include <iostream>
#include <string>
#include <cpp_httplib/httplib.h>
#include <json/json.hpp>
#include <File/File.h>
#include <cstdlib>
#include <ctime>

using namespace httplib;
using json = nlohmann::json;

Server server;

const char* SERVER_HOST = "127.0.0.1";
const int SERVER_PORT = 1234;
int File::indent = 3;

#include "routes/login.h"
#include "routes/game.h"
#include "routes/leaders.h"

int main() {
   std::srand(std::time(nullptr));

   server
      .Post("/login", RouteLogin::Handler)
      .Post("/leaders", RouteLeaders::Handler)
      .Post("/game", RouteGame::Handler);

   // Starting server
   std::cout << "Server started on " << SERVER_HOST << ":" << SERVER_PORT << "\n";
   server.listen(SERVER_HOST, SERVER_PORT);

   return 0;
}
