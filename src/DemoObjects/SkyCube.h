#ifndef _SkyCube
#define _SkyCube

#include <d3d11.h>
#include "DirectXTex.h"
#include "Model.h"
#include "d3dUtil.h"

class ShaderTexture;
class Texture;

class SkyCube : public Align16
{
private:
	Model* pBox;

public:
	SkyCube(const SkyCube&) = delete;
	SkyCube(Model&&) = delete;
	SkyCube& operator=(const SkyCube&) & = delete;
	SkyCube& operator=(SkyCube&&) & = delete;
	~SkyCube();

	SkyCube(ID3D11Device* dev, ShaderTexture* shader, Texture* tex, float len);

	void SetWorld(const Matrix& m);
	void Render();
private:
	Texture* pTex;
	ShaderTexture* pStex;
	Matrix world;
	StandardVertex* pVerts;
	TriangleByIndex* pTriList;
};

#endif _SkyCube
