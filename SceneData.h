#pragma once

class SceneData
{
public:
	bool isFirst = true;

	static SceneData* GetInstance();
};