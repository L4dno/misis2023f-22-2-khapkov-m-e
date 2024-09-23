// a simple class to help build up faces of a cube
class GeomtryBuilder
{
public:

    // setup the builder with the mesh it is going to fill out
    GeomtryBuilder(Mesh& mesh) : MeshRef(mesh)
    {
    }

    // we need to know how many triangles are going to be in the mesh before we start
    // this way we can allocate the correct buffer sizes for the mesh
    void Allocate(int triangles)
    {
        // there are 
        MeshRef.vertexCount = triangles * 6;
        MeshRef.triangleCount = triangles * 2;

        MeshRef.vertices = static_cast<float*>(MemAlloc(sizeof(float) * 3 * MeshRef.vertexCount));
        MeshRef.normals = static_cast<float*>(MemAlloc(sizeof(float) * 3 * MeshRef.vertexCount));
        MeshRef.texcoords = static_cast<float*>(MemAlloc(sizeof(float) * 2 * MeshRef.vertexCount));
        MeshRef.texcoords2 = static_cast<float*>(MemAlloc(sizeof(float) * 2 * MeshRef.vertexCount));
        MeshRef.colors = nullptr;	// static_cast<unsigned char*>(MemAlloc(sizeof(unsigned char) * 4 * MeshRef.vertexCount));

        MeshRef.animNormals = nullptr;
        MeshRef.animVertices = nullptr;
        MeshRef.boneIds = nullptr;
        MeshRef.boneWeights = nullptr;
        MeshRef.tangents = nullptr;
        MeshRef.indices = nullptr;
    }

    // set texture cords in the mesh
    inline void SetSetUV(Vector2& value) { UV = value; }
    inline void SetSetUV(float x, float y) { UV = Vector2{ x,y }; }
    inline void SetSetUV2(float x, float y) { UV2 = Vector2{ x,y }; }

    // creare vertex by index
    inline void PushVertex(Vector3& vertex, float xOffset = 0, float yOffset = 0, float zOffset = 0)
    {
        size_t index = TriangleIndex * 12 + VertIndex * 3;

        if (MeshRef.colors != nullptr)
        {
            MeshRef.colors[index] = VertColor.r;
            MeshRef.colors[index + 1] = VertColor.g;
            MeshRef.colors[index + 2] = VertColor.b;
            MeshRef.colors[index + 3] = VertColor.a;
        }

        if (MeshRef.texcoords != nullptr)
        {
            index = TriangleIndex * 6 + VertIndex * 2;
            MeshRef.texcoords[index] = UV.x;
            MeshRef.texcoords[index + 1] = UV.y;
        }

        if (MeshRef.texcoords2 != nullptr)
        {
            index = TriangleIndex * 6 + VertIndex * 2;
            MeshRef.texcoords2[index] = UV2.x;
            MeshRef.texcoords2[index + 1] = UV2.y;
        }

        index = TriangleIndex * 9 + VertIndex * 3;
        MeshRef.vertices[index] = vertex.x + xOffset;
        MeshRef.vertices[index + 1] = vertex.y + yOffset;
        MeshRef.vertices[index + 2] = vertex.z + zOffset;

        // counting triangles in the mesh
        VertIndex++;
        if (VertIndex > 2)
        {
            TriangleIndex++;
            VertIndex = 0;
        }
    }

protected:
    Mesh& MeshRef;

    size_t TriangleIndex = 0;
    size_t VertIndex = 0;

    Color VertColor = WHITE;
    Vector2 UV = { 0,0 };
    Vector2 UV2 = { 0,0 };
};
