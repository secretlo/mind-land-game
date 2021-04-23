namespace RouteLogin {
   std::string pwd = File::pwd();

   void Handler(const Request& req, Response& res) {
      auto type = getParam(req, "type");
      auto login = getParam(req, "login"),
         password = getParam(req, "password");
      size_t id;

      File* users = new File(pwd + "/../data/users.json");

      std::cout << "Login: Request (type: " << type << ", login: " << login << ", password: " << password << ")\n";

      if (type == "login") {
         users->updateChilds(
            [&](json& user){ 
            return 
               user["login"].get<std::string>() == login && 
               user["password"].get<std::string>() == password;
            },
            [&](json& user){
               id = user["id"].get<size_t>();
            });
         
         if (id)
            response(res, "OK", "login", json{{"id", id}});
         else
            response(res, "Error", "login", json{{"message", "No such user"}});
      }
      else if (type == "register") {
         if (login == "" || password == "") {
            response(res, "Error", "redister", json{{"message", "Free login or password"}});
            return;
         }

         json userTpl = File::ReadJson(pwd + "/../data/default-user.json");
         size_t maxId = 0;
         users->forEach(
            [&](json& user){
               size_t userId = user["id"].get<size_t>();
               if (userId < maxId)
                  maxId = userId;
            }
         );
         
         userTpl["login"] = login;
         userTpl["password"] = password;
         id = maxId + 1;
         userTpl["id"] = id;
         
         users->pushChild(userTpl);
         
         response(res, "OK", "login", json{
            {"id", id},
         });
      }
   }
} // RouteLogin

