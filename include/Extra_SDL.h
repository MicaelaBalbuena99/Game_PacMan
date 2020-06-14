#ifndef SPHERE_H_
#define SPHERE_H_
#include "SDL_ttf.h"
#include <string>
#include <unordered_map>
#include<ngl/Text.h>


class Extra_SDL

{
public:
	
	void addFont(std::string id, std::string path, int fontSize);
	TTF_Font* getFont(std::string id);


private:
	std::map<std::string, TTF_Font*>fonts;



};

#endif