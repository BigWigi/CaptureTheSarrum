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
// Prevent pieces from moving backwards
// Add new piece that behaves like knight in chess
// Allow Sarrum and Gisgigir to castle (as with king and rook in chess)
// Track number of moves
// Allow the player to save the game
// Prevent program from crashing, when entering incorrect coordinates
// Add a new piece to the game: Kashshaptu
// Add a variable to display the number of pieces each player has
// Add taken pieces Counter
// Print if moving piece does not belong to current player
// Remove the restriction of one tile on the Nabu
// Add a way to forfeit the game
// Use GetTypeOfGame to ask the user what type of game they want to play
// Change the size of the board
// Add a point scoring system
// Allow the Redum to perform an 'en passant' move
// Only allow the user to enter one character when choosing the type of game
// Allow the user to undo a move
// Prevent the program from crashing when enter is pressed without any input
// Change Colour of pieces
// Change the Etlu to behave like a knight in chess
// Perhaps add demonstration game to demonstrate a move eg Castling
// Choose what piece the redum is promoted to when it reaches the end of the board
// Make program exit upon a wrong input entered
// Modify the program such that you can play against the computer
// Promote Redum to Kashshaptu when it reaches home rank
// create graphical effect of display. as well as showing switching orientation for who's turn it is (current always at the bottom with ^^^^^ to show direction

// Signatures
void output_menu_error ();
void initialise_game ();
char choose_player ();
void display_board ();
void display_turn (char player);
void get_legal_moves ();
void request_move ();
void update_board (int move_from_rank, int move_from_file, int move_to_rank, int move_to_file, string selected_piece);
bool friendly_fire (int move_to_rank, int move_to_file, char player);
void validate_move (string move_from, string move_to);
string fetch_legal_redum_moves(string piece_data, int move_to_rank, int move_to_file);
string fetch_legal_gisgigir_moves(string piece_data, int move_to_rank, int move_to_file);
string fetch_legal_etlu_moves(string piece_data, int move_to_rank, int move_to_file);
string fetch_legal_nabu_moves(string piece_data, int move_to_rank, int move_to_file);
string fetch_legal_marzaz_pani_moves(string piece_data, int move_to_rank, int move_to_file);
string fetch_legal_sarrum_moves(string piece_data, int move_to_rank, int move_to_file);
string fetch_legal_kashaptu_moves(string piece_data, int move_to_rank, int move_to_file);



// Globals
const int board_dimensions {8};
vector<vector<string>> board(board_dimensions, vector<string>(board_dimensions));
vector<string> move_history;
vector<string> all_legal_black_moves {};
vector<string> all_legal_white_moves {};
int turn_number = 1;
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
}

void display_turn (char player) {
    cout << "\n\nTurn #" << turn_number;
    if (turn_number % 2 == 1 && player == 'B')
        cout << " Player [B]";
    if (turn_number % 2 == 1 && player == 'W')
        cout << " Player [W]";
    if (turn_number % 2 == 0 && player == 'B')
        cout << " Computer [B]";
    if (turn_number % 2 == 0 && player == 'W')
        cout << " Computer [W]";
}

void get_legal_moves () {
    vector<string> black_piece_positions {};
    vector<string> white_piece_positions {};
    black_piece_positions.clear();
    white_piece_positions.clear();

    // format   >> [from_rank][from_file][piece][to_rank][to_file][enemy_piece] (if no enemy piece then use 00)
    //     e.g. >> [33BR42WR] >> Black Rook taking White Rook
    //     e.g. >> [10BR1300] >> Black Rook moving 2 spaces from first rank
    vector<string> black_legal_moves {};
    vector<string> white_legal_moves {};
    black_legal_moves.clear();
    white_legal_moves.clear();

    // do this with a .find() ??
    // Store all piece data
    for (int from_rank = 0; from_rank < board.size(); from_rank++) {
        for (int from_file = 0; from_file < board[from_rank].size(); from_file++) {
            // look through every board position for pieces
            if (board[from_rank][from_file][0] == 'B') {
                // save black pieces in format [rank][file][piece] to black_piece_positions vector
                string concat = (to_string(from_rank) + to_string(from_file) + board[from_rank][from_file]);
                black_piece_positions.push_back(concat);
            } else if (board[from_rank][from_file][0] == 'W') {
                // save white pieces in format [rank][file][piece] to white_piece_positions vector
                string concat = (to_string(from_rank) + to_string(from_file) + board[from_rank][from_file]);
                white_piece_positions.push_back(concat);
            }
        }
    }

    int from_rank {};
    int from_file {};

    for (auto & piece_position : black_piece_positions) {
        // look through all black_piece_positions
        cout << piece_position << endl;

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

                from_rank = piece_position.at(0);
                from_file = piece_position.at(1);
                string piece = to_string(piece_position.at(2)) + to_string(piece_position.at(3));

                //check takes
                //check west take [ - ]
                if (board[from_rank + 1][from_file - 1] == "0") {
                    string concat = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file - 1) + to_string(piece_position.at(2)) + to_string(piece_position.at(3));
                    black_legal_moves.push_back(concat);
                }
                //check east take [ + ]
                if (board[from_rank + 1][from_file + 1] == "0") {
                    string concat = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file + 1) + to_string(piece_position.at(2)) + to_string(piece_position.at(3));
                    black_legal_moves.push_back(concat);
                }

                //check first double advance
                if (from_rank == starting_rank && board[from_rank + 2][from_file] == "0") {
                    string concat = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 2) + to_string(from_file) + "00";
                    black_legal_moves.push_back(concat);
                }

                //check advance
                if (board[from_rank + 1][from_file] == "0") {
                    string concat = to_string(from_rank) + to_string(from_file) + piece + to_string(from_rank + 1) + to_string(from_file) + "00";
                    black_legal_moves.push_back(concat);
                }
            }   break;

            case 'G': {
                // Gisgigir [G] (Chariot)
                //  - Can move any number of squares, at a time, in either a vertical or horizontal direction.
                //  - Cannot jump over pieces.

                // <<find available moves>>
                // check each direction until:
                // >> friendly fire or out of bounds (obstruction)
                // >> enemy piece (take available)
                // for each space until obstruction or take
                // >> store move (including take)

                const int starting_rank {1};

                from_rank = piece_position.at(0);
                from_file = piece_position.at(1);
                string piece = to_string(piece_position.at(2)) + to_string(piece_position.at(3));
                bool obstructed = false;

                // check north ( - rank , same file )
                int i = from_rank;
                do {
                    // check for empty space
                    if (board[i][from_file].at(0) == '0') {
                        string concat = to_string(from_rank) + to_string(from_file) + piece + to_string(i) + to_string(from_file) + "00";
                        black_legal_moves.push_back(concat);
                    }
                    // check for enemy piece
                    else if (board[i][from_file].at(0) == 'W') {
                        string concat = to_string(from_rank) + to_string(from_file) + piece + to_string(piece_position.at(2)) + to_string(piece_position.at(3));
                        black_legal_moves.push_back(concat);
                        obstructed = true;
                    }
                    // check for friendly piece
                    else if (board[i][from_file].at(0) == 'B') {
                        obstructed = true;
                    }
                    i--;
                } while (i >= 0 || obstructed == true);

                // check south ( + rank , same file )
                i = from_rank;
                do {
                    // check for empty space
                    if (board[i][from_file].at(0) == '0') {
                        string concat = to_string(from_rank) + to_string(from_file) + piece + to_string(i) + to_string(from_file) + "00";
                        black_legal_moves.push_back(concat);
                    }
                    // check for enemy piece
                    else if (board[i][from_file].at(0) == 'W') {
                        string concat = to_string(from_rank) + to_string(from_file) + piece + to_string(piece_position.at(2)) + to_string(piece_position.at(3));
                        black_legal_moves.push_back(concat);
                        obstructed = true;
                    }
                    // check for friendly piece
                    else if (board[i][from_file].at(0) == 'B') {
                        obstructed = true;
                    }
                    i++;
                } while (i < board_dimensions || obstructed == true);

                // check east ( same rank , + file )
                i = from_file;
                do {
                    // check for empty space
                    if (board[from_rank][i].at(0) == '0') {
                        string concat = to_string(from_rank) + to_string(from_file) + piece + to_string(from_file) + to_string(i) + "00";
                        black_legal_moves.push_back(concat);
                    }
                    // check for enemy piece
                    else if (board[from_rank][i].at(0) == 'W') {
                        string concat = to_string(from_rank) + to_string(from_file) + piece + to_string(piece_position.at(2)) + to_string(piece_position.at(3));
                        black_legal_moves.push_back(concat);
                        obstructed = true;
                    }
                    // check for friendly piece
                    else if (board[from_rank][i].at(0) == 'B') {
                        obstructed = true;
                    }
                    i++;
                } while (i < board_dimensions || obstructed == true);

                // check west ( same rank , - file )
                i = from_file;
                do {
                    // check for empty space
                    if (board[from_rank][i].at(0) == '0') {
                        string concat = to_string(from_rank) + to_string(from_file) + piece + to_string(from_file) + to_string(i) + "00";
                        black_legal_moves.push_back(concat);
                    }
                    // check for enemy piece
                    else if (board[from_rank][i].at(0) == 'W') {
                        string concat = to_string(from_rank) + to_string(from_file) + piece + to_string(piece_position.at(2)) + to_string(piece_position.at(3));
                        black_legal_moves.push_back(concat);
                        obstructed = true;
                    }
                    // check for friendly piece
                    else if (board[from_rank][i].at(0) == 'B') {
                        obstructed = true;
                    }
                    i--;
                } while (i >=0 || obstructed == true);
            }   break;

            case 'E': {
                // Etlu [E] (Warrior)  - Can move exactly two squares at a time in either a vertical or horizontal direction. Can jump over other pieces.
                

            }   break;
        }
    }
}


// <<<<=== THIS NEEDS WORK ===>>>>
// For each piece:
// Current
//  -- Iterate each board position and save if legal
// Goal
//  -- Calculate each valid move per piece and store
//  - R
//      - Get pos. Get owner (for direction).
//      - If on starting rank, check +2+0
//      - Check +1-1 (Take enemy), +1+0, +1+1 (Take enemy).


// <<<<=== Check for check ===>>>>
// From legal moves
// - find all moves that target enemy Sarrum
// - if true, !!!must prevent check!!!(how?)
// - look at all legal moves, find all moves from all legal moves, check for check
// - what about moves that put yourself in check??????????(how?)

void request_move (const char player) {
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

            cout << selected_piece << endl;
            cout << owner << endl;
            cout << piece << endl;

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
        cout << "\nMove To [Rank][Row]>>> : ";
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



    // if (turn_number % 2 == 1 && player == 'B') {
    //
    // }
    // else if (turn_number % 2 == 0 && player == 'W') {
    //     cout << "\n>>> : ";
    //     cin >> move_from >> move_to;
    //
    // } else {
    //     string next_move {};
    //     if (player == 'B') {
    //         next_move = get_legal_moves('W');
    //     } else {
    //         next_move = get_legal_moves('B');
    //     }
    // }


    // cout << move_from.at(0) << move_from.at(1) << ":" << move_to.at(0) << move_to.at(1);


    validate_move (move_from, move_to);
}

//void validate_move (string move_from, string move_to) {
//     switch (piece) {

//         case 'E': {
//
//
//             // 4 valid move locations
//             //  - north
//             if ((move_to_file == move_from_file) && (move_to_rank == move_from_rank - 2)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//             //  - south
//             else if ((move_to_file == move_from_file) && (move_to_rank == move_from_rank + 2)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//             //  - east
//             else if ((move_to_rank == move_from_rank) && (move_to_file == move_from_file + 2)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//             //  - west
//             else if ((move_to_rank == move_from_rank) && (move_to_file == move_from_file - 2)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//         }
//             break;
//         case 'N': {
//             // Nabu [N] (Seer)  - Can move one square at a time along a diagonal.
//
//             // 4 valid move locations
//             //  - north/east
//             if ((move_to_file == move_from_file + 1) && (move_to_rank == move_from_rank - 1)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//             //  - south/east
//             else if ((move_to_file == move_from_file + 1) && (move_to_rank == move_from_rank + 1)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//             //  - south/west
//             else if ((move_to_rank == move_from_rank + 1) && (move_to_file == move_from_file - 1)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//             //  - north/west
//             else if ((move_to_rank == move_from_rank - 1) && (move_to_file == move_from_file - 1)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//         }
//             break;
//         case 'M': {
//             // Marzaz Pani [M] (Royal Attendant)  -  Can move one square at a time either vertically or horizontally.
//
//             // 4 valid move locations
//             //  - north
//             if ((move_to_file == move_from_file) && (move_to_rank == move_from_rank - 1)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//             //  - south
//             else if ((move_to_file == move_from_file) && (move_to_rank == move_from_rank + 1)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//             //  - east
//             else if ((move_to_rank == move_from_rank) && (move_to_file == move_from_file + 1)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//             //  - west
//             else if ((move_to_rank == move_from_rank) && (move_to_file == move_from_file - 1)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//         }
//             break;
//         case 'S': {
//             // Sarrum [S] (King)  - Can move one square at a time in any direction.
//
//             // 8 valid move locations
//             //  - north
//             if ((move_to_file == move_from_file) && (move_to_rank == move_from_rank - 1)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//             //  - north/east
//             else if ((move_to_file == move_from_file + 1) && (move_to_rank == move_from_rank - 1)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//             //  - east
//             else if ((move_to_rank == move_from_rank) && (move_to_file == move_from_file + 1)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//             //  - south/east
//             else if ((move_to_file == move_from_file + 1) && (move_to_rank == move_from_rank + 1)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//             //  - south
//             else if ((move_to_file == move_from_file) && (move_to_rank == move_from_rank + 1)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//             //  - south/west
//             else if ((move_to_rank == move_from_rank + 1) && (move_to_file == move_from_file - 1)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//             //  - west
//             else if ((move_to_rank == move_from_rank) && (move_to_file == move_from_file - 1)) {
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//             }
//             //  - north/west
//             else if ((move_to_rank == move_from_rank - 1) && (move_to_file == move_from_file - 1))
//                 if (!friendly_fire(move_to_rank, move_to_file, owner))
//                     update_board(move_from_rank, move_from_file, move_to_rank, move_to_file, selected_piece);
//         }   break;
//
//         case 'K': {
//             // Kashshaptu (Witch) K
//             // Not known how this piece was used in the game.
//             //
//             // It was revealed in the exam how this piece moved. Then it was up to the candidates to program in the Kashshaptu piece.
//
//
//         }
//             break;
//
//         default:
//             break;
//     }
//}

void update_board (int move_from_rank, int move_from_file, int move_to_rank, int move_to_file, string selected_piece) {
    board.at(move_from_rank).at(move_from_file) = "0";
    board.at(move_to_rank).at(move_to_file) = std::move(selected_piece);
}

bool friendly_fire (int move_to_rank, int move_to_file, char owner) {
    if (board[move_to_rank][move_to_file][0] == owner) {
        return true;
    }   return false;
}



string fetch_legal_redum_moves(string piece_data, int move_to_rank, int move_to_file) {
    const int starting_rank {6};
    int move_from_rank = piece_data.at(0) - '0';
    int move_from_file = piece_data.at(1) - '0';
    // cout << " rmtr:" <<move_to_rank << " rmtf:" << move_to_file << endl;

    string selected_piece = board.at(move_from_rank).at(move_from_file);

    char owner {};
    owner = selected_piece.at(0);

    string data {};

    // check if 'forward two square' is true and free of pieces on first move
    if (move_from_rank == starting_rank) {
        if ((move_to_rank == move_from_rank - 2) && (move_to_file == move_from_file) && (board.at(move_to_rank).at(move_to_file) == "0")) {
            if (!friendly_fire(move_to_rank, move_to_file, owner)) {
                data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
                // cout << "data: " << data << endl;
            }
        }
    }

    // check if 'forward one square' is true and free of pieces
    if ((move_to_rank == move_from_rank - 1) && (move_to_file == move_from_file) && (board.at(move_to_rank).at(move_to_file) == "0")) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)){
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }

    // check if 'diagonal & forward one square' is true and contains enemy piece
    if (board.at(move_to_rank).at(move_to_file).at(0) == 'B') {
        if ((move_to_rank == move_from_rank - 1) && ((move_to_file == move_from_file - 1) || (move_to_file == move_from_file + 1))) {
            if (!friendly_fire(move_to_rank, move_to_file, owner)){
                data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
                // cout << "data: " << data << endl;
            }
        }
    }
    return data;
}

string fetch_legal_gisgigir_moves(string piece_data, int move_to_rank, int move_to_file) {
    constexpr int starting_rank {6};
    int move_from_rank = piece_data.at(0) - '0';
    int move_from_file = piece_data.at(1) - '0';
    // cout << " gmtr:" <<move_to_rank << " gmtf:" << move_to_file << endl;

    string selected_piece = board.at(move_from_rank).at(move_from_file);

    char owner {};
    owner = selected_piece.at(0);

    string data {};

    // Gisgigir [G] (Chariot)
    //  - Can move any number of squares, at a time, in either a vertical or horizontal direction.
    //  - Cannot jump over pieces.

    // check cardinal directions
    //  - north
    if ((move_to_file == move_from_file) && (move_to_rank < move_from_rank)) {
        bool obstruction {false};
        int i = move_from_rank - 1;
        do {
            if (board[i][move_to_file] != "0") {
                obstruction = true;
            } else i--;
        } while (!obstruction && i >= move_to_rank);

        if (!obstruction && !friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }

    //  - south
    else if ((move_to_file == move_from_file) && (move_to_rank > move_from_rank)) {
        bool obstruction {false};
        int i = move_from_rank + 1;
        do {
            if (board[i][move_to_file] != "0") {
                obstruction = true;
            } else i++;
        } while (!obstruction && i <= move_to_rank);

        if (!obstruction && !friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - east
    else if ((move_to_rank == move_from_rank) && (move_to_file > move_from_file)) {
        bool obstruction {false};
        int i = move_from_file + 1;
        do {
            if (board[move_to_rank][i] != "0") {
                obstruction = true;
            } else i++;
        } while (!obstruction && i <= move_to_file);

        if (!obstruction && !friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - west
    else if ((move_to_rank == move_from_rank) && (move_to_file < move_from_file)) {
        bool obstruction {false};
        int i = move_from_file - 1;
        do {
            if (board[move_to_rank][i] != "0") {
                obstruction = true;
            } else i--;
        } while (!obstruction && i >= move_to_file);

        if (!obstruction && !friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    return data;
}


string fetch_legal_etlu_moves(string piece_data, int move_to_rank, int move_to_file) {
    constexpr int starting_rank {6};
    int move_from_rank = piece_data.at(0) - '0';
    int move_from_file = piece_data.at(1) - '0';
    // cout << " emtr:" <<move_to_rank << " emtf:" << move_to_file << endl;

    string selected_piece = board.at(move_from_rank).at(move_from_file);

    char owner {};
    owner = selected_piece.at(0);

    string data {};

    // Etlu [E] (Warrior)  - Can move exactly two squares at a time in either a vertical or horizontal direction. Can jump over other pieces.
    // 4 valid move locations
    //  - north
    if ((move_to_file == move_from_file) && (move_to_rank == move_from_rank - 2)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - south
    else if ((move_to_file == move_from_file) && (move_to_rank == move_from_rank + 2)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - east
    else if ((move_to_rank == move_from_rank) && (move_to_file == move_from_file + 2)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - west
    else if ((move_to_rank == move_from_rank) && (move_to_file == move_from_file - 2)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    return data;
}


string fetch_legal_nabu_moves(string piece_data, int move_to_rank, int move_to_file) {
    constexpr int starting_rank {6};
    int move_from_rank = piece_data.at(0) - '0';
    int move_from_file = piece_data.at(1) - '0';
    // cout << " nmtr:" <<move_to_rank << " nmtf:" << move_to_file << endl;

    string selected_piece = board.at(move_from_rank).at(move_from_file);

    char owner {};
    owner = selected_piece.at(0);

    string data {};

    // Nabu [N] (Seer)  - Can move one square at a time along a diagonal.
    // 4 valid move locations
    //  - north/east
    if ((move_to_file == move_from_file + 1) && (move_to_rank == move_from_rank - 1)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - south/east
    else if ((move_to_file == move_from_file + 1) && (move_to_rank == move_from_rank + 1)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - south/west
    else if ((move_to_rank == move_from_rank + 1) && (move_to_file == move_from_file - 1)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - north/west
    else if ((move_to_rank == move_from_rank - 1) && (move_to_file == move_from_file - 1)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    return data;
}

string fetch_legal_marzaz_pani_moves(string piece_data, int move_to_rank, int move_to_file) {
    constexpr int starting_rank {6};
    int move_from_rank = piece_data.at(0) - '0';
    int move_from_file = piece_data.at(1) - '0';
    // cout << " mmtr:" <<move_to_rank << " mmtf:" << move_to_file << endl;

    string selected_piece = board.at(move_from_rank).at(move_from_file);

    char owner {};
    owner = selected_piece.at(0);

    string data {};

    // Marzaz Pani [M] (Royal Attendant)  -  Can move one square at a time either vertically or horizontally.
    // 4 valid move locations
    //  - north
    if ((move_to_file == move_from_file) && (move_to_rank == move_from_rank - 1)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - south
    else if ((move_to_file == move_from_file) && (move_to_rank == move_from_rank + 1)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - east
    else if ((move_to_rank == move_from_rank) && (move_to_file == move_from_file + 1)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - west
    else if ((move_to_rank == move_from_rank) && (move_to_file == move_from_file - 1)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    return data;
}

string fetch_legal_sarrum_moves(string piece_data, int move_to_rank, int move_to_file) {
    constexpr int starting_rank {6};
    int move_from_rank = piece_data.at(0) - '0';
    int move_from_file = piece_data.at(1) - '0';
    // cout << " smtr:" <<move_to_rank << " smtf:" << move_to_file << endl;

    string selected_piece = board.at(move_from_rank).at(move_from_file);

    char owner {};
    owner = selected_piece.at(0);

    string data {};

    // Sarrum [S] (King)  - Can move one square at a time in any direction.
    // 8 valid move locations
    //  - north
    if ((move_to_file == move_from_file) && (move_to_rank == move_from_rank - 1)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - north/east
    else if ((move_to_file == move_from_file + 1) && (move_to_rank == move_from_rank - 1)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - east
    else if ((move_to_rank == move_from_rank) && (move_to_file == move_from_file + 1)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - south/east
    else if ((move_to_file == move_from_file + 1) && (move_to_rank == move_from_rank + 1)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - south
    else if ((move_to_file == move_from_file) && (move_to_rank == move_from_rank + 1)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - south/west
    else if ((move_to_rank == move_from_rank + 1) && (move_to_file == move_from_file - 1)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - west
    else if ((move_to_rank == move_from_rank) && (move_to_file == move_from_file - 1)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    //  - north/west
    else if ((move_to_rank == move_from_rank - 1) && (move_to_file == move_from_file - 1)) {
        if (!friendly_fire(move_to_rank, move_to_file, owner)) {
            data = (piece_data + to_string(move_to_rank) + to_string(move_to_file));
            // cout << "data: " << data << endl;
        }
    }
    return data;
}

string fetch_legal_kashaptu_moves(string piece_data, int move_to_rank, int move_to_file) {
    // constexpr int starting_rank {6};
    // int move_from_rank = piece_data.at(0) - '0';
    // int move_from_file = piece_data.at(1) - '0';
    // // cout << " smtr:" <<move_to_rank << " smtf:" << move_to_file << endl;
    //
    // string selected_piece = board.at(move_from_rank).at(move_from_file);
    //
    // char owner {};
    // owner = selected_piece.at(0);
    //
    // string data {};

    // Kashshaptu (Witch) K
    // Not known how this piece was used in the game.
    //
    // It was revealed in the exam how this piece moved. Then it was up to the candidates to program in the Kashshaptu piece.
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
                char player = choose_player();
                display_board ();
                do {
                    get_legal_moves();
                    display_turn(player);
                    request_move(player);
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