#pragma once
#include "Renderer.h"
#include "Texture.h"
#include "SpriteRenderData.h"
#include "Camera.h"
#include <map>

class SpriteRenderData;

class SpriteRenderer :
	public Renderer
{
private:
	std::map<Camera*, SpriteRenderData> datas;
	SpriteRenderData defaultData;

public:
	SpriteRenderer();
	~SpriteRenderer();

	std::type_index GetID(void) override { return typeid(SpriteRenderer); }
	static std::type_index GetFamilyID(void) { return typeid(Renderer); }

	void Update();
	void Render();
	void Render(ViewRenderer*);
	void Draw();
	void Draw(ViewRenderer*);

	std::map<Camera*, SpriteRenderData>* GetDatas();
	SpriteRenderData* GetDefaultData();
};