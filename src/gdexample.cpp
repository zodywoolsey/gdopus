#include "gdexample.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void test::_bind_methods() {
}

test::test() {
    // initialize any variables here
    time_passed = 0.0;
    size = 200;
    cSeed = 0;
    noiseScale = 1;
    snapScale = .5;
    amesh ;
    verts = PackedVector3Array();
    normals = PackedVector3Array();
    faceNormals = PackedVector3Array();
    offset = 0;
}

test::~test() {
    // add your cleanup here
}

void test::_ready(){
    
}

void test::_process(float delta) {
    time_passed += delta;

    Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

}

void test::generate(){
    
	// verts = PackedVector3Array()
	// amesh = ArrayMesh.new()
	// var mult = .5
	// printf('test')
	// for x in range(size):
	// 	for z in range(size):
	// 		var tmpx = x-(size/2)
	// 		var tmpz = z-(size/2)
	// 		var n = noise.get_noise_2d((tmpx+offset)*mult,(tmpz+offset)*mult)*noiseScale
	// 		n = snapped(n, snapScale)
	// 		addQuadPoint(Vector3(tmpx,n,tmpz),offset,mult)
	// var meshArr = []
	// meshArr.resize(Mesh.ARRAY_MAX)
	// meshArr[Mesh.ARRAY_VERTEX] = verts
	// meshArr[Mesh.ARRAY_NORMAL] = normals
	
	
	// amesh.add_surface_from_arrays(Mesh.PRIMITIVE_TRIANGLES,meshArr)
	// amesh.lightmap_unwrap(Transform3D(),1.0)
	// ter.mesh = amesh
	// offset += 1
	// for child in ter.get_children():
	// 	ter.remove_child(child)
	// ter.create_trimesh_collision()
	// ter.find_child("CollisionShape3D").hide()
}