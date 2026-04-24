extends Control

const ONE_MINUTE = 60;
const TWO_MINUTES = 120;
const THREE_MINUTES = 180;
const FIVE_MINUTES = 300;
const TEN_MINUTES = 600;
const FIFTEEN_MINUTES = 900;
const THIRTY_MINUTES = 1800;

func _process(_delta: float) -> void:
	if !owner.is_settings_menu_visible() and Input.is_action_just_pressed("flip_board"):
		owner.flip_board()
	if Input.is_action_just_pressed("esc"):
		owner.hide_settings_menu()
	if Input.is_action_just_pressed("left_click"):
		owner.hide_game_over_message()
		owner.hide_error_menu()
	if Input.is_action_just_pressed("advance_move"):
		owner.on_next_move_button_pressed()
	if Input.is_action_just_pressed("go_back_move"):
		owner.on_previous_move_button_pressed()

func _notification(what: int) -> void:
	if what == NOTIFICATION_WM_CLOSE_REQUEST:
		owner.quit_engine()
		get_tree().quit()

func set_bottom_timer_label(seconds: int) -> void:
	%timer_bottom.text = seconds_to_string(seconds)

func set_top_timer_label(seconds: int) -> void:
	%timer_top.text = seconds_to_string(seconds)

func seconds_to_string(seconds: int) -> String:
	var minutes_str = str(floor(seconds / 60))
	var seconds_str = ""

	if seconds % 60 < 10:
		seconds_str += "0"

	seconds_str += str(seconds % 60)

	return minutes_str + ":" + seconds_str

func _on_settings_button_pressed() -> void:
	owner.show_settings_menu()

func _on_back_button_pressed() -> void:
	owner.on_previous_move_button_pressed();
	
func _on_next_button_pressed() -> void:
	owner.on_next_move_button_pressed();

func _on_bottom_resign_button_pressed() -> void:
	owner.apply_bottom_resignation();

func _on_top_resign_button_pressed() -> void:
	owner.apply_top_resignation();

func _on_play_button_pressed() -> void:
	owner.on_play_button_pressed()

func _on_black_button_pressed() -> void:
	owner.on_black_button_pressed();

func _on_random_button_pressed() -> void:
	owner.on_random_colour_button_pressed();

func _on_white_button_pressed() -> void:
	owner.on_white_button_pressed();

func _on_one_minute_button_pressed() -> void:
	owner.set_timer_mode(10, 0.1)

func _on_one_minute_one_button_pressed() -> void:
	owner.set_timer_mode(ONE_MINUTE, 1)

func _on_two_minute_one_button_pressed() -> void:
	owner.set_timer_mode(TWO_MINUTES, 1)

func _on_three_minutes_button_pressed() -> void:
	owner.set_timer_mode(THREE_MINUTES, 0)

func _on_three_minutes_two_button_pressed() -> void:
	owner.set_timer_mode(THREE_MINUTES, 2)

func _on_five_minutes_button_pressed() -> void:
	owner.set_timer_mode(FIVE_MINUTES, 0)

func _on_ten_minutes_button_pressed() -> void:
	owner.set_timer_mode(TEN_MINUTES, 0)

func _on_fifteen_minutes_ten_button_pressed() -> void:
	owner.set_timer_mode(FIFTEEN_MINUTES, 10)

func _on_thirty_minutes_button_pressed() -> void:
	owner.set_timer_mode(THIRTY_MINUTES, 0)

func _on_play_against_ai_button_toggled(toggled_on: bool) -> void:
	owner.set_ai_mode(toggled_on)
