#pragma once
#include "Object.h"

class Object;

class Component
{
private:
	virtual void Update() = 0;
	virtual void Render() = 0;

	friend class Object;

public:
	Component();
	~Component();

	virtual std::type_index GetID(void) = 0 { return typeid(Component); }
	static std::type_index GetFamilyID(void) { return typeid(Component); }

	void OnCreate() {} // ��ü ������ ���ÿ� �����
	void OnFirstUpdate() {} // ������Ʈ�� ù ������Ʈ
	void OnFirstUpdateBefore() {} // ������Ʈ�� ù ������Ʈ ����
	void OnUpdate() {} // ������Ʈ���� ��
	void OnUpdateBefore() {} // ������Ʈ ��
	void OnDestroy() {} // ��ü�� �������� ��

	std::function<void()> onCreateListener = NULL;
	std::function<void()> onFirstUpdateListener = NULL;
	std::function<void()> onFirstUpdateBeforeListener = NULL;
	std::function<void()> onUpdateListener = NULL;
	std::function<void()> onUpdateBeforeListener = NULL;
	std::function<void()> onDestroyListener = NULL;
};