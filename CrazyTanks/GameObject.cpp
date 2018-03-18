#include "GameObject.h"

GameObject::GameObject()
{
}



GameObject::~GameObject()
{
}



void GameObject::setPositionX(int x) { positionX_ = x; }
void GameObject::setPositionY(int y) { positionY_ = y; }



int GameObject::getPositionX() { return positionX_; }
int GameObject::getPositionY() { return positionY_; }