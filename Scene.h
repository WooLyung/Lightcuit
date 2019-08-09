#pragma once
#include "Object.h"
#include "Camera.h"
#include "ObjectBuilder.h"
#include "CameraBuilder.h"

class Scene
{
public:
	enum SCENE_STATE
	{
		UNREGISTERED,
		START,
		ALIVE
	};

private:
	void Render(); // ������
	void Update(); // ������Ʈ
	
	std::vector<Object*> objects; // �� ���� ������Ʈ
	std::vector<Camera*> cameras; // �� ���� ī�޶�
	ObjectBuilder* objectBuilder; // �� ���� ������Ʈ ����
	CameraBuilder* cameraBuilder; // �� ���� ī�޶� ����

	SCENE_STATE state;
	bool isFirstRender = true;
	bool isFirstUpdate = true;
	bool isFirstRegister = true;

public:
	Scene();
	~Scene();

	// ���� ���� �޼���
	ObjectBuilder* CreateObjectBuilder(); // ���� ���� �Ҽӵ� ������Ʈ ������ ����
	CameraBuilder* CreateCameraBuilder(); // ���� ���� �Ҽӵ� ī�޶� ������ ����

	// ������Ʈ ���� �޼���
	Object* CreateObject(); // �� ������Ʈ ����, ������ ������Ʈ ������ ������ �̿��ؾ���
	Object* FindObject(const Object*); // ������Ʈ�� ã��
	Object* FindObjectByTag(const std::string); // �±׿� �´� ������Ʈ�� ã��
	Object* FindObjectByName(const std::string); // �̸��� �´� ������Ʈ�� ã��
	Object* FindObjectCondition(std::function<bool(const Object*)>); // ���ǿ� �´� ������Ʈ�� ã��
	std::vector<Object*> FindObjectsByTag(const std::string); // �±׿� �´� ������Ʈ���� ã��
	std::vector<Object*> FindObjectsByName(const std::string); // �̸��� �´� ������Ʈ���� ã��
	std::vector<Object*> FindObjectsCondition(std::function<bool(const Object*)>); // ���ǿ� �´� ������Ʈ���� ã��

	// ī�޶� ���� �޼���
	Camera* CreateCamera(); // �� ī�޶� ����, ������ ī�޶� ������ ������ �̿��ؾ���
	Camera* FindCamera(const Camera*); // ī�޶� ã��
	Camera* FindCameraByName(const std::string); // �̸��� �´� ī�޶� ã��
	Camera* FindCameraCondition(std::function<bool(const Camera*)>); // ���ǿ� �´� ������Ʈ�� ã��
	std::vector<Camera*> FindCamerasCondition(std::function<bool(const Camera*)>); // ���ǿ� �´� ������Ʈ���� ã��

	// ����������Ŭ ������
	std::function<void()> onCreateListener = NULL;
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
	void OnCreate(); // ��ü ������ ���ÿ� �����
	void OnFirstRegister(); // ���� ó�� ��ω��� ��
	void OnRegister(); // ���� ��ω��� ��
	void OnFirstUpdate(); // ���� ù ������Ʈ
	void OnFirstUpdateBefore(); // ���� ù ������Ʈ ����
	void OnUpdate(); // ������Ʈ���� ��
	void OnUpdateBefore(); // ������Ʈ ��
	void OnFirstRender(); // ù ������ ���� ��
	void OnFirstRenderBefore(); // ù ������ ����
	void OnRender(); // ������ ���� ��
	void OnRenderBefore(); // ������ ��
	void OnFinish(); // ���� ����� Ǯ���� ��
	void OnDestroy(); // ��ü�� �������� ��

	// ��Ÿ
	bool GetIsFirstRender() { return isFirstRender; }
	bool GetIsFirstUpdate() { return isFirstUpdate; }
	bool GetIsFirstRegister() { return isFirstRegister; }
	SCENE_STATE GetState() { return state; }
};