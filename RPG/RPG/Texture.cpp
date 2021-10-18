#include "Texture.h"

Texture::Texture() {
    init();
}

Texture::Texture(std::string path) {
    init();
    filePath = path;
}

void Texture::init() {
    filePath = "";
    height = 0;
    width = 0;
    texture = NULL;
}

Texture::~Texture() {
    free();
}

void Texture::free() {

    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
    width = 0;
    height = 0;
    filePath = "";
}

bool Texture::resize(int newHeight, int newWidth) {
    height = newHeight;
    width = newWidth;
    return true;
}
