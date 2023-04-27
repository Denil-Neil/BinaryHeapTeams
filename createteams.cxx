#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"
#include "priorityqueue.h"

using namespace std;
using json = nlohmann::json;

bool is_player_in_team(int player_num, const vector<int>& used_player_nums) {
    for (const auto& num : used_player_nums) {
        if (num == player_num) {
            return true;
        }
    }
    return false;
}

void create_teams(const json& data, json& final_teams) {
    int num_players = data["metadata"]["numPlayers"];
    int num_teams = num_players / 2;

    vector<pair<double, pair<int, int>>> team_data;
    for (auto& team_stat : data["teamStats"]) {
        double win_perc = team_stat["winPercentage"];
        int player1 = team_stat["playerOne"];
        int player2 = team_stat["playerTwo"];
        double win_margin = abs(50.00 - win_perc);
        team_data.push_back(make_pair(win_margin, make_pair(player1, player2)));
    }
    sort(team_data.begin(), team_data.end());

    vector<int> used_player_nums;
    for (int i = 0; i < num_teams; i++) {
        while (!team_data.empty()) {
            auto curr_team = team_data.front().second;
            if (!is_player_in_team(curr_team.first, used_player_nums) &&
                !is_player_in_team(curr_team.second, used_player_nums)) {
                final_teams["teams"][i] = curr_team;
                used_player_nums.push_back(curr_team.first);
                used_player_nums.push_back(curr_team.second);
                team_data.erase(team_data.begin());
                break;
            } else {
                team_data.erase(team_data.begin());
            }
        }
    }
}


int main(int argc, char** argv) {
    ifstream file(argv[1]);
    json data = json::parse(file);

    json final_teams;
    create_teams(data, final_teams);

    cout << final_teams.dump(2) << endl;

    return 1;
}

