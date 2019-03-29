#include "GraphicObject_TextureLight.h"
#include "Model.h"
#include "ShaderColor.h"
#include "ShaderTextureLight.h"
#include "ShaderMultiPointlight.h"
#include <assert.h>
#include "Vect.h"
#include "Texture.h"

GraphicObject_TextureLight::GraphicObject_TextureLight(ShaderTextureLight* shader, Model* mod)
{
	SetModel(mod);
	pShaderL = shader;
	pShaderMulti = nullptr;
	World = Matrix(IDENTITY);

	meshCount = mod->GetMeshCount();
	MeshColors = new Vect[meshCount];
	for (int i = 0; i < meshCount; i++)
		MeshColors[i] = Vect(1, 1, 1);
}

GraphicObject_TextureLight::GraphicObject_TextureLight(ShaderMultiPointlight* shader, Model* mod) {
	SetModel(mod);
	pShaderMulti = shader;
	pShaderL = nullptr;
	World = Matrix(IDENTITY);

	meshCount = mod->GetMeshCount();
	MeshColors = new Vect[meshCount];
	for (int i = 0; i < meshCount; i++)
		MeshColors[i] = Vect(1, 1, 1);
}

GraphicObject_TextureLight::~GraphicObject_TextureLight()
{
	delete[] MeshColors;
}

void GraphicObject_TextureLight::SetColor(const Vect& col)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		MeshColors[i] = col;
}

void GraphicObject_TextureLight::SetColor(const Vect& col, int meshnum) {
	assert(pModel->ValidMeshNum(meshnum));
	MeshColors[meshnum] = col;
}

void GraphicObject_TextureLight::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_TextureLight::Render()
{
	//if rendering with just the texture light shader
	if (pShaderMulti == nullptr) {
		pModel->SetToContext(pShaderL->GetContext());
		pTex->SetToContext(pShaderL->GetContext());
		for (int i = 0; i < pModel->GetMeshCount(); i++)
		{
			pShaderL->SendWorldAndMaterial(World, MeshColors[i], MeshColors[i]);
			pModel->RenderMesh(pShaderL->GetContext(), i);
		}
	}
	//rendering with multi pointlight
	else {
		pModel->SetToContext(pShaderMulti->GetContext());
		pTex->SetToContext(pShaderMulti->GetContext());
		for (int i = 0; i < pModel->GetMeshCount(); i++)
		{
			pShaderMulti->SendWorldAndMaterial(World, MeshColors[i], MeshColors[i]);
			pModel->RenderMesh(pShaderMulti->GetContext(), i);
		}
	}
}

void GraphicObject_TextureLight::SetTexture(Texture* tex) {
	pTex = tex;
}