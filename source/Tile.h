#pragma once
#include <raylib.h>

#define TILE_SIZE 128

struct Tile
{
    bool faceUp = false;
    Vector2 position;
    Vector2 size;
    Rectangle body;
    Color tint;
    Texture2D face;

    Tile(Vector2 positionIn);
    ~Tile();

    bool IsUnderMouse();
    void Draw(const Texture2D& faceDownTexture);
};
