#ifndef ARENA_H_
#define ARENA_H_

#include "GameItem.h"
#include <vector>
#include <string>
#include <unordered_map>
#include<ngl/Text.h>



class Arena
{
public:
	Arena() = default;
	~Arena() = default;
	Arena(unsigned int _w, unsigned int _h);
	Arena(const std::string& _filename);
	void draw() const;
	void update(float _dt);
	void keyEvent(int _x, int _y);
	bool isEqual(int a[4], int b[4]);



private:
	void setItem(unsigned int _x, unsigned int _y, ItemType _type, GameObject* _obj = nullptr);
	void createDefaultObjects();
	void drawWall(unsigned int _x, unsigned int _y) const;
	void drawFruit(unsigned int _x, unsigned int _y) const;
	unsigned int m_width = 0;
	unsigned int m_height = 0;

	//Load up assets
	std::vector<GameItem> m_items;
	std::unordered_map<std::string, GameObject*> m_objects;
	
};


#endif // ARENA_H_