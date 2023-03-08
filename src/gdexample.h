#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/fast_noise_lite.hpp>

namespace godot {

class test : public MeshInstance3D{
    GDCLASS(test, MeshInstance3D)

private:
    float time_passed;
    int size;
    int cSeed;
    float noiseScale;
    float snapScale;
    FastNoiseLite noise;
    Mesh amesh;
    PackedVector3Array verts;
    PackedVector3Array normals;
    PackedVector3Array faceNormals;
    float offset;

protected:
    static void _bind_methods();

public:
    test();
    ~test();

    void _ready();
    void _process(float delta);
    void generate();
    void addQuad(Vector3 pos, float offset, float mult);
};

}

#endif