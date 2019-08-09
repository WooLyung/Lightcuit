#pragma once
#include "Component.h"
#include "Scene.h"
#include "Camera.h"

class Component;
class Scene;
class Camera;

enum ObjectState
{
	OBJ_NONE,
	OBJ_START,
	OBJ_ALIVE,
	OBJ_DESTROY,
	OBJ_DISABLE
};

class Object
{
private:
	void Render();
	void Update();
	
	std::map<std::type_index, Component*> components;
	std::vector<Object*> childs;
	Object* parent = nullptr;
	Scene* scene = nullptr;

	ObjectState state = OBJ_NONE;
	std::string name = "";
	std::string tag = "";

	bool isFirstRender = true;
	bool isFirstUpdate = true;
	bool isEnable = true;

	friend class Scene;

public:
	Object();
	~Object();

	// �θ� ����
	void ChangeParent(Object*); // �θ� ����
	Object* DetachParent(); // �θ� ����
	bool IsParent(Object*); // �θ� üũ

	// �ڽ� ����
	void DetachChild(Object*); // �ڽ� ����
	void AttachChild(Object*); // �ڽ� �߰�
	Object* FindChild(const Object*); // ������Ʈ�� ã��
	Object* FindChildByTag(const std::string); // �±׿� �´� ������Ʈ�� ã��
	Object* FindChildByName(const std::string); // �̸��� �´� ������Ʈ�� ã��
	Object* FindChildCondition(std::function<bool(const Object*)>); // ���ǿ� �´� ������Ʈ�� ã��
	std::vector<Object*> FindChildsByTag(const std::string); // �±׿� �´� ������Ʈ���� ã��
	std::vector<Object*> FindChildsByName(const std::string); // �̸��� �´� ������Ʈ���� ã��
	std::vector<Object*> FindChildsCondition(std::function<bool(const Object*)>); // ���ǿ� �´� ������Ʈ���� ã��
	bool IsChild(Object*); // �ڽ� üũ

	// ������Ʈ ����
	std::string GetTag(); // �±� ���
	std::string GetName(); // �̸� ���
	void SetTag(std::string); // �±� ����
	void SetName(std::string); // �̸� ����
	void Destroy(); // ������Ʈ ����
	bool IsEnable(); // Ȱ��ȭ ���� ���
	ObjectState GetState() { return state; }

	template<typename T>
	T* AttachComponent(); // ������Ʈ�� �߰�
	template<typename T>
	void DetachComponent(); // ������Ʈ�� ����
	template<typename T>
	T* GetComponent(); // ������Ʈ ȹ��

	// �� �޼���
	Scene* GetScene();
	Object* CreateObject(); // �� ������Ʈ ����, ������ ������Ʈ ������ ������ �̿��ؾ���
	Object* AttachObject(Object*); // ������ ������Ʈ�� ����
	Object* FindObject(const Object*); // ������Ʈ�� ã��
	Object* FindObjectByTag(const std::string); // �±׿� �´� ������Ʈ�� ã��
	Object* FindObjectByName(const std::string); // �̸��� �´� ������Ʈ�� ã��
	Object* FindObjectCondition(std::function<bool(const Object*)>); // ���ǿ� �´� ������Ʈ�� ã��
	std::vector<Object*> FindObjectsByTag(const std::string); // �±׿� �´� ������Ʈ���� ã��
	std::vector<Object*> FindObjectsByName(const std::string); // �̸��� �´� ������Ʈ���� ã��
	std::vector<Object*> FindObjectsCondition(std::function<bool(const Object*)>); // ���ǿ� �´� ������Ʈ���� ã��
	Camera* CreateCamera(); // �� ī�޶� ����, ������ ī�޶� ������ ������ �̿��ؾ���
	Camera* AttachCamera(Camera*); // ������ ī�޶� ����
	Camera* FindCamera(const Camera*); // ī�޶� ã��
	Camera* FindCameraByName(const std::string); // �̸��� �´� ī�޶� ã��
	Camera* FindCameraCondition(std::function<bool(const Camera*)>); // ���ǿ� �´� ������Ʈ�� ã��
	std::vector<Camera*> FindCamerasCondition(std::function<bool(const Camera*)>); // ���ǿ� �´� ������Ʈ���� ã��

	// ����������Ŭ �޼���
	void OnCreate() {} // ��ü ������ ���ÿ� �����
	void OnFirstUpdate() {} // ���� ù ������Ʈ
	void OnFirstUpdateBefore() {} // ���� ù ������Ʈ ����
	void OnUpdate() {} // ������Ʈ���� ��
	void OnUpdateBefore() {} // ������Ʈ ��
	void OnFirstRender() {} // ù ������ ���� ��
	void OnFirstRenderBefore() {} // ù ������ ����
	void OnRender() {} // ������ ���� ��
	void OnRenderBefore() {} // ������ ��
	void OnDestroy() {} // ��ü�� �������� ��

	// �̺�Ʈ �޼���
	void OnAttachComponent() {} // ������Ʈ�� �߰����� ��
	void OnDetachComponent() {} // ������Ʈ�� �������� ��
	void OnCollisionEnter() {} // �浹���� ��
	void OnCollisionStay() {} // �浹��
	void OnCollisionExit() {} // �浹�� ������ ��
	void OnChangeName() {} // �̸� ����
	void OnChangeTag() {} // �±� ����
	void OnChangeParent() {} // �θ� ������Ʈ ������ �ٲ���� ��
	void OnAttachChild() {} // �ڽ� ������Ʈ ������ �߰����� ��
	void OnDetachChild() {} // �ڽ� ������Ʈ ������ �������� ��

	// ����������Ŭ ������
	std::function<void()> onCreateListener = NULL;
	std::function<void()> onFirstUpdateListener = NULL;
	std::function<void()> onFirstUpdateBeforeListener = NULL;
	std::function<void()> onUpdateListener = NULL;
	std::function<void()> onUpdateBeforeListener = NULL;
	std::function<void()> onFirstRenderListener = NULL;
	std::function<void()> onFirstRenderBeforeListener = NULL;
	std::function<void()> onRenderListener = NULL;
	std::function<void()> onRenderBeforeListener = NULL;
	std::function<void()> onDestroyListener = NULL;

	// �̺�Ʈ ������
	std::function<void()> onAttachComponentListener = NULL;
	std::function<void()> onDetachComponentListener = NULL;
	std::function<void()> onCollisionEnterListener = NULL;
	std::function<void()> onCollisionStayListener = NULL;
	std::function<void()> onCollisionExitListener = NULL;
	std::function<void()> onChangeNameListener = NULL;
	std::function<void()> onChangeTagListener = NULL;
	std::function<void()> onChangeParentListener = NULL;
	std::function<void()> onAttachChildListener = NULL;
	std::function<void()> onDetachChildListener = NULL;

	// ��Ÿ
	bool GetIsFirstRender() { return isFirstRender; }
	bool GetIsFirstUpdate() { return isFirstUpdate; }
};

template<typename T>
T* Object::AttachComponent()
{
	std::type_index i(T::GetFamilyID());
	if (components.count(i) > 0)
		delete components[i];

	T* component = new T();
	components[i] = component;

	return component;
}

template<typename T>
void Object::DetachComponent(void)
{
	std::type_index i(T::GetFamilyID());
	Component* component = components[i];
	delete component;
	components.erase(i);
}

template<typename T>
T* Object::GetComponent(void)
{
	std::type_index i(T::GetFamilyID());
	if (components.count(i) <= 0)
		return nullptr;

	return static_cast<T*>(components[i]);
}