#ifndef GHOST_H_
#define GHOST_H_

#include "GameObject.h"

class Ghost : public GameObject
{
public:
	Ghost(const Vec2& _p, unsigned int _w, unsigned int _h);

	virtual void update(float _dt) override;
	virtual void drawG() const override;
	virtual void chase(const Vec2& _g) { m_pos = _g; } //have pac man's new position
	//virtual void moveEvent(const Vec2& _m) override;

	Vec2 getPosG() const { return m_pos; }
	Vec2 getDirG() const { return m_dir; }

	void setPos(const Vec2& _g) { m_pos = _g; }

private:
	Vec2 m_pos;
	Vec2 m_dir;
	unsigned int m_width;
	unsigned int m_height;

};


#endif#
