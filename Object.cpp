#include "stdafx.h"
#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
	ApplyListener(onDestroyListener);
	OnDestroy();

	for (auto iter : childs)
	{
		delete iter;
	}
	for (auto& iter : components)
	{
		delete iter.second;
	}
}

void Object::Render()
{
	// 컴포넌트 렌더

	for (auto iter : childs)
	{
		if (iter->isFirstRender)
		{
			ApplyListener(iter->onFirstRenderBeforeListener);
			iter->OnFirstRenderBefore();
		}
		ApplyListener(iter->onRenderBeforeListener);
		iter->OnRenderBefore();

		iter->Render();

		if (iter->isFirstRender)
		{
			ApplyListener(iter->onFirstRenderListener);
			iter->OnFirstRender();

			iter->isFirstRender = false;
		}
		ApplyListener(iter->onRenderListener);
		iter->OnRender();
	}
}

void Object::Update()
{
	// 컴포넌트 업데이트

	for (auto iter : childs)
	{
		if (iter->isFirstUpdate)
		{
			ApplyListener(iter->onFirstUpdateBeforeListener);
			iter->OnFirstUpdateBefore();
		}
		ApplyListener(iter->onUpdateBeforeListener);
		iter->OnUpdateBefore();

		iter->Update();

		if (iter->isFirstUpdate)
		{
			ApplyListener(iter->onFirstUpdateListener);
			iter->OnFirstUpdate();

			iter->isFirstUpdate = false;
		}
		ApplyListener(iter->onUpdateListener);
		iter->OnUpdate();
	}
}

void Object::ChangeParent(Object*)
{

}

Object* Object::DetachParent()
{
	return nullptr; // 만들어야함
}

void Object::DetachChild(Object*)
{

}

void Object::AttachChild(Object*)
{

}

Object* Object::FindChild(const Object*)
{
	return nullptr; // 만들어야함
}

Object* Object::FindChildByTag(const std::string)
{
	return nullptr; // 만들어야함
}

Object* Object::FindChildByName(const std::string)
{
	return nullptr; // 만들어야함
}

Object* Object::FindChildCondition(std::function<bool(const Object*)>)
{
	return nullptr; // 만들어야함
}

std::vector<Object*> Object::FindChildsByTag(const std::string)
{
	return std::vector<Object*>(); // 만들어야함
}

std::vector<Object*> Object::FindChildsByName(const std::string)
{
	return std::vector<Object*>(); // 만들어야함
}

std::vector<Object*> Object::FindChildsCondition(std::function<bool(const Object*)>)
{
	return std::vector<Object*>(); // 만들어야함
}

Object* Object::CreateObject()
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->CreateObject();
}

Object* Object::AttachObject(Object* object)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->AttachObject(object);
}

Object* Object::FindObject(const Object* object)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->FindObject(object);
}

Object* Object::FindObjectByTag(const std::string tag)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->FindObjectByTag(tag);
}

Object* Object::FindObjectByName(const std::string name)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->FindObjectByName(name);
}

Object* Object::FindObjectCondition(std::function<bool(const Object*)> condition)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->FindObjectCondition(condition);
}

std::vector<Object*> Object::FindObjectsByTag(const std::string tag)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return std::vector<Object*>();
	}
	return scene->FindObjectsByTag(tag);
}

std::vector<Object*> Object::FindObjectsByName(const std::string name)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return std::vector<Object*>();
	}
	return scene->FindObjectsByName(name);
}

std::vector<Object*> Object::FindObjectsCondition(std::function<bool(const Object*)> condition)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return std::vector<Object*>();
	}
	return scene->FindObjectsCondition(condition);
}

Camera* Object::CreateCamera()
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->CreateCamera();
}

Camera* Object::AttachCamera(Camera* cam)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->AttachCamera(cam);
}

Camera* Object::FindCamera(const Camera* cam)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->FindCamera(cam);
}

Camera* Object::FindCameraByName(const std::string name)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->FindCameraByName(name);
}

Camera* Object::FindCameraCondition(std::function<bool(const Camera*)> condition)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->FindCameraCondition(condition);
}

std::vector<Camera*> Object::FindCamerasCondition(std::function<bool(const Camera*)> condition)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return std::vector<Camera*>();
	}
	return scene->FindCamerasCondition(condition);
}

Scene* Object::GetScene()
{
	return scene;
}

std::string Object::GetTag()
{
	return tag;
}

std::string Object::GetName()
{
	return name;
}

void Object::SetTag(std::string tag)
{
	this->tag = tag;

	ApplyListener(onChangeTagListener);
	OnChangeTag();
}

void Object::SetName(std::string name)
{
	this->name = name;

	ApplyListener(onChangeNameListener);
	OnChangeName();
}

bool Object::IsChild(Object*)
{
	return true; // 만들어야함
}

bool Object::IsParent(Object* object)
{
	return object == parent;
}

void Object::Destroy()
{
	state = OBJ_DESTROY;

	for (auto iter : childs)
	{
		iter->Destroy();
	}
}

bool Object::IsEnable()
{
	return isEnable;
}