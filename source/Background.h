#pragma once
#include <raylib.h>

struct WindowData;

// Wrapper shader used to draw the background
struct BGShader
{
    Shader shader;
    Texture2D texture;
    int timeLocation;
    int particleColorLocation;
};

struct PauseShader
{
    Shader shader;
    Texture2D texture;
};

BGShader SetupBackground(const WindowData& data);
void UpdateBackground(const BGShader& bgShader, float* time);
void CleanBackground(const BGShader& bgShader);

PauseShader SetupPauseShader(const WindowData& data);
void CleanPauseShader(const PauseShader& pauseShader);
