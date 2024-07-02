extends Control
@onready var audio_stream_player :AudioStreamPlayer= $AudioStreamPlayer
@onready var button = $Button
@onready var texture_rect = $TextureRect
@onready var h_slider = $HSlider
@onready var label = $HSlider/Label

const image_file = "res://1583102181970.jpg"

var img : Image = Image.new()

var decoder :AudioStreamOpusDecoder
var playbacker:AudioStreamGeneratorPlayback
var effect:GDOpusEncoder

var packets :Array[Dictionary] = []

var img_data_as_packets :Array[PackedVector2Array] = []

func _ready():
	effect = AudioServer.get_bus_effect(2,1)
	decoder = audio_stream_player.stream
	playbacker = audio_stream_player.get_stream_playback()
	img = img.load_from_file(image_file)
	texture_rect.texture = ImageTexture.create_from_image(img)
	var imgdata :PackedByteArray= img.get_data()
	var as_array := Array(imgdata)
	var as_float32 := PackedFloat32Array(as_array)
	var normalized_as_float32 :PackedFloat32Array= BarkHelpers.normalize_float32_array(as_float32)
	var as_audio :PackedVector2Array = PackedVector2Array()
	as_audio.resize(normalized_as_float32.size()/2)
	var last_valx :float
	var last_valy :float
	for i in normalized_as_float32.size()/2:
		last_valx = lerp(last_valx, normalized_as_float32[i], .8)
		last_valy = lerp(last_valy, normalized_as_float32[i+1], .8)
		as_audio[i] = Vector2(normalized_as_float32[i]*4.0, normalized_as_float32[i+1]*4.0)
	for i in range(as_audio.size()/960):
		img_data_as_packets.append(as_audio.slice(i*960, (i+1)*960))
	for i in range(as_float32.size()/(960*2)):
		var encoded :Dictionary = (effect.encode_buffer(as_float32.slice(i*(960*2),(i+1)*(960*2)), 200))
		packets.append(encoded)
	button.pressed.connect(opus_the_image)
	h_slider.value_changed.connect(func(value:float):
		label.text = "quality: "+str(value)
		)

func opus_the_image():
	var img = texture_rect.texture.get_image()
	var imgdata = img.get_data()
	var as_array := Array(imgdata)
	var as_float32 := PackedFloat32Array(as_array)
	var decoded_img_bytes :PackedByteArray = PackedByteArray()
	var img_packets :Array[Dictionary] = []
	for i in range(as_float32.size()/(960*2)):
		var encoded :Dictionary = (effect.encode_buffer(as_float32.slice(i*(960*2),(i+1)*(960*2)), h_slider.value))
		img_packets.append(encoded)
	for i in img_packets:
		var tmp :PackedVector2Array = decoder.gdopus_decode(i.output, i.encoded_bytes)
		decoded_img_bytes.append_array(tmp.to_byte_array())
	var decoded_img = Image.create_from_data(img.get_width(), img.get_height(), img.has_mipmaps(), img.get_format(), decoded_img_bytes.slice(0, imgdata.size()))
	texture_rect.texture.update(decoded_img)
	

func _process(delta):
	opus_the_image()
	#if playbacker.can_push_buffer(960) and !packets.is_empty():
		#var encoded :Dictionary= packets.pop_front()
		#var decoded :PackedVector2Array= decoder.gdopus_decode(encoded.output, encoded.encoded_bytes)
		#print(playbacker.push_buffer(decoded))
	#if playbacker.can_push_buffer(960) and !img_data_as_packets.is_empty():
		#var audio :PackedVector2Array= img_data_as_packets.pop_front()
		##print(audio)
		#print(playbacker.push_buffer(audio))
