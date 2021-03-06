#include "../include/camera.h"
#include "../include/screen.h"
#include "../include/types.h"

#define vWidth Screen::Instance().GetWidth()
#define vHeight Screen::Instance().GetHeight()

Camera::Camera()
{
	x = y = 0;
	boundx0 = boundy0 = boundx1 = boundy1 = 0;
	followingSprite = NULL;
}

void Camera::SetPosition(double x, double y)
{
	SetX(x);
	SetY(y);
}

void Camera::SetX(double x)
{
	if (!HasBounds())
		this->x = x;
	else if (x < GetMinX())
		this->x = GetMinX();
	else if (x > GetMaxX())
		this->x = GetMaxX();
	else
		this->x = x;
}

void Camera::SetY(double y)
{
	if (!HasBounds())
		this->y = y;
	else if (y < GetMinY())
		this->y = GetMinY();
	else if (y > GetMaxY())
		this->y = GetMaxY();
	else
		this->y = y;
}

double Camera::GetX() const
{
	return x;
}

double Camera::GetY() const
{
	return y;
}

void Camera::SetBounds(double bx0, double by0, double bx1, double by1)
{
	if (bx0 < bx1 && by0 < by1)
	{
		boundx0 = bx0;
		boundy0 = by0;
		boundx1 = bx1;
		boundy1 = by1;
	}
}

bool Camera::HasBounds() const
{
	return (boundx0 != boundx1) && (boundy0 != boundy1);
}

double Camera::GetMinX() const
{
	return boundx0;
}

double Camera::GetMinY() const
{
	return boundy0;
}

double Camera::GetMaxX() const
{
	return boundx1 - vWidth;
}

double Camera::GetMaxY() const
{
	return boundy1 - vHeight;
}

void Camera::FollowSprite(Sprite* sprite)
{
	followingSprite = sprite;
}

void Camera::Update()
{
	if (followingSprite)
		SetPosition(followingSprite->GetX() - (vWidth / 2), followingSprite->GetY() - (vHeight / 2));
}
