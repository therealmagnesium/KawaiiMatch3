#include "Board.h"
#include "raylib.h"
#include <stdio.h>

#define CARD_FLIP_TIME_IN_SECS 1.0f

enum class MatchState
{
    Correct = 0,
    Incorrect
};

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

// Right and wrong match textures
static Texture2D incorrectMatchTexture;
static Texture2D correctMatchTexture;

static MatchState matchState = MatchState::Incorrect;
static std::vector<Tile*> cardsFlipped;

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

    // Load right and wrong match textures
    incorrectMatchTexture = LoadTexture("assets/textures/incorrect_match.png");
    correctMatchTexture = LoadTexture("assets/textures/correct_match.png");

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

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && cardsFlipped.size() < 2)
            {
                tiles[i]->faceUp = true;
                cardsFlipped.push_back(tiles[i]);

                if (cardsFlipped.size() == 2)
                    StartTimer(&timer, CARD_FLIP_TIME_IN_SECS);
            }
        }
    }
    if (cardsFlipped.size() == 2)
    {
        // Check for matches
        if (cardsFlipped[0]->face.id == cardsFlipped[1]->face.id)
        {
            cardsFlipped[0]->isMatch = true;
            cardsFlipped[1]->isMatch = true;
            matchState = MatchState::Correct;
        }
        UpdateTimer(&timer);
    }

    if (timer.hasStarted && IsTimerDone(&timer))
    {
        // If the card isn't a match, flip it back over
        for (int i = 0; i < tiles.size(); i++)
            if (!tiles[i]->isMatch)
                tiles[i]->faceUp = false;

        matchState = MatchState::Incorrect;
        cardsFlipped.clear();

        ResetTimer(&timer, CARD_FLIP_TIME_IN_SECS);
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

    // Show the correct texture if there was match or not
    if (timer.lifetime > 0.f && timer.hasStarted)
    {
        switch (matchState)
        {
        case MatchState::Correct:
        {
            Rectangle source, dest;
            source.x = source.y = 0;
            source.width = correctMatchTexture.width;
            source.height = correctMatchTexture.height;

            dest.width = 400;
            dest.height = 400;
            dest.x = 1280.f / 2 - dest.width / 2;
            dest.y = 720.f / 2 - dest.height / 2;

            DrawTexturePro(correctMatchTexture, source, dest, {0.f, 0.f}, 0.f, WHITE);

            break;
        }
        case MatchState::Incorrect:
        {
            Rectangle source, dest;
            source.x = source.y = 0;
            source.width = incorrectMatchTexture.width;
            source.height = incorrectMatchTexture.height;

            dest.width = 400;
            dest.height = 400;
            dest.x = 1280.f / 2 - dest.width / 2;
            dest.y = 720.f / 2 - dest.height / 2;

            DrawTexturePro(incorrectMatchTexture, source, dest, {0.f, 0.f}, 0.f, WHITE);
            break;
        }
        }
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

    UnloadTexture(incorrectMatchTexture);
    UnloadTexture(correctMatchTexture);

    // Unload textures from selected std::vector
    for (int i = 0; i < selected.size(); i++)
        UnloadTexture(selected[i]);
}
