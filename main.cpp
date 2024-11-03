#include <iostream>
#include "./headers/Grid.h"
#include "./headers/Cell.h"

int main() {
    int gridSize = 9;
    int nrMines = 4;

    Grid gameGrid(gridSize, nrMines);
    gameGrid.generateGame();

    std::cout << "Bombele din grid (x = bomba, o = safe):\n";
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
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
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            const Cell& cell = gameGrid.getCell(row, col);
            std::cout << "Cell (" << row << ", " << col << "): "
                      << (cell.isMine() ? "Mine" : "No mine") << ", "
                      << (cell.isRevealed() ? "Revealed" : "Hidden") << ", "
                      << (cell.isFlagged() ? "Flagged" : "Not flagged") << "\n";
        }
    }

    std::cout<<std::endl;
    std::cout<<gameGrid;
    return 0;
}