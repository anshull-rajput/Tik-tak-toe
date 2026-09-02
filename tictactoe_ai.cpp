#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

using Board = array<char, 9>;

const int wins[8][3] = {
    {0,1,2}, {3,4,5}, {6,7,8},
    {0,3,6}, {1,4,7}, {2,5,8},
    {0,4,8}, {2,4,6}
};

void showBoard(const Board& b) {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        cout << " " << b[i] << " ";
        if (i % 3 != 2) cout << "|";
        else if (i != 8) cout << "\n---+---+---\n";
    }
    cout << "\n\n";
}

char winner(const Board& b) {
    for (auto& w : wins)
        if (b[w[0]] != ' ' && b[w[0]] == b[w[1]] && b[w[1]] == b[w[2]])
            return b[w[0]];

    for (char c : b)
        if (c == ' ') return 'N';
    return 'T';
}

int minimax(Board& b, bool aiTurn) {
    char result = winner(b);
    if (result == 'O') return 10;
    if (result == 'X') return -10;
    if (result == 'T') return 0;

    int best = aiTurn ? -1000 : 1000;
    for (int i = 0; i < 9; i++) {
        if (b[i] != ' ') continue;
        b[i] = aiTurn ? 'O' : 'X';
        int score = minimax(b, !aiTurn);
        b[i] = ' ';
        best = aiTurn ? max(best, score) : min(best, score);
    }
    return best;
}

int bestMove(Board& b) {
    int move = -1, bestScore = -1000;
    for (int i = 0; i < 9; i++) {
        if (b[i] != ' ') continue;
        b[i] = 'O';
        int score = minimax(b, false);
        b[i] = ' ';
        if (score > bestScore) bestScore = score, move = i;
    }
    return move;
}

int main() {
    Board board = {'1','2','3','4','5','6','7','8','9'};
    char player = 'X';

    cout << "Tic-Tac-Toe: Player X vs AI O\n";

    while (winner(board) == 'N') {
        showBoard(board);

        if (player == 'O') {
            board[bestMove(board)] = 'O';
        } else {
            int pos;
            cout << "Enter position (1-9): ";
            cin >> pos;

            if (cin.fail() || pos < 1 || pos > 9 || board[pos - 1] == 'X' || board[pos - 1] == 'O') {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid move. Try again.\n";
                continue;
            }
            board[pos - 1] = 'X';
        }
        player = (player == 'X') ? 'O' : 'X';
    }

    showBoard(board);
    char result = winner(board);
    cout << (result == 'T' ? "It's a tie!\n" : string("Player ") + result + " wins!\n");
    return 0;
}
