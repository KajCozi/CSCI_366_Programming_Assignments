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

#include <math.h>
#include "BitArray2D.hpp"
#include "common.hpp"


BitArray2D::BitArray2D(unsigned int rows, unsigned int columns) {

    if(rows < 1 || rows > BOARD_SIZE){
        throw BitArray2DException("BitArray2D Exception: 'BitArray2D' function ROWS");
    }

    if(columns < 1 || columns > BOARD_SIZE){
        throw BitArray2DException("BitArray2D Exception: 'BitArray2D' function COLUMNS");
    }

}


BitArray2D::~BitArray2D() {

}


bool BitArray2D::get(unsigned int row, unsigned int column){

// check array bounds
    if(row < 0 || row >= BOARD_SIZE){
        throw BitArray2DException("BitArray2D Exception: 'get' function ROW");
    }

    if(column < 0 || column >= BOARD_SIZE){
        throw BitArray2DException("BitArray2D Exception: 'get' function COLUMN");
    }

// get the element
    return get_bit_elem(array, columns, row, column);

}


void BitArray2D::set(unsigned int row, unsigned int column){

//    check array bounds
    if(row < 0 || row >= BOARD_SIZE){
        throw BitArray2DException("BitArray2D Exception: 'set' function ROW");
    }

    if(column < 0 || column >= BOARD_SIZE){
        throw BitArray2DException("BitArray2D Exception: 'set' function COLUMN");
    }
    
   // set the element
   set_bit_elem(array, columns, row, column);
}
