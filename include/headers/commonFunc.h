#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include "defs.h"

namespace commonFunc
{
    inline bool isCollide(Entity a, Entity b)
    {
        float left_a   = a.GetPos().GetX();
        float right_a  = a.GetPos().GetX() + (float)a.GetCurrFrame().w;
        float top_a    = a.GetPos().GetY();
        float bottom_a = a.GetPos().GetY()+ (float)a.GetCurrFrame().h;

        float left_b   = b.GetPos().GetX();
        float right_b  = b.GetPos().GetX() + (float)b.GetCurrFrame().w;
        float top_b    = b.GetPos().GetY();
        float bottom_b = b.GetPos().GetY()+ (float)b.GetCurrFrame().h; 
        

        if (right_a >= left_b && left_a <= right_b && bottom_a >= top_b && top_a <= bottom_b)
        {
            return true;
        }
        return false;
    }

    inline bool isCollide(Vector a, Entity b)
    {
        float a_x = a.GetX();
        float a_y = a.GetY();

        float left_b   = b.GetPos().GetX();
        float right_b  = b.GetPos().GetX() + (float)b.GetCurrFrame().w;
        float top_b    = b.GetPos().GetY();
        float bottom_b = b.GetPos().GetY()+ (float)b.GetCurrFrame().h; 

        if(a_x >= left_b  && a_x <= right_b && a_y >= top_b && a_y <= bottom_b )
        {
            return true;
        }
        return false;
    }

    inline int getRandomValues(int p_min, int p_max)
    {
        return (rand() % (p_max - p_min + 1)) + p_min;
    }
    inline float getRandomFloat(float p_min, float p_max) 
    {
        float scaledRandom = (float)(rand()) / RAND_MAX;

        return p_min + scaledRandom * (p_max - p_min);
    }
    inline bool CheckPass(Entity entity, float x_pos, float y_pos, float value = PIPE_GAP)
    {
        float left_e = entity.GetPos().GetX();
        float right_e = left_e + entity.GetCurrFrame().w;

        float top_e = entity.GetPos().GetY();
        float bot_e = top_e + entity.GetCurrFrame().h;

        return (right_e >= x_pos && left_e <= x_pos+1) && (bot_e >= y_pos - value && top_e <= y_pos);
    }
    inline void HighScoreInOut(int &highScore, int &currScore, bool isClassic)
    {
        std::string path;
        if (isClassic)
        {
             path = "res/HighScoreClassic.txt";
        } else
        {
            path = "res/HighScoreHell.txt";
        }
        
        std::ifstream inFile(path);
		if (inFile.is_open()) {
			inFile >> highScore;
			inFile.close();
		} else {
			std::cerr << "Unable to open file for reading high score. Assuming zero.\n";
		}
		if (currScore > highScore)
		{
			std::ofstream outFile(path);
			if (outFile.is_open()) {
				outFile << currScore;
				outFile.close();
			} else {
				std::cerr << "Unable to open file for writing high score.\n";
    		}
		}
    }
    inline void CoinIn(int& totalCoin)
    {
        std::ifstream inFileCoin("res/Coin.txt");
	    if (inFileCoin.is_open()) {
	    	inFileCoin >> totalCoin;
	    	inFileCoin.close();
	    } else {
	    	std::cerr << "Unable to open file for coins.\n";
	    }
    }
    inline void CoinOut(int &totalCoin)
    {
        std::ofstream outFileCoin("res/Coin.txt");
		if (outFileCoin.is_open()) {
			outFileCoin << totalCoin;
			outFileCoin.close();
		} else {
			std::cerr << "Unable to open file for coin.\n";
    	}
    }
    inline void PriceIn(std::vector<int>& price)
    {
        std::ifstream inFilePrice("res/Price.txt");
		if (inFilePrice.is_open())
		{
			int n;
			int i = 0;
			while (inFilePrice >> n)
			{
				price[i++] = n;
			}
			inFilePrice.close();
		}  else {
			std::cerr << "Unable to open file for price.\n";
		}
    }
} // namespace commonFunc
