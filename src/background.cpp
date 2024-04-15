#include<headers/background.h>

Background::Background(Vector p_pos, SDL_Texture* p_tex,float p_scrollSpeed)
	:Entity(p_pos, p_tex), scrollSpeed(p_scrollSpeed)
{}

void Background::Update()
{
	SetPos(Vector(GetPos().GetX() - scrollSpeed, GetPos().GetY()));

	if (GetPos().GetX() <= -GetCurrFrame().w)
	{
		SetPos(Vector(GetCurrFrame().w, GetPos().GetY()));
	}

}

ParallaxBG::ParallaxBG(Window& p_window, int& p_Score)
		   :renderWindow(p_window), currScore(&p_Score)
{
	layer0.emplace_back(Background(Vector(0,0), renderWindow.Load("res/gfx/sky.png"), 0.f));

	layer1.emplace_back(Background(Vector(0.f,-20.f), renderWindow.Load("res/gfx/clouds_bg.png"), 0.4f));
	layer1.emplace_back(layer1[0]);
	layer1[1].SetPos(Vector(layer1[1].GetCurrFrame().w,layer1[0].GetPos().GetY()));

	layer2.emplace_back(Background(Vector(0,0), renderWindow.Load("res/gfx/glacial_mountains.png"), 0.25f));
	layer2.emplace_back(layer2[0]);
	layer2[1].SetPos(Vector(layer2[1].GetCurrFrame().w, layer2[0].GetPos().GetY()));

	SDL_Texture* layer3Texture = renderWindow.Load("res/gfx/clouds_mg_3.png");
	SDL_SetTextureAlphaMod(layer3Texture,180);
	layer3.emplace_back(Background(Vector(0,-30), layer3Texture,0.5f));
	layer3.emplace_back(layer3[0]);
	layer3[1].SetPos(Vector(layer3[0].GetCurrFrame().w, layer3[0].GetPos().GetY()));

	SDL_Texture* layer4Texture = renderWindow.Load("res/gfx/clouds_mg_2.png");
	layer4.emplace_back(Background(Vector(0,-10), layer4Texture , 1.f));
	layer4.emplace_back(layer4[0]);
	layer4[1].SetPos(Vector(layer4[0].GetCurrFrame().w, layer4[0].GetPos().GetY()));
};

void ParallaxBG::Render()
{
	renderWindow.Render(layer0[0]);
	for (int i = 0; i < layer1.size(); i++)
	{
		renderWindow.Render(layer1[i]);
	}
	std::string currScoreS = std::to_string(*currScore);
	if(currScoreS.length() < 2) currScoreS = "0" + currScoreS;
	if(ShowText)
		renderWindow.RenderText(Vector(13, 140), currScoreS , "res/font/origa___.ttf", 80, white, 1);
	for (int i = 0; i < layer2.size(); i++)
	{
		renderWindow.Render(layer2[i]);
	}
	for (int i = 0; i < layer3.size(); i++)
	{
		renderWindow.Render(layer3[i]);
	}
	for (int i = 0; i < layer4.size(); i++)
	{
		renderWindow.Render(layer4[i]);
	}
}

void ParallaxBG::Update()
{
	for (int i = 0; i < layer1.size(); i++)
	{
		layer1[i].Update();
	}
	for (int i = 0; i < layer2.size(); i++)
	{
		layer2[i].Update();
	}
	for (int i = 0; i < layer3.size(); i++)
	{
		layer3[i].Update();
	}
	for (int i = 0; i < layer4.size(); i++)
	{
		layer4[i].Update();
	}
}


void ParallaxBG::Reset()
{
	layer1[0].SetPos(Vector(0,layer1[0].GetPos().GetY()));
	layer1[1].SetPos(Vector(layer1[1].GetCurrFrame().w,layer1[0].GetPos().GetY()));

	layer2[0].SetPos(Vector(0.f,layer2[0].GetPos().GetY()));
	layer2[1].SetPos(Vector(layer2[0].GetCurrFrame().w,layer2[0].GetPos().GetY()));

	layer3[0].SetPos(Vector(0.f,layer3[0].GetPos().GetY()));
	layer3[1].SetPos(Vector(layer3[1].GetCurrFrame().w,layer3[0].GetPos().GetY()));

	layer4[0].SetPos(Vector(0.f,layer4[0].GetPos().GetY()));
	layer4[1].SetPos(Vector(layer4[1].GetCurrFrame().w,layer4[0].GetPos().GetY()));
}

