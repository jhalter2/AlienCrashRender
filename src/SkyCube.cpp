#include "SkyCube.h"
#include "Model.h"
#include "d3dUtil.h"
#include "Texture.h"
#include "ShaderTexture.h"

SkyCube::SkyCube(ID3D11Device* dev, ShaderTexture* shader, Texture* tex, float len) {
	pStex = shader;
	pTex = tex;
	int nverts = 24;
	pVerts = new StandardVertex[nverts];

	int ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	//bottom face
	pVerts[0].set(-0.5f * len, 0, -0.5f * len, 0.25, 0.97);
	pVerts[1].set(-0.5f * len, 0, 0.5f * len, 0.25, 0.66);
	pVerts[2].set(0.5f * len, 0, 0.5f * len, 0.50, 0.66);
	pVerts[3].set(0.5f * len, 0, -0.5f * len, 0.50, 0.97);

	//right face
	pVerts[4].set(0.5f * len, 0,		   0.5f * len, 0.50, 0.65);
	pVerts[5].set(0.5f * len, 1.0f * len, 0.5f * len,  0.50, 0.33);
	pVerts[6].set(0.5f * len, 1.0f * len, -0.5f * len, 0.75, 0.33);
	pVerts[7].set(0.5f * len, 0, -0.5f * len,          0.75, 0.65);

	//left face
	pVerts[8].set(-0.5f * len, 0, -0.5f * len,			0, 0.65);
	pVerts[9].set(-0.5f * len, 1.0f * len, -0.5f * len, 0, 0.33);
	pVerts[10].set(-0.5f * len, 1.0f * len, 0.5f * len, 0.25, 0.33);
	pVerts[11].set(-0.5f * len, 0, 0.5f * len,			0.25, 0.65);

	//front face
	pVerts[12].set(-0.5f * len,  0,           0.5f * len, 0.25, 0.65);
	pVerts[13].set(-0.5f * len,  1.0f * len,  0.5f * len, 0.25, 0.33);
	pVerts[14].set( 0.5f * len,  1.0f * len,  0.5f * len, 0.50, 0.33);
	pVerts[15].set( 0.5f * len,  0,           0.5f * len, 0.50, 0.65);

	//top face
	pVerts[16].set(0.5f * len,   1.0f * len,    0.5f * len, 0.48, 0.35);
	pVerts[17].set(-0.5f * len, 1.0f * len, 0.5f * len, 0.25, 0.33);
	pVerts[18].set(-0.5f * len, 1.0f * len, -0.5f * len, 0.25, 0);
	pVerts[19].set(0.5f * len, 1.0f * len, -0.5f * len, 0.50, 0);

	//back face
	pVerts[20].set(-0.5f * len, 0, -0.5f * len, 0.75, 0.66);
	pVerts[21].set(-0.5f * len, 1.0f * len, -0.5f * len, 0.75, 0.33);
	pVerts[22].set(0.5f * len, 1.0f * len, -0.5f * len, 1.0, 0.33);
	pVerts[23].set(0.5f * len, 0, -0.5f * len, 1.0, 0.66);

	//triangles
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);
	pTriList[2].set(4, 5, 6);
	pTriList[3].set(4, 6, 7);
	pTriList[4].set(8, 9, 10);
	pTriList[5].set(8, 10, 11);
	pTriList[6].set(12, 13, 14);
	pTriList[7].set(12, 14, 15);
	pTriList[8].set(16, 17, 18);
	pTriList[9].set(16, 18, 19);
	pTriList[10].set(23, 22, 20);
	pTriList[11].set(20, 22, 21);

	pBox = new Model(dev, pVerts, nverts, pTriList, ntri);
}

SkyCube::~SkyCube()
{
	delete[] pVerts;
	delete[] pTriList;
	delete pBox;
}

void SkyCube::SetWorld(const Matrix& m) {
	world = m;
}

void SkyCube::Render()
{
	pTex->SetToContext(pStex->GetContext());
	pStex->SendWorldColor(world, Vect(1, 1, 1));
	pBox->SetToContext(pStex->GetContext());
	pBox->Render(pStex->GetContext());
}