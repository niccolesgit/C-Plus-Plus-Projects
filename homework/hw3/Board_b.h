#include <string>
#include <iostream>
#ifndef BOARD_H //guard for the class
#define BOARD_H //guard for the class
class Board{//creates the class
    private: //creates private variables for:
        std::string **m_data;
        int row;
        int col;
        int * m_height;
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
        void insert(int coln, bool btoken); //determines if player can insert token in the column
        int numTokensInRow(const int rown); //tokens in a row counting function
        int numTokensInColumn(const int coln); //tokens in a column counting function
        std::string getbl() const {return bl_char;} //gets the background token
        //returns the m_data at the 
        std::string getm_data(int i, int j){return m_data[i][j];}
        int getHeight(int i) const {return m_height[i];}
        //Modifiers
        void clear(); //clear function
        void winner(); //determines if there is a winner function
        void addElement(int coln, std::string tok); //
        void expandBoard(int coln, std::string tok);

};
//ostream to send class of board into declared class
std::ostream& operator<< (std::ostream& out, Board& b);

#endif //end guard for the class
