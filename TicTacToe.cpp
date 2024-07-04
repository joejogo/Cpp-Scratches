#include <iostream>
#include <cmath>
#include <unordered_map>
#include <string>
#include "TicTacConsts.hpp"

using namespace std;

void GetPlayerMove(int* outMoveArr);

void ShowGrid(char gameGrid[][3]);

void SetMove(char gameGrid[][3], char playerId, int moveRow, int moveCol);

bool IsWin(char gameGrid[][3], char userChar);

bool IsDraw(char gameGrid[][3], char emptyChar);

bool IsWinOrDraw(char gameGrid[][3], char userChar, char emptyChar);

bool VecCollectionContains(vector<vector<int>> vecColl, int* randArr);

void GetComputerMove(char gameGrid[][3], int* outMoveArr);

int main()
{
    // Create the grid
    char grid[3][3] = {};
    fill(&grid[0][0], &grid[0][0] + sizeof(grid), EmptyChar);

    bool GameOver = false;
    while (!GameOver)
    {
        // Get player move
        int playerMove[2];
        GetPlayerMove(playerMove);
        cout << "Your move: Row " << playerMove[0] << " Column: " << playerMove[1] << endl;

        // Set player move
        SetMove(grid, PlayerChar, playerMove[0]-1, playerMove[1]-1);
        // Check for winner / draw (Player)
        GameOver = IsWinOrDraw(grid, PlayerChar, EmptyChar);
        if (GameOver) { break; }

        // Get computer move
        int compMove[2] = {1, 1};
        GetComputerMove(grid, compMove);

        // Set computer move
        SetMove(grid, CompChar, compMove[0], compMove[1]);
        
        // Check for winner / draw (Computer)
        GameOver = IsWinOrDraw(grid, CompChar, EmptyChar);
        if (GameOver) { break; }
    }    
    return 0;
}

void GetPlayerMove(int* outMoveArr)
{
    int moveRow;
    int moveCol;
    cout << "Enter move Row: ";
    cin >> moveRow;
    outMoveArr[0] = moveRow;
    cout << "Enter move Column: ";
    cin >> moveCol;
    outMoveArr[1] = moveCol;
}

void ShowGrid(char gameGrid[][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << gameGrid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void SetMove(char gameGrid[][3], char playerId, int moveRow, int moveCol)
{
    gameGrid[moveRow][moveCol] = playerId;
    ShowGrid(gameGrid);
}

bool IsWin(char gameGrid[][3], char userChar)
{
    // If any row or column is full of a single character
    bool winRow = false;
    bool winCol = false;
    for (int i = 0; i < 3; i++)
    {
        bool rowComplete = true;
        bool colComplete = true;
        for (int j = 0; j < 3; j++)
        {
            if (gameGrid[i][j] != userChar) { rowComplete = false; }
            if (gameGrid[j][i] != userChar) { colComplete = false; }
        }
        if (rowComplete) { winRow = true; }
        if (colComplete) { winCol = true; }
    }

    // If any Across is full (a0, b1, c2) or (a2, b1, c0)
    bool winDiag1 = true;
    for (int i = 0; i < 3; i++)
    {
        if (gameGrid[i][i] != userChar)
        {
            winDiag1 = false;
            break;
        }
    }
    bool winDiag2 = true;
    int winDiag2Coords[3][2] = {
        {2, 0},
        {1, 1},
        {0, 2}
    };
    for (int i = 0; i < 3; i++)
    {
        int diagCoordRow = winDiag2Coords[i][0];
        int diagCoordCol = winDiag2Coords[i][1];
        if (gameGrid[diagCoordRow][diagCoordCol] != userChar)
        {
            winDiag2 = false;
            break;
        }
    }
    bool winDiag = (winDiag1 || winDiag2);

    return (winRow || winCol || winDiag);
}

bool IsDraw(char gameGrid[][3], char emptyChar)
{
    bool GridFull = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (gameGrid[i][j] == emptyChar)
            {
                GridFull = false;
            }
        }
    }
    return GridFull;
}

bool IsWinOrDraw(char gameGrid[][3], char userChar, char emptyChar)
{
    bool Win = IsWin(gameGrid, userChar);
    bool Draw = IsDraw(gameGrid, emptyChar);
    bool IsGameOver = (Win || Draw);

    // Print out any message for end of game
    if (Win)
    {
        switch (userChar) {
        case PlayerChar:
            cout << "You win!" << endl;
            break;
        case CompChar:
            cout << "You lose ... :( " << endl;
            break;
        }
    }
    else if (Draw)
    {
        cout << "Draw! Nobody Wins." << endl;
    }
    return IsGameOver;
}

bool VecCollectionContains(vector<vector<int>> vecColl, int* randArr)
{
    bool ArrContained = false;
    for (vector<int> vec : vecColl)
    {
        if (vec[0] == randArr[0] && vec[1] == randArr[1])
        {
            ArrContained = true;
            break;
        }
    }
    return ArrContained;
}

void GetComputerMove(char gameGrid[][3], int* outMoveArr)
{
    // Get empty tile coordinates
    vector<vector<int>> freeTileCoords;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (gameGrid[i][j] == EmptyChar)
            {
                freeTileCoords.push_back({ i, j });
            }
        }
    }
    int numFreeTiles = freeTileCoords.size();

    // Pick a random one from the empty tiles
    vector<int> randomFreeTile = freeTileCoords.at(rand() % numFreeTiles);
    outMoveArr[0] = randomFreeTile[0];
    outMoveArr[1] = randomFreeTile[1];
}

