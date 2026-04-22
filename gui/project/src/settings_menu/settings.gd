extends Control

@onready var ENGINE_PATH := get_global_path("res://predownloaded_engines/adoce/engine.exe")
@onready var STARTING_FEN := "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

@onready var file_dialog := $file_dialog
@onready var engine_path_line_edit := %path_line_edit
@onready var fen_line_edit := %fen_line_edit

func get_global_path(path_res: String) -> String:
	if OS.has_feature("editor"):
		return ProjectSettings.globalize_path(path_res)
	else:
		var base = OS.get_executable_path().get_base_dir()
		var relativa = path_res.replace("res://", "")
		return base + "/" + relativa
		
func _ready() -> void:
	set_curr_fen(STARTING_FEN)
	engine_path_line_edit.text = ENGINE_PATH

	await owner.ready
	owner.set_game_config(engine_path_line_edit.text, fen_line_edit.text)
	
func set_curr_fen(fen: String) -> void:
	fen_line_edit.text = fen
	
func _on_apply_button_pressed() -> void:
	visible = false
	owner.set_game_config(engine_path_line_edit.text, fen_line_edit.text)

func _on_cancel_button_pressed() -> void:
	visible = false

func _on_path_button_pressed() -> void:
	file_dialog.visible = true

func _on_file_dialog_file_selected(path: String) -> void:
	engine_path_line_edit.text = path

func _on_fen_reload_button_pressed() -> void:
	fen_line_edit.text = STARTING_FEN
