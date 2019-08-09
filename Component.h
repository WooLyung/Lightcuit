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

	void OnCreate() {} // 객체 생성과 동시에 실행됨
	void OnFirstUpdate() {} // 컴포넌트의 첫 업데이트
	void OnFirstUpdateBefore() {} // 컴포넌트의 첫 업데이트 이전
	void OnUpdate() {} // 업데이트됐을 때
	void OnUpdateBefore() {} // 업데이트 전
	void OnDestroy() {} // 객체가 삭제됐을 때

	std::function<void()> onCreateListener = NULL;
	std::function<void()> onFirstUpdateListener = NULL;
	std::function<void()> onFirstUpdateBeforeListener = NULL;
	std::function<void()> onUpdateListener = NULL;
	std::function<void()> onUpdateBeforeListener = NULL;
	std::function<void()> onDestroyListener = NULL;
};