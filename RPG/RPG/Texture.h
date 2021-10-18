#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture
{
public:
    //attributes
    std::string filePath;
    int height;
    int width;
    SDL_Texture* texture;

    //constructors
    Texture(std::string path);
    Texture();

    //destructor
    ~Texture();

    //methods
    void free();
    bool resize(int newHeight, int newWidth);

private:
    //methods
    void init();
};

