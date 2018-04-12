#pragma once
#include "stdafx.h"
#include "PhysicsEngine\MyMiniPysicsEngine.h"
#include <unordered_map>

class StaticObject 
{
private:
	unordered_map<int, Position> m_boxPos;

	bool staticobject{ true };

	XMFLOAT3 OffLookvector;
	XMFLOAT3 OffRightvector;

	XMFLOAT3 Lookvector; 
	XMFLOAT3 Rightvector;
	XMFLOAT3 Upvector;

	StaticObject_Info sobj_data;

	list<StaticObject*> m_staticObjs;
	
public:
	StaticObject(){};

	void SET_PosOfBox();
	void InitBoxObjects();

	void UpdateLookVector();
	void GetUpVector();

	list<StaticObject*> GET_SObj_List() const { return m_staticObjs; } 

	~StaticObject();
};

