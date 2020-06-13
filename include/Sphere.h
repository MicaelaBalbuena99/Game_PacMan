#ifndef SPHERE_H_
#define SPHERE_H_
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>


class Sphere

{
public:
	
	Sphere() = default;
	Sphere(const ngl::Vec3 & _pos, float _radius);
	~Sphere() = default;
	Sphere(const Sphere&) = default;
	void draw(const ngl::Mat4 & _vp) const;
	void setRadius(ngl::Real _r);


private:

	ngl::Vec3 m_pos;
	ngl::Real m_radius = 1.0f;
	ngl::Vec4 m_colour = ngl::Vec4(1.0f, 1.0f, 1.0f, 1.0f);


};

#endif