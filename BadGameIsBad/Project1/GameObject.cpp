#include "GameObject.h"

//! ctor
/*
* init Gameobject position and status
*/
GameObject::GameObject(): m_x(0), m_y(0), m_alive(false)
{
}

//! dtor
GameObject::~GameObject()
{
}

//! x
/*
* getter for the X coordinate
*/
float GameObject::x(void) const
{
	return m_x;
}

//! y
/*
* getter for the Y coordinate
*/
float GameObject::y(void) const
{
	return m_y;
}

//! isAlive
/*
* return true is alive
*/
bool GameObject::isAlive(void) const
{
	return m_alive;
}

//! active
/*
* manually change status to alive
*/
void GameObject::active(void)
{
	m_alive = true;
}

//! disactive
/*
* manually change status
*/
void GameObject::disactive(void)
{
	m_alive = false;
}
