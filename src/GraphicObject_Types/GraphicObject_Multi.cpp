#include "GraphicObject_Multi.h"
#include "Model.h"
#include "ShaderColor.h"
#include "ShaderTextureLight.h"
#include "ShaderColorLight.h"
#include <assert.h>

GraphicObject_Multi::GraphicObject_Multi(ShaderTextureLight* shader0, ShaderColorLight* shader1, ShaderColor* shader2, Model* mod)
{
	SetModel(mod);
	pShaderTexLight = shader0;
	pShaderColLight = shader1;
	pShaderCol = shader2;

	//Color = Vect(1, 1, 1);
	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	Vect w = Vect(1, 1, 1);
	MeshColors = new Mesh_Data[n];
	//fill each data struct with white as default color and
	//cast the mesh number to a different shader defined in the enum class
	for (int i = 0; i < n; i++) {
		MeshColors[i].Color = w;
		MeshColors[i].st = static_cast<ShaderType>(i);
	}
}

GraphicObject_Multi::~GraphicObject_Multi()
{
	delete[] MeshColors;
}

void GraphicObject_Multi::SetColor(const Vect& col, int meshnum, int shadernum) {
	assert(pModel->ValidMeshNum(meshnum));
	MeshColors[meshnum].Color = col;
}

void GraphicObject_Multi::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_Multi::SetTexture(Texture* t, ID3D11Device* d3dDev)
{
	tex = t;
	pShaderTexLight->SetTexture(d3dDev);
}

void GraphicObject_Multi::Render()
{
	//render everything different based on its enum in the struct

	//render plain colors
	pModel->SetToContext(pShaderCol->GetContext());
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		if (static_cast<int>(MeshColors->st) == 0) {
			pShaderCol->SendWorldColor(World, MeshColors[i].Color);
			pModel->RenderMesh(pShaderCol->GetContext(), i);
		}	
	}
	//render color lights
	pModel->SetToContext(pShaderColLight->GetContext());
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		if (static_cast<int>(MeshColors->st) == 1) {
			pShaderColLight->SendWorldAndMaterial(World, MeshColors[i].Color, MeshColors[i].Color);
			pModel->RenderMesh(pShaderColLight->GetContext(), i);
		}	
	}
	//render textures
	tex->SetToContext(pShaderTexLight->GetContext());
	pModel->SetToContext(pShaderTexLight->GetContext());
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		if (static_cast<int>(MeshColors->st) == 2) {
			pShaderTexLight->SendWorldAndMaterial(World, MeshColors[i].Color, MeshColors[i].Color);
			pModel->RenderMesh(pShaderTexLight->GetContext(), i);
		}
	}
}