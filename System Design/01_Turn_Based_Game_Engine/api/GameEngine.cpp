#include "src/board/TicTacBoard.h"
#include "src/game/Board.h"
#include "src/game/GameResult.h"
#include "src/game/Move.h"
#include "src/game/Player.h"

class TicTacGameEngine{
    public:

    Board start(){  // assign a new board to play
        return Board();
    }

    void move(Board board, Player player, Move move){

    }

    GameResult isComplete(TicTacBoard &board1) {
        string firstChar;

        // Check rows
        for (int i = 0; i < 3; i++) {
            firstChar = board1.getCell(i, 0);
            bool rowComplete = (firstChar != "-");
            for (int j = 1; j < 3 && rowComplete; j++) {
                if (board1.getCell(i, j) != firstChar) {
                    rowComplete = false;
                }
            }
            if (rowComplete) return GameResult(true, firstChar);
        }

        // Check columns
        for (int i = 0; i < 3; i++) {
            firstChar = board1.getCell(0, i);
            bool colComplete = (firstChar != "-");
            for (int j = 1; j < 3 && colComplete; j++) {
                if (board1.getCell(j, i) != firstChar) { // FIXED
                    colComplete = false;
                }
            }
            if (colComplete) return GameResult(true, firstChar);
        }

        // Check main diagonal
        firstChar = board1.getCell(0, 0);
        bool diagComplete = (firstChar != "-");
        for (int i = 1; i < 3 && diagComplete; i++) {
            if (board1.getCell(i, i) != firstChar) {
                diagComplete = false;
            }
        }
        if (diagComplete) return GameResult(true, firstChar);

        // Check reverse diagonal
        firstChar = board1.getCell(0, 2);
        bool revDiagComplete = (firstChar != "-");
        for (int i = 1; i < 3 && revDiagComplete; i++) {
            if (board1.getCell(i, 2 - i) != firstChar) {
                revDiagComplete = false;
            }
        }
        if (revDiagComplete) return GameResult(true, firstChar);

        // Check full board
        int countCells = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                string cell = board1.getCell(i, j);
                if (cell == "x" || cell == "o") {
                    countCells++;
                }
            }
        }
        if (countCells == 9) return GameResult(true, "-");

        return GameResult(false, "-");
    }

    
};