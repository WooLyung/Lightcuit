#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

std::string Camera::GetName()
{
	return name;
}

Scene* Camera::GetScene()
{
	return scene;
}

Vec2F Camera::GetPos()
{
	return pos;
}

Vec2F Camera::GetZoom()
{
	return zoom;
}

float Camera::GetRot()
{
	return rot;
}

void Camera::SetIsFlipX(bool flag)
{
	isFlipX = flag;
}

void Camera::SetIsFlipY(bool flag)
{
	isFlipY = flag;
}

void Camera::SetPos(Vec2F pos)
{
	this->pos = pos;
}

void Camera::SetZoom(Vec2F zoom)
{
	this->zoom = zoom;
}

void Camera::SetRot(float rot)
{
	this->rot = rot;
}

void Camera::SetPosX(float x)
{
	this->pos.x = x;
}

void Camera::SetPosY(float y)
{
	this->pos.y = y;
}

void Camera::SetZoomX(float x)
{
	this->zoom.x = x;
}

void Camera::SetZoomY(float y)
{
	this->zoom.y = y;
}

void Camera::Update()
{
	
}