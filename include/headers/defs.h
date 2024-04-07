#pragma once

const int SCREEN_HEIGHT   = 768;
const int SCREEN_WIDTH    = 432;
const int MULTIPLIER      =   3;

const int PIPE_UP_MAX_Y   = -10;
const int PIPE_UP_MIN_Y   = -90;
const int PIPE_DOWN_MAX_Y = 180;
const int PIPE_DOWN_MIN_Y = 140;
const int PIPE_GAP        = 50;

enum GAME_STATE{MAIN_MENU, PENDING,MODE_SELECTION, PLAY, PAUSE, DIE, QUIT};
enum GAME_MODE{CLASSIC_MODE, HELL_MODE};

const float timeStep = 0.01f;
const float scoreStep = 1.f;

const SDL_Color white = {255,255,255};

