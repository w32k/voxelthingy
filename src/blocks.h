#ifndef BLOCKS_H_INCLUDED
#define BLOCKS_H_INCLUDED






#include <raylib.h>

#define BLOCK_SIZE 1.0f

typedef enum block {
    BLOCK_AIR,
    BLOCK_STONE,
    BLOCK_DIRT,
    BLOCK_GRASS,
    BLOCK_BEDROCK,

    BLOCK_END_OF_ENUM
} block_t;

typedef enum blockface {
    BLOCKFACE_FRONT,
    BLOCKFACE_BACK,
    BLOCKFACE_TOP,
    BLOCKFACE_BOTTOM,
    BLOCKFACE_RIGHT,
    BLOCKFACE_LEFT,
    BLOCKFACE_END_OF_ENUM
} blockface_t;


Vector2 get_block_face_texture(block_t block, blockface_t face);
void draw_block(Texture2D texture, block_t block, Vector3 position, float width, float height, float length);












#endif
