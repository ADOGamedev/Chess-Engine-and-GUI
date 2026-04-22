extends Node2D

const INITIAL_SCALE = 5.0
const INITIAL_SEGMENT_LENGHT = 16.0 * INITIAL_SCALE
const INITIAL_TIP_LENGHT = 8.0 * INITIAL_SCALE

@onready var arrow_segment := $arrow_segment
@onready var arrow_tip := $arrow_tip

var arrow_vector := Vector2.ZERO
var arrow_origin := Vector2.ZERO

func set_arrow_origin(vector: Vector2) -> void:
	arrow_origin = vector
	global_position = vector
	
func set_arrow_vector(vector: Vector2) -> void:
	arrow_vector = vector

	set_lenght(vector.length())
	rotation = atan2(vector.y, vector.x)
	
func set_lenght(lenght: float) -> void:
	arrow_segment.scale.x = (lenght - INITIAL_TIP_LENGHT) / INITIAL_SEGMENT_LENGHT
	arrow_tip.global_position.x = arrow_segment.global_position.x + INITIAL_SEGMENT_LENGHT * arrow_segment.scale.x + INITIAL_TIP_LENGHT
