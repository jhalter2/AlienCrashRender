#include "GraphicObject_Texture.h"
#include "Model.h"
#include "ShaderColor.h"
#include "ShaderTexture.h"
#include <assert.h>

GraphicObject_Texture::GraphicObject_Texture(ShaderTexture* shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;

	//Color = Vect(1, 1, 1);
	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	MeshColors = new Vect[n];
	for (int i = 0; i < n; i++)
		MeshColors[i] = Vect(0, 0, 0);
}

GraphicObject_Texture::~GraphicObject_Texture()
{
	delete[] MeshColors;
}

void GraphicObject_Texture::SetColor(const Vect& col)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		MeshColors[i] = col;
}

void GraphicObject_Texture::SetColor(const Vect& col, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	MeshColors[meshnum] = col;
}

void GraphicObject_Texture::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_Texture::SetTexture(Texture* t) 
{
	tex = t;
}

void GraphicObject_Texture::Render()
{
	//pShader->SendWorldColor(World, Color);
	pModel->SetToContext(pShader->GetContext());
	tex->SetToContext(pShader->GetContext());
	//pModel->Render(pShader->GetContext());
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldColor(World, MeshColors[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}
