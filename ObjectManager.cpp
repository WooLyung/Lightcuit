#include "stdafx.h"
#include "ObjectManager.h"
#include "Line.h"

ObjectManager::ObjectManager(InGameScene* scene)
{
	this->scene = scene;
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::OnStart()
{
}

void ObjectManager::SetSpriteOnConnect(Line* lastLine, Line* newLine, Vec2L tilePos)
{
	Transform* newLineTrans = newLine->GetTransform();
	Transform* lastLineTrans = lastLine->GetTransform();
	SpriteRenderer* lastLineRen = lastLine->GetSpriteRenderer();

	if (lastLine->dir == RIGHT)
	{
		if (tilePos.x > lastLine->tilePos.x)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line2.png");
			newLineTrans->SetRot(0);
			newLine->dir = RIGHT;
		}
		else if (tilePos.y > lastLine->tilePos.y)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lastLineTrans->SetRot(90);
			newLineTrans->SetRot(270);
			newLine->dir = UP;
		}
		else if (tilePos.y < lastLine->tilePos.y)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lastLineTrans->SetRot(0);
			newLineTrans->SetRot(90);
			newLine->dir = DOWN;
		}
	}
	else if (lastLine->dir == LEFT)
	{
		if (tilePos.x < lastLine->tilePos.x)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line2.png");
			newLineTrans->SetRot(180);
			newLine->dir = LEFT;
		}
		else if (tilePos.y > lastLine->tilePos.y)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lastLineTrans->SetRot(180);
			newLineTrans->SetRot(270);
			newLine->dir = UP;
		}
		else if (tilePos.y < lastLine->tilePos.y)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lastLineTrans->SetRot(270);
			newLineTrans->SetRot(90);
			newLine->dir = DOWN;
		}
	}
	else if (lastLine->dir == UP)
	{
		if (tilePos.y > lastLine->tilePos.y)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line2.png");
			newLineTrans->SetRot(270);
			newLine->dir = UP;
		}
		else if (tilePos.x > lastLine->tilePos.x)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lastLineTrans->SetRot(270);
			newLineTrans->SetRot(0);
			newLine->dir = RIGHT;
		}
		else if (tilePos.x < lastLine->tilePos.x)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lastLineTrans->SetRot(0);
			newLineTrans->SetRot(180);
			newLine->dir = LEFT;
		}
	}
	else if (lastLine->dir == DOWN)
	{
		if (tilePos.y < lastLine->tilePos.y)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line2.png");
			newLineTrans->SetRot(90);
			newLine->dir = DOWN;
		}
		else if (tilePos.x > lastLine->tilePos.x)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lastLineTrans->SetRot(180);
			newLineTrans->SetRot(0);
			newLine->dir = RIGHT;
		}
		else if (tilePos.x < lastLine->tilePos.x)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lastLineTrans->SetRot(90);
			newLineTrans->SetRot(180);
			newLine->dir = LEFT;
		}
	}
}

void ObjectManager::SetSpriteOnFinish(Line* line, Vec2L tilePos)
{
	Transform* lineTrans = line->GetTransform();
	SpriteRenderer* lineRen = line->GetSpriteRenderer();

	if (line->dir == RIGHT)
	{
		if (tilePos.x > line->tilePos.x)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line2.png");
		}
		else if (tilePos.y > line->tilePos.y)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lineTrans->SetRot(90);
		}
		else if (tilePos.y < line->tilePos.y)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lineTrans->SetRot(0);
		}
	}
	else if (line->dir == LEFT)
	{
		if (tilePos.x < line->tilePos.x)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line2.png");
		}
		else if (tilePos.y > line->tilePos.y)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lineTrans->SetRot(180);
		}
		else if (tilePos.y < line->tilePos.y)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lineTrans->SetRot(270);
		}
	}
	else if (line->dir == UP)
	{
		if (tilePos.y > line->tilePos.y)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line2.png");
		}
		else if (tilePos.x > line->tilePos.x)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lineTrans->SetRot(270);
		}
		else if (tilePos.x < line->tilePos.x)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lineTrans->SetRot(0);
		}
	}
	else if (line->dir == DOWN)
	{
		if (tilePos.y < line->tilePos.y)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line2.png");
		}
		else if (tilePos.x > line->tilePos.x)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lineTrans->SetRot(180);
		}
		else if (tilePos.x < line->tilePos.x)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lineTrans->SetRot(90);
		}
	}
}

void ObjectManager::PushGate(Gate* gate)
{
	gates.push_back(gate);
}