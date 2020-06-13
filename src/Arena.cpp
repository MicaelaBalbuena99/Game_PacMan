#include "Arena.h"
#include <iostream>
#include <ngl/Image.h>
#include <ngl/Transformation.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include "RenderGlobals.h"
#include <memory>
#include<ngl/Text.h>
#include <SDL.h>



#include "Player.h"

const static char* Player1 = "Player1";
const static char* Wall = "Wall";
const static char* Fruit = "Fruit";
const static char* Empty = "Empty";
const static char* White = "White";

int eatenFruits = 0;




Arena::Arena(unsigned int _w, unsigned int _h)
{
    m_width = _w;
    m_height = _h;
    m_items.resize(m_width * m_height);
    createDefaultObjects();
}


Arena::Arena(const std::string& _filename)
{
    ngl::Image img(_filename);
    m_width = img.width();
    m_height = img.height();
    m_items.resize(m_width * m_height);
    createDefaultObjects();
  

    int white[4] = { 255, 255, 255, 255 }; 
    int red[4] = { 255, 0, 0, 255 };
    int black[4] = { 0, 0, 0, 255 };
    int currentColor[4] = { 0, 0, 0, 0};
    for (unsigned int y = 0; y < m_height; ++y)
    {
        for (unsigned int x = 0; x < m_width; ++x)
        {
            currentColor[0] = img.getColour(x, y)[0];
            currentColor[1] = img.getColour(x, y)[1];
            currentColor[2] = img.getColour(x, y)[2];
            currentColor[3] = img.getColour(x, y)[3];
            
            if (isEqual(currentColor, white)) {
                setItem(x, y, ItemType::White, m_objects[White]);
            }
            if (isEqual(currentColor, black)) {
                setItem(x, y, ItemType::Wall, m_objects[Wall]);
            }
            if (isEqual(currentColor, red)) {
                setItem(x, y, ItemType::Fruit, m_objects[Fruit]);
            }
        }
    }

    setItem(4, 4, ItemType::Player, m_objects[Player1]);
    ngl::VAOPrimitives::instance()->createTrianglePlane("floor", m_width, m_height, 1.0f, 1.0f, ngl::Vec3::up());
    ngl::VAOPrimitives::instance()->createSphere("sphere", 0.3f, 10.0f); //Dots as fruits
    ngl::VAOPrimitives::instance()->createSphere("pacman", 0.55f, 10.0f); //Dot as PACMAN

    //m_text.reset(new ngl::Text(QFont("Arial", 16)));
    //m_text->setScreenSize(width(), height());
   // m_text->setColour(1, 1, 1);
    

}

bool Arena::isEqual(int a[4], int b[4]) {
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3];
}

void Arena::createDefaultObjects()
{
    m_objects[Wall] = new GameObject();
    m_objects[Fruit] = new GameObject();
    m_objects[Empty] = new GameObject();
    m_objects[White] = new GameObject();
    m_objects[Player1] = new Player(Vec2(4, 4), m_width, m_height);

}

void Arena::keyEvent(int _x, int _y)
{
    std::cout << _x << ' ' << _y << '\n';
    m_objects[Player1]->moveEvent(Vec2(_x, _y));
}


void Arena::draw() const
{
    auto shader = ngl::ShaderLib::instance();
    shader->use(ngl::nglDiffuseShader);
#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif
    shader->setUniform("Colour", 1.0f, 0.0f, 0.0f, 1.0f); //draw in red
    size_t index = 0;
    for (size_t y = 0; y < m_height; ++y)
    {
        for (size_t x = 0; x < m_width; ++x)
        {
            switch (m_items[index++].type)
            {
            case ItemType::Empty: std::cout << ' '; break;
            case ItemType::Player: std::cout << 'P'; break;
            case ItemType::Fruit: std::cout << 'F';  drawFruit(x, y); break;
            case ItemType::White: std::cout << '-'; break;
            case ItemType::Wall: std::cout << 'W'; drawWall(x, y);  break;
            }
        }
        std::cout << '\n';
    }

    for (auto& o : m_objects)
    {
        o.second->draw();
    }
    shader->use(ngl::nglDiffuseShader);
    ngl::Transformation tx;
    tx.setPosition(0.0f, -0.6f, 0.0f);
    shader->setUniform("Colour", 0.0f, 0.0f, 0.0f, 1.0f);//black
   
    shader->setUniform("MVP", RenderGlobals::getVPMatrix() * tx.getMatrix());
    ngl::VAOPrimitives::instance()->draw("floor");

    //m_text->renderText(10, 18, "PACMAN");


}
void Arena::update(float _dt)
{
    std::cout << "update \n";

    for (auto& o : m_objects)
    {
        o.second->update(_dt);
    }
    Player* p = static_cast<Player*>(m_objects[Player1]);
    auto pos = p->getPos();
    auto dir = p->getDir();
    Vec2 newPos = pos;

    auto getItem = [=](unsigned int _x, unsigned int _y)
    {
        size_t index = _y * m_width + _x;
        return m_items[index].type;
    };

    if (dir.x != 0 && getItem(pos.x + dir.x, pos.y + dir.y) != ItemType::Wall)
    {
        newPos.x = pos.x + dir.x;
        if (newPos.x >= m_width) {
            newPos.x = 1;
        }        
        if (newPos.x <= 0) {
            newPos.x = m_width;
        }
    }

    if (dir.y != 0 && getItem(pos.x + dir.x, pos.y + dir.y) != ItemType::Wall)
    {
        newPos.y = pos.y + dir.y;
    }

    p->setPos(newPos);

    if (newPos.x && newPos.y && getItem(newPos.x + dir.x, newPos.y + dir.y) == ItemType::Fruit)
    {
        setItem(newPos.x, newPos.y, ItemType::White, m_objects[White]);
        
        eatenFruits++;
        //std::cout << eatenFruits, "FRUITSSSSSSS\n";
        //SDL_Delay(5000);

    }
    
    
}
void Arena::setItem(unsigned int _x, unsigned int _y, ItemType _type, GameObject* _obj)
{
    size_t index = _y * m_width + _x;
    m_items[index].type = _type;
    m_items[index].obj = _obj;
}


void Arena::drawWall(unsigned int _x, unsigned int _y) const
{
    float halfZ = -(m_height / 2.0f);
    float halfX = -(m_width / 2.0f);
    ngl::Transformation tx;
    tx.setPosition(halfX + _x, 0.0f, halfZ + _y);
    auto shader = ngl::ShaderLib::instance();
    shader->setUniform("MVP", RenderGlobals::getVPMatrix() * tx.getMatrix());
    shader->use(ngl::nglDiffuseShader);
    //shader->setUniform("Colour", 0.0f, 0.0f, 0.0f, 1.0f);
    shader->setUniform("Colour", 0.3f, 0.0f, 1.0f, 0.3f); //blue
    ngl::VAOPrimitives::instance()->draw(ngl::cube);
}

void Arena::drawFruit(unsigned int _x, unsigned int _y) const
{
    
    float halfZ = -(m_height / 2.0f);
    float halfX = -(m_width / 2.0f);
 
    ngl::Transformation tx;
    tx.setPosition(halfX + _x, 0.0f, halfZ + _y);

    auto shader = ngl::ShaderLib::instance();
    shader->setUniform("MVP", RenderGlobals::getVPMatrix() * tx.getMatrix());
    shader->setUniform("Colour", 1.0f, 1.0f, 0.0f, 1.0f);
    

    //ngl::VAOPrimitives::instance()->draw(ngl::teapot);
   
    ngl::VAOPrimitives::instance()->draw("sphere");

}

