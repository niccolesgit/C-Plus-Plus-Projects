#include <iostream>
#include "Board.h"

Board::Board(std::string ap1_char, std::string ap2_char, std::string abl_char){
    col = 4;
    row = 5;
    m_data = new std::string*[col];
    m_height = new int[col];
    p1_char = ap1_char;
    p2_char = ap2_char;
    bl_char = abl_char;
    for (int i =0; i<col;i++){
        m_data[i] = NULL;
        m_height[i] = 0;
    }

}
Board::~Board(){
    for (int i = col-1;i>=0;i--){
        delete [] m_data[i];
    }
    delete [] m_data;
    delete [] m_height;
}
std::ostream& operator<< (std::ostream& out, Board& b){
    for(int i = b.numRows()-1; i>=0;i--){
        for(int j = 0; j<b.numColumns();j++){
            if(b.getHeight(j) != 0){
                 if(b.getHeight(j)>i){
                    out << b.getm_data(j, i) << " ";
                }else{
                    out << b.getbl() << " ";
                }
            }else{
                out << b.getbl() << " ";
                }
            }
             out << "\n";
        }
    return out;

}
int Board::numTokensInColumn(const int coln){
    if (coln > col-1){
        return -1;
    }else{
        return(m_height[coln]);
    }
}
int Board::numTokensInRow(const int rown){
    int tk = 0;
    if(rown > row-1){
        return -1;
    }else{
    for(int i = 0; i< col;i++){
        if(rown<=(m_height[i]-1)){
            if(m_height[i]!=0){
                tk++;
                }
            }
        }
        return tk; 
    }
}

void Board::insert(const int coln, bool btoken){
    if(coln<col){
        if(btoken){
            addElement(coln, p1_char);
        }else{
           addElement(coln, p2_char); 
        }
    }else if(col>=0){
        if(btoken){
            expandBoard(coln, p1_char);
        }else{
           expandBoard(coln, p2_char); 
        }
    }
}
void Board::addElement(int coln, std::string tok){
    int maxCol = 0;
    std::string* temp;
    m_height[coln] +=1;
    maxCol = m_height[coln];
    if(maxCol == 0){
        temp = new std::string[1];
        temp[0] = tok;
        m_data[coln] = temp;
    }else{
        temp = new std::string[maxCol];
        if(maxCol >row){
            row = maxCol;
        }
        for(int i = 0;i<maxCol-1;i++){
            temp[i] = m_data[coln][i];
        }
        temp[maxCol-1] = tok;

    }
    delete [] m_data[coln];
    m_data[coln] = temp;

}
void Board::expandBoard(int coln, std::string tok){
    std::string ** nm_data;
    int* nm_height;
    nm_data = new std::string*[coln];
    nm_height = new int[coln];
    
    for(int j = 0;j<coln+1;j++){
        if(j<col){
            if (m_data[j] == NULL) {
                nm_data[j] = NULL;
                nm_height[j] = 0;
            }
            else {
                nm_data[j] = new std::string[m_height[j]];
                for(int i = 0; i<m_height[j];i++){
                    nm_data[j][i] = m_data[j][i];
                }
               nm_height[j] = m_height[j];
            }
        }else if(j != coln){
           nm_data[j] = NULL;
            nm_height[j] = 0;
        }else{
            nm_data[j] = new std::string[1];
            nm_data[j][0] = tok;
            nm_height[j] =1;  
        }
    }
    for(int i =0;i<col;i++){
        delete[] m_data[i];
    }
    delete[] m_data;
    delete[] m_height;
    col = coln+1;

    m_data = nm_data;
    m_height = nm_height;

}
void Board::winner(){


}
void Board::clear(){
    for(int i = 0;i<col;i++){
        delete [] m_data[i];
    }
    delete [] m_data;
    m_data = new std::string*[col];
    for(int i=0;i<4;i++){
        m_data[i] = NULL;
    }
}
