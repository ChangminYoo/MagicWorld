#pragma once
#include "d3dUtil.h"
#include "Shader.h"
#include "Timer.h"
#include "Light.h"
#include "CPlayer.h"
using Microsoft::WRL::ComPtr;

#define LIGHT_MAX 10
#define GS_START 1//시작상태
#define GS_LOAD 2//로딩상태
#define GS_PLAY 3//플레이 상태
#define GS_END 4//엔딩 상태


class Scene
{
public:
	Scene(HWND hwnd, ID3D12Device* m_Device, ID3D12GraphicsCommandList* m_DC, float cw, float ch);
	Scene();
	~Scene();
	float mWidth = 0;
	float mHeight = 0;
	bool resize = false;

	//게임오브젝트, 카메라,세이더오브젝트,라이트,샘플러 포함해야댐	
	int nShader;//세이더 갯수
	int GAMESTATE = GS_START;//게임상태.
	bool FirstLoad = false;//첫 로딩인가?

	HWND hWnd;
	ComPtr<ID3D12RootSignature> rootsg;//루트시그니처
	array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSamplers();

public:

	//주의 할점. 이 두가지는 프레임워크에서 생성해둔것을 가져다가만 쓰므로 멋대로 릴리즈 하면 안된다.
	ID3D12GraphicsCommandList* commandlist;//커맨드리스트 = dc
	ID3D12Device* device;//디바이스

	void SetGameState(int num) { GAMESTATE = num; }//게임상태 변경
	void SceneState();
	void CreateRootSignature();//루트시그니처는 항상 연결될 리소스들과 동일해야함.(물론 버텍스나 인덱스버퍼는 제외)
	void CreateShaderObject();
	void CreateGameObject();
	void CreateUI();
	//UI마다 틱함수를 만들기보단 그냥 UI들의 모든틱을 여기에서 처리함. 왜이렇게하냐면 UI는 딱히 어떤 오브젝트리스트에 들어가지 않기때문.
	void UITick(const GameTimer& gt);
	//	void CreateAllObject();
	//	void DeleteStaticMesh();

	int GetGameState() { return GAMESTATE; }

	void Render(const GameTimer& gt);	//이후 카메라를 인자로 받아야됨
	void Tick(const GameTimer& gt);


	Shader* Shaders = NULL;
	CPlayer* Player = NULL;
	CLight* light = NULL;

	list<CGameObject*> DynamicObject;//애니메이션이 되는 오브젝트들이 여기에 모임.
	list<CGameObject*> BulletObject;//투사체들이 모인다.
	//list<CGameObject*> MoveStaticObject;//애니메이션은 없지만 이동하는
	list<CGameObject*> StaticObject;//애니메이션이 없는 모든 오브젝트들이 모인다.
	list<CGameObject*> BbObject;//빌보드가 사용되는 오브젝트들(데미지, hp바, 기타 파티클등)
	list<CGameObject*> RigidObject;//리지드바디를 사용하는 오브젝트들.
	CGameObject* SkyObject = NULL;//스카이박스용 객체를 다룬다. 스카이박스는 하나면 됨.

	vector<CGameObject*> LandObject;


	CGameObject* AimUI = NULL;
	CGameObject* BackGround = NULL;
	CGameObject* SkillUI[4] = {NULL};
	CGameObject* SkillFrameUI[4] = { NULL };
	CGameObject* SkillCoolBar[4] = { NULL };
	CGameObject* SelectBar = NULL; //스킬선택

public:
	Player_Data * Get_PlayerServerData(const unsigned int& id);
	Player_Data* Get_MonsterServerData(const unsigned int& id);
	int my_ClientID{ 0 };

	void SET_PLAYER_BY_SEVER_DATA(const unsigned short& id,const Player_Data& playerdata, const unsigned char& packet_type);
	void SET_SOBJECT_BY_SERVER_DATA(const unsigned short& id, StaticObject_Info& sobjdata, const unsigned char& type);
	void SET_BULLET_BY_SERVER_DATA(BulletObject_Info& bulldata, const unsigned char& packet_type);
	void SET_PLAYER_ANIMATION_BY_SERVER_DATA(const unsigned short& id, const unsigned char& ani);
	void Set_RemovePlayerData(const unsigned int& id, Player_Data& playerdata);
	void SET_PLAYER_STATE_BY_SERVER_DATA(const Player_Data& playerdata);

	//서버에서 받은 PlayerData를 이용하면 이 함수는 없어도됨
	//PlayerData를 기반으로 Player의 값이 달라질것이므로
	CGameObject* Get_GameObject{ nullptr };

private:
	//여기다 물체 배치에 대한 상수들 넣는다.
	float BigWall_X1 = 300 * sinf(0.4f * MMPE_PI);
	float BigWall_Z1 = (600 * cosf(0.4f * MMPE_PI) + 600) / 2;

	float BigWall_X2 = ((600 * sinf(0.4f * MMPE_PI)) + (600 * sinf(0.8f * MMPE_PI))) / 2;
	float BigWall_Z2 = ((600 * cosf(0.4f * MMPE_PI)) + (-600 * cosf(0.2f * MMPE_PI))) / 2;

	float BigWall_Z3 = -600 * cosf(0.2f * MMPE_PI);

	float BigWall_Rad1 = MMPE_PI / 5; //36degree


};

