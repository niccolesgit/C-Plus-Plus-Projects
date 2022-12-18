#ifndef Board_h //guard for the class
#define Board_h //guard for the class
class Board{//creates the class
    private: //creates private variables for:
        std::string p1_char; //player 1 character
        std::string p2_char; //player 2 character
        std::string bl_char; //blank space character
    public:
    //creates the board class and functions
    std::string board[5][4]; //creates default board size
        Board(std::string ap1_char, std::string ap2_char, std::string abl_char){
                for (unsigned int i = 0; i < 5; ++i) {   // for each row
                    for (unsigned int j = 0; j < 4; ++j) { // for each column
                    board[i][j] = abl_char;
                }
            }
        }
        friend std::ostream& operator<<(std::ostream& out, Board& b)
        {
            for (int i = 0; i < 5; i++){
                for (int j = 0; j < 4; j++){
                     out << b.board[i][j] << " ";
                }
                out << "\n";
            }	
        } 
        void numTokensInRow(const int rown){}; //tokens in a row counting function
        /*void numTokensInColumn(const int coln); //tokens in a column counting function
        void Insert(const int coln, bool pltoken); //determines if player can insert token in the column

        void Clear(); //clear function
        void numRows(); //num row counting function
        void numColumns(); //num columns counting function
        */
};
#endif //end guard for the class
