extends Control

func display_message(message: String) -> void:
	visible = true
	%game_over_label.text = message

func hide_message() -> void:
	visible = false
