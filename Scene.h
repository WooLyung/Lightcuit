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
	void Render(); // ������
	void Update(); // ������Ʈ
	
	std::vector<Object*> objects; // �� ���� ������Ʈ
	std::vector<Camera*> cameras; // �� ���� ī�޶�
	Camera* mainCamera = nullptr;
	ObjectBuilder* objectBuilder; // �� ���� ������Ʈ ����
	CameraBuilder* cameraBuilder; // �� ���� ī�޶� ����

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

	// ���� ���� �޼���
	ObjectBuilder* CreateObjectBuilder(); // ���� ���� �Ҽӵ� ������Ʈ ������ ����
	CameraBuilder* CreateCameraBuilder(); // ���� ���� �Ҽӵ� ī�޶� ������ ����

	// ������Ʈ ���� �޼���
	Object* CreateObject(); // �� ������Ʈ ����, ������ ������Ʈ ������ ������ �̿��ؾ���
	Object* AttachObject(Object*); // ������ ������Ʈ�� ����
	Object* FindObject(const Object*); // ������Ʈ�� ã��
	Object* FindObjectByTag(const std::string); // �±׿� �´� ������Ʈ�� ã��
	Object* FindObjectByName(const std::string); // �̸��� �´� ������Ʈ�� ã��
	Object* FindObjectCondition(std::function<bool(const Object*)>); // ���ǿ� �´� ������Ʈ�� ã��
	std::vector<Object*> FindObjectsByTag(const std::string); // �±׿� �´� ������Ʈ���� ã��
	std::vector<Object*> FindObjectsByName(const std::string); // �̸��� �´� ������Ʈ���� ã��
	std::vector<Object*> FindObjectsCondition(std::function<bool(const Object*)>); // ���ǿ� �´� ������Ʈ���� ã��

	// ī�޶� ���� �޼���
	Camera* CreateCamera(); // �� ī�޶� ����, ������ ī�޶� ������ ������ �̿��ؾ���
	Camera* AttachCamera(Camera*); // ������ ī�޶� ����
	Camera* FindCamera(const Camera*); // ī�޶� ã��
	Camera* FindCameraByName(const std::string); // �̸��� �´� ī�޶� ã��
	Camera* FindCameraCondition(std::function<bool(const Camera*)>); // ���ǿ� �´� ������Ʈ�� ã��
	std::vector<Camera*> FindCamerasCondition(std::function<bool(const Camera*)>); // ���ǿ� �´� ������Ʈ���� ã��

	// ����������Ŭ ������
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

	// ����������Ŭ �޼���
	virtual void OnStart() {} // ���� ù ������Ʈ ���۽ÿ�
	virtual void OnFirstRegister() {} // ���� ó�� ��ω��� ��
	virtual void OnRegister() {} // ���� ��ω��� ��
	virtual void OnFirstUpdate() {} // ���� ù ������Ʈ
	virtual void OnFirstUpdateBefore() {} // ���� ù ������Ʈ ����
	virtual void OnUpdate() {} // ������Ʈ���� ��
	virtual void OnUpdateBefore() {} // ������Ʈ ��
	virtual void OnFirstRender() {} // ù ������ ���� ��
	virtual void OnFirstRenderBefore() {} // ù ������ ����
	virtual void OnRender() {} // ������ ���� ��
	virtual void OnRenderBefore() {} // ������ ��
	virtual void OnFinish() {} // ���� ����� Ǯ���� ��
	virtual void OnDestroy() {} // ��ü�� �������� ��

	// ��Ÿ
	bool GetIsFirstRender() { return isFirstRender; }
	bool GetIsFirstUpdate() { return isFirstUpdate; }
	bool GetIsFirstRegister() { return isFirstRegister; }
	SceneState GetState() { return state; }
	Camera* GetMainCamera() { return mainCamera; }
	Matrix GetMatrix() { return matrix; }
	Matrix GetDefaultMatrix() { return defaultMatrix; }
};