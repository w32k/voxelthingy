#include "chunks.h"
#include <stdlib.h>
#define TEX_SIZE 16.0f
#define TEX_IMAGE_SIZE 128.0f // TODO: don't be a lazy stupid chud

static void add_vertex_to_mesh(Mesh* mesh, int index, Vector3 vertices, Vector3 normals, Vector2 texCoords){
    int vertexIndex = index * 3;
    int normalIndex = index * 3;
    int texIndex = index * 2;
    mesh->vertices[vertexIndex] = vertices.x;
    mesh->vertices[vertexIndex + 1] = vertices.y;
    mesh->vertices[vertexIndex + 2] = vertices.z;

    mesh->normals[normalIndex] = normals.x;
    mesh->normals[normalIndex + 1] = normals.y;
    mesh->normals[normalIndex + 2] = normals.z;

    mesh->texcoords[texIndex] = texCoords.x;
    mesh->texcoords[texIndex + 1] = texCoords.y;
}

static void add_face_to_block(Mesh* mesh, blockface_t bFace, int* index, Vector3 pos, Vector2 texCoords){
    Vector3 normal;
    Vector3 v[4];
    Vector2 t[4];
    mesh->triangleCount += 2;
    mesh->vertexCount = mesh->triangleCount * 3;
    switch(bFace){
        case BLOCKFACE_FRONT:{
            normal = (Vector3){0.0f, 0.0f, 1.0f};
            t[0] = (Vector2){(texCoords.x) / TEX_IMAGE_SIZE, (texCoords.y + TEX_SIZE) / TEX_IMAGE_SIZE};
            v[0] = (Vector3){pos.x - BLOCK_SIZE / 2, pos.y - BLOCK_SIZE / 2, pos.z + BLOCK_SIZE / 2};
            t[1] = (Vector2){(texCoords.x + TEX_SIZE) / TEX_IMAGE_SIZE, (texCoords.y + TEX_SIZE) / TEX_IMAGE_SIZE};
            v[1] = (Vector3){pos.x + BLOCK_SIZE / 2, pos.y - BLOCK_SIZE / 2, pos.z + BLOCK_SIZE / 2};
            t[2] = (Vector2){(texCoords.x + TEX_SIZE) / TEX_IMAGE_SIZE, (texCoords.y) / TEX_IMAGE_SIZE};
            v[2] = (Vector3){pos.x + BLOCK_SIZE / 2, pos.y + BLOCK_SIZE / 2, pos.z + BLOCK_SIZE / 2};
            t[3] = (Vector2){(texCoords.x) / TEX_IMAGE_SIZE, (texCoords.y) / TEX_IMAGE_SIZE};
            v[3] = (Vector3){pos.x - BLOCK_SIZE / 2, pos.y + BLOCK_SIZE / 2, pos.z + BLOCK_SIZE / 2};
            break;
        }
        case BLOCKFACE_BACK:{
            normal = (Vector3){0.0f, 0.0f, -1.0f};
            t[0] = (Vector2){(texCoords.x + TEX_SIZE) / TEX_IMAGE_SIZE, (texCoords.y + TEX_SIZE) / TEX_IMAGE_SIZE};
            v[0] = (Vector3){pos.x - BLOCK_SIZE / 2, pos.y - BLOCK_SIZE / 2, pos.z - BLOCK_SIZE / 2};
            v[1] = (Vector3){pos.x - BLOCK_SIZE / 2, pos.y + BLOCK_SIZE / 2, pos.z - BLOCK_SIZE / 2};
            v[2] = (Vector3){pos.x + BLOCK_SIZE / 2, pos.y + BLOCK_SIZE / 2, pos.z - BLOCK_SIZE / 2};
            v[3] = (Vector3){pos.x + BLOCK_SIZE / 2, pos.y - BLOCK_SIZE / 2, pos.z - BLOCK_SIZE / 2};
            break;
        }
        case BLOCKFACE_TOP:{
            normal = (Vector3){0.0f, 1.0f, 0.0f};
            v[0] = (Vector3){pos.x - BLOCK_SIZE / 2, pos.y + BLOCK_SIZE / 2, pos.z - BLOCK_SIZE / 2};
            v[1] = (Vector3){pos.x - BLOCK_SIZE / 2, pos.y + BLOCK_SIZE / 2, pos.z + BLOCK_SIZE / 2};
            v[2] = (Vector3){pos.x + BLOCK_SIZE / 2, pos.y + BLOCK_SIZE / 2, pos.z + BLOCK_SIZE / 2};
            v[3] = (Vector3){pos.x - BLOCK_SIZE / 2, pos.y + BLOCK_SIZE / 2, pos.z - BLOCK_SIZE / 2};
            break;
        }
        case BLOCKFACE_BOTTOM:{
            normal = (Vector3){0.0f, -1.0f, 0.0f};
            v[0] = (Vector3){pos.x - BLOCK_SIZE / 2, pos.y - BLOCK_SIZE / 2, pos.z - BLOCK_SIZE / 2};
            v[1] = (Vector3){pos.x - BLOCK_SIZE / 2, pos.y - BLOCK_SIZE / 2, pos.z + BLOCK_SIZE / 2};
            v[2] = (Vector3){pos.x + BLOCK_SIZE / 2, pos.y - BLOCK_SIZE / 2, pos.z + BLOCK_SIZE / 2};
            v[3] = (Vector3){pos.x - BLOCK_SIZE / 2, pos.y - BLOCK_SIZE / 2, pos.z - BLOCK_SIZE / 2};
            break;
        }
        case BLOCKFACE_RIGHT:{
            normal = (Vector3){1.0f, 0.0f, 0.0f};
            v[0] = (Vector3){pos.x + BLOCK_SIZE / 2, pos.y - BLOCK_SIZE / 2, pos.z - BLOCK_SIZE / 2};
            v[1] = (Vector3){pos.x + BLOCK_SIZE / 2, pos.y + BLOCK_SIZE / 2, pos.z - BLOCK_SIZE / 2};
            v[2] = (Vector3){pos.x + BLOCK_SIZE / 2, pos.y + BLOCK_SIZE / 2, pos.z + BLOCK_SIZE / 2};
            v[3] = (Vector3){pos.x + BLOCK_SIZE / 2, pos.y - BLOCK_SIZE / 2, pos.z + BLOCK_SIZE / 2};
            break;
        }
        case BLOCKFACE_LEFT:{
            normal = (Vector3){-1.0f, 0.0f, 0.0f};
            v[0] = (Vector3){pos.x + BLOCK_SIZE / 2, pos.y - BLOCK_SIZE / 2, pos.z - BLOCK_SIZE / 2};
            v[1] = (Vector3){pos.x + BLOCK_SIZE / 2, pos.y + BLOCK_SIZE / 2, pos.z - BLOCK_SIZE / 2};
            v[2] = (Vector3){pos.x + BLOCK_SIZE / 2, pos.y + BLOCK_SIZE / 2, pos.z + BLOCK_SIZE / 2};
            v[3] = (Vector3){pos.x + BLOCK_SIZE / 2, pos.y - BLOCK_SIZE / 2, pos.z + BLOCK_SIZE / 2};
            break;
        }
        default:{
            return;
        }
    }
    for(int i = 0; i < 4; i++){
        add_vertex_to_mesh(mesh, *index, v[0], normal, t[0]);
        (*index)++;
    }

    index++;
}

static void add_block_to_chunk(chunk_t* chunk, block_t block, Vector3 pos){
    for(int i = 0; i < BLOCKFACE_END_OF_ENUM; i++){
        add_face_to_block(&chunk->mesh, i, &chunk->index, pos, (Vector2){0.0f, 0.0f});
    }
}


void build_chunk_mesh(chunk_t* chunk){

}
