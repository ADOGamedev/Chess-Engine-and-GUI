extends Control

func display_message(message: String) -> void:
	await get_tree().create_timer(0.05).timeout
	visible = true
	%game_over_label.text = message

func hide_message() -> void:
	if visible:
		visible = false
