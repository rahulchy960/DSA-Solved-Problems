#include "Board.h"
#include<string>
using namespace std;
class TicTacBoard: public Board{ 
    string cells[3][3];
    public:
        string getCell(int row, int col){
            return cells[row][col];
        }

};