#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"
#include "Model.h"
#include "d3dUtil.h"

class Model;
class Texture;
class ShaderMultiPointlight;

class TerrainModel : public Align16
{

private:
	Model * pModTerrain;

	int TexelIndex(int side, int i, int j);
	void CalculateVerts(int nverts, float len, float height, float trans, float scale, float xtrans, float ztrans);
	void CalculateTris(float len, float uRep, float vRep);
	void SetUV(float ur, float vr, int len);

	TriangleByIndex* pTriList;
	StandardVertex* pVerts;

	const DirectX::Image* hgtmap;

	ShaderMultiPointlight* pSMP;
	Matrix world;
	Texture* pTex;
public:
	TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, ShaderMultiPointlight* smp, Texture* tex, float len, float maxheight, float ytrans, float RepeatU, 
		float RepeatV, float scale = 1.0f, float xtrans = 0.0f, float ztrans = 0.0f);
	~TerrainModel();

	void SetWorld(const Matrix& m);
	void Render();
};

#endif _TerrainModel
