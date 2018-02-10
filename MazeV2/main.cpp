//
//  main.cpp
//  MazeV2
//
//  Created by Andrew Birnberg on 2/10/18.
//  Copyright © 2018 Andrew. All rights reserved.
//

#include <iostream>
#include <Eigen/Dense>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

using namespace Eigen;

#define mapWidth 24
#define mapHeight 24
#define width 1080
#define height 640

#define FONT_NAME "Courier New.ttf"

int worldMap[mapWidth][mapHeight]=
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void printText(std::string& text, SDL_Renderer *renderer, SDL_Rect *rect) {
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    SDL_Window *win;
    SDL_Renderer *renderer;
    enum {north, east, south, west};
    
    atexit(SDL_Quit);
    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (!(win = SDL_CreateWindow("MazeV2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0))) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (!(renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED))) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(win);
        exit(EXIT_FAILURE);
    }
    if (TTF_Init() == -1) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize fonts: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        exit(EXIT_FAILURE);
    }
    atexit(TTF_Quit);
    
    TTF_Font *font = TTF_OpenFont(FONT_NAME, 16);
    if (!font) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load font file [%s]: %s", FONT_NAME, TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        exit(EXIT_FAILURE);
    }
    
    SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0x00};
    SDL_Surface *textSurface;
    textSurface = TTF_RenderText_Solid(font, "Testing", textColor);
    if (!textSurface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load font file [%s]: %s", FONT_NAME, TTF_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        exit(EXIT_FAILURE);
    }
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    
    Vector2f pos(22, 12);
    Vector2f dir(-1, 0);
    Vector2f viewPlane(0, 2.0/3);

    double theta = M_PI / 90;
    Matrix2f rotleft, rotright;
    rotleft << std::cos(theta), -std::sin(theta),
               std::sin(theta), std::cos(theta);
    
    rotright << std::cos(-theta), -std::sin(-theta),
                std::sin(-theta), std::cos(-theta);
    bool done = false;
    
    while(!done) {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        for (int x = 0; x < width; x++) {
            double t = 2 * x / double(width) - 1;
            Vector2f ray = dir + viewPlane * t;
            Vector2d mapPos(pos(0), pos(1));
            Vector2f dDist = ray.cwiseAbs().cwiseInverse();
            bool hit = false;
            int side = 0;

            Vector2d stepDir;
            Vector2f sideDist;

            if (ray(0) < 0) {
                sideDist(0) = (pos(0) - mapPos(0)) * dDist(0);
                stepDir(0) = -1;
            } else {
                sideDist(0) = (mapPos(0) + 1.0 - pos(0)) * dDist(0);
                stepDir(0) = 1;
            }
            if (ray(1) < 0) {
                sideDist(1) = (pos(1) - mapPos(1)) * dDist(1);
                stepDir(1) = -1;
            } else {
                sideDist(1) = (mapPos(1) + 1.0 - pos(1)) * dDist(1);
                stepDir(1) = 1;
            }
            while (!hit) {
                std::ptrdiff_t i;
                sideDist.minCoeff(&i);
                side = int(i);
                sideDist(i) += dDist(i);
                mapPos(i) += stepDir(i);
                
                if (worldMap[int(mapPos(0))][int(mapPos(1))])
                    hit = true;
            }
            double perpWallDist;
            if (side == 0) perpWallDist = (mapPos(0) - pos(0) + (1 - stepDir(0)) / 2) / ray(0);
            else           perpWallDist = (mapPos(1) - pos(1) + (1 - stepDir(1)) / 2) / ray(1);
            
            int lineHeight = (int)(height / perpWallDist);
            
            //calculate lowest and highest pixel to fill in current stripe
            int drawStart = (height - lineHeight) / 2;
            if (drawStart < 0) drawStart = 0;
            int drawEnd = (lineHeight + height) / 2;
            if (drawEnd >= height) drawEnd = height- 1;
            
            int color = 0x8F;
            if (side == 1)
                color = 0x4D;
            
            SDL_SetRenderDrawColor(renderer, color, color, color, 0x00);
            SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
        }
        SDL_RenderPresent(renderer);
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                done = true;
            }
            double moveSpeed = 0.2;
            switch (e.key.keysym.sym) {
                case SDLK_q:
                    done = true;
                    break;
                case SDLK_LEFT:
                    dir = rotleft * dir;
                    viewPlane = rotleft * viewPlane;
                    break;
                case SDLK_RIGHT:
                    dir = rotright * dir;
                    viewPlane = rotright * viewPlane;
                    break;
                case SDLK_UP:
                    if (!worldMap[int(pos(0) + dir(0) * moveSpeed)][int(pos(1))])
                        pos(0) += dir(0) * moveSpeed;
                    if (!worldMap[int(pos(0))][int(pos(1) + dir(1) * moveSpeed)])
                        pos(1) += dir(1) * moveSpeed;
                    break;
                case SDLK_DOWN:
                    if (!worldMap[int(pos(0) + dir(0) * moveSpeed)][int(pos(1))])
                        pos(0) -= dir(0) * moveSpeed;
                    if (!worldMap[int(pos(0))][int(pos(1) + dir(1) * moveSpeed)])
                        pos(1) -= dir(1) * moveSpeed;
                    break;
            }
        }
    }
    TTF_CloseFont(font);
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
