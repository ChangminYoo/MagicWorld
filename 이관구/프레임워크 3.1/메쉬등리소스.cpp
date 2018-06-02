#include"CGameObject.h"
#include"CGameUIObject.h"


bool CCubeManObject::CreateMesh=false;
unordered_map<string, unique_ptr<CTexture>> CCubeManObject::Textures;//텍스처들을 저장함
CMesh  CCubeManObject::Mesh;//나중에 메쉬는 static으로 둬야함
std::vector<ModelAnimation> CCubeManObject::animations;//애니메이션 데이터 저장. 메쉬와 이거,텍스처는 한번만생성해서 공유하도록해야됨
ComPtr<ID3D12DescriptorHeap> CCubeManObject::SrvDescriptorHeap;//텍스처 용 힙
CMaterial CCubeManObject::Mat;


//--------------------------------------------------------------------------------------
bool BulletCube::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> BulletCube::Textures;//텍스처들을 저장함
CMesh  BulletCube::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> BulletCube::SrvDescriptorHeap;//텍스처 용 힙
CMaterial BulletCube::Mat;

//--------------------------------------------------------------------------------------
bool HeavyBulletCube::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> HeavyBulletCube::Textures;//텍스처들을 저장함
CMesh  HeavyBulletCube::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> HeavyBulletCube::SrvDescriptorHeap;//텍스처 용 힙
CMaterial HeavyBulletCube::Mat;
//--------------------------------------------------------------------------------------
bool Tetris1::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> Tetris1::Textures;//텍스처들을 저장함
CMesh  Tetris1::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> Tetris1::SrvDescriptorHeap;//텍스처 용 힙
CMaterial Tetris1::Mat;
//--------------------------------------------------------------------------------------
bool Tetris2::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> Tetris2::Textures;//텍스처들을 저장함
CMesh  Tetris2::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> Tetris2::SrvDescriptorHeap;//텍스처 용 힙
CMaterial Tetris2::Mat;
//--------------------------------------------------------------------------------------
bool Tetris3::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> Tetris3::Textures;//텍스처들을 저장함
CMesh  Tetris3::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> Tetris3::SrvDescriptorHeap;//텍스처 용 힙
CMaterial Tetris3::Mat;
//--------------------------------------------------------------------------------------
bool Tetris4::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> Tetris4::Textures;//텍스처들을 저장함
CMesh  Tetris4::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> Tetris4::SrvDescriptorHeap;//텍스처 용 힙
CMaterial Tetris4::Mat;
//--------------------------------------------------------------------------------------
bool Tetrike::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> Tetrike::Textures;//텍스처들을 저장함
CMesh  Tetrike::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> Tetrike::SrvDescriptorHeap;//텍스처 용 힙
CMaterial Tetrike::Mat;
//--------------------------------------------------------------------------------------
bool DiceStrike::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> DiceStrike::Textures;//텍스처들을 저장함
CMesh  DiceStrike::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> DiceStrike::SrvDescriptorHeap;//텍스처 용 힙
CMaterial DiceStrike::Mat;
//--------------------------------------------------------------------------------------
bool ShieldAmor::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> ShieldAmor::Textures;//텍스처들을 저장함
CMesh ShieldAmor::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> ShieldAmor::SrvDescriptorHeap;//텍스처 용 힙
CMaterial ShieldAmor::Mat;
//--------------------------------------------------------------------------------------
bool SphereObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> SphereObject::Textures;//텍스처들을 저장함
CMesh  SphereObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> SphereObject::SrvDescriptorHeap;//텍스처 용 힙
//--------------------------------------------------------------------------------------
bool CubeObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> CubeObject::Textures;//텍스처들을 저장함
CMesh  CubeObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> CubeObject::SrvDescriptorHeap;//텍스처 용 힙
CMaterial CubeObject::Mat;
//--------------------------------------------------------------------------------------
bool MoveCubeObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> MoveCubeObject::Textures;//텍스처들을 저장함
CMesh  MoveCubeObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> MoveCubeObject::SrvDescriptorHeap;//텍스처 용 힙
CMaterial MoveCubeObject::Mat;
//--------------------------------------------------------------------------------------
bool GridObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> GridObject::Textures;//텍스처들을 저장함
CMesh  GridObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> GridObject::SrvDescriptorHeap;//텍스처 용 힙
CMaterial GridObject::Mat;
//--------------------------------------------------------------------------------------
bool ParticleObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> ParticleObject::Textures;//텍스처들을 저장함
CMesh  ParticleObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> ParticleObject::SrvDescriptorHeap;//텍스처 용 힙
//--------------------------------------------------------------------------------------
bool DamageObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> DamageObject::Textures;//텍스처들을 저장함
CMesh  DamageObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> DamageObject::SrvDescriptorHeap;//텍스처 용 힙
//--------------------------------------------------------------------------------------
bool RigidCubeObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> RigidCubeObject::Textures;//텍스처들을 저장함
CMesh  RigidCubeObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> RigidCubeObject::SrvDescriptorHeap;//텍스처 용 힙
CMaterial RigidCubeObject::Mat;
//--------------------------------------------------------------------------------------
bool AimObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> AimObject::Textures;//텍스처들을 저장함
CMesh  AimObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> AimObject::SrvDescriptorHeap;//텍스처 용 힙
 //--------------------------------------------------------------------------------------
bool BackGroundObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> BackGroundObject::Textures;//텍스처들을 저장함
CMesh  BackGroundObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> BackGroundObject::SrvDescriptorHeap;//텍스처 용 힙
//--------------------------------------------------------------------------------------
bool SkillFrameUIObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> SkillFrameUIObject::Textures;//텍스처들을 저장함
CMesh  SkillFrameUIObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> SkillFrameUIObject::SrvDescriptorHeap;//텍스처 용 힙

bool SkillUIObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> SkillUIObject::Textures;//텍스처들을 저장함
CMesh  SkillUIObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> SkillUIObject::SrvDescriptorHeap;//텍스처 용 힙
//--------------------------------------------------------------------------------------
bool BarObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> BarObject::Textures;//텍스처들을 저장함
CMesh  BarObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> BarObject::SrvDescriptorHeap;//텍스처 용 힙
//--------------------------------------------------------------------------------------
bool BarFrameObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> BarFrameObject::Textures;//텍스처들을 저장함
CMesh  BarFrameObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> BarFrameObject::SrvDescriptorHeap;//텍스처 용 힙

//--------------------------------------------------------------------------------------
bool SelectBarObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> SelectBarObject::Textures;//텍스처들을 저장함
CMesh SelectBarObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> SelectBarObject::SrvDescriptorHeap;//텍스처 용 힙			

//--------------------------------------------------------------------------------------
bool CoolBarObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> CoolBarObject::Textures;//텍스처들을 저장함
CMesh  CoolBarObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> CoolBarObject::SrvDescriptorHeap;//텍스처 용 힙

//--------------------------------------------------------------------------------------
bool DiceObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> DiceObject::Textures;//텍스처들을 저장함
CMesh  DiceObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> DiceObject::SrvDescriptorHeap;//텍스처 용 힙

//--------------------------------------------------------------------------------------

CMaterial SmallWallObject::Mat;
bool SmallWallObject::CreateMesh;//최초로 false며 메쉬를 만든후 true가된다.
unordered_map<string, unique_ptr<CTexture>> SmallWallObject::Textures;//텍스처들을 저장함
CMesh SmallWallObject::Mesh;//오로지 한번만 만들어짐
ComPtr<ID3D12DescriptorHeap> SmallWallObject::SrvDescriptorHeap;//텍스처 용 힙

// --------------------------------------------------------------------------------------

CMaterial BigWallObject::Mat;
bool BigWallObject::CreateMesh;//최초로 false며 메쉬를 만든후 true가된다.
unordered_map<string, unique_ptr<CTexture>> BigWallObject::Textures;//텍스처들을 저장함
CMesh BigWallObject::Mesh;//오로지 한번만 만들어짐
ComPtr<ID3D12DescriptorHeap> BigWallObject::SrvDescriptorHeap;//텍스처 용 힙

// --------------------------------------------------------------------------------------

CMaterial BuildingObject::Mat;
bool BuildingObject::CreateMesh;//최초로 false며 메쉬를 만든후 true가된다.
unordered_map<string, unique_ptr<CTexture>> BuildingObject::Textures;//텍스처들을 저장함
CMesh BuildingObject::Mesh;//오로지 한번만 만들어짐
ComPtr<ID3D12DescriptorHeap> BuildingObject::SrvDescriptorHeap;//텍스처 용 힙

// --------------------------------------------------------------------------------------

CMaterial Rock1Object::Mat;
bool Rock1Object::CreateMesh;//최초로 false며 메쉬를 만든후 true가된다.
unordered_map<string, unique_ptr<CTexture>> Rock1Object::Textures;//텍스처들을 저장함
CMesh Rock1Object::Mesh;//오로지 한번만 만들어짐
ComPtr<ID3D12DescriptorHeap> Rock1Object::SrvDescriptorHeap;//텍스처 용 힙


 //--------------------------------------------------------------------------------------

bool RangeObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> RangeObject::Textures;//텍스처들을 저장함
CMesh  RangeObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> RangeObject::SrvDescriptorHeap;//텍스처 용 힙
CMaterial RangeObject::Mat;

bool BloodParticleObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> BloodParticleObject::Textures;//텍스처들을 저장함
CMesh BloodParticleObject::Mesh;//나중에 메쉬는 static으로 둬야함
ComPtr<ID3D12DescriptorHeap> BloodParticleObject::SrvDescriptorHeap;//텍스처 용 힙
																	
//-------------------------------------------------------------------------------------
bool ImpObject::CreateMesh = false;
unordered_map<string, unique_ptr<CTexture>> ImpObject::Textures;//텍스처들을 저장함
CMesh  ImpObject::Mesh;//나중에 메쉬는 static으로 둬야함
std::vector<ModelAnimation> ImpObject::animations;//애니메이션 데이터 저장. 메쉬와 이거,텍스처는 한번만생성해서 공유하도록해야됨
ComPtr<ID3D12DescriptorHeap> ImpObject::SrvDescriptorHeap;//텍스처 용 힙
CMaterial ImpObject::Mat;
