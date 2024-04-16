#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include<unordered_map>
#include<defs.h>


const int SCREEN_HEIGHT   = 768;
const int SCREEN_WIDTH    = 432;
const int MULTIPLIER      =   3;

const int PIPE_UP_MAX_Y   = -10;
const int PIPE_UP_MIN_Y   = -100;
const int PIPE_GAP        = 70;

enum GAME_STATE{MAIN_MENU, PENDING,MODE_SELECTION, MUSIC_MANAGER ,SHOP, PLAY, PAUSE, DIE, QUIT};
enum GAME_MODE{CLASSIC_MODE, HELL_MODE};
enum SOUND {JUMP, COIN_HIT, PIPE_HIT, PLAYER_DIE, TOTAL_CHUNK};
enum CHARACTER {CAT,BREAD, HAMBURGER ,TOTAL_CHAR};

const float timeStep  = 0.01f;
const float scoreStep = 1.f;

const SDL_Color white = {255,255,255};
const SDL_Color black = {0,0,0};

