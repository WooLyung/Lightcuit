#pragma once
#include "Object.h"
#include "Camera.h"
#include "ObjectBuilder.h"
#include "CameraBuilder.h"
#include "SceneManager.h"

class SceneManager;
class CameraBuilder;
class ObjectBuilder;
class Camera;
class Object;

enum SceneState
{
	SCENE_UNREGISTERED,
	SCENE_START,
	SCENE_ALIVE
};

class Scene
{
private:
	void Render(); // 렌더링
	void Update(); // 업데이트
	
	std::vector<Object*> objects; // 씬 안의 오브젝트
	std::vector<Camera*> cameras; // 씬 안의 카메라
	Camera* mainCamera = nullptr;
	ObjectBuilder* objectBuilder; // 씬 내장 오브젝트 빌더
	CameraBuilder* cameraBuilder; // 씬 내장 카메라 빌더

	Matrix matrix;
	Matrix defaultMatrix;
	SceneState state = SCENE_UNREGISTERED;
	bool isFirstRender = true;
	bool isFirstUpdate = true;
	bool isFirstRegister = true;

	friend class SceneManager;

public:
	Scene();
	~Scene();

	// 빌더 관련 메서드
	ObjectBuilder* CreateObjectBuilder(); // 현재 씬에 소속된 오브젝트 빌더를 생성
	CameraBuilder* CreateCameraBuilder(); // 현재 씬에 소속된 카메라 빌더를 생성

	// 오브젝트 관련 메서드
	Object* CreateObject(); // 빈 오브젝트 생성, 복잡한 오브젝트 생성시 빌더를 이용해야함
	Object* AttachObject(Object*); // 생성할 오브젝트를 지정
	Object* FindObject(const Object*); // 오브젝트를 찾음
	Object* FindObjectByTag(const std::string); // 태그에 맞는 오브젝트를 찾음
	Object* FindObjectByName(const std::string); // 이름에 맞는 오브젝트를 찾음
	Object* FindObjectCondition(std::function<bool(const Object*)>); // 조건에 맞는 오브젝트를 찾음
	std::vector<Object*> FindObjectsByTag(const std::string); // 태그에 맞는 오브젝트들을 찾음
	std::vector<Object*> FindObjectsByName(const std::string); // 이름에 맞는 오브젝트들을 찾음
	std::vector<Object*> FindObjectsCondition(std::function<bool(const Object*)>); // 조건에 맞는 오브젝트들을 찾음

	// 카메라 관련 메서드
	Camera* CreateCamera(); // 빈 카메라 생성, 복잡한 카메라 생성시 빌더를 이용해야함
	Camera* AttachCamera(Camera*); // 생성할 카메라를 지정
	Camera* FindCamera(const Camera*); // 카메라를 찾음
	Camera* FindCameraByName(const std::string); // 이름에 맞는 카메라를 찾음
	Camera* FindCameraCondition(std::function<bool(const Camera*)>); // 조건에 맞는 오브젝트를 찾음
	std::vector<Camera*> FindCamerasCondition(std::function<bool(const Camera*)>); // 조건에 맞는 오브젝트들을 찾음

	// 라이프사이클 리스너
	std::function<void()> onStartListener = NULL;
	std::function<void()> onFirstRegisterListener = NULL;
	std::function<void()> onRegisterListener = NULL;
	std::function<void()> onFirstUpdateListener = NULL;
	std::function<void()> onFirstUpdateBeforeListener = NULL;
	std::function<void()> onUpdateListener = NULL;
	std::function<void()> onUpdateBeforeListener = NULL;
	std::function<void()> onFirstRenderListener = NULL;
	std::function<void()> onFirstRenderBeforeListener = NULL;
	std::function<void()> onRenderListener = NULL;
	std::function<void()> onRenderBeforeListener = NULL;
	std::function<void()> onFinishListener = NULL;
	std::function<void()> onDestroyListener = NULL;

	// 라이프사이클 메서드
	virtual void OnStart() {} // 씬의 첫 업데이트 시작시에
	virtual void OnFirstRegister() {} // 씬이 처음 등록됬을 때
	virtual void OnRegister() {} // 씬이 등록됬을 때
	virtual void OnFirstUpdate() {} // 씬의 첫 업데이트
	virtual void OnFirstUpdateBefore() {} // 씬의 첫 업데이트 이전
	virtual void OnUpdate() {} // 업데이트됬을 때
	virtual void OnUpdateBefore() {} // 업데이트 전
	virtual void OnFirstRender() {} // 첫 렌더링 됬을 때
	virtual void OnFirstRenderBefore() {} // 첫 렌더링 이전
	virtual void OnRender() {} // 렌더링 됬을 때
	virtual void OnRenderBefore() {} // 렌더링 전
	virtual void OnFinish() {} // 씬의 등록이 풀렸을 때
	virtual void OnDestroy() {} // 객체가 삭제됬을 때

	// 기타
	bool GetIsFirstRender() { return isFirstRender; }
	bool GetIsFirstUpdate() { return isFirstUpdate; }
	bool GetIsFirstRegister() { return isFirstRegister; }
	SceneState GetState() { return state; }
	Camera* GetMainCamera() { return mainCamera; }
	Matrix GetMatrix() { return matrix; }
	Matrix GetDefaultMatrix() { return defaultMatrix; }
};