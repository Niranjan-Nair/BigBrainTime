#ifndef types_h
#define types_h

/*******************************************
 * TYPES.H: Types used throughout project. *
 *******************************************/

#include "common.h"

/* Bitboards to represent position */
typedef uint64_t Bitboard;

/* Zobrist hash for transposition table */
typedef uint64_t ZobristHash;

/* Efficient Move representation through 16 bit unsigned */
typedef uint16_t Move;

/* Enum for piece types */
typedef enum
{
    WHITE_PAWN,
    WHITE_KNIGHT,
    WHITE_BISHOP,
    WHITE_ROOK,
    WHITE_QUEEN,
    WHITE_KING,
    BLACK_PAWN,
    BLACK_KNIGHT,
    BLACK_BISHOP,
    BLACK_ROOK,
    BLACK_QUEEN,
    BLACK_KING,
    PIECE_NONE,
} Piece;

/* Enum for side to move */
typedef enum
{
    BLACK,
    WHITE,
    SIDE_NONE,
} Side;

/* Enum for squares: A1 is 0 and H8 is 63 */
typedef enum
{
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
    SQUARE_NONE,
} Square;

/* Flag to label special types of moves */
typedef enum
{
    FLAG_NONE = 0b0000,
    DOUBLE_PAWN_PUSH = 0b0001,
    KING_CASTLE = 0b0010,
    QUEEN_CASTLE = 0b0011,
    CAPTURE = 0b0100,
    EN_PASSANT = CAPTURE | DOUBLE_PAWN_PUSH,
    KNIGHT_PROMOTION = 0b1000,
    BISHOP_PROMOTION = 0b1001,
    ROOK_PROMOTION = 0b1010,
    QUEEN_PROMOTION = 0b1011,
    KNIGHT_PROMOTION_CAPTURE = KNIGHT_PROMOTION | CAPTURE,
    BISHOP_PROMOTION_CAPTURE = BISHOP_PROMOTION | CAPTURE,
    ROOK_PROMOTION_CAPTURE = ROOK_PROMOTION | CAPTURE,
    QUEEN_PROMOTION_CAPTURE = QUEEN_PROMOTION | CAPTURE,
} MoveFlag;

/* Enum to represent castling rights indices */
typedef enum 
{
    WHITE_KING_CASTLE,
    WHITE_QUEEN_CASTLE,
    BLACK_KING_CASTLE,
    BLACK_QUEEN_CASTLE,
} CastlingRights;

/* Struct to represent board state */
typedef struct
{
    Square en_passant_square;
    bool castling_rights[4];
    Side turn;
    int fifty_move_counter;
} State;

/* Wrapper for moves to easily unmake a move */
typedef struct 
{
    Move move;
    State state;
    Piece captured;
} MoveInfo;

/* Dynamic array of moves stored in board */
typedef struct
{
    size_t size;
    size_t capacity;
    MoveInfo *items;
} MoveList;

/* Scructure to store zobrist keys */
typedef struct
{
    ZobristHash squares[64][12];
    ZobristHash en_passant_files[8];
    ZobristHash castling_rights[4];
    ZobristHash turn;
} Zobrist;

/* Structure to represent board state */
typedef struct
{
    MoveList halfmoves;
    int halfmove_counter;
    ZobristHash zobrist;
    State state;
} Board;

#endif
