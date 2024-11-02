#include <iostream>
#include "./headers/Grid.h"
#include "./headers/Cell.h"

int main() {
    int gridSize = 5;
    int nrMines = 8;

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

    //testing reveal
    int testX = 2, testY = 2;
    gameGrid.revealCell(testX, testY);
    const Cell& revealedCell = gameGrid.getCell(testX, testY);
    std::cout << "Cell (" << testX << ", " << testY << ") "
              << (revealedCell.isRevealed() ? "is revealed." : "is still hidden.") << "\n";


    // Check each cell's status for additional testing
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