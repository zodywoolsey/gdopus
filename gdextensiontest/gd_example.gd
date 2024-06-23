extends Node
@onready var playback = $playback
@onready var h_slider = $HSlider
@onready var label = $Label
@onready var label_2 = $Label2
@onready var button = $Button
@onready var button_2 = $Button2

var timer := 0.1
var prevtime := 0.0

var playbacker:AudioStreamGeneratorPlayback
var stream:AudioStreamOpusDecoder
var effect:GDOpusEncoder

var thread:Thread = Thread.new()
var thread2:= Thread.new()
var packet_size :int = 0
var losing_packets := false
var nopush := false

func _ready():
	#print(ClassDB.get_class_list())
	#playback.play()
	stream = playback.stream
	playback.has_stream_playback()
	playbacker = playback.get_stream_playback()
	await get_tree().process_frame
	thread.start(go)
	effect = AudioServer.get_bus_effect(2,1)
	effect.gdopus_set_bitrate(2000)
	h_slider.value = 2000
	h_slider.value_changed.connect(func(value:float):
		label.text = "bitrate: " +str(value)
		effect.gdopus_set_bitrate(value)
		)
	button.button_down.connect(func():
		losing_packets = true
		)
	button.button_up.connect(func():
		losing_packets = false
		)
	button_2.button_down.connect(func():
		nopush = true
		)
	button_2.button_up.connect(func():
		nopush = false
		)

func _process(delta):
	label_2.text = "packet size: "+str(packet_size)

func go():
	while true:
		if effect.can_get_buffer(960):
			var encoded1 = effect.gdopus_encode()
			#var encoded2 = effect.gdopus_encode()
			var decoded :PackedVector2Array
			if !losing_packets:
				decoded = stream.gdopus_decode(encoded1.output,encoded1.output.size())
			else:
				decoded = stream.gdopus_decode_loss()
			#decoded.append_array(stream.gdopus_decode(encoded2.output,encoded2.output.size()))
			packet_size = encoded1.output.size()
			#packet_size += encoded2.output.size()
			if !nopush:
				playbacker.push_buffer(decoded)
