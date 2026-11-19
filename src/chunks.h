#ifndef CHUNKS_H_INCLUDED
#define CHUNKS_H_INCLUDED







#include <raylib.h>


#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 255

#include "blocks.h"

typedef struct chunk {
    block_t blocks[CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z];
    Mesh mesh;
    int index;
} chunk_t;








#endif
