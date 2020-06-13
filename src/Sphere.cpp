#include "Sphere.h"
#include <ngl/VAOPrimitives.h>
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>


Sphere::Sphere(const ngl::Vec3& _pos, float _radius) : m_pos{ _pos }, m_radius{ _radius }
{

}



void Sphere::draw(const ngl::Mat4 &_vp) const
{
	ngl::Transformation tx;
	tx.setPosition(m_pos);
	tx.setScale(m_radius, m_radius, m_radius);
	auto shader = ngl::ShaderLib::instance();
	auto MVP = _vp * tx.getMatrix();
	shader->setUniform("MVP", MVP);
	shader->setUniform("Colour", 0.0f, 1.0f, 0.0f, 1.0f);
	ngl::VAOPrimitives::instance()->draw("sphere");
}



void Sphere::setRadius(ngl::Real _r)
{
	m_radius = _r;
}