//#include "ImageLoader.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/**
    Initialize image loader. Call before anything else here!
*/
bool initImageLoader(){
    int flags = IMG_INIT_PNG;
    if(!(IMG_Init(flags) & flags)){
        cerr << "IMG_Init failed: " << IMG_GetError() << endl;
        return false;
    }
    return true;
}


/**
    Load list of images contained in file res/img/images.cfg.
    Image paths are relative to res/img/.
*/
vector<SDL_Texture*> loadImages(SDL_Renderer* renderer){
    vector<SDL_Texture*> textures;

    //Open config file
    ifstream in;
    in.open("res/img/images.cfg");
    string imgpath;

    //Read the file line by line
    while(getline(in, imgpath)){
        //Load image as a surface
        SDL_Surface *img = IMG_Load(("res/img/" + imgpath).c_str());
        if(img == nullptr){
            cerr << "IMG_Load failed: " << IMG_GetError() << endl;
            continue;
        }

        //Create a texture from the image just loaded
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, img);
        if(tex == nullptr){
            cerr << "IMG_CreateTextureFromSurface failed: " << SDL_GetError() << endl;
            continue;
        }
        //Free the now unneeded surface
        SDL_FreeSurface(img);
        //Add it to the texture vector
        textures.push_back(tex);
    }
    return textures;
}
