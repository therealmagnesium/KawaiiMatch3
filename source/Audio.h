#pragma once
#define PLAYLIST_LENGTH 5

#include "Types.h"
#include <raylib.h>

enum class Songs
{
    AIRLAND_JAZZ = 0,
    GLASS_OF_WINE,
    LETTER_FROM_BRAZIL,
    MAGIC_IN_YOU,
    SONA_CITY
};

struct Playlist
{
    u8 currentSongIndex = 0;
    Music songs[PLAYLIST_LENGTH];

    void LoadSongs();
    void UnloadSongs();
    void Update();
    void DisplayCurrentSongInfo(const Font& font);

    inline Music GetCurrentSong()
    {
        return songs[currentSongIndex];
    }
};

void HandleAudioChanges(const Music& currentSong, bool paused);
void ProcessLowpassFilterEffect(void* buffer, u32 frames);
