#include <iostream>
#include <thread>
#include <utility>
#include <vector>

using namespace std;

// << To Do >>
// Give user option to selectively place pieces onto board.
// Give an option to exit game
// Skill trees and levelling up
// Add more options to menu
// Give user option to randomly place pieces onto board
// Promote Marzaz Pani to Kashshaptu when it reaches home rank
// Add new piece that behaves like knight in chess
// Allow Sarrum and Gisgigir to castle (as with king and rook in chess)
// Track number of moves
// Allow the player to save the game
// Add a new piece to the game: Kashshaptu
// Add a variable to display the number of pieces each player has
// Add taken pieces Counter
// Print if moving piece does not belong to current player
// Remove the restriction of one tile on the Nabu
// Add a way to forfeit the game
// Change the size of the board
// Add a point scoring system
// Allow the Redum to perform an 'en passant' move
// Allow the user to undo a move
// Change Colour of pieces
// Change the Etlu to behave like a knight in chess
// Choose what piece the redum is promoted to when it reaches the end of the board
// Promote Redum to Kashshaptu when it reaches home rank
// create graphical effect of display. as well as showing switching orientation for who's turn it is (current always at the bottom with ^^^^^ to show direction

// Signatures
void output_menu_error ();
void initialise_game ();
char choose_player ();
void display_board ();
void display_turn (char player);
void get_legal_moves ();
string request_move (char player);
void execute_move (string got_legal_move);

// Globals
const int board_dimensions {8};
vector<vector<string>> board(board_dimensions, vector<string>(board_dimensions));
vector<string> move_history;
vector<string> black_legal_moves {};
vector<string> white_legal_moves {};
int turn_number = 1;
bool is_player_turn = true;
bool game_over = false;



void output_menu_error () {
    cout << "You suck at typing";
    this_thread::sleep_until(chrono::system_clock::now() + chrono::seconds(1));
    cout <<".";
    this_thread::sleep_until(chrono::system_clock::now() + chrono::seconds(1));
    cout <<".";
    this_thread::sleep_until(chrono::system_clock::now() + chrono::seconds(1));
    cout <<".";
    this_thread::sleep_until(chrono::system_clock::now() + chrono::seconds(1));
}

void initialise_game () {
    //set variables
    game_over = false;

    // format white space
    for (int i = 0; i < board_dimensions; i++) {
        for (int j = 0; j < board_dimensions; j++) {
            board[i][j] = "0";
        }
    }

    // set black pieces
    board[0][0] = "BG"; // Gisgigir [G] (Chariot)
    board[0][1] = "BE"; // Etlu [E] (Warrior)
    board[0][2] = "BN"; // Nabu [N] (Seer)
    board[0][3] = "BM"; // Marzaz Pani [M] (Royal Attendant)
    board[0][4] = "BS"; // Sarrum [S] (King)
    board[0][5] = "BN";
    board[0][6] = "BE";
    board[0][7] = "BG";
    for (int i = 0; i < board_dimensions; ++i)
        board[1][i] = "BR"; // Redum [R] (Soldier)

    //set white pieces
    board[7][0] = "WG"; // Gisgigir [G] (Chariot)
    board[7][1] = "WE"; // Etlu [E] (Warrior)
    board[7][2] = "WN"; // Nabu [N] (Seer)
    board[7][3] = "WM"; // Marzaz Pani [M] (Royal Attendant)
    board[7][4] = "WS"; // Sarrum [S] (King)
    board[7][5] = "WN";
    board[7][6] = "WE";
    board[7][7] = "WG";
    for (int i = 0; i < board_dimensions; ++i)
        board[6][i] = "WR"; // Redum [R] (Soldier)
}

void display_board () {
    for (int i = 0; i < board.size(); i++) {
        cout << "\n     _________________________";
        cout << "\n " << i + 1 << "   ";
        for (int j = 0; j < board[i].size(); j++) {
            if (board.at(i).at(j) == "0") {
                cout << "|  ";
            } else {
                cout << "|" << board[i][j];
            }
        }
        cout << "|";
    }
    cout << "\n     _________________________";
    cout << "\n\n      1  2  3  4  5  6  7  8";

    // The Board
    //
    // Rank
    // V   _________________________
    // 1   |BG|BE|BN|BM|BS|BN|BE|BG|
    //     _________________________
    // 2   |BR|BR|BR|BR|BR|BR|BR|BR|
    //     _________________________
    // 3   |  |  |  |  |  |  |  |  |
    //     _________________________
    // 4   |  |  |  |  |  |  |  |  |
    //     _________________________
    // 5   |  |  |  |  |  |  |  |  |
    //     _________________________
    // 6   |  |  |  |  |  |  |  |  |
    //     _________________________
    // 7   |WR|WR|WR|WR|WR|WR|WR|WR|
    //     _________________________
    // 8   |WG|WE|WN|WM|WS|WN|WE|WG|
    //     _________________________
    //
    //      1  2  3  4  5  6  7  8 <File
}

char choose_player () {
    char input {0};

    cout << "\nChoose Colour:";
    cout << "\nB: Black";
    cout << "\nW: White";
    cout << "\nR: Random";
    cout << "\n>>>>>:";
    cin >> input;

    switch (input) {
        case 'b':
        case 'B':
            return 'B';
            break;
        case 'w':
        case 'W':
            return 'W';
            break;
        case 'r':
        case 'R': {
            srand(time(nullptr));
            int randnum = rand() % 2;
            if (randnum == 0)
                return 'B';
            return 'W';
        }   break;
        default:
            output_menu_error();
            break;
    }
    return 'B';
}

void display_turn (char player1) {
    cout << "\n\nTurn #" << turn_number;
    if (turn_number % 2 == 1 && player1 == 'B') {
        is_player_turn = true;
        cout << " Player [B]";
    }

    if (turn_number % 2 == 1 && player1 == 'W') {
        is_player_turn = true;
        cout << " Player [W]";
    }
    if (turn_number % 2 == 0 && player1 == 'B') {
        is_player_turn = false;
        cout << " Computer [W]";
    }
    if (turn_number % 2 == 0 && player1 == 'W') {
        is_player_turn = false;
        cout << " Computer [B]";
    }
}

void get_legal_moves () {
    vector<string> black_piece_positions {};
    vector<string> white_piece_positions {};
    black_piece_positions.clear();
    white_piece_positions.clear();

    // format   >> [from_rank][from_file][piece][to_rank][to_file][enemy_piece] (if no enemy piece then use 00)
    //     e.g. >> [33BR42WR] >> Black Rook taking White Rook
    //     e.g. >> [10BR1300] >> Black Rook moving 2 spaces from first rank
    black_legal_moves.clear();
    white_legal_moves.clear();

    // do this with a .find() ??
    // Store all piece data
    for (int from_rank = 0; from_rank < board.size(); from_rank++) {
        for (int from_file = 0; from_file < board[from_rank].size(); from_file++) {
            // look through every board position for pieces
            // cout << "Pieces: \n";
            if (board[from_rank][from_file][0] == 'B') {
                // save black pieces in format [rank][file][piece] to black_piece_positions vector
                string concat = (to_string(from_rank) + to_string(from_file) + board[from_rank][from_file]);
                // cout << concat << endl;
                black_piece_positions.push_back(concat);
            } else if (board[from_rank][from_file][0] == 'W') {
                // save white pieces in format [rank][file][piece] to white_piece_positions vector
                string concat = (to_string(from_rank) + to_string(from_file) + board[from_rank][from_file]);
                // cout << concat << endl;
                white_piece_positions.push_back(concat);
            }
        }
    }

    int from_rank {};
    int from_file {};

    // Get all legal black moves
    for (auto & piece_position : black_piece_positions) {
        // look through all black_piece_positions
        // piece_position [01BE][02BN]...
        switch (piece_position[3]) {
            case'R': {
                // Redum [R] (Soldier)
                // - Can move forward one square at a time, if the square directly in front is empty.
                // - If a diagonal square contains an opponent's piece, the Redum can move into that square and will capture the piece.
                // - If it reaches the back rank, it is promoted into a Marzaz Pani.

                // <<find available moves>>
                // if starting rank >> +2 and  !friendly_fire
                // else >> +1 and check for unoccupied space && out of bounds
                //      >> +1 +1/-1 and check for enemy piece && out of bounds
                //      - Check if promotion available.
                //      - Add En-pas
                //      - Add score weights for each move
                //          - +Promote
                //          - +Take
                //          - +Sprint
                //          - +Guard

                const int starting_rank {1};

                from_rank = piece_position.at(0) - 48;
                from_file = piece_position.at(1) - 48;

                string piece {};
                piece.push_back(piece_position.at(2));
                piece.push_back(piece_position.at(3));

                cout << "\nPiecePos: " << piece_position;
                cout << "\nMoves: ";

                // check bounds
                if ((0 <= from_rank + 1 && from_rank + 1 < board_dimensions) && (0 <= from_file - 1 && from_file - 1 < board_dimensions)) {
                    //check west take [ - ]
                    if (board[from_rank + 1][from_file - 1] == "W") {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file - 1) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank + 1 && from_rank + 1 < board_dimensions) && (0 <= from_file + 1 && from_file + 1 < board_dimensions)) {
                    //check east take [ + ]
                    if (board[from_rank + 1][from_file + 1] == "W") {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file + 1) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank + 2 && from_rank + 2 < board_dimensions) && (0 <= from_file && from_file < board_dimensions)) {
                    //check first double advance
                    if (from_rank == starting_rank && board[from_rank + 2][from_file] == "0") {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 2) + to_string(from_file) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank + 1 && from_rank + 1 < board_dimensions) && (0 <= from_file && from_file < board_dimensions)) {
                    //check advance
                    if (board[from_rank + 1][from_file] == "0") {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }
            }   break;

            case 'G': {
                // Gisgigir [G] (Chariot)
                //  - Can move any number of squares, at a time, in either a vertical or horizontal direction.
                //  - Cannot jump over pieces.

                from_rank = piece_position.at(0) - 48;
                from_file = piece_position.at(1) - 48;

                string piece {};
                piece.push_back(piece_position.at(2));
                piece.push_back(piece_position.at(3));
                bool obstructed = false;

                cout << "\nPiecePos: " << piece_position;
                cout << "\nMoves: ";

                // check north ( - rank , same file )
                int i = from_rank;
                do {
                    // check bounds
                    if (0 <= i && i < board_dimensions) {
                        // check for empty space
                        if (board[i][from_file].at(0) == '0') {
                            string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(i) + to_string(from_file) + "00";
                            cout << move_data << " ";
                            black_legal_moves.push_back(move_data);
                        }
                        // check for enemy piece
                        else if (board[i][from_file].at(0) == 'W') {
                            string enemy_piece {};
                            enemy_piece.push_back(piece_position.at(2));
                            enemy_piece.push_back(piece_position.at(3));
                            string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(i) + to_string(from_file) + enemy_piece;
                            cout << move_data << " ";
                            black_legal_moves.push_back(move_data);
                            obstructed = true;
                        }
                        // check for friendly piece
                        else if (board[i][from_file].at(0) == 'B') {
                            obstructed = true;
                        }
                    } else obstructed = true;
                    i--;
                } while (!obstructed);

                // check south ( + rank , same file )
                i = from_rank;
                obstructed = false;
                do {
                    // check bounds
                    if (0 <= i && i < board_dimensions) {
                        // check for empty space
                        if (board[i][from_file].at(0) == '0') {
                            string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(i) + to_string(from_file) + "00";
                            cout << move_data << " ";
                            black_legal_moves.push_back(move_data);
                        }
                        // check for enemy piece
                        else if (board[i][from_file].at(0) == 'W') {
                            string enemy_piece {};
                            enemy_piece.push_back(piece_position.at(2));
                            enemy_piece.push_back(piece_position.at(3));
                            string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(i) + to_string(from_file) + enemy_piece;
                            cout << move_data << " ";
                            black_legal_moves.push_back(move_data);
                            obstructed = true;
                        }
                        // check for friendly piece
                        else if (board[i][from_file].at(0) == 'B') {
                            obstructed = true;
                        }
                    }
                    i++;
                } while (!obstructed);

                // check east ( same rank , + file )
                i = from_file;
                obstructed = false;
                do {
                    // check bounds
                    if (0 <= i && i < board_dimensions) {
                        // check for empty space
                        if (board[from_rank][i].at(0) == '0') {
                            string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(i) + to_string(from_file) + to_string(i) + "00";
                            cout << move_data << " ";
                            black_legal_moves.push_back(move_data);
                        }
                        // check for enemy piece
                        else if (board[from_rank][i].at(0) == 'W') {
                            string enemy_piece {};
                            enemy_piece.push_back(piece_position.at(2));
                            enemy_piece.push_back(piece_position.at(3));
                            string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(i) + enemy_piece;
                            cout << move_data << " ";
                            black_legal_moves.push_back(move_data);
                            obstructed = true;
                        }
                        // check for friendly piece
                        else if (board[from_rank][i].at(0) == 'B') {
                            obstructed = true;
                        }
                    }
                    i++;
                } while (!obstructed);

                // check west ( same rank , - file )
                i = from_file;
                obstructed = false;
                do {
                    // check bounds
                    if (0 <= i && i < board_dimensions) {
                        // check for empty space
                        if (board[from_rank][i].at(0) == '0') {
                            string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(i) + to_string(from_file) + to_string(i) + "00";
                            cout << move_data << " ";
                            black_legal_moves.push_back(move_data);
                        }
                        // check for enemy piece
                        else if (board[from_rank][i].at(0) == 'W') {
                            string enemy_piece {};
                            enemy_piece.push_back(piece_position.at(2));
                            enemy_piece.push_back(piece_position.at(3));
                            string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(i) + enemy_piece;
                            cout << move_data << " ";
                            black_legal_moves.push_back(move_data);
                            obstructed = true;
                        }
                        // check for friendly piece
                        else if (board[from_rank][i].at(0) == 'B') {
                            obstructed = true;
                        }
                    }
                    i--;
                } while (!obstructed);
            }   break;

            case 'E': {
                // Etlu [E] (Warrior)  - Can move exactly two squares at a time in either a vertical or horizontal direction. Can jump over other pieces.

                from_rank = piece_position.at(0) - 48;
                from_file = piece_position.at(1) - 48;

                string piece {};
                piece.push_back(piece_position.at(2));
                piece.push_back(piece_position.at(3));

                cout << "\nPiecePos: " << piece_position;
                cout << "\nMoves: ";

                // check bounds
                if ((0 <= from_rank - 2 && from_rank - 2 < board_dimensions) && (0 <= from_file && from_file < board_dimensions)) {
                    // check north
                    if (board[from_rank - 2][from_file].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 2) + to_string(from_file) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank - 2][from_file].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 2) + to_string(from_file) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank + 2 && from_rank + 2 < board_dimensions) && (0 <= from_file && from_file < board_dimensions)) {
                    // check south
                    if (board[from_rank + 2][from_file].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 2) + to_string(from_file) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank + 2][from_file].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 2) + to_string(from_file) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank && from_rank < board_dimensions) && (0 <= from_file + 2 && from_file + 2 < board_dimensions)) {
                    // check east
                    if (board[from_rank][from_file + 2].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file + 2) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank][from_file + 2].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file + 2) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank && from_rank < board_dimensions) && (0 <= from_file - 2 && from_file - 2 < board_dimensions)) {
                    // check west
                    if (board[from_rank][from_file - 2].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file - 2) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank][from_file - 2].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file - 2) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }
            }   break;
            case 'N': {
                // Nabu [N] (Seer)  - Can move one square at a time along a diagonal.

                from_rank = piece_position.at(0) - 48;
                from_file = piece_position.at(1) - 48;

                string piece {};
                piece.push_back(piece_position.at(2));
                piece.push_back(piece_position.at(3));

                cout << "\nPiecePos: " << piece_position;
                cout << "\nMoves: ";

                // check bounds
                if ((0 <= from_rank - 1 && from_rank - 1 < board_dimensions) && (0 <= from_file + 1 && from_file + 1 < board_dimensions)) {
                    // check NE
                    if (board[from_rank - 1][from_file + 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file + 1) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank - 1][from_file + 1].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file + 1) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }


                // check bounds
                if ((0 <= from_rank + 1 && from_rank + 1 < board_dimensions) && (0 <= from_file + 1 && from_file + 1 < board_dimensions)) {
                    // check SE
                    if (board[from_rank + 1][from_file + 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file + 1) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank + 1][from_file + 1].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file + 1) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank + 1 && from_rank + 1 < board_dimensions) && (0 <= from_file - 1 && from_file - 1 < board_dimensions)) {
                    // check SW
                    if (board[from_rank + 1][from_file - 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file - 1) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank + 1][from_file - 1].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file - 1) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank - 1 && from_rank - 1 < board_dimensions) && (0 <= from_file - 1 && from_file - 1 < board_dimensions)) {
                    // check NW
                    if (board[from_rank - 1][from_file - 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file - 1) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank - 1][from_file - 1].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file - 1) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }
            }   break;

            case 'M': {
                // Marzaz Pani [M] (Royal Attendant)  -  Can move one square at a time either vertically or horizontally.

                from_rank = piece_position.at(0) - 48;
                from_file = piece_position.at(1) - 48;

                string piece {};
                piece.push_back(piece_position.at(2));
                piece.push_back(piece_position.at(3));

                cout << "\nPiecePos: " << piece_position;
                cout << "\nMoves: ";


                // check bounds
                if ((0 <= from_rank - 1 && from_rank - 1 < board_dimensions) && (0 <= from_file && from_file < board_dimensions)) {
                    // check north
                    if (board[from_rank - 1][from_file].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank - 1][from_file].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank + 1 && from_rank + 1 < board_dimensions) && (0 <= from_file && from_file < board_dimensions)) {
                    // check south
                    if (board[from_rank + 1][from_file].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file) + "00";
                        // cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank + 1][from_file].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file) + enemy_piece;
                        // cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank && from_rank < board_dimensions) && (0 <= from_file + 1 && from_file + 1 < board_dimensions)) {
                    // check east
                    if (board[from_rank][from_file + 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file + 1) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank][from_file + 1].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file + 1) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank && from_rank < board_dimensions) && (0 <= from_file - 1 && from_file - 1 < board_dimensions)) {
                    // check west
                    if (board[from_rank][from_file - 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file - 1) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank][from_file - 1].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file - 1) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }
            }   break;

            case 'S': {
                // Sarrum [S] (King)  - Can move one square at a time in any direction.

                from_rank = piece_position.at(0) - 48;
                from_file = piece_position.at(1) - 48;

                string piece {};
                piece.push_back(piece_position.at(2));
                piece.push_back(piece_position.at(3));

                cout << "\nPiecePos: " << piece_position;
                cout << "\nMoves: ";

                // check bounds
                if ((0 <= from_rank - 1 && from_rank - 1 < board_dimensions) && (0 <= from_file && from_file < board_dimensions)) {
                    // check north
                    if (board[from_rank - 1][from_file].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank - 1][from_file].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank + 1 && from_rank + 1 < board_dimensions) && (0 <= from_file && from_file < board_dimensions)) {
                    // check south
                    if (board[from_rank + 1][from_file].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank + 1][from_file].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank && from_rank < board_dimensions) && (0 <= from_file + 1 && from_file + 1 < board_dimensions)) {
                    // check east
                    if (board[from_rank][from_file + 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file + 1) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank][from_file + 1].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file + 1) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank && from_rank < board_dimensions) && (0 <= from_file - 1 && from_file - 1 < board_dimensions)) {
                    // check west
                    if (board[from_rank][from_file - 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file - 1) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank][from_file - 1].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file - 1) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank - 1 && from_rank - 1 < board_dimensions) && (0 <= from_file + 1 && from_file + 1 < board_dimensions)) {
                    // check NE
                    if (board[from_rank - 1][from_file + 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file + 1) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank - 1][from_file + 1].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file + 1) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank + 1 && from_rank + 1 < board_dimensions) && (0 <= from_file + 1 && from_file + 1 < board_dimensions)) {
                    // check SE
                    if (board[from_rank + 1][from_file + 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file + 1) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank + 1][from_file + 1].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file + 1) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank + 1 && from_rank + 1 < board_dimensions) && (0 <= from_file - 1 && from_file - 1 < board_dimensions)) {
                    // check SW
                    if (board[from_rank + 1][from_file - 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file - 1) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank + 1][from_file - 1].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file - 1) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank - 1 && from_rank - 1 < board_dimensions) && (0 <= from_file - 1 && from_file - 1 < board_dimensions)) {
                    // check NW
                    if (board[from_rank - 1][from_file - 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file - 1) + "00";
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    } else if (board[from_rank - 1][from_file - 1].at(0) == 'W') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file - 1) + enemy_piece;
                        cout << move_data << " ";
                        black_legal_moves.push_back(move_data);
                    }
                }
            }   break;

//         case 'K': {
//             // Kashshaptu (Witch) K
//             // Not known how this piece was used in the game.
//             //
//             // It was revealed in the exam how this piece moved. Then it was up to the candidates to program in the Kashshaptu piece.
//         }    break;
        }
    }

    // get all legal white moves
    for (auto & piece_position : white_piece_positions) {
        // look through all white_piece_positions
        // piece_position [061WE][62WN]...
        switch (piece_position[3]) {
            case'R': {
                // Redum [R] (Soldier)
                // - Can move forward one square at a time, if the square directly in front is empty.
                // - If a diagonal square contains an opponent's piece, the Redum can move into that square and will capture the piece.
                // - If it reaches the back rank, it is promoted into a Marzaz Pani.

                // <<find available moves>>
                // if starting rank >> +2 and  !friendly_fire
                // else >> +1 and check for unoccupied space && out of bounds
                //      >> +1 +1/-1 and check for enemy piece && out of bounds
                //      - Check if promotion available.
                //      - Add En-pas
                //      - Add score weights for each move
                //          - +Promote
                //          - +Take
                //          - +Sprint
                //          - +Guard

                const int starting_rank {6};

                from_rank = piece_position.at(0) - 48;
                from_file = piece_position.at(1) - 48;

                string piece {};
                piece.push_back(piece_position.at(2));
                piece.push_back(piece_position.at(3));

                cout << "\nPiecePos: " << piece_position;
                cout << "\nMoves: ";

                // check bounds
                if ((0 <= from_rank - 1 && from_rank - 1 < board_dimensions) && (0 <= from_file - 1 && from_file - 1 < board_dimensions)) {
                    //check west take [ - ]
                    if (board[from_rank - 1][from_file - 1] == "B") {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file - 1) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank - 1 && from_rank - 1 < board_dimensions) && (0 <= from_file + 1 && from_file + 1 < board_dimensions)) {
                    //check east take [ + ]
                    if (board[from_rank - 1][from_file + 1] == "B") {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file + 1) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank - 2 && from_rank - 2 < board_dimensions) && (0 <= from_file && from_file < board_dimensions)) {
                    //check first double advance
                    if (from_rank == starting_rank && board[from_rank - 2][from_file] == "0") {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 2) + to_string(from_file) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank - 1 && from_rank - 1 < board_dimensions) && (0 <= from_file && from_file < board_dimensions)) {
                    //check advance
                    if (board[from_rank - 1][from_file] == "0") {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }
            }   break;

            case 'G': {
                // Gisgigir [G] (Chariot)
                //  - Can move any number of squares, at a time, in either a vertical or horizontal direction.
                //  - Cannot jump over pieces.

                from_rank = piece_position.at(0) - 48;
                from_file = piece_position.at(1) - 48;

                string piece {};
                piece.push_back(piece_position.at(2));
                piece.push_back(piece_position.at(3));
                bool obstructed = false;

                cout << "\nPiecePos: " << piece_position;
                cout << "\nMoves: ";

                // check north ( - rank , same file )
                int i = from_rank;
                do {
                    // check bounds
                    if (0 <= i && i < board_dimensions) {
                        // check for empty space
                        if (board[i][from_file].at(0) == '0') {
                            string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(i) + to_string(from_file) + "00";
                            cout << move_data << " ";
                            white_legal_moves.push_back(move_data);
                        }
                        // check for enemy piece
                        else if (board[i][from_file].at(0) == 'B') {
                            string enemy_piece {};
                            enemy_piece.push_back(piece_position.at(2));
                            enemy_piece.push_back(piece_position.at(3));
                            string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(i) + to_string(from_file) + enemy_piece;
                            cout << move_data << " ";
                            white_legal_moves.push_back(move_data);
                            obstructed = true;
                        }
                        // check for friendly piece
                        else if (board[i][from_file].at(0) == 'W') {
                            obstructed = true;
                        }
                    } else obstructed = true;
                    i--;
                } while (!obstructed);

                // check south ( + rank , same file )
                i = from_rank;
                obstructed = false;
                do {
                    // check bounds
                    if (0 <= i && i < board_dimensions) {
                        // check for empty space
                        if (board[i][from_file].at(0) == '0') {
                            string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(i) + to_string(from_file) + "00";
                            cout << move_data << " ";
                            white_legal_moves.push_back(move_data);
                        }
                        // check for enemy piece
                        else if (board[i][from_file].at(0) == 'B') {
                            string enemy_piece {};
                            enemy_piece.push_back(piece_position.at(2));
                            enemy_piece.push_back(piece_position.at(3));
                            string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(i) + to_string(from_file) + enemy_piece;
                            cout << move_data << " ";
                            white_legal_moves.push_back(move_data);
                            obstructed = true;
                        }
                        // check for friendly piece
                        else if (board[i][from_file].at(0) == 'W') {
                            obstructed = true;
                        }
                    }
                    i++;
                } while (!obstructed);

                // check east ( same rank , + file )
                i = from_file;
                obstructed = false;
                do {
                    // check bounds
                    if (0 <= i && i < board_dimensions) {
                        // check for empty space
                        if (board[from_rank][i].at(0) == '0') {
                            string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(i) + to_string(from_file) + to_string(i) + "00";
                            cout << move_data << " ";
                            white_legal_moves.push_back(move_data);
                        }
                        // check for enemy piece
                        else if (board[from_rank][i].at(0) == 'B') {
                            string enemy_piece {};
                            enemy_piece.push_back(piece_position.at(2));
                            enemy_piece.push_back(piece_position.at(3));
                            string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(i) + enemy_piece;
                            cout << move_data << " ";
                            white_legal_moves.push_back(move_data);
                            obstructed = true;
                        }
                        // check for friendly piece
                        else if (board[from_rank][i].at(0) == 'W') {
                            obstructed = true;
                        }
                    }
                    i++;
                } while (!obstructed);

                // check west ( same rank , - file )
                i = from_file;
                obstructed = false;
                do {
                    // check bounds
                    if (0 <= i && i < board_dimensions) {
                        // check for empty space
                        if (board[from_rank][i].at(0) == '0') {
                            string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(i) + to_string(from_file) + to_string(i) + "00";
                            cout << move_data << " ";
                            white_legal_moves.push_back(move_data);
                        }
                        // check for enemy piece
                        else if (board[from_rank][i].at(0) == 'B') {
                            string enemy_piece {};
                            enemy_piece.push_back(piece_position.at(2));
                            enemy_piece.push_back(piece_position.at(3));
                            string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(i) + enemy_piece;
                            cout << move_data << " ";
                            white_legal_moves.push_back(move_data);
                            obstructed = true;
                        }
                        // check for friendly piece
                        else if (board[from_rank][i].at(0) == 'W') {
                            obstructed = true;
                        }
                    }
                    i--;
                } while (!obstructed);
            }   break;

            case 'E': {
                // Etlu [E] (Warrior)  - Can move exactly two squares at a time in either a vertical or horizontal direction. Can jump over other pieces.

                from_rank = piece_position.at(0) - 48;
                from_file = piece_position.at(1) - 48;

                string piece {};
                piece.push_back(piece_position.at(2));
                piece.push_back(piece_position.at(3));

                cout << "\nPiecePos: " << piece_position;
                cout << "\nMoves: ";

                // check bounds
                if ((0 <= from_rank - 2 && from_rank - 2 < board_dimensions) && (0 <= from_file && from_file < board_dimensions)) {
                    // check north
                    if (board[from_rank - 2][from_file].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 2) + to_string(from_file) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank - 2][from_file].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 2) + to_string(from_file) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank + 2 && from_rank + 2 < board_dimensions) && (0 <= from_file && from_file < board_dimensions)) {
                    // check south
                    if (board[from_rank + 2][from_file].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 2) + to_string(from_file) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank + 2][from_file].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 2) + to_string(from_file) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank && from_rank < board_dimensions) && (0 <= from_file + 2 && from_file + 2 < board_dimensions)) {
                    // check east
                    if (board[from_rank][from_file + 2].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file + 2) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank][from_file + 2].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file + 2) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank && from_rank < board_dimensions) && (0 <= from_file - 2 && from_file - 2 < board_dimensions)) {
                    // check west
                    if (board[from_rank][from_file - 2].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file - 2) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank][from_file - 2].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file - 2) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }
            }   break;
            case 'N': {
                // Nabu [N] (Seer)  - Can move one square at a time along a diagonal.

                from_rank = piece_position.at(0) - 48;
                from_file = piece_position.at(1) - 48;

                string piece {};
                piece.push_back(piece_position.at(2));
                piece.push_back(piece_position.at(3));

                cout << "\nPiecePos: " << piece_position;
                cout << "\nMoves: ";

                // check bounds
                if ((0 <= from_rank - 1 && from_rank - 1 < board_dimensions) && (0 <= from_file + 1 && from_file + 1 < board_dimensions)) {
                    // check NE
                    if (board[from_rank - 1][from_file + 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file + 1) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank - 1][from_file + 1].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file + 1) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }


                // check bounds
                if ((0 <= from_rank + 1 && from_rank + 1 < board_dimensions) && (0 <= from_file + 1 && from_file + 1 < board_dimensions)) {
                    // check SE
                    if (board[from_rank + 1][from_file + 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file + 1) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank + 1][from_file + 1].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file + 1) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank + 1 && from_rank + 1 < board_dimensions) && (0 <= from_file - 1 && from_file - 1 < board_dimensions)) {
                    // check SW
                    if (board[from_rank + 1][from_file - 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file - 1) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank + 1][from_file - 1].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file - 1) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank - 1 && from_rank - 1 < board_dimensions) && (0 <= from_file - 1 && from_file - 1 < board_dimensions)) {
                    // check NW
                    if (board[from_rank - 1][from_file - 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file - 1) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank - 1][from_file - 1].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file - 1) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }
            }   break;

            case 'M': {
                // Marzaz Pani [M] (Royal Attendant)  -  Can move one square at a time either vertically or horizontally.

                from_rank = piece_position.at(0) - 48;
                from_file = piece_position.at(1) - 48;

                string piece {};
                piece.push_back(piece_position.at(2));
                piece.push_back(piece_position.at(3));

                cout << "\nPiecePos: " << piece_position;
                cout << "\nMoves: ";


                // check bounds
                if ((0 <= from_rank - 1 && from_rank - 1 < board_dimensions) && (0 <= from_file && from_file < board_dimensions)) {
                    // check north
                    if (board[from_rank - 1][from_file].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank - 1][from_file].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank + 1 && from_rank + 1 < board_dimensions) && (0 <= from_file && from_file < board_dimensions)) {
                    // check south
                    if (board[from_rank + 1][from_file].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank + 1][from_file].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank && from_rank < board_dimensions) && (0 <= from_file + 1 && from_file + 1 < board_dimensions)) {
                    // check east
                    if (board[from_rank][from_file + 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file + 1) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank][from_file + 1].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file + 1) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank && from_rank < board_dimensions) && (0 <= from_file - 1 && from_file - 1 < board_dimensions)) {
                    // check west
                    if (board[from_rank][from_file - 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file - 1) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank][from_file - 1].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file - 1) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }
            }   break;

            case 'S': {
                // Sarrum [S] (King)  - Can move one square at a time in any direction.

                from_rank = piece_position.at(0) - 48;
                from_file = piece_position.at(1) - 48;

                string piece {};
                piece.push_back(piece_position.at(2));
                piece.push_back(piece_position.at(3));

                cout << "\nPiecePos: " << piece_position;
                cout << "\nMoves: ";

                // check bounds
                if ((0 <= from_rank - 1 && from_rank - 1 < board_dimensions) && (0 <= from_file && from_file < board_dimensions)) {
                    // check north
                    if (board[from_rank - 1][from_file].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank - 1][from_file].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank + 1 && from_rank + 1 < board_dimensions) && (0 <= from_file && from_file < board_dimensions)) {
                    // check south
                    if (board[from_rank + 1][from_file].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank + 1][from_file].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank && from_rank < board_dimensions) && (0 <= from_file + 1 && from_file + 1 < board_dimensions)) {
                    // check east
                    if (board[from_rank][from_file + 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file + 1) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank][from_file + 1].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file + 1) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank && from_rank < board_dimensions) && (0 <= from_file - 1 && from_file - 1 < board_dimensions)) {
                    // check west
                    if (board[from_rank][from_file - 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file - 1) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank][from_file - 1].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank) + to_string(from_file - 1) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank - 1 && from_rank - 1 < board_dimensions) && (0 <= from_file + 1 && from_file + 1 < board_dimensions)) {
                    // check NE
                    if (board[from_rank - 1][from_file + 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file + 1) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank - 1][from_file + 1].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file + 1) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank + 1 && from_rank + 1 < board_dimensions) && (0 <= from_file + 1 && from_file + 1 < board_dimensions)) {
                    // check SE
                    if (board[from_rank + 1][from_file + 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file + 1) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank + 1][from_file + 1].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file + 1) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank + 1 && from_rank + 1 < board_dimensions) && (0 <= from_file - 1 && from_file - 1 < board_dimensions)) {
                    // check SW
                    if (board[from_rank + 1][from_file - 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file - 1) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank + 1][from_file - 1].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file - 1) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }

                // check bounds
                if ((0 <= from_rank - 1 && from_rank - 1 < board_dimensions) && (0 <= from_file - 1 && from_file - 1 < board_dimensions)) {
                    // check NW
                    if (board[from_rank - 1][from_file - 1].at(0) == '0') {
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file - 1) + "00";
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    } else if (board[from_rank - 1][from_file - 1].at(0) == 'B') {
                        string enemy_piece {};
                        enemy_piece.push_back(piece_position.at(2));
                        enemy_piece.push_back(piece_position.at(3));
                        string move_data = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank - 1) + to_string(from_file - 1) + enemy_piece;
                        cout << move_data << " ";
                        white_legal_moves.push_back(move_data);
                    }
                }
            }   break;

//         case 'K': {
//             // Kashshaptu (Witch) K
//             // Not known how this piece was used in the game.
//             //
//             // It was revealed in the exam how this piece moved. Then it was up to the candidates to program in the Kashshaptu piece.
//         }    break;
        }
    }

    // <<<<=== Check for check ===>>>>
    // From legal moves
    // - find all moves that target enemy Sarrum
    // - if true, !!!must prevent check!!!(how?)
    // - look at all legal moves, find all moves from all legal moves, check for check
    // - what about moves that put yourself in check??????????(how?)

    bool white_in_check = false;
    for (auto move_data : black_legal_moves) {
        if (move_data.at(5) == 'S') {
            white_in_check = true;
        }
    }
    bool black_in_check = false;
    for (auto move_data : white_legal_moves) {
        if (move_data.at(5) == 'S') {
            black_in_check = true;
        }
    }
}

string request_move (const char player) {
    string move_from {};
    string move_to {};

    bool checked = false;
    int from_rank {};
    int from_file {};
    int to_rank {};
    int to_file {};
    string selected_piece {};
    char owner {};
    char piece {};
    string move_data {};

    if (is_player_turn) {
        //repeat input check for move_from coords
        do {
            cout << "\nMove From [Rank][Row]>>> : ";
            cin >> move_from;

            from_rank = move_from.at(0) - '1';
            from_file = move_from.at(1) - '1';

            // cout << move_from << endl;
            // cout << from_rank << endl;
            // cout << from_file << endl;

            bool within_bounds = false;
            if (from_rank >= 0 && from_file <= board_dimensions - 1) {
                within_bounds = true;

                selected_piece = board[from_rank][from_file];
                owner = selected_piece.at(0);
                piece = selected_piece.at(1);

                // cout << selected_piece << endl;
                // cout << owner << endl;
                // cout << piece << endl;

                bool is_player_piece = false;
                if (owner == player)
                    is_player_piece = true;
                else
                    cout << "Invalid: Enemy Piece";
                if (within_bounds && is_player_piece)
                    checked = true;
            }   else cout << "Invalid: Out of Bounds";
        } while (!checked);

        //repeat input check for move_to coords
        do {
            cout << "Move To [Rank][Row]>>> : ";
            cin >> move_to;

            to_rank = move_to.at(0) - '1';
            to_file = move_to.at(1) - '1';

            // cout << move_to << endl;
            // cout << to_rank << endl;
            // cout << to_file << endl;

            bool within_bounds = false;
            if (to_rank >= 0 && to_file <= board_dimensions - 1) {
                within_bounds = true;

                // cout << selected_piece << endl;
                // cout << owner << endl;
                // cout << piece << endl;

                if (within_bounds)
                    checked = true;
            }   else cout << "Invalid: Out of Bounds";
        } while (!checked);
        move_data.push_back(from_rank + 48);
        move_data.push_back(from_file + 48);
        move_data.push_back(to_rank + 48);
        move_data.push_back(to_file + 48);
    } else if (!is_player_turn && player == 'B') {
        cout << "\nBSize:" + white_legal_moves.size();
        srand(time(nullptr));
        int picker = rand() % white_legal_moves.size() - 1;
        move_data = white_legal_moves[picker];
    } else if (!is_player_turn && player == 'W') {
        cout << "\nWSize:" + black_legal_moves.size();
        srand(time(nullptr));
        int picker = rand() % black_legal_moves.size() - 1;
        move_data = black_legal_moves[picker];
    }
    return move_data;
}

void execute_move (string move_data) {
    // cout << move_data << endl;

    int move_from_rank {0};
    int move_from_file {0};
    int move_to_rank {0};
    int move_to_file {0};
    string piece {};

    move_from_rank = move_data.at(0) - 48;
    move_from_file = move_data.at(1) - 48;
    if (move_data.size() == 4) {
        move_to_rank = move_data.at(2) - 48;
        move_to_file = move_data.at(3) - 48;
    } else if (move_data.size() == 8) {
        move_to_rank = move_data.at(4) - 48;
        move_to_file = move_data.at(5) - 48;
    }

    piece = board.at(move_from_rank).at(move_from_file);
    // cout << piece << endl;
    board.at(move_from_rank).at(move_from_file) = '0';
    board.at(move_to_rank).at(move_to_file) = piece;
}

int main() {
    cout << "\n<<< ========== >>>";
    cout << "\n Capture the Sarum";
    cout << "\n     <<BgWg>>";
    cout << "\n<<< ========== >>>\n";
    cout << "\nWelcome and all that";

    char main_menu_input {};
    do {
        cout << "\n1: Play against computer";
        // cout << "\n2: Load game";
        // cout << "\n3: Sample game";
        // cout << "\n4: Settings";
        cout << "\nQ: Quit";
        cout << "\n>>>>> ";

        cin.clear();
        cin >> main_menu_input;

        switch (main_menu_input) {
            case '1': {
                initialise_game();
                char player1 = choose_player();
                display_board ();
                do {
                    get_legal_moves();
                    display_turn(player1);
                    string move_data = request_move(player1);
                    // cout << move_data << endl;
                    execute_move(move_data);
                    turn_number++;
                    system("cls");
                    display_board();
                }   while (game_over == false);
            }   break;

            // case '2':
            //     // load game
            //     break;
            // case '3':
            //     // sample game
            //     break;
            // case '4':
            //     // settings
            //     break;

            case 'q':
            case 'Q':
                cout << "Quitting";
                this_thread::sleep_until(chrono::system_clock::now() + chrono::seconds(1));
                cout <<".";
                this_thread::sleep_until(chrono::system_clock::now() + chrono::seconds(1));
                cout <<".";
                this_thread::sleep_until(chrono::system_clock::now() + chrono::seconds(1));
                cout <<".";
                this_thread::sleep_until(chrono::system_clock::now() + chrono::seconds(1));
                break;
            default:
                output_menu_error();
                break;
        }
    } while (main_menu_input != 'q' && main_menu_input != 'Q');

    return 0;
}