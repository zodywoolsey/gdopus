extends Node
@onready var playback = $playback
@onready var h_slider = $HSlider

var timer := 0.1
var prevtime := 0.0

var playbacker:AudioStreamGeneratorPlayback
var stream:AudioStreamOpusDecoder
var effect:GDOpusEncoder

var thread:Thread = Thread.new()
var thread2:= Thread.new()

func _ready():
	#print(ClassDB.get_class_list())
	playback.play()
	stream = playback.stream
	playback.has_stream_playback()
	playbacker = playback.get_stream_playback()
	await get_tree().process_frame
	thread.start(go)
	effect = AudioServer.get_bus_effect(2,1)
	h_slider.value_changed.connect(func(value:float):
		effect.gdopus_set_bitrate(value)
		)

func _process(delta):
#	playback.play()
	if !thread.is_alive() and thread.is_started():
		#print('restart')
		thread.wait_to_finish()
		thread.start(go)
#	print(playbacker.get_frames_available())
#	playbacker.pl
#	print(playback.playing)
#	var tmp:AudioEffectCapture = AudioServer.get_bus_effect(0,0)
#	print(tmp.get_buffer(960))

func go():
	while true:
		if effect.can_get_buffer(960*2):
			var encoded1 = effect.gdopus_encode()
			var encoded2 = effect.gdopus_encode()
			var decoded = stream.gdopus_decode(encoded1.output,encoded1.output.size())
			decoded.append_array(stream.gdopus_decode(encoded2.output,encoded2.output.size()))
			playbacker.push_buffer(decoded)
