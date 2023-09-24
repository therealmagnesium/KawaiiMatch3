#include "Tile.h"

Tile::Tile(Vector2 positionIn, const Texture2D& faceIn) : position(positionIn), face(faceIn)
{
    size = {TILE_SIZE, TILE_SIZE};
    body = {position.x, position.y, size.x, size.y};
    tint = {0xFF, 0xFF, 0xFF, 0xFF};
}

Tile::~Tile()
{
    UnloadTexture(face);
}

bool Tile::IsUnderMouse()
{
    return GetMouseX() >= position.x && GetMouseX() <= position.x + size.x && GetMouseY() >= position.y &&
           GetMouseY() <= position.y + size.y;
}

void Tile::Draw(const Texture2D& faceDownTexture)
{
    if (faceUp)
        DrawTexturePro(face, {0.f, 0.f, (float)face.width, (float)face.height}, body, {0.f, 0.f}, 0.f, tint);
    else
        DrawTexturePro(faceDownTexture, {0.f, 0.f, (float)face.width, (float)face.height}, body, {0.f, 0.f}, 0.f, tint);
}
