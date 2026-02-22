#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

int cx = 0, cy = 0; 
bool turnX = true;

void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void printBoard() {
    system("cls");
    cout << "Lets Check your Mind and Your Friends Mind who are the Best  ";
    cout << "\n  Use Arrow Keys to Move | Press ENTER to Place X/O\n\n";
    for (int i = 0; i < 3; i++) {
        cout << "     ";
        for (int j = 0; j < 3; j++) {
            if (i == cy && j == cx)
                cout << "[" << board[i][j] << "]";
            else
                cout << " " << board[i][j] << " ";
        }
        cout << "\n";
    }
}

bool checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            board[i][0] != ' ')
            return true;

        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i] &&
            board[0][i] != ' ')
            return true;
    }
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        board[0][0] != ' ')
        return true;

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
        board[0][2] != ' ')
        return true;

    return false;
}
int main() {
    int key;

    while (true) {
        printBoard();

        key = _getch();

        if (key == 224) {
            int arrow = _getch();
            if (arrow == 72 && cy > 0) cy--;
            else if (arrow == 80 && cy < 2) cy++;
            else if (arrow == 75 && cx > 0) cx--;
            else if (arrow == 77 && cx < 2) cx++;
        }
        else if (key == 13) {
            if (board[cy][cx] == ' ') {
                board[cy][cx] = (turnX ? 'X' : 'O');
                turnX = !turnX;

                if (checkWin()) {
                    printBoard();
                    cout << "\n\n  Player " << (turnX ? 'O' : 'X') << " Wins!\n";
                    break;
                }
            }
        }
    }
    return 0;
}
