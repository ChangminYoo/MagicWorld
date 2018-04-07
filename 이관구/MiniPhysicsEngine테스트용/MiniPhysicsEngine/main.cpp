// MiniPhysicsEngine.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//
#include<time.h>
#include<stdlib.h>
#include "stdafx.h"
#include"MyMiniPysicsEngine.h"

#include<iostream>
using namespace std;

//물리엔진은 다음과 같은 순서로 작동해야함.
//1. 힘을 가함. 즉 시스템 함수들에 의해 힘이 가해진다.
//2. 적분기를 통해 위치를 변경 시키고 속도또한 변경시킨다.
//3. 사후처리를 해준다. 대표적으로 충돌이 있다.

//예를들면 1. 위치가 0 보다 크면 중력을 가함. 2. 적분기를 통해 아래로 내려가는 속도가 만들어짐 3. 위치가 0보다 작으면
//위치를 0으로 만들어주는 사후처리를 한다.

/*
	제너레이트 함수를 이용해 시스템함수 만들기.

	시스템함수는 FrameWork에서 만든다.
	예를들어 그라비티시스템이라 해보자

	그라비티시스템 슈도코드

	void SystemGravity()
	{
		for i in dynamicobject
		{
			if(i의 centerpos의 y가 0보다 클경우)//땅보다 위에 있을경우
			{
				GeneratorGravity.Update(i의physicspoint);
			}
			else//0이하일경우
			{
				i의 CenterPos.y=0;
			}
		}
	}

	그리고 게임오브젝트는 항상 physicspoint의 적분기를 호출해서 정점의 위치를 갱신한다.

*/


int main()
{
	RigidBody p1;
	XMFLOAT4 or1{ 0,0,0,1 };
	XMFLOAT4 pos1{ 0,0,0,1 };
	XMFLOAT3 l1{ 0,0,1 };
	XMFLOAT3 r1{ 1,0,0 };
	XMFLOAT3 u1{ 0,1,0 };

	p1.SetHalfBox(2, 2, 2);
	p1.SetOrient(&or1);
	p1.SetPosition(&pos1);

	//=============p2================//

	RigidBody p2;
	XMFLOAT4 or2{ 0,0,0,1 };
	
	XMVECTOR rot = XMQuaternionRotationAxis(XMVectorSet(0, 0, 1, 0), MMPE_PI / 4);
	XMFLOAT4 rotf;
	XMStoreFloat4(&rotf, rot);
	auto t1 = QuaternionRotation(l1, MMPE_PI / 6);
	auto t2= QuaternionRotation(r1, -MMPE_PI / 4);
	auto t3= QuaternionRotation(u1, -MMPE_PI / 4);
	or2= QuaternionMultiply( or2 , t2);
	or2 = QuaternionMultiply(or2, t3);
	or2 = QuaternionMultiply(or2, t1);


	XMFLOAT4 pos2{ -1.38f,1.48f,0.19f,1 };
	XMFLOAT3 l2{ 0,0,1 };
	XMFLOAT3 r2{ 1,0,0 };
	XMFLOAT3 u2{ 0,1,0 };

	XMVECTOR l = XMLoadFloat3(&l2);
	XMVECTOR r = XMLoadFloat3(&r2);
	XMVECTOR u = XMLoadFloat3(&u2);

	XMVECTOR test = XMVectorSet(1, 1, 0, 1);
	auto m = XMMatrixRotationQuaternion(XMLoadFloat4(&or2));

	l = XMVector3Transform(l, m);
	r = XMVector3Transform(r, m);
	u = XMVector3Transform(u, m);

	test = XMVector3Transform(test, m);

	p2.SetHalfBox(1, 1, 1);
	p2.SetOrient(&or2);
	p2.SetPosition(&pos2);

	XMStoreFloat3(&l2, l);
	XMStoreFloat3(&r2, r);
	XMStoreFloat3(&u2, u);

	bool iscol = false;

	iscol=p1.CollisionTest(p2, l1, r1, u1, l2, r2, u2);

	cout << "상자 1 의 위치 : " << pos1.x <<","<< pos1.y << "," << pos1.z << endl << endl;
	cout << "상자 2 의 위치 : " << pos2.x << "," << pos2.y << "," << pos2.z << endl << endl;
	cout << "충돌 했는지 여부  :" << iscol << endl;
	return 0;
}

