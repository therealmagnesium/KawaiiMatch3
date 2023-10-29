#include "Background.h"
#include "Types.h"

BGShader SetupBackground(const WindowData& data)
{
    BGShader returnVal;
    Vector3 particleColor = {0.06f, 0.27f, 0.36f};

    // Generate the texture from the image buffer, then unload the temp image
    Image tempImage = GenImageColor(data.width + 220, data.width + 220, BLANK);
    returnVal.texture = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);

    // Set the base shader and set the uniform locations
    returnVal.shader = LoadShader(NULL, "assets/shaders/BackgroundFrag.glsl");
    returnVal.timeLocation = GetShaderLocation(returnVal.shader, "uTime");
    returnVal.particleColorLocation = GetShaderLocation(returnVal.shader, "uParticleColor");

    SetShaderValue(returnVal.shader, returnVal.particleColorLocation, &particleColor, SHADER_UNIFORM_VEC3);

    return returnVal;
}

void UpdateBackground(const BGShader& bgShader, float* time)
{
    SetShaderValue(bgShader.shader, bgShader.timeLocation, time, SHADER_UNIFORM_FLOAT);
}

void CleanBackground(const BGShader& bgShader)
{
    UnloadShader(bgShader.shader);
}

PauseShader SetupPauseShader(const WindowData& data)
{
    PauseShader returnVal;

    // Generate the texture from the image buffer, then unload the temp image
    Image tempImage = GenImageColor(data.width, data.height, BLANK);
    returnVal.texture = LoadTextureFromImage(tempImage);
    UnloadImage(tempImage);

    returnVal.shader = LoadShader(NULL, "assets/shaders/PauseFrag.glsl");

    return returnVal;
}

void CleanPauseShader(const PauseShader& pauseShader)
{
    UnloadShader(pauseShader.shader);
}
