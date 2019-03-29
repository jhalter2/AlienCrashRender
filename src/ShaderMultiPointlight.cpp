#include "ShaderMultiPointlight.h"
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>
#include "Texture.h"

ShaderMultiPointlight::ShaderMultiPointlight(ID3D11Device* dev)
	: ShaderBase(dev, L"../Assets/Shaders/TextureMultiPointlight.hlsl")
{
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	this->CreateInputLayout(layout, numElements);

	HRESULT hr = S_OK;

	// View Projection buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CamMatrices);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferCamMatrices);
	assert(SUCCEEDED(hr));

	// light param
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_LightParams);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferLightParams);
	assert(SUCCEEDED(hr));

	// Color buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_WorldAndMaterial);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWordAndMaterial);
	assert(SUCCEEDED(hr));

	// Fog buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_FogParameters);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferFogParams);
	assert(SUCCEEDED(hr));

	index = 0;
	//default fog parameters
	SetFogParameters();
}

ShaderMultiPointlight::~ShaderMultiPointlight()
{
	ReleaseAndDeleteCOMobject(mpBuffWordAndMaterial);
	ReleaseAndDeleteCOMobject(mpBufferLightParams);
	ReleaseAndDeleteCOMobject(mpBufferCamMatrices);
	ReleaseAndDeleteCOMobject(mpBufferFogParams);
}

void ShaderMultiPointlight::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	CamMatrices	mCamMatrices;
	mCamMatrices.View = view;
	mCamMatrices.Projection = proj;

	this->GetContext()->UpdateSubresource(mpBufferCamMatrices, 0, nullptr, &mCamMatrices, 0, 0);
}

void ShaderMultiPointlight::SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	PointLight PL;
	PL.Light.Ambient = amb;
	PL.Light.Diffuse = dif;
	PL.Light.Specular = sp;
	PL.Position = pos;
	PL.Attenuation = att;
	PL.Range = r;

	Lightlist[index++] = PL;
}

void ShaderMultiPointlight::SendLightParameters(const Vect& eyepos)
{
	Data_LightParams dl;
	dl.EyePosWorld = eyepos;
	for (int i = 0; i < 3; i++) {
		dl.PntLight[i] = Lightlist[i];
	}
	this->GetContext()->UpdateSubresource(mpBufferLightParams, 0, nullptr, &dl, 0, 0);
}

void ShaderMultiPointlight::SendWorldAndMaterial(const Matrix& world, const Vect& amb, const Vect& dif, const Vect& sp)
{
	Data_WorldAndMaterial wm;
	wm.World = world;
	wm.WorlInv = world.getInv();
	wm.Mat.Ambient = amb;
	wm.Mat.Diffuse = dif;
	wm.Mat.Specular = sp;

	this->GetContext()->UpdateSubresource(mpBuffWordAndMaterial, 0, nullptr, &wm, 0, 0);
}

void ShaderMultiPointlight::SetToContext(ID3D11DeviceContext* devcon)
{
	ShaderBase::SetContext(devcon);
	//in case fog params were never set/sent
	SendFogParameters();
	ShaderBase::SetToContext_VS_PS_InputLayout();

	devcon->VSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->VSSetConstantBuffers(1, 1, &mpBufferLightParams);
	devcon->VSSetConstantBuffers(2, 1, &mpBuffWordAndMaterial);
	devcon->VSSetConstantBuffers(3, 1, &mpBufferFogParams);

	devcon->PSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->PSSetConstantBuffers(1, 1, &mpBufferLightParams);
	devcon->PSSetConstantBuffers(2, 1, &mpBuffWordAndMaterial);
	devcon->PSSetConstantBuffers(3, 1, &mpBufferFogParams);
}

void ShaderMultiPointlight::PrepareRender(ID3D11DeviceContext* devcon, const Matrix& view, const Matrix& proj, const Vect& eyepos) {
	SetToContext(devcon);
	SendCamMatrices(view, proj);
	SendLightParameters(eyepos);
}

void ShaderMultiPointlight::ChangeLightPos(const int& ind, const Vect& pos) {
	Lightlist[ind].Position = pos;
}

void ShaderMultiPointlight::ChangeLightAtten(const int& ind, const Vect& att) {
	Lightlist[ind].Attenuation = att;
}

void ShaderMultiPointlight::SetFogParameters(const float& fStart, const float& fRange, const Vect& fColor) {
	dFp.FogColor = fColor;
	dFp.FogRange = fRange;
	dFp.FogStart = fStart;
}

void ShaderMultiPointlight::SetFogParameters() {
	dFp.FogColor = Vect(0.0f, 0.0f, 0.0f);
	dFp.FogRange = 0.0f;
	dFp.FogStart = 10000.0f;
}

void ShaderMultiPointlight::SendFogParameters() {
	Data_FogParameters fp;
	fp.FogStart = dFp.FogStart;
	fp.FogRange = dFp.FogRange;
	fp.FogColor = dFp.FogColor;

	this->GetContext()->UpdateSubresource(mpBufferFogParams, 0, nullptr, &fp, 0, 0);
}