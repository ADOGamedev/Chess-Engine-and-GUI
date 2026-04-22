extends Node2D

@onready var arrow := preload("res://scenes/arrow.tscn")

func draw_or_erase_arrow(from_pos: Vector2, to_pos: Vector2) -> void:
	var arrow_erased = check_and_erase_arrow_if_needed(from_pos, to_pos)

	if arrow_erased:
		return

	var new_arrow = arrow.instantiate()
	add_child(new_arrow)

	var arrow_vector = to_pos - from_pos

	new_arrow.set_arrow_origin(from_pos)
	new_arrow.set_arrow_vector(arrow_vector)

func check_and_erase_arrow_if_needed(from_pos: Vector2, to_pos: Vector2) -> bool:
	var arrow_vector = to_pos - from_pos

	for child in get_children():
		if child.arrow_vector == arrow_vector and child.arrow_origin == from_pos:
			child.queue_free()
			return true
	
	return false

func clear_arrows() -> void:
	for child in get_children():
		child.queue_free()
