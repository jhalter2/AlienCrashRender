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
	SkyCube(const SkyCube&) = delete;				// Copy constructor
	SkyCube(Model&&) = delete;						// Move constructor
	SkyCube& operator=(const SkyCube&) & = delete;  // Copy assignment operator
	SkyCube& operator=(SkyCube&&) & = delete;       // Move assignment operator
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
