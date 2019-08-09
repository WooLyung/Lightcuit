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