#include "Ghost.h"
#include "GameObject.h"
#include <iostream>
#include <ngl/Transformation.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include "RenderGlobals.h"
Ghost::Ghost(const Vec2& _p, unsigned int _w, unsigned int _h) : GameObject()
{
	m_pos = _p;
	m_width = _w;
	m_height = _h;
}


void Ghost::update(float _dt)
{
}
void Ghost::chase(const Vec2& _g) { m_pos = _g; }//  getting pacMan's previos position
{
	return null;
}

void Ghost::drawG() const
{

	float halfZ = -(m_height / 2.0f);
	float halfX = -(m_width / 2.0f);
	ngl::Transformation tgx;
	tgx.setPosition(halfX + m_pos.x, 0.0f, halfZ + m_pos.y);
	auto shader = ngl::ShaderLib::instance();
	shader->setUniform("MVP", RenderGlobals::getVPMatrix() * tgx.getMatrix());
	shader->use(ngl::nglDiffuseShader);
	shader->setUniform("Colour", 1.0f, 0.0f, 1.0f, 0.0f); //blue
	ngl::VAOPrimitives::instance()->draw("ghost");
}

////void Ghost::moveEvent(const Vec2& _m)
//{
//	m_dir = _m;
//}