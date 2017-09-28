#ifndef IMAGELOADER_H_INCLUDED
#define IMAGELOADER_H_INCLUDED

bool initImageLoader();
std::vector<SDL_Texture*> loadImages(SDL_Renderer*);

#endif // IMAGELOADER_H_INCLUDED
