#include <string>
#include <iostream>
#ifndef BOARD_H //guard for the class
#define BOARD_H //guard for the class
class Board{//creates the class
    private: //creates private variables for:
        std::string **m_data; //m_data
        int row; //rows
        int col; //columns
        int * m_height; //height pointer
        std::string p1_char; //player 1 character
        std::string p2_char; //player 2 character
        std::string bl_char; //blank space character
    public:
    //creates the board class and functions
        //constuctor
        Board(std::string ap1_char, std::string ap2_char, std::string abl_char);
        //deconsturctor
        ~Board();
        //Acessors:
        int numRows() const {return row;} //num row counting function
        int numColumns() const {return col;} //num columns counting function
        std::string insert(int coln, bool btoken); //determines if player can insert token in the column
        int numTokensInRow(const int rown); //tokens in a row counting function
        int numTokensInColumn(const int coln); //tokens in a column counting function
        std::string getbl() const {return bl_char;} //gets the background token
        //returns the m_data token at that given column and row
        std::string getm_data(int i, int j){return m_data[i][j];}
        int getHeight(int i) const {return m_height[i];} //gets the height of 
        //Modifiers
        void clear(); //clear function
        //function to add token in row (also expands row)
        void addElement(int coln, std::string tok); 
        //function to expand the columns
        void expandBoard(int coln, std::string tok);

};
//ostream to send class of board into declared class
std::ostream& operator<< (std::ostream& out, Board& b);

#endif //end guard for the class
