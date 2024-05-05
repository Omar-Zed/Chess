#include "chessboard.h"

ChessBoard::ChessBoard() {
    for (int ligne = 0; ligne < 8; ligne++){
        for (int colonne = 0; colonne < 8; colonne++){
            *plateau_[ligne][colonne] = Piece(this);
        }
    }
}
