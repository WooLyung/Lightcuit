#include "stdafx.h"
#include "Camera.h"
#include "Engine.h"
#include "Settings.h"

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

Size2F Camera::GetCameraDefaultSize()
{
	float diagonal = sqrtf(
		(float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height));
	
	return Size2F(RG2R_WindowM->GetSize().width * (DIAGONAL_LENGTH / diagonal), RG2R_WindowM->GetSize().height * (DIAGONAL_LENGTH / diagonal));
}

Size2F Camera::GetCameraSize()
{
	float diagonal = sqrtf(
		(float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height));

	return Size2F(RG2R_WindowM->GetSize().width * (DIAGONAL_LENGTH / diagonal) / zoom.x, RG2R_WindowM->GetSize().height * (DIAGONAL_LENGTH / diagonal) / zoom.y);
}