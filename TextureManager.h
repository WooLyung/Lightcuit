#pragma once
#include"Texture.h"
class TextureManager
{
private:
	IWICImagingFactory* wicFactory_;
	std::map<std::string, Texture*> textures_;
	std::list<std::experimental::filesystem::path> paths_;
	std::list<std::experimental::filesystem::path>::iterator pathIter_;
	int filesToLoadPerFrame_;
	int filesLoaded_;
	//LoadAll(Update)이 돌아가고 있을때는 false
	bool isLoaded_;
	friend class Texture;
public:
	TextureManager();
	~TextureManager();

	Texture* Load(const std::string& path);
	void Unload(const std::string& path);
	//비동기처럼 실행됨 ?
	void LoadAll(const std::string& rootPath, int filesToLoadPerFrame_ = 5);
	bool IsLoading();
	float GetProgressRate();
	std::string GetCurrentLoadingPath();
	//

	void UnloadAll(const std::string& rootPath);

	void Update();

};

