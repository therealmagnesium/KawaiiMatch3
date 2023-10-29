#include "Audio.h"

static float songInfoFontSize = 32.f;
static float songInfoFontSpacing = 2.f;
static Vector2 songInfoPosition = (Vector2){10.f, 10.f};

void Playlist::LoadSongs()
{
    currentSongIndex = rand() % PLAYLIST_LENGTH;

    songs[(u8)Songs::AIRLAND_JAZZ] = LoadMusicStream("assets/audio/music/airland-jazz.mp3");
    songs[(u8)Songs::GLASS_OF_WINE] = LoadMusicStream("assets/audio/music/glass-of-wine.mp3");
    songs[(u8)Songs::LETTER_FROM_BRAZIL] = LoadMusicStream("assets/audio/music/letter-from-brazil.mp3");
    songs[(u8)Songs::MAGIC_IN_YOU] = LoadMusicStream("assets/audio/music/magic-in-you-jazz.mp3");
    songs[(u8)Songs::SONA_CITY] = LoadMusicStream("assets/audio/music/sona-city.mp3");

    for (int i = 0; i < PLAYLIST_LENGTH; i++)
        songs[i].looping = false;
}

void Playlist::UnloadSongs()
{
    for (int i = 0; i < PLAYLIST_LENGTH; i++)
        UnloadMusicStream(songs[i]);
}

void Playlist::Update()
{
    UpdateMusicStream(songs[currentSongIndex]);

    if (!IsMusicStreamPlaying(songs[currentSongIndex]))
    {
        currentSongIndex = rand() % PLAYLIST_LENGTH;

        if (IsMusicReady(songs[currentSongIndex]))
            PlayMusicStream(songs[currentSongIndex]);
    }
}

void Playlist::DisplayCurrentSongInfo(const Font& font)
{
    switch (currentSongIndex)
    {
    case (u8)Songs::AIRLAND_JAZZ:
        DrawTextEx(font, "Currently playing 'Airland'", songInfoPosition, songInfoFontSize, songInfoFontSpacing,
                   PURPLE);
        break;
    case (u8)Songs::GLASS_OF_WINE:
        DrawTextEx(font, "Currently playing 'Glass of Wine'", songInfoPosition, songInfoFontSize, songInfoFontSpacing,
                   PURPLE);
        break;
    case (u8)Songs::LETTER_FROM_BRAZIL:
        DrawTextEx(font, "Currently playing 'Letter from Brazil'", songInfoPosition, songInfoFontSize,
                   songInfoFontSpacing, PURPLE);
        break;
    case (u8)Songs::MAGIC_IN_YOU:
        DrawTextEx(font, "Currently playing 'Magic in You'", songInfoPosition, songInfoFontSize, songInfoFontSpacing,
                   PURPLE);
        break;
    case (u8)Songs::SONA_CITY:
        DrawTextEx(font, "Currently playing 'Sona City'", songInfoPosition, songInfoFontSize, songInfoFontSpacing,
                   PURPLE);
        break;
    }
}

void HandleAudioChanges(const Music& currentSong, bool paused)
{
    if (paused)
        AttachAudioStreamProcessor(currentSong.stream, ProcessLowpassFilterEffect);
    else
        DetachAudioStreamProcessor(currentSong.stream, ProcessLowpassFilterEffect);
}

void ProcessLowpassFilterEffect(void* buffer, u32 frames)
{
    static float low[2] = {0.0f, 0.0f};
    static const float cutoff = 70.0f / 44100.0f;      // 70 Hz lowpass filter
    const float k = cutoff / (cutoff + 0.1591549431f); // RC filter formula

    for (unsigned int i = 0; i < frames * 2; i += 2)
    {
        float l = ((float*)buffer)[i], r = ((float*)buffer)[i + 1];
        low[0] += k * (l - low[0]);
        low[1] += k * (r - low[1]);
        ((float*)buffer)[i] = low[0];
        ((float*)buffer)[i + 1] = low[1];
    }
}
