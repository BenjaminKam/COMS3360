#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include "helper.h"
#include "hittable.h"
#include "hittable_list.h"
#include "bvh.h"
#include "triangle.h"
#include "material.h"

// Disable strict warnings for this header from the Microsoft Visual C++ compiler.
#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#define TINYOBJLOADER_IMPLEMENTATION
#include "external/tiny_obj_loader.h"

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <iostream>

shared_ptr<hittable> load_obj_mesh(const std::string &filename, shared_ptr<material> mat)
{
    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(filename))
    {
        std::cerr << "Error loading OBJ: " << reader.Error() << std::endl;
        return nullptr;
    }

    auto &attrib = reader.GetAttrib();
    auto &shapes = reader.GetShapes();

    auto mesh = make_shared<hittable_list>();

    for (const auto &shape : shapes)
    {
        size_t index_offset = 0;

        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
        {
            size_t fv = shape.mesh.num_face_vertices[f];

            // Only handle triangles (fv == 3)
            if (fv == 3)
            {
                point3 vertices[3];
                vec2 uvs[3];

                for (size_t v = 0; v < 3; v++)
                {
                    tinyobj::index_t idx = shape.mesh.indices[index_offset + v];

                    vertices[v] = point3(
                        attrib.vertices[3 * idx.vertex_index + 0],
                        attrib.vertices[3 * idx.vertex_index + 1],
                        attrib.vertices[3 * idx.vertex_index + 2]);

                    if (idx.texcoord_index >= 0)
                    {
                        uvs[v] = vec2(
                            attrib.texcoords[2 * idx.texcoord_index + 0],
                            1.0 - attrib.texcoords[2 * idx.texcoord_index + 1]);
                    }
                    else
                    {
                        uvs[v] = vec2(0, 0);
                    }
                }

                mesh->add(make_shared<triangle>(
                    vertices[0], vertices[1], vertices[2],
                    uvs[0], uvs[1], uvs[2],
                    mat));
            }

            index_offset += fv;
        }
    }

    return make_shared<bvh_node>(*mesh);
}

#endif