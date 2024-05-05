#ifndef PIECES_H
#define PIECES_H

#include <utility>
#include <vector>

enum class TypePiece{Vide, Pion, Tour, Cavalier, Fou, Reine, Roi};
enum class Couleur{Blanc, Noir};

const std::vector<std::pair<int, int>> KingMovements = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
const std::vector<std::pair<int, int>> QueenMovements = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
const std::vector<std::pair<int, int>> RookMovements = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
const std::vector<std::pair<int, int>> KnightMovements = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
const std::vector<std::pair<int, int>> BishopMovements = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
const std::vector<std::pair<int, int>> PawnMovements = {{1, 0}};


class ChessBoard;

class Piece
{
public:
    Piece(ChessBoard* plateau);
    Piece(TypePiece type, Couleur couleur, std::pair<int, int> coordonnees, ChessBoard* plateau);
    ~Piece() = default;

    virtual void getMouvementsPossibles(){};
    bool movePiece(int ligne, int colonne);


protected:
    TypePiece type_ = TypePiece::Vide;
    Couleur couleur_ = Couleur::Blanc;
    std::pair<int, int> coordonnees_ = {0, 0};
    ChessBoard* plateau_ = nullptr;
    std::vector<std::pair<int, int>> mouvementsPossibles_{};
    const std::vector<std::pair<int, int>>* primitives_ = nullptr;
};


class Roi : virtual public Piece
{
public:
    Roi(Couleur couleur, std::pair<int, int> coordonnees, ChessBoard* plateau);
    ~Roi() = default;

    // Autres méthodes spécifiques au Roi si nécessaire
};

class Reine : virtual public Piece
{
public:
    Reine(Couleur couleur, std::pair<int, int> coordonnees, ChessBoard* plateau);
    ~Reine() = default;

    // Autres méthodes spécifiques à la Reine si nécessaire
};

class Tour : virtual public Piece
{
public:
    Tour(Couleur couleur, std::pair<int, int> coordonnees, ChessBoard* plateau);
    ~Tour() = default;

    // Autres méthodes spécifiques à la Tour si nécessaire
};

class Cavalier : virtual public Piece
{
public:
    Cavalier(Couleur couleur, std::pair<int, int> coordonnees, ChessBoard* plateau);
    ~Cavalier() = default;

    // Autres méthodes spécifiques au Cavalier si nécessaire
};

class Fou : virtual public Piece
{
public:
    Fou(Couleur couleur, std::pair<int, int> coordonnees, ChessBoard* plateau);
    ~Fou() = default;

    // Autres méthodes spécifiques au Fou si nécessaire
};

class Pion : virtual public Piece
{
public:
    Pion(Couleur couleur, std::pair<int, int> coordonnees, ChessBoard* plateau);
    void getMouvementsPossibles() override;
    ~Pion() = default;

private:
    bool isFistMove = true;
};



#endif // PIECES_H
