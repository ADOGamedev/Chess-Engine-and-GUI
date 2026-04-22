extends Control

enum Piece {
    WHITE_KNIGHT = 1,
    WHITE_BISHOP = 2,
    WHITE_ROOK = 3,
    WHITE_QUEEN = 4,

    BLACK_KNIGHT = 7,
    BLACK_BISHOP = 8,
    BLACK_ROOK = 9,
    BLACK_QUEEN = 10,
}

signal promotion_piece_selected(piece)

func show_promotion_menu():
    visible = true

func hide_promotion_menu():
    visible = false

func show_buttons_of_white_pieces():
    %hbox_container_white.visible = true
    %hbox_container_black.visible = false

func show_buttons_of_black_pieces():
    %hbox_container_white.visible = false
    %hbox_container_black.visible = true

func _on_white_queen_button_pressed() -> void:
    emit_signal("promotion_piece_selected", Piece.WHITE_QUEEN)

func _on_white_rook_button_pressed() -> void:
    emit_signal("promotion_piece_selected", Piece.WHITE_ROOK)

func _on_white_bishop_button_pressed() -> void:
    emit_signal("promotion_piece_selected", Piece.WHITE_BISHOP)

func _on_white_knight_button_pressed() -> void:
    emit_signal("promotion_piece_selected", Piece.WHITE_KNIGHT)

func _on_black_queen_button_pressed() -> void:
    emit_signal("promotion_piece_selected", Piece.BLACK_QUEEN)

func _on_black_rook_button_pressed() -> void:
    emit_signal("promotion_piece_selected", Piece.BLACK_ROOK)

func _on_black_bishop_button_pressed() -> void:
    emit_signal("promotion_piece_selected", Piece.BLACK_BISHOP)

func _on_black_knight_button_pressed() -> void:
    emit_signal("promotion_piece_selected", Piece.BLACK_KNIGHT)
