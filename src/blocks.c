#include "blocks.h"
#include <rlgl.h>

// front
// back
// top
// bottom
// right
// left
// in that order, NEVER forget

static const Vector2 blockTexturePos[][6] = {
    [BLOCK_STONE] = {{0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}},
    [BLOCK_DIRT] = {{16.0f, 0.0f}, {16.0f, 0.0f}, {16.0f, 0.0f}, {16.0f, 0.0f}, {16.0f, 0.0f}, {16.0f, 0.0f}},
    [BLOCK_GRASS] {{32.0f, 0.0f}, {32.0f, 0.0f}, {48.0f, 0.0f}, {16.0f, 0.0f}, {32.0f, 0.0f}, {32.0f, 0.0f}},
    [BLOCK_BEDROCK] {{64.0f, 0.0f}, {64.0f, 0.0f}, {64.0f, 0.0f}, {64.0f, 0.0f}, {64.0f, 0.0f}, {64.0f, 0.0f}},
};

void draw_block(Texture2D texture, block_t block, Vector3 position, float width, float height, float length){
    if(block >= BLOCK_END_OF_ENUM || block == BLOCK_AIR) return;
    float x = position.x;
    float y = position.y;
    float z = position.z;
    float texWidth = (float)texture.width;
    float texHeight = (float)texture.height;

    Vector2 frontSource = blockTexturePos[block][0];
    Vector2 backSource = blockTexturePos[block][1];
    Vector2 topSource = blockTexturePos[block][2];
    Vector2 bottomSource = blockTexturePos[block][3];
    Vector2 rightSource = blockTexturePos[block][4];
    Vector2 leftSource = blockTexturePos[block][5];
    rlSetTexture(texture.id);

    rlBegin(RL_QUADS);
        rlColor4ub(255, 255, 255, 255);

        // front
        rlNormal3f(0.0f, 0.0f, 1.0f);

        rlTexCoord2f(frontSource.x/texWidth, (frontSource.y + 16.0f)/texHeight);
        rlVertex3f(x - width/2, y - height/2, z + length/2);

        rlTexCoord2f((frontSource.x + 16.0f)/texWidth, (frontSource.y + 16.0f)/texHeight);
        rlVertex3f(x + width/2, y - height/2, z + length/2);

        rlTexCoord2f((frontSource.x + 16.0f)/texWidth, frontSource.y/texHeight);
        rlVertex3f(x + width/2, y + height/2, z + length/2);

        rlTexCoord2f(frontSource.x/texWidth, frontSource.y/texHeight);
        rlVertex3f(x - width/2, y + height/2, z + length/2);

        // back
        rlNormal3f(0.0f, 0.0f, - 1.0f);

        rlTexCoord2f((backSource.x + 16.0f)/texWidth, (backSource.y + 16.0f)/texHeight);
        rlVertex3f(x - width/2, y - height/2, z - length/2);

        rlTexCoord2f((backSource.x + 16.0f)/texWidth, backSource.y/texHeight);
        rlVertex3f(x - width/2, y + height/2, z - length/2);

        rlTexCoord2f(backSource.x/texWidth, backSource.y/texHeight);
        rlVertex3f(x + width/2, y + height/2, z - length/2);

        rlTexCoord2f(backSource.x/texWidth, (backSource.y + 16.0f)/texHeight);
        rlVertex3f(x + width/2, y - height/2, z - length/2);

        // top
        rlNormal3f(0.0f, 1.0f, 0.0f);

        rlTexCoord2f(topSource.x/texWidth, topSource.y/texHeight);
        rlVertex3f(x - width/2, y + height/2, z - length/2);

        rlTexCoord2f(topSource.x/texWidth, (topSource.y + 16.0f)/texHeight);
        rlVertex3f(x - width/2, y + height/2, z + length/2);

        rlTexCoord2f((topSource.x + 16.0f)/texWidth, (topSource.y + 16.0f)/texHeight);
        rlVertex3f(x + width/2, y + height/2, z + length/2);

        rlTexCoord2f((topSource.x + 16.0f)/texWidth, topSource.y/texHeight);
        rlVertex3f(x + width/2, y + height/2, z - length/2);

        // bottom
        rlNormal3f(0.0f, - 1.0f, 0.0f);

        rlTexCoord2f((bottomSource.x + 16.0f)/texWidth, bottomSource.y/texHeight);
        rlVertex3f(x - width/2, y - height/2, z - length/2);

        rlTexCoord2f(bottomSource.x/texWidth, bottomSource.y/texHeight);
        rlVertex3f(x + width/2, y - height/2, z - length/2);

        rlTexCoord2f(bottomSource.x/texWidth, (bottomSource.y + 16.0f)/texHeight);
        rlVertex3f(x + width/2, y - height/2, z + length/2);

        rlTexCoord2f((bottomSource.x + 16.0f)/texWidth, (bottomSource.y + 16.0f)/texHeight);
        rlVertex3f(x - width/2, y - height/2, z + length/2);

        // right
        rlNormal3f(1.0f, 0.0f, 0.0f);

        rlTexCoord2f((rightSource.x + 16.0f)/texWidth, (rightSource.y + 16.0f)/texHeight);
        rlVertex3f(x + width/2, y - height/2, z - length/2);

        rlTexCoord2f((rightSource.x + 16.0f)/texWidth, rightSource.y/texHeight);
        rlVertex3f(x + width/2, y + height/2, z - length/2);

        rlTexCoord2f(rightSource.x/texWidth, rightSource.y/texHeight);
        rlVertex3f(x + width/2, y + height/2, z + length/2);

        rlTexCoord2f(rightSource.x/texWidth, (rightSource.y + 16.0f)/texHeight);
        rlVertex3f(x + width/2, y - height/2, z + length/2);

        // left
        rlNormal3f( - 1.0f, 0.0f, 0.0f);

        rlTexCoord2f(leftSource.x/texWidth, (leftSource.y + 16.0f)/texHeight);
        rlVertex3f(x - width/2, y - height/2, z - length/2);

        rlTexCoord2f((leftSource.x + 16.0f)/texWidth, (leftSource.y + 16.0f)/texHeight);
        rlVertex3f(x - width/2, y - height/2, z + length/2);

        rlTexCoord2f((leftSource.x + 16.0f)/texWidth, leftSource.y/texHeight);
        rlVertex3f(x - width/2, y + height/2, z + length/2);

        rlTexCoord2f(leftSource.x/texWidth, leftSource.y/texHeight);
        rlVertex3f(x - width/2, y + height/2, z - length/2);

    rlEnd();

    rlSetTexture(0);
}

Vector2 get_block_face_texture(block_t block, blockface_t face){
    if(block >= BLOCK_END_OF_ENUM || block == BLOCK_AIR) return (Vector2){0};
    if(face >= BLOCKFACE_END_OF_ENUM) return (Vector2){0};
    return blockTexturePos[block][face];
}
