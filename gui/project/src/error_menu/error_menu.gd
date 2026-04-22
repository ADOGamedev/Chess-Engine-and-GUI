extends Control

@onready var error_label := %error_label

func display_error_message(message: String) -> void:
    visible = true
    error_label.text = message
