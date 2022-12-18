#ifndef BOARD_H //guard for the class
#define BOARD_H //guard for the class
#include <string>
class Board{//creates the class
    private: //creates private variables for:
        std::string **m_data;
        std::string * m_tokens;
        int row;
        int col;
        int tklen;
        std::string p1_char; //player 1 character
        std::string p2_char; //player 2 character
        std::string bl_char; //blank space character
    public:
    //creates the board class and functions
        Board(std::string ap1_char, std::string ap2_char, std::string abl_char);
        ~Board();
        std::string** getm_data();
        std::string getbl() const {return bl_char;}
        int numRows(); //num row counting function
        int numColumns(); //num columns counting function
        int numTokensInRow(const int rown); //tokens in a row counting function
        int numTokensInColumn(const int coln); //tokens in a column counting function
        void insert(const int coln, bool btoken); //determines if player can insert token in the column
        void expRow(const int coln, std::string token);
        void expCol(const int coln, std::string token);
        /*
        void clear(); //clear function
        int numRows(); //num row counting function
        int numColumns(); //num columns counting function
        */
};
std::ostream& operator<<(std::ostream& out, Board& b);
#endif //end guard for the class
