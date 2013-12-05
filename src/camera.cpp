#include "../include/camera.h"
#include "../include/screen.h"
#include "../include/types.h"

#define vWidth Screen::Instance().GetDesktopWidth()
#define vHeight Screen::Instance().GetDesktopHeight()

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
	if (boundx0 <= x && x + vWidth <= boundx1)
		this->x = x;
}

void Camera::SetY(double y)
{
	if (boundy0 <= y && y + vHeight <= boundy1)
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
	return boundx1;
}

double Camera::GetMaxY() const
{
	return boundy1;
}

void Camera::FollowSprite(Sprite* sprite)
{
	followingSprite = sprite;
}

void Camera::Update()
{
	if (followingSprite && HasBounds())
		SetPosition(followingSprite->GetX() - (vWidth / 2), followingSprite->GetY() - (vHeight / 2));
}
