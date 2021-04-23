namespace RouteGame {
   std::string pwd = File::pwd();

   int randint(int min, int max) {
      return min + (std::rand() % static_cast<int>(max - min + 1));
   }

   size_t getMinGid(json games) {
      if (games.size() == 0) return 0;

      size_t prevGid = 0;

      for (auto& game : games) {
         size_t gid = game["gid"].get<size_t>();
         if (gid - prevGid > 1) return prevGid + 1;
         prevGid = gid;
      }
      
      return prevGid + 1;
   }

   void sendAll(size_t gid, size_t senderId, std::string action, json data) {
      data["action"] = action;
      data["sender_id"] = senderId;
      std::cout << "Game, sendAll: action '" << action << "' with data " << data.dump() << '\n';

      File* games = new File(pwd + "/../data/games.json");
      games->updateChilds("gid", gid, [&](json& game){
         for (json user : game["users"]) {
            std::string userHost = user["host"].get<std::string>();
            userHost = "http://" + userHost;
            Client* userServer = new Client(userHost.c_str());
            userServer->Post("/", data.dump(), "application/json");
         }
      });
   }

   void Handler(const Request& req, Response& res) {
      File* words = new File(pwd + "/../data/words.json");
      std::string action = getParam(req, "action");

      std::cout << "Game: Request\n";

      if (action == "select-word") {
         auto category = getParam(req, "category");
         std::cout << "Category is '" << category << "', words " << words->abspath << "\n";
         words->updateJson([&](json words){
            if (!words.contains(category)) {
               std::cout << "Game, select-word: Error, No target category \"" << category << "\" in DB\n";
               response(res, "Error", action, json{{"message", "No such category"}});
            }
            else {
               auto categoryJson = words[category];
               std::cout << "Game, select-word: Category size is " << categoryJson.size() << "\n";

               auto lastIndex = categoryJson.size() - 1;
               auto targetI = randint(0, lastIndex);
               std::cout << "Game, select-word: Target i is " << targetI << "\n";

               auto targetWordEntity = categoryJson.begin();
               for (int i = 0; i < targetI; i++)
                  targetWordEntity++;
               auto targetWord = targetWordEntity.key();
               auto targetDescription = targetWordEntity.value();

               std::cout << "Game, select-word: Word selected '" << targetWord << "' with description:\n" << targetDescription << "\n";
               
               response(res, "OK", action, json{
                  {"word", targetWord},
                  {"description", targetDescription},
               });
            }
            return words;
         });
      }
      
      else if (action == "result") {
         size_t id = std::stoi(getParam(req, "id"));
         size_t duration = std::stoi(getParam(req, "duration"));
         
         File* users = new File(pwd + "/../data/users.json");
         double new_avg;
         size_t new_n;
         users->updateChilds("id", id, [&](json& user){
            // updating AVG duration
            size_t new_el = duration;
            double prev_avg = user["avg_duration"].get<double>();
            size_t prev_n = user["avg_n"].get<size_t>();
            new_n = prev_n + 1;
            new_avg = prev_avg + (new_el / new_n) - (prev_avg / new_n);

            user["avg_duration"] = new_avg;
            user["avg_n"] = new_n;
         });
         
         response(res, "OK", action, json{
            {"avg_duration", new_avg},
            {"avg_n", new_n},
         });
      }
      
      else if (action == "create-game") {
         File* games = new File(pwd + "/../data/games.json");
         json gameTpl = File::ReadJson(pwd + "/../data/default-game.json");
         size_t gid;
         
         std::cout << "Game, create-game: Query\n";

         games->updateJson([&](json games){
            gid = getMinGid(games);
            gameTpl["gid"] = gid;
            games.push_back(gameTpl);
            return games;
         });
         
         response(res, "OK", action, json{{"gid", gid}});
      }

      else if (action == "connect") {
         File* games = new File(pwd + "/../data/games.json");
         json userTpl = File::ReadJson(pwd + "/../data/default-game-user.json");

         size_t gid = std::stoi(getParam(req, "gid"));
         size_t id = std::stoi(getParam(req, "id"));
         std::string host = getParam(req, "host");

         size_t playersCount;

         games->updateChilds("gid", gid, [&](json& game){
            userTpl["host"] = host;
            userTpl["id"] = id;
            game["users"].push_back(userTpl);

            playersCount = game["users"].size();
         });

         response(res, "OK", action);
         sendAll(gid, id, "connect", json{
            {"count", playersCount},
         });
      }
   }
} // RouteGame

