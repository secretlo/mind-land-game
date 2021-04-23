namespace RouteLeaders {
   std::string pwd = File::pwd();

   void Handler(const Request& req, Response& res) {
      std::cout << "Leaders: Query\n";

      File* users = new File(pwd + "/../data/users.json");
      std::vector<std::pair<double, std::string>> rating;

      users->forEach([&](json& user){
         auto login = user["login"].get<std::string>();
         auto duration = user["avg_duration"].get<double>();
         rating.push_back(std::make_pair(duration, login));
      });
      
      std::sort(rating.begin(), rating.end());
      json result = json::array();

      for (int i = 0; i < 5; i++) {
         json data;
         data["login"] = rating[i].second;
         data["duration"] = rating[i].first;
         result.push_back(data);
      }

      response(res, "OK", "leaders", json{
         {"rating", result},
      });
   }
} // RouteLeaders

