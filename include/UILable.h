//#ifndef ARENA_H_
//#define ARENA_H_
//
//#include "GameItem.h"
//#include <vector>
//#include <string>
//#include <unordered_map>
//#include<ngl/Text.h>
//#include "Arena.h"
//#include "Extra_SDL.h"
//#include "Arena.h"
//#include <SDL.h>
//#include <SDL_ttf.h>
//#include <string>
//
//class UILable 
//{
//public:
//	UILable(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour): labelText(text, labelFont(font),textColour(colour)
//	{
//		position.x = xpos;
//		position.y = ypos;
//
//	}
//	UILable()
//	{
//		
//
//	}
//
//	void SetLableText()
//	{
//		SDL_Surface* surf = TTF_RenderText_Blended(main::maps->GetFont(labelFont), labelText.c_srtinf(), textColour);
//		labelTexture = SDL_CreateTextureFromSurface(Game::renderer; surf);
//		SDL_FreeSurface(surf);
//
//		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
//	}
//	void draw() override 
//	
//	{
//		SDL_renderCopy(Game::renderer, labelTexture, nullptr, &position);
//
//
//	}
//
//
//private:
//	SDL_Rect position;
//	std::string lableText;
//	std::string lableFont;
//	SDL_Color textColour;
//	SDL_Texture* labelRexrure;
//	std::map<std::string, TTF_Font*>fonts;
//};
//
//#endif