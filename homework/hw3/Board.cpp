#include <iostream>
#include "Board.h"
//constructs the board
Board::Board(std::string ap1_char, std::string ap2_char, std::string abl_char){
    col = 4; //sets default column
    row = 5; //sets default row
    m_data = new std::string*[col]; //creates m_data based on columns
    //creates a height pointer based on column length (keeps track of column height
    //of the tokens)
    m_height = new int[col]; 
    p1_char = ap1_char; //p1 char
    p2_char = ap2_char; //p2 char
    bl_char = abl_char; //background char
    //sets the m_data to nulls
    //sets m_heights to 0 (no tokens in the columns yet)
    for (int i =0; i<col;i++){
        m_data[i] = NULL;
        m_height[i] = 0;
    }

}
//deconstructor
Board::~Board(){
    for (int i = col-1;i>=0;i--){
        delete [] m_data[i];
    }
    delete [] m_data;
    delete [] m_height;
}
//prints the board
std::ostream& operator<< (std::ostream& out, Board& b){
    //loops through the rows and columns
    for(int i = b.numRows()-1; i>=0;i--){
        for(int j = 0; j<b.numColumns();j++){
            //if the height isnt 0 (meaning theres a token)
            if(b.getHeight(j) != 0){
                 if(b.getHeight(j)>i){
                     //prints token
                    out << b.getm_data(j, i) << " ";
                }else{
                    //prints background char
                    out << b.getbl() << " ";
                }
            }else{
                //prints background char
                out << b.getbl() << " ";
                }
            }
             out << "\n";
        }
    return out;

}
//counts the number of tokens in the column
int Board::numTokensInColumn(const int coln){
    if (coln > col-1){
        return -1; //if column doesnt exist return -1
    }else{
        //m_height pointer keeps track of the height based on tokens
        return(m_height[coln]);
    }
}
int Board::numTokensInRow(const int rown){
    int tk = 0;
    if(rown > row-1){
        return -1; //if row doesnt exist return -1
    }else{
    //if the column is in the row
    for(int i = 0; i< col;i++){
        if(rown<=(m_height[i]-1)){
            if(m_height[i]!=0){ //and if there are tokens in therer
                tk++; //increment the number of tokens
                }
            }
        }
        return tk; 
    }
}
//insert function
std::string Board::insert(const int coln, bool btoken){
    //if btoken is true = p1 char, if false = p2 char
    //if the column is not expanding
    if(coln<col){
        //adds the token into the columns
        if(btoken){
            addElement(coln, p1_char);
        }else{
           addElement(coln, p2_char); 
        }
    //if your column is greater than the column size
    }else if(col>=0){
        //expands the board and adds the token
        if(btoken){
            expandBoard(coln, p1_char);
        }else{
           expandBoard(coln, p2_char); 
        }
    }
    return bl_char;
}
//adds the element into the rows
void Board::addElement(int coln, std::string tok){
    int maxCol = 0; //makes the max col int
    std::string* temp; //creates temp array
    m_height[coln] +=1; //increments the column length plus one
    maxCol = m_height[coln]; //sets the max col to the height
    //if there are no tokens
    if(maxCol == 0){
        //creates an array to hold the one token
        temp = new std::string[1];
        temp[0] = tok;
        m_data[coln] = temp;
    //if there are tokens in there
    }else{
        //creates array to hold maxlength of the column
        temp = new std::string[maxCol];
        //if the maxcol is greater than the rows
        if(maxCol >row){
            row = maxCol; //sets the row to the maxcolumn
        }
        //adds the token on top of current spot
        for(int i = 0;i<maxCol-1;i++){
            temp[i] = m_data[coln][i];
        }
        //adds token on current spot
        temp[maxCol-1] = tok;

    }
    //deletes old, replaces it with new array
    delete [] m_data[coln];
    m_data[coln] = temp;

}
//expands the board if the column exceeds the boarder
void Board::expandBoard(int coln, std::string tok){
    std::string ** nm_data; //creates new m_data
    int* nm_height; //creates new height pointer
    nm_data = new std::string*[coln]; //sets it to the column num
    nm_height = new int[coln]; //sets the height to the column num

    //loops through the columns
    for(int j = 0;j<coln+1;j++){
        //if the column is less than the current column
        if(j<col){
            //sets data to nulls and height to 0, if there is no token there
            if (m_data[j] == NULL) {
                nm_data[j] = NULL;
                nm_height[j] = 0;
            }
            else{
                //sets the nm_data to the height of the column
                nm_data[j] = new std::string[m_height[j]];
                //loops through and adds the token to the spot
                for(int i = 0; i<m_height[j];i++){
                    nm_data[j][i] = m_data[j][i];
                }
            //also sets the token the spot
               nm_height[j] = m_height[j];
            }
        //if the column number isnt in bounds
        }else if(j != coln){
            //sets nm_data to null
           nm_data[j] = NULL;
            nm_height[j] = 0;
        }else{//if there are no other cases
            //sets the array to hold one token
            nm_data[j] = new std::string[1];
            nm_data[j][0] = tok;
            nm_height[j] =1;  
        }
    }
    //deletes all the memmory
    for(int i =0;i<col;i++){
        delete[] m_data[i];
    }
    delete[] m_data;
    delete[] m_height;
    //increments the columns  number
    col = coln+1;
    //replaces old with new
    m_data = nm_data;
    m_height = nm_height;

}
//clears the board
void Board::clear(){
    //deletes the old memory
    for(int i = 0;i<col;i++){
        delete [] m_data[i];
    }
    delete [] m_data;
    //resets the m_data to size of original and resets the n_data to null
    m_data = new std::string*[col];
    for(int i=0;i<col;i++){
        m_data[i] = NULL;
    }
}
