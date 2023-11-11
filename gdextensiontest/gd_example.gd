extends Node
@onready var playback = $playback

var timer := 0.1
var prevtime := 0.0

var playbacker:AudioStreamGeneratorPlayback
var stream:AudioStreamOpusDecoder
var effect:GDOpusEncoder

var thread:Thread = Thread.new()

func _ready():
	playback.play()
	stream = playback.stream
	playback.has_stream_playback()
	playbacker = playback.get_stream_playback()
	thread.start(go)
	effect = AudioServer.get_bus_effect(2,1)

func _process(delta):
#	playback.play()
	if !thread.is_alive() and thread.is_started():
		print('restart')
		thread.wait_to_finish()
		thread.start(go)
#	print(playbacker.get_frames_available())
#	playbacker.pl
#	print(playback.playing)
#	var tmp:AudioEffectCapture = AudioServer.get_bus_effect(0,0)
#	print(tmp.get_buffer(960))

func go():
	while true:
		var delta:float = Time.get_unix_time_from_system()*1000.0-prevtime
		prevtime = Time.get_unix_time_from_system()*1000.0
		timer += delta
		var encoded = effect.gdopus_encode()
		var decoded = stream.gdopus_decode(encoded.output,encoded.encoded_bytes)
		var rawbuffer = effect.get_buffer(960)
		playbacker.push_buffer(decoded)
