#include "computer.h"
#include "player.h"
#include "board.h"
#include "piece.h"
#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include "tools.h"
#include <fstream>

using namespace std;

int symbolToMaterialValue(char c) {
    switch(tolower(c)) {
        case 'p' : return 1;
        case 'n' : return 3;
        case 'b' : return 3;
        case 'r' : return 5;
        case 'q' : return 9;
        case 'k' : return 0;
    }
};

Computer::Computer(string team, bool isCpu, bool myTurn) : 
    Player(team, isCpu, myTurn) {}

Computer::~Computer() {}

pair<int, int> Computer::convertToCoord(string notation) {
    char letter = notation[0];
    char number = notation[1];

    int col = letter - 'a'; 
    int row = 7 - (number - '1');

    return make_pair(row, col);
}


vector<pair<int, int>> Computer::makeComputerMove(Board& b, int level)  {

    vector<pair<int, int>> move;

    if (level == 1) {
        move = levelOne(b);
    } else if (level == 2) {
        move = levelTwo(b);
    } else if (level == 3) {
        move = levelThree(b);
    } else if (level == 4) {
        move = levelFour(b);
    } else if (level == 5) {
        move = levelFive(b);
    }

    return move;
}

vector<pair<int, int>> Computer::levelOne(Board& b)  {
    int randomIndex;

    // this is a vector of pairs of <currentPosition, vectorPossibleMoves>
    vector<
        pair<
            pair<int, int>, // current
            pair<int, int> // possibleMove
        >
    > moves;

    for(int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (b.getPiece(x, y)->getTeam() == this->getTeam() && !b.getPiece(x, y)->isBlank()) {

                vector<pair<int, int>> possibleMoves =  b.getPiece(x, y)->calculatePossibleMoves();
                pair<int, int> current(b.getPiece(x, y)->getRow(), b.getPiece(x, y)->getCol());

                for (pair<int, int> move : possibleMoves) {
                    pair<pair<int, int>, pair<int, int>> currentAndPossibleMove(current, move);
                    moves.emplace_back(currentAndPossibleMove);
                }        
            }
        }
    }

    // seed-safe random move generation for availabliePieces
    randomIndex = randomGenerator(0, moves.size() - 1);

    pair<pair<int, int>, pair<int, int>> move = moves[randomIndex];

    vector<pair<int, int>> fromToMove;

    fromToMove.emplace_back(move.first);
    fromToMove.emplace_back(move.second);

    return fromToMove;
}

// levelTwo Computer
vector<pair<int, int>> Computer::levelTwo(Board& b)  {
    int randomIndex;

    // this is a vector of pairs of <currentPosition, vectorPossibleMoves>
    vector<
        pair<
            pair<int, int>, // current
            pair<int, int> // possibleMove
        >
    > moves;

    vector<
        pair<
            pair<int, int>, // current
            pair<int, int> // possibleMove
        >
    > captureMoves;

    for(int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (b.getPiece(x, y)->getTeam() == this->getTeam() && !b.getPiece(x, y)->isBlank()) {

                vector<pair<int, int>> possibleCaptureMoves = b.getPiece(x, y)->capturingMoves();
                vector<pair<int, int>> possibleMoves =  b.getPiece(x, y)->calculatePossibleMoves();

                pair<int, int> current(b.getPiece(x, y)->getRow(), b.getPiece(x, y)->getCol());

                for (pair<int, int> move : possibleCaptureMoves) {
                    pair<pair<int, int>, pair<int, int>> currentAndPossibleMove(current, move);
                    captureMoves.emplace_back(currentAndPossibleMove);
                }

                for (pair<int, int> move : possibleMoves) {
                    pair<pair<int, int>, pair<int, int>> currentAndPossibleMove(current, move);
                    moves.emplace_back(currentAndPossibleMove);
                }

            }
        }
    }

    pair<pair<int, int>, pair<int, int>> move;

    if (captureMoves.size() != 0) {
        // seed-safe random move generation for availabliePieces
        randomIndex = randomGenerator(0, captureMoves.size() - 1);
        move = captureMoves[randomIndex];
    } else if (moves.size() != 0) {
        randomIndex = randomGenerator(0, moves.size() - 1);
        move = moves[randomIndex];
    }

    vector<pair<int, int>> fromToMove;

    fromToMove.emplace_back(move.first);
    fromToMove.emplace_back(move.second);

    return fromToMove;
}

// Minimax Algorithm functions

// Minimax Algorithm
// Credit to Chess Programming Wiki for the pseudocode and understanding of implementation
// https://www.chessprogramming.org/Minimax
pair<vector<pair<int, int>>, int> Computer::minimax(Board& b, int depth, const string maximizingPlayerColor, bool maximize) {
    if (depth == 0) {
        return {vector<pair<int, int>>(), eval(b, maximizingPlayerColor)};
    }

    string currentPlayerColor = maximize ? maximizingPlayerColor : (maximizingPlayerColor == "black" ? "white" : "black");
    vector<pair<pair<int, int>, pair<int, int>>> moves = getMoves(b, currentPlayerColor);

    int bestEval = maximize ? INT_MIN : INT_MAX;

    vector<pair<int ,int>> bestMove;

    for (const auto& move : moves) {
        vector<pair<int, int>> moveSequence = {move.first, move.second};

        b.boardtoState();

        b.movePiece(moveSequence);
        auto [recursiveBestMove, recursiveEval] = minimax(b, depth - 1, maximizingPlayerColor, !maximize);

        b.reversePiece();

        if (maximize && recursiveEval > bestEval) {
            bestEval = recursiveEval;
            bestMove = moveSequence;
        } else if (!maximize && recursiveEval < bestEval) {
            bestEval = recursiveEval;
            bestMove = moveSequence;
        }
    }

    return {bestMove, bestEval};
}

vector<pair<pair<int, int>, pair<int, int>>> Computer::getMoves(Board& b, string team) {

    // this is a vector of pairs of <currentPosition, vectorPossibleMoves>
    vector<
        pair<
            pair<int, int>, // current
            pair<int, int> // possibleMove
        >
    > moves;

    // get every single possible move
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (b.getPiece(row, col)->getTeam() == team && !b.getPiece(row, col)->isBlank()) {

                vector<pair<int, int>> possibleMoves =  b.getPiece(row, col)->calculatePossibleMoves();
                pair<int, int> current(b.getPiece(row, col)->getRow(), b.getPiece(row, col)->getCol());

                for (pair<int, int> move : possibleMoves) {
                    pair<pair<int, int>, pair<int, int>>currentAndPossibleMove(current, move);
                    moves.emplace_back(currentAndPossibleMove);
                }        
            }
        }
    }

    return moves;
}

// The eval function evaluates a given board to find the material value of a given team
int Computer::eval(Board& b, const string maximizingPlayerColor) {
    int totalMaterialValueMaximizingTeam = 0;
    int totalMaterialValueMinimizingTeam = 0;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (!b.getPiece(x, y)->isBlank()) {
                int pieceValue = symbolToMaterialValue(b.getPiece(x, y)->getSymbol());
                if (b.getPiece(x, y)->getTeam() == maximizingPlayerColor) {
                    totalMaterialValueMaximizingTeam += pieceValue;
                } else {
                    totalMaterialValueMinimizingTeam += pieceValue;
                }
            }
        }
    }
    return totalMaterialValueMaximizingTeam - totalMaterialValueMinimizingTeam;
}

vector<pair<int, int>> Computer::levelThree(Board &b) {
    pair<vector<pair<int, int>>, int> bestMaterialMove = minimax(b, 2, "black", true);

    return bestMaterialMove.first;
}

vector<pair<int, int>> Computer::levelFour(Board &b) {
    pair<vector<pair<int, int>>, int> bestMaterialMove = minimax(b, 3, "black", true);

    return bestMaterialMove.first;
}

// levelFive utilizes the stockfish chess engine to do the board analysis
// Source: https://stockfishchess.org/
vector<pair<int, int>> Computer::levelFive(Board &b) {
    string fen;

    // the next lines convert our board structure into the FEN format because stockfish only understands FEN syntax for board evals
    // Source: https://www.chess.com/terms/fen-chess
    for (int row = 0; row < 8; ++row) {

        if (row > 0) {
            fen += '/';
        }

        int emptyPieceCount = 0;

        for (int col = 0; col < 8; ++col) {
            Piece* piece = b.getPiece(row, col);
            char symbol = piece->getSymbol();

            if (piece->isBlank()) {
                emptyPieceCount++;
            } else {
                if (emptyPieceCount > 0) {
                    fen += to_string(emptyPieceCount);
                    emptyPieceCount = 0;
                }
                fen += symbol;
            }
        }

        if (emptyPieceCount > 0) {
            fen += to_string(emptyPieceCount);
        }
    }
    
    // adding some extra FEN things stockfish needs to understand specifcally the team color
    fen += " ";
    fen += this->getTeam()[0];
    fen += " - - ";
    fen += "0 0";

    // the stockfish execs path
    string pathToStockfish = "src/stockfish";

    // for some reason I could not utilize the fopen command correctly so i switched to the system command api and
    // did a trivial solution of taking command input through a txt file and also dumping it into a text file for me to read
    string inputFilePath = "src/stockfish_commands.txt";
    string outputFilePath = "src/stockfish_output.txt";
    
    ofstream inputFile(inputFilePath);

    // stockfish API call commands
    inputFile << "position fen " << fen << endl;
    inputFile << "go depth 12" << endl;
    inputFile.close();

    // system command
    string command = pathToStockfish + " < " + inputFilePath + " > " + outputFilePath;

    system(command.c_str());

    ifstream outputFile(outputFilePath);
    string line;
    string bestMoveOutput;

    // parsing the file to find the bestmove line then stripping for the actual move syntax i.e. a7a6
    while (getline(outputFile, line)) {
        if (line.find("bestmove") != string::npos) {
            bestMoveOutput = line.substr(line.find("bestmove") + 9);
            break;
        }
    }

    // closing the file
    outputFile.close();

    // correct type return to makeComputerMove
    vector<pair<int, int>> fromToMove;

    fromToMove.emplace_back(convertToCoord(bestMoveOutput.substr(0, 2)));
    fromToMove.emplace_back(convertToCoord(bestMoveOutput.substr(2, 2)));

    return fromToMove;

}