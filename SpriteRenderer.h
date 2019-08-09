#pragma once
#include "Renderer.h"
#include "Texture.h"

class SpriteRenderer :
	public Renderer
{
private:
	Texture* texture;
	Rect visibleArea = { 0, 0, 0, 0 };
	Rect realArea = { 0, 0, 0, 0 };
	float z_index = 0;

public:
	SpriteRenderer();
	~SpriteRenderer();

	std::type_index GetID(void) override { return typeid(SpriteRenderer); }
	static std::type_index GetFamilyID(void) { return typeid(Renderer); }

	void Update();
	void Render();
	void Draw();

	SpriteRenderer* SetTexture(const std::string&);
	SpriteRenderer* SetVisibleArea(Rect);
	SpriteRenderer* SetZ_index(float);

	Texture* GetTexture();
	Rect GetVisibleArea();
	Rect GetRealArea();
	float GetZ_index();
};