#include <iostream>
#include "Board.h"
int Board::numRows(){
   return row;
}
int Board::numColumns(){
   return col;
}
int Board::numTokensInRow(const int rown){
    int tk = 0;
    if (rown > row-1){
        return -1;
    }else{
        for (int i = rown; i < rown+1; i++){
                for (int j = 0; j < col; j++){
                    if (m_data[i][j]!=bl_char){
                        tk+=1;
                    }
                }
            }
        return tk;
        }
    return tk;
    
}

int Board::numTokensInColumn(const int coln){
    int tk = 0;
    if (coln > col-1){
        return -1;
    }else{
        for (int i = 0; i < row; i++){
                for (int j = col; j < col+1; j++){
                    if (m_data[i][j]!=bl_char){
                        tk+=1;
                    }
                }
            }
        return tk;
        }
    return tk;
    
}

void Board::insert(const int coln, bool pltoken){
    //make new array of strings 
    std::string token;

    bool win;
    if (pltoken == true){
        token = p1_char;
    }else{
        token = p2_char;
    }

    if (coln < row && coln < col){
        for (int i = row-1; i >= 0; i--){
        if (m_data[i][coln] == bl_char){
            m_data[i][coln] = token;
            break;
            }
        }       
    
    }else if(coln > row){
        cr +=1;
        for (int i = row; i >= 0; i--){
        if (m_data[i][coln] == bl_char){
            m_data[i][coln] = token;
            break;
            }       
        }    
    }
}
/*
void Board::clear(){

}*/
