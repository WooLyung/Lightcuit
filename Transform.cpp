#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::Update()
{

}

void Transform::Render()
{

}

Vec2F Transform::GetPos()
{
	return pos;
}

Vec2F Transform::GetScale()
{
	return scale;
}

float Transform::GetRot()
{
	return rot;
}

Vec2F Transform::GetCenter()
{
	return center;
}

Vec2F Transform::GetAnchor_rot()
{
	return anchor_rot;
}

Vec2F Transform::GetAnchor_scale()
{
	return anchor_scale;
}

void Transform::SetPos(Vec2F pos)
{
	this->pos = pos;
}

void Transform::SetScale(Vec2F scale)
{
	this->scale = scale;
}

void Transform::SetRot(float rot)
{
	this->rot = rot;
}

void Transform::SetPosX(float x)
{
	this->pos.x = x;
}

void Transform::SetPosY(float y)
{
	this->pos.y = y;
}

void Transform::SetScaleX(float x)
{
	this->scale.x = x;
}

void Transform::SetScaleY(float y)
{
	this->scale.y = y;
}

void Transform::SetCenter(Vec2F center)
{
	this->center = center;
}

void Transform::SetAnchor_scale(Vec2F anchor)
{
	this->anchor_scale = anchor;
}

void Transform::SetAnchor_rot(Vec2F anchor)
{
	this->anchor_rot = anchor;
}

void Transform::SetCenterX(float x)
{
	this->center.x = x;
}

void Transform::SetCenterY(float y)
{
	this->center.y = y;
}

void Transform::SetAnchor_scaleX(float x)
{
	this->anchor_scale.x = x;
}

void Transform::SetAnchor_scaleY(float y)
{
	this->anchor_scale.y = y;
}

void Transform::SetAnchor_rotX(float x)
{
	this->anchor_rot.x = x;
}

void Transform::SetAnchor_rotY(float y)
{
	this->anchor_rot.y = y;
}

bool Transform::GetIsRelative()
{
	return isRelative;
}

void Transform::SetIsRelative(bool isRelative)
{
	this->isRelative = isRelative;
}