#pragma once
//#include "../PhysicsEngine/MyMiniPysicsEngine.h"
//#include "../PhysicsEngine/PhysicalEffect.h"

struct ObjectStatus
{
	unsigned short attack{ 10 };
	unsigned char speed{ 50 };
	unsigned short orignHP{ 100 };
	unsigned short curHP{ 100 };
	unsigned short exp{ 0 };
	unsigned char level{ 1 };
};

class CMonoObject
{
protected:
	unsigned short		m_id{ 0 };
	char				m_fixed{ true };
	char				m_alive{ true };
	Position			m_pos4f;
	Rotation			m_rot4f;
	char				m_dir;
	char				m_ai;
	char				m_godmode{ false };
	char				m_airbone{ false };
	unsigned char	    m_type;			//스테틱 오브젝트 종류(box, wall, building...)

	//1. 오브젝트 스테이터스(공격력, 속력, 체력, 경험치, 레벨)
	ObjectStatus	    m_ability;

	//2. 룩벡터와 라이트벡터
	XMFLOAT3			m_Lookvector;//룩벡터. 오브젝트가 바라보고있는 방향.
	XMFLOAT3			m_Rightvector;//라이트벡터. 오브젝트가 바라보고있는 방향의 오른쪽방향.
	XMFLOAT3			m_Upvector; //업벡터
	XMFLOAT3			m_OffLookvector;//초기룩벡터. 오브젝트가 바라보고있는 방향.
	XMFLOAT3			m_OffRightvector;//초기라이트벡터. 오브젝트가 바라보고있는 방향의 오른쪽방향.

	//3. 물리효과
	RigidBody			*rb{ nullptr };
	PhysicsPoint		*pp{ nullptr };
	//PhysicalEffect		*pe{ nullptr };

	__int64				m_prevtime{ 0 };
	__int64				m_currtime{ 0 };
	float				m_deltime{ 0 };


public:
	CMonoObject();
	virtual void Initialize();
	virtual void Update(float deltime);
	virtual void Collision();
	virtual void AfterGravitySystem(float deltime);
	virtual void GravitySystem(float deltime);
	virtual void Tick(float deltime);
	void UpdateUpvector();
	void UpdateLookvector();
	void UpdatePPosCenterPos();
	virtual ~CMonoObject();
};

