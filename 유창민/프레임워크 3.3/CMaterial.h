#pragma once
#include"UploadBuffer.h"

using namespace DirectX;

struct MaterialData
{
	XMFLOAT4 Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	float Roughness = 0.25f;	//��ĥ��
	XMFLOAT3 CustomMaterial = { 0,0,0 };
	XMFLOAT4 Emissive = { 0, 0, 0, 1.0f };

};


class CMaterial
{
public:
	CMaterial(ID3D12Device* Device, ID3D12GraphicsCommandList* commandlist);
	CMaterial();
	~CMaterial();

	void UpdateConstantBuffer(ID3D12GraphicsCommandList* commandlist);
	UploadBuffer<MaterialData>* ConstBuffer = nullptr;
	MaterialData MatData;
};

