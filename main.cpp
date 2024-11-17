#include <iostream>
#include "./headers/Game.h"
#include "./headers/Grid.h"
#include "./headers/Cell.h"
//#include <thread>

int main() {
    Game game(15,15,40);
    game.run();

    int rows = 15;
    int cols = 15;
    int nrMines = 40;

    Grid gameGrid(rows, cols, nrMines);
    gameGrid.generateMines();
    std::cout << "Bombele din grid (x = bomba, o = safe):\n";
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            const Cell& cell = gameGrid.getCell(row, col);
            std::cout << (cell.isMine() ? "x " : "o ");
        }
        std::cout << '\n';
    }
    std::cout << "\n";

    //testez reveal & flag pt (2,2) si (3,3)
    int testX = 5, testY = 5;
    gameGrid.revealCell(testX, testY);
    gameGrid.flagCell(testX+1, testY+1);

    std::cout << "\nDetalii pt fiecare celula:\n";
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            const Cell& cell = gameGrid.getCell(row, col);
            std::cout << "Cell (" << row << ", " << col << "): "
                      << (cell.isMine() ? "Mine" : "No mine") << ", "
                      << (cell.isRevealed() ? "Revealed" : "Hidden") << ", "
                      << (cell.isFlagged() ? "Flagged" : "Not flagged") << "\n";
        }
    }

    std::cout<<std::endl;
    std::cout<<gameGrid;
/*

 */
    return 0;
}