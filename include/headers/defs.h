#pragma once

const int SCREEN_HEIGHT   = 768;
const int SCREEN_WIDTH    = 432;
const int MULTIPLIER      =   3;

const int PIPE_UP_MAX_Y   = -10;
const int PIPE_UP_MIN_Y   = -80;
const int PIPE_DOWN_MAX_Y = 180;
const int PIPE_DOWN_MIN_Y = 140;
const int PIPE_GAP        = 190;

enum GAME_STATE{MAIN_MENU, PENDING,MODE_SELECTION , PLAY, DIE, QUIT};

const float timeStep = 0.01f;