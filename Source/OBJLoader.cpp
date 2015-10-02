#include "OBJLoader.hpp"
#include <fstream>

using namespace DirectX;

// Load an OBJ file
std::shared_ptr<Mesh> OBJLoader::Load( const std::string& fname, ID3D11Device* device )
{
    std::shared_ptr<Mesh> mesh = nullptr;

    // File input object
    std::ifstream obj( fname.c_str(), std::ios::in | std::ios::binary );

    // Check for successful open
    if ( !obj.is_open() )
        return mesh;

    // Variables used while reading the file
    std::vector<XMFLOAT3> positions;     // Positions from the file
    std::vector<XMFLOAT3> normals;       // Normals from the file
    std::vector<XMFLOAT2> uvs;           // UVs from the file
    std::vector<Vertex> verts;           // Verts we're assembling
    std::vector<UINT> indices;           // Indices of these verts
    unsigned int triangleCounter = 0;    // Count of triangles/indices
    char chars[ 100 ];                     // String for line reading

    // Still good?
    while ( obj.good() )
    {
        // Get the line (100 characters should be more than enough)
        obj.getline( chars, 100 );

        // Check the type of line
        if ( chars[ 0 ] == 'v' && chars[ 1 ] == 'n' )
        {
            // Read the 3 numbers directly into an XMFLOAT3
            XMFLOAT3 norm;
            sscanf_s(
                chars,
                "vn %f %f %f",
                &norm.x, &norm.y, &norm.z );

            // Add to the list of normals
            normals.push_back( norm );
        }
        else if ( chars[ 0 ] == 'v' && chars[ 1 ] == 't' )
        {
            // Read the 2 numbers directly into an XMFLOAT2
            XMFLOAT2 uv;
            sscanf_s(
                chars,
                "vt %f %f",
                &uv.x, &uv.y );

            // Add to the list of uv's
            uvs.push_back( uv );
        }
        else if ( chars[ 0 ] == 'v' )
        {
            // Read the 3 numbers directly into an XMFLOAT3
            XMFLOAT3 pos;
            sscanf_s(
                chars,
                "v %f %f %f",
                &pos.x, &pos.y, &pos.z );

            // Add to the positions
            positions.push_back( pos );
        }
        else if ( chars[ 0 ] == 'f' )
        {
            // Read the 9 face indices into an array
            unsigned int i[ 9 ];
            sscanf_s(
                chars,
                "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &i[ 0 ], &i[ 1 ], &i[ 2 ],
                &i[ 3 ], &i[ 4 ], &i[ 5 ],
                &i[ 6 ], &i[ 7 ], &i[ 8 ] );

            // - Create the verts by looking up
            //    corresponding data from vectors
            // - OBJ File indices are 1-based, so
            //    they need to be adusted
            Vertex v1;
            v1.Position = positions[ i[ 0 ] - 1 ];
            v1.UV = uvs[ i[ 1 ] - 1 ];
            v1.Normal = normals[ i[ 2 ] - 1 ];

            Vertex v2;
            v2.Position = positions[ i[ 3 ] - 1 ];
            v2.UV = uvs[ i[ 4 ] - 1 ];
            v2.Normal = normals[ i[ 5 ] - 1 ];

            Vertex v3;
            v3.Position = positions[ i[ 6 ] - 1 ];
            v3.UV = uvs[ i[ 7 ] - 1 ];
            v3.Normal = normals[ i[ 8 ] - 1 ];

            // Add the verts to the vector
            verts.push_back( v1 );
            verts.push_back( v2 );
            verts.push_back( v3 );

            // Add three more indices
            indices.push_back( triangleCounter++ );
            indices.push_back( triangleCounter++ );
            indices.push_back( triangleCounter++ );
        }
    }

    // Close the file
    obj.close();

    // - At this point, "verts" is a vector of Vertex structs, and can be used
    //    directly to create a vertex buffer:  &verts[0] is the first vert
    // - The vector "indices" is similar. It's a vector of unsigned ints and
    //    can be used directly for the index buffer: &indices[0] is the first int
    // - "triangleCounter" is BOTH the number of vertices and the number of indices

    mesh = std::make_shared<Mesh>( device, verts, indices );
    return mesh;
}