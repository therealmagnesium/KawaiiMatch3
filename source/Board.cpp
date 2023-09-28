#include "Board.h"
#include <stdio.h>

// A bunch of card face textures
static Texture2D bearTexture;
static Texture2D bunnyTexture;
static Texture2D catTexture;
static Texture2D cowTexture;
static Texture2D dogTexture;
static Texture2D horseTexture;
static Texture2D mouseTexture;
static Texture2D pandaTexture;
static Texture2D pigTexture;
static Texture2D wolfTexture;

static void LoadTileTextures(Texture2D textureArray[BOARD_TEXTURE_AMOUNT], Texture2D* faceDown)
{
    // Load card face textures
    bearTexture = LoadTexture("assets/textures/bear.png");
    bunnyTexture = LoadTexture("assets/textures/bunny.png");
    catTexture = LoadTexture("assets/textures/cat.png");
    cowTexture = LoadTexture("assets/textures/cow.png");
    dogTexture = LoadTexture("assets/textures/dog.png");
    horseTexture = LoadTexture("assets/textures/horse.png");
    mouseTexture = LoadTexture("assets/textures/mouse.png");
    pandaTexture = LoadTexture("assets/textures/panda.png");
    pigTexture = LoadTexture("assets/textures/pig.png");
    wolfTexture = LoadTexture("assets/textures/wolf.png");

    // Load the face down texture
    *faceDown = LoadTexture("assets/textures/leaf.png");

    // Set textureArray's elements to the card face textures
    textureArray[0] = bearTexture;
    textureArray[1] = bunnyTexture;
    textureArray[2] = catTexture;
    textureArray[3] = cowTexture;
    textureArray[4] = dogTexture;
    textureArray[5] = horseTexture;
    textureArray[6] = mouseTexture;
    textureArray[7] = pandaTexture;
    textureArray[8] = pigTexture;
    textureArray[9] = wolfTexture;
}

void Board::Setup(u32 windowWidth, u32 windowHeight)
{
    // Calculate the offset to set the board in the center of the screen
    tileOffset.x = windowWidth / 2.f - (BOARD_COLS * TILE_SIZE) / 2.f;
    tileOffset.y = windowHeight / 2.f - (BOARD_ROWS * TILE_SIZE) / 2.f;

    // Place the tiles on the board
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            Vector2 position = {j * (TILE_SIZE + 8) + tileOffset.x, i * (TILE_SIZE + 8) + tileOffset.y};
            Tile* tile = new Tile(position, selected.back());
            selected.pop_back();
            tiles.push_back(tile);
        }
    }
}

void Board::Fill()
{
    LoadTileTextures(faces, &faceDownTexture);
    facesLength = BOARD_TEXTURE_AMOUNT;

    // Choose two copies of each card from a random index in the faces array
    for (int i = 0; i < BOARD_TEXTURE_AMOUNT; i++)
    {
        int randomIndex = rand() % facesLength;
        Texture2D face = faces[randomIndex];

        selected.push_back(face);
        selected.push_back(face);

        for (int j = randomIndex; j < BOARD_TEXTURE_AMOUNT; j++)
            faces[j] = faces[j + 1];

        facesLength--;
    }
}

void Board::Shuffle()
{
    // Basically do a Fisher-Yates shuffle
    int counter = selected.size();

    while (counter > 0)
    {
        int randomIndex = rand() % counter;
        counter--;

        Texture2D temp = selected[counter];
        selected[counter] = selected[randomIndex];
        selected[randomIndex] = temp;
    }
}

void Board::Update()
{
    // Handle events from the user
    for (int i = 0; i < tiles.size(); i++)
    {
        tiles[i]->tint = {0xFF, 0xFF, 0xFF, 0xFF};

        if (tiles[i]->IsUnderMouse() && !tiles[i]->faceUp)
        {
            tiles[i]->tint = {0xDD, 0xDD, 0xDD, 0xFF};

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                tiles[i]->faceUp = true;
        }
    }
}

void Board::Draw()
{
    // Draw all the card tiles
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i])
            tiles[i]->Draw(faceDownTexture);
    }
}

void Board::Clean()
{
    // FREE ALLOCATED MEMORY
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i])
            delete tiles[i];
    }

    // Unload textures from selected std::vector
    for (int i = 0; i < selected.size(); i++)
        UnloadTexture(selected[i]);
}
