//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "common.hpp"
#include "Client.hpp"

Client::~Client() {
}


void Client::initialize(unsigned int player, unsigned int board_size){
    //Make sure to distinguish between parameter and actual player/board_size from Client

    Client::player = player;
    Client::board_size = board_size;

//create a 2D vector
//Used geeksforgeeks : https://www.geeksforgeeks.org/2d-vector-in-cpp-with-user-defined-size/

    vector<vector<int>> board;
    board.resize(board_size, std::vector<int>(board_size, 0));

//Convert numeric value to string to allow it to be added to the file name
    string playerNum = std::to_string(player);

//Used github example: https://github.com/USCiLab/cereal/tree/a5a30953125e70b115a28dd76b64adf3c97cc883
    std::ofstream create("player_" + playerNum + ".action_board.json");
    cereal::JSONOutputArchive archive_out(create);
    archive_out(CEREAL_NVP(board));

//Sets the player number and player action board for client according to id
    if(player == 1){
        board_name = "player_1.action_board.json";
    }

    if(player = 2){
        board_name = "player_2.action_board.json";
    }
}


void Client::fire(unsigned int x, unsigned int y) {
    //Write shot to file
    if(player == 1){
        std::ofstream FireShot1("player_1.shot.json");
        cereal::JSONOutputArchive shot1(FireShot1);
        shot1(CEREAL_NVP(x), CEREAL_NVP(y));
    }

    if(player == 2){
        std::ofstream FireShot2("player_2.shot.json");
        cereal::JSONOutputArchive shot2(FireShot2);
        shot2(CEREAL_NVP(x), CEREAL_NVP(y));
    }
}


bool Client::result_available() {

    //Check to see if result file is available
    if(player == 1){

        ifstream fileAvailable1("player_1.result.json");

        if(fileAvailable1.good()) {
            return true;
        }else{
            return false;
        }
    }
    else if(player == 2){

        ifstream fileAvailable2("player_2.result.json");

        if(fileAvailable2.good()) {
            return true;
        }else{
            return false;
        }
    }
}


int Client::get_result() {
    int p1ReturnNum;
    int p2ReturnNum;

    if(player == 1){

        ifstream result1("player_1.result.json");
        cereal::JSONInputArchive p1Result(result1);
        p1Result(p1ReturnNum);

        remove("player_1.result.json");

        if(p1ReturnNum == 1){
            return HIT;
        }
        if(p1ReturnNum == -1){
            return MISS;
        }
        if(p1ReturnNum == 0){
            return OUT_OF_BOUNDS;
        }else{
            throw ClientException("Error");
        }
    }

    if(player == 2){
        ifstream result2("player_2.result.json");
        cereal::JSONInputArchive p2Result(result2);
        p2Result(p2ReturnNum);

        remove("player_2.result.json");


        if(p2ReturnNum == 1){
            return HIT;
        }
        if(p2ReturnNum == -1){
            return MISS;
        }
        if(p2ReturnNum == 0){
            return OUT_OF_BOUNDS;
        }else{
            throw ClientException("Error");
        }
    }
}


void Client::update_action_board(int result, unsigned int x, unsigned int y) {
    vector<vector<int>> action;

//Used: https://uscilab.github.io/cereal/assets/doxygen/group__Utility.html

    if(player == 1){

        ifstream board_in("player_1.action_board.json");
        cereal::JSONInputArchive update_in(board_in);
        update_in(action);
        action[x][y] = result;

        ofstream board_out("player_1.action_board.json");
        cereal::JSONOutputArchive update_out(board_out);
        update_out(cereal::make_nvp("board", action));

    }else if(player == 2){

        ifstream board_in("player_2.action_board.json");
        cereal::JSONInputArchive update_in(board_in);
        update_in(action);
        action[x][y] = result;

        ofstream board_out("player_2.action_board.json");
        cereal::JSONOutputArchive update_out(board_out);
        update_out(cereal::make_nvp("board", action));

    }
}


string Client::render_action_board(){
}