#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>

std::string board[3][3];
std::string original_board[3][3];

int PLAYER_WIN = 0;
int COMPUTER_WIN = 1;
int NO_WIN = 2;

int current_pos;

void print_board() {
    if (end(board)-begin(board) == 3) {
        for (int i = 0; i < end(board) - begin(board); i++) {
            std::cout << "   |   |   " << std::endl;
            for (int j = 0; j < end(board[i]) - begin(board[i]); j++) {
                if (j == end(board[i]) - begin(board[i]) - 1) {
                    std::cout << " " << board[i][j] << " " << std::endl;
                } else {
                    std::cout << " " << board[i][j] << " |";
                }
            }
            if (i == end(board) - begin(board) - 1) {
                std::cout << "   |   |   " << std::endl;
            } else {
                std::cout << "___|___|___" << std::endl;

            }
        }
    } else {
        // dynamically print
        for (int i = 0; i < end(board) - begin(board); i++) {
            for (int j = 0; j < end(board[i]) - begin(board[i]); j++) {
                if (j == end(board[i]) - begin(board[i]) - 1) {
                    std::cout << " " << board[i][j] << " " << std::endl;
                } else {
                    std::cout << " " << board[i][j];
                }
            }
        }
    }
}

void user_input(bool again) {
    if (again) {
        std::cout << "Invalid input. Use a position that is not in use." << std::endl;
    }
    int pos;
    std::cout << std::endl;
    std::cout << "Enter a position (or -1 to quit): ";
    scanf("%d", &pos);

    if (pos == -1) {
        exit(0);
    }

    for (int i = 0; i<end(board)-begin(board); i++) {
        for (int j = 0; j<end(board[i])-begin(board[i]); j++) {
            if (original_board[i][j] == std::to_string(pos)) {
                if (board[i][j] == "X" || board[i][j] == "O") {
                    user_input(true);
                }
                else {
                    board[i][j] = "X";
                    break;
                }

            }
        }
    }
}

void computer_move() {
    int pos;
    int rows = *(&board + 1) - board;
    int columns = *(&board[0] + 1) - board[0];

    pos = rand() % (rows * columns) + 1;


    bool moved = false;
    for (int i = 0; i<end(board)-begin(board); i++) {
        for (int j = 0; j<end(board[i])-begin(board[i]); j++) {
            if (original_board[i][j] == std::to_string(pos)) {
                if (board[i][j] == "X" || board[i][j] == "O") {
                    computer_move();
                    moved = true;
                    break;
                }
                else {
                    board[i][j] = "O";
                    moved = true;
                    break;
                }
            }
        }
    }

    if (!moved) {
        computer_move();
    }
}

int check_win() {
    system("cls");
    // check for 3 in a row with any square size
    bool row = false;
    bool column = false;
    bool diagonal = false;
    bool diagonal2 = false;

    bool temp = false;

    int rows = *(&board + 1) - board;
    int columns = *(&board[0] + 1) - board[0];

    // check for 3 in a row
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<columns; j++) {
            if (board[i][j] == "X") {
                temp = true;
            } else {
                temp = false;
                break;
            }
        }
        if (temp) {
            row = true;
            break;
        }
    }

    // check for 3 in a column
    for (int i = 0; i<columns; i++) {
        for (int j = 0; j<rows; j++) {
            if (board[j][i] == "X") {
                temp = true;
            } else {
                temp = false;
                break;
            }
        }
        if (temp) {
            column = true;
            break;
        }
    }

    // check for 3 in a diagonal
    for (int i = 0; i<rows; i++) {
        if (board[i][i] == "X") {
            temp = true;
        } else {
            temp = false;
            break;
        }
    }

    if (temp) {
        diagonal = true;
    }

    // check for 3 in a diagonal
    for (int i = 0; i<rows; i++) {
        if (board[i][rows - i - 1] == "X") {
            temp = true;
        } else {
            temp = false;
            break;
        }
    }

    if (temp) {
        diagonal2 = true;
    }

    if (row || column || diagonal || diagonal2) {
        system("cls");
        std::cout << "Player <X>  -  Computer <O>" << std::endl;
        std::cout << std::endl;
        print_board();
        std::cout << std::endl;
        std::cout << "Player <X> wins!" << std::endl;
        return PLAYER_WIN;
    }

    temp = false;
    row = false;
    column = false;
    diagonal = false;
    diagonal2 = false;

    // check for 3 in a row
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<columns; j++) {
            if (board[i][j] == "O") {
                temp = true;
            } else {
                temp = false;
                break;
            }
        }
        if (temp) {
            row = true;
            break;
        }
    }

    // check for 3 in a column
    for (int i = 0; i<columns; i++) {
        for (int j = 0; j<rows; j++) {
            if (board[j][i] == "O") {
                temp = true;
            } else {
                temp = false;
                break;
            }
        }
        if (temp) {
            column = true;
            break;
        }
    }

    // check for 3 in a diagonal
    for (int i = 0; i<rows; i++) {
        if (board[i][i] == "O") {
            temp = true;
        } else {
            temp = false;
            break;
        }
    }

    if (temp) {
        diagonal = true;
    }

    // check for 3 in a diagonal
    for (int i = 0; i<rows; i++) {
        if (board[i][rows - i - 1] == "O") {
            temp = true;
        } else {
            temp = false;
            break;
        }
    }

    if (temp) {
        diagonal2 = true;
    }

    if (row || column || diagonal || diagonal2) {
        system("cls");
        std::cout << "Player <X>  -  Computer <O>" << std::endl;
        std::cout << std::endl;
        print_board();
        std::cout << std::endl;
        std::cout << "Computer <O> wins!" << std::endl;
        return COMPUTER_WIN;
    }
    return NO_WIN;
}

bool check_draw() {
    bool all_taken = true;
    for (int i = 0; i<end(board)-begin(board); i++) {
        for (int j = 0; j<end(board[i])-begin(board[i]); j++) {
            if (board[i][j] != "X" || board[i][j] != "O") {
                all_taken = false;
            }
        }
    }
    if (all_taken) {
        return true;
    }

    return false;
}

void main_loop(bool player) {

    while (true) {
        system("cls");
        std::cout << "Player <X>  -  Computer <O>" << std::endl;
        std::cout << std::endl;

        print_board();
        if (player) {
            user_input(false);
            if (check_draw()) {
                break;
            }
            computer_move();
        } else {
            if (check_draw()) {
                break;
            }
            computer_move();
            system("cls");
            std::cout << "Player <X>  -  Computer <O>" << std::endl;
            std::cout << std::endl;
            print_board();
            if (check_draw()) {
                break;
            }
            user_input(false);
        }



        if (check_win() != NO_WIN) {
            break;
        }
        if (check_draw()) {
            system("cls");
            print_board();
            std::cout << "Draw!" << std::endl;
            break;
        }

    }

}

int main(int argc, char *argv[]) {





    current_pos = 0;

    //board = "Player 1 <X>  -  Player 2 <O>\n   |   |   \n %d | %d | %d \n __|___|__\n   |   |   \n %d | %d | %d \n __|___|__\n   |   |   \n %d | %d | %d \n";

    srand(time(nullptr));

    bool player_first = false;


    for (int i = 0; i<end(board)-begin(board); i++) {
        for (int j = 0; j<end(board[i])-begin(board[i]); j++) {
            board[i][j] = std::to_string(current_pos);
            original_board[i][j] = std::to_string(current_pos);
            current_pos += 1;
        }
    }


    int num;
    num = rand() % 10 + 1;

    if (num > 5) {
        player_first = true;
    }

    main_loop(player_first);


    return 0;
}
