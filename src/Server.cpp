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
#include "Server.hpp"


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */

char arrayboard1 [BOARD_SIZE][BOARD_SIZE];
char arrayboard2 [BOARD_SIZE][BOARD_SIZE];

int get_file_length(ifstream *file){
}


void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){
    //Figured out that I was originally comparing BOARD_SIZE to the parameter instead of the actual board_size of players 1 and 2
    this->board_size = board_size;

//Determines if board size is wrong
    if (this->board_size != BOARD_SIZE){
        throw ServerException("The board size is wrong");
    }

//Determines if file name is bad
    if(p1_setup_board !=  "player_1.setup_board.txt" && p2_setup_board != "player_2.setup_board.txt"){
        throw ServerException("Bad file name");
    }


//Used this site: http://www.cplusplus.com/doc/tutorial/files/
//read in the file for player 1

    ifstream begin1("player_1.setup_board.txt");

    for(int i=0; i < BOARD_SIZE; i++){
        for(int j=0; j < BOARD_SIZE; j++){
            begin1 >> arrayboard1[i][j];
//                 cout << arrayboard1[i][j];
        }
//            cout << "\n";
    }

//read in the file for player
    ifstream begin2("player_2.setup_board.txt");

    for(int i=0; i < BOARD_SIZE; i++) {
//            cout << i;
        for (int j = 0; j < BOARD_SIZE; j++) {
            begin2 >> arrayboard2[i][j];
//                cout << arrayboard2[i][j];
//                cout << j;
        }
//            cout << "\n";
    }

}


Server::~Server() {
}


BitArray2D *Server::scan_setup_board(string setup_board_name){
}

int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    //Determines if player number is too low or too high
    if (player < 1 || player > 2) {
        throw ServerException("Player number out of bounds");
    }

//Determines if shot was out of bounds for X and Y
    if (x >= board_size || y >= board_size) {
        return OUT_OF_BOUNDS;
    }

//Determines if hit or miss was detected

//Swapped order of x & y because incorrect output was being produced
    if(player == 1){
        if(arrayboard2[y][x] == 'C' || arrayboard2[y][x] == 'B' || arrayboard2[y][x] == 'R'||arrayboard2[y][x] == 'S'||arrayboard2[y][x] == 'D'){
            return HIT;
        }
        else{
            return MISS;
        }
    }

    if(player == 2){
        if(arrayboard1[y][x] == 'C' || arrayboard1[y][x] == 'B' || arrayboard1[y][x] == 'R'||arrayboard1[y][x] == 'S'||arrayboard1[y][x] == 'D'){
            return HIT;
        }
        else{
            return MISS;
        }
    }

}


int Server::process_shot(unsigned int player) {
    int x;
    int y;

//Determines if player number is too low or too high
    if (player < 1 || player > 2) {
        throw ServerException("Wrong number of players");
    }

//Used Stack Overflow: https://stackoverflow.com/questions/32205981/reading-json-files-in-c?fbclid=IwAR2mE88zb0yzC55CeEAdr-szLUxcQFF9cwGoJ5sJ8Sn-Tr0V_vB2C-sgvy8
//read 1
    std::ifstream shot_file_read1("player_1.shot.json");

    if(shot_file_read1.fail())
        return NO_SHOT_FILE;

//Used Mike Wittie's example on github
    cereal::JSONInputArchive archive_in1(shot_file_read1);
    archive_in1(x,y);

    /*Help from Cooper - result is found elsewhere in the files, tried
     *  use "outcome" as my variable name. However this did not
     *  work so we changed to result*/

    int result;
    result = evaluate_shot(player, x, y);
    printf("\n\n");
    printf("%d", result);
    printf("\n\n");

//write 1
    std::ofstream shot_file_write1("player_1.result.json");
    cereal::JSONOutputArchive archive_out1(shot_file_write1);
    archive_out1(CEREAL_NVP(result));

    remove("player_1.shot.json");


//read 2
    std::ifstream shot_file_read2("player_1.shot.json");

    if(shot_file_read2.fail())
        return NO_SHOT_FILE;

    cereal::JSONInputArchive archive_in2(shot_file_read2);
    archive_in2(x,y);

    result = evaluate_shot(player, x, y);
    printf("\n\n");
    printf("%d", result);
    printf("\n\n");

//write 2
    std::ofstream shot_file_write("player_1.result.json");
    cereal::JSONOutputArchive archive_out2(shot_file_write);
    archive_out2(CEREAL_NVP(result));

    remove("player_1.shot.json");

    return SHOT_FILE_PROCESSED;
}