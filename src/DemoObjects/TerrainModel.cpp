#include "TerrainModel.h"
#include <assert.h>
#include "Texture.h"
#include "ShaderMultiPointlight.h"


TerrainModel::TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, ShaderMultiPointlight* smp, Texture* tex, 
	float len, float maxheight, float ytrans, float RepeatU, float RepeatV, float scale, float xtrans, float ztrans)
{
	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));
	hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width);

	pTex = tex;
	pSMP = smp;

	world = Matrix(IDENTITY);

	int nverts = (int)(len*len);
	pVerts = new StandardVertex[nverts];
	int ntri = (int)((len - 1) * (len - 1)) * 2;
	pTriList = new TriangleByIndex[ntri];

	CalculateVerts(nverts, len, maxheight, ytrans, scale, xtrans, ztrans);
	CalculateTris(len, RepeatU, RepeatV);

	pModTerrain = new Model(dev, pVerts, nverts, pTriList, ntri);
}

TerrainModel::~TerrainModel() {
	delete[] pVerts;
	delete[] pTriList;
	delete pModTerrain;
}

void TerrainModel::CalculateTris(float len, float uRep, float vRep) {
	int triCount = 0;
	int inc = 0;

	int l = (int)len;

	for (int i = 0; i < (l - 1); i++) {
		inc = i * 16;
		for (int j = 0; j < (l - 1); j++) {
			if (j == 14) {
				triCount = triCount;
			};
			pTriList[triCount++].set(j + inc, (j + 1) + inc, (j + l) + inc);
			pTriList[triCount++].set((j + l + 1) + inc, (j + l) + inc, (j + 1) + inc);
		}
	}

	SetUV(uRep, vRep, l);
}

int TerrainModel::TexelIndex(int side, int i, int j) {
	size_t pixel_width = 4;			// 4 bytes RGBA per pixel
	return pixel_width * (j*side + i);
}

void TerrainModel::CalculateVerts(int nverts, float len, float height, float trans, float scale,
	float xtrans, float ztrans) {
	size_t side = hgtmap->height;	// the image should be square
									//uint8_t h_val = hgtmap->pixels[TexelIndex(side, 3, 2)]; // the 'R' byte of the pixel at (3,2)
									//0 = black, 255 = white

	float fnverts = (float)nverts;
	int vert = 0;

	float iresult = 0;
	float jresult = 0;

	float calc = len / fnverts;

	int l = (int)len;

	float yVal;
	//rows
	for (int i = 0; i < l; i++) {
		//columns
		for (int j = 0; j < l; j++) {
			iresult = (((calc * i) * (len / 2)) * scale) + xtrans;
			jresult = (((calc * j) * (len / 2)) * scale) + ztrans;
			yVal = ((((float)(hgtmap->pixels[TexelIndex(side, i * 16, j * 16)]) / height) * scale) + trans);
			pVerts[vert++].set(iresult, yVal, jresult);
		}
	}

	//set normals
	int i, j, index = 0;
	float sum[3], length;
	Vect* normals = new Vect[256];

	for (j = 0; j < l; j++)
	{
		for (i = 0; i < l; i++)
		{
			index = (j * l) + i;
			normals[index] = pVerts[index].Pos.getNorm();
		}
	}

	// Now go through all the vertices and take a sum of the face normals that touch this vertex.
	for (j = 0; j < l; j++)
	{
		for (i = 0; i < l; i++)
		{
			// Initialize the sum.
			sum[0] = 0.0f;
			sum[1] = 0.0f;
			sum[2] = 0.0f;

			// Bottom left face.
			if (((i - 1) >= 0) && ((j - 1) >= 0))
			{
				index = ((j - 1) * l) + (i - 1);

				sum[0] += normals[index].X();
				sum[1] += normals[index].Y();
				sum[2] += normals[index].Z();
			}

			// Bottom right face.
			if ((i < l) && ((j - 1) >= 0))
			{
				index = ((j - 1) * l) + i;

				sum[0] += normals[index].X();
				sum[1] += normals[index].Y();
				sum[2] += normals[index].Z();
			}

			// Upper left face.
			if (((i - 1) >= 0) && (j < l))
			{
				index = (j * l) + (i - 1);

				sum[0] += normals[index].X();
				sum[1] += normals[index].Y();
				sum[2] += normals[index].Z();
			}

			// Upper right face.
			if ((i < l) && (j < l))
			{
				index = (j * l) + i;

				sum[0] += normals[index].X();
				sum[1] += normals[index].Y();
				sum[2] += normals[index].Z();
			}

			// Calculate the length of this normal.
			length = (float)sqrt((sum[0] * sum[0]) + (sum[1] * sum[1]) + (sum[2] * sum[2]));

			// Get an index to the vertex location in the height map array.
			index = (j * l) + i;

			// Normalize the final shared normal for this vertex and store it in the height map array.
			pVerts[index].normal.X() = (sum[0] / length);
			pVerts[index].normal.Y() = (sum[1] / length);
			pVerts[index].normal.Z() = (sum[2] / length);
		}
	}

	delete[] normals;
}

void TerrainModel::SetUV(float ur, float vr, int len) {
	int in = 15;
	int incr = 0;
	for (int j = 0; j < len / 2; j++) {
		for (int i = 0; i < len; i += 2) {
			pVerts[i + incr].u = ur;
			pVerts[i + incr].v = vr;

			pVerts[i + 1 + incr].u = ur;
			pVerts[i + 1 + incr].v = 0;

			pVerts[i + in + 1 + incr].u = 0;
			pVerts[i + in + 1 + incr].v = 0;

			pVerts[i + in + incr].u = 0;
			pVerts[i + in + incr].v = vr;
		}
		incr += 32;
	}
}

void TerrainModel::SetWorld(const Matrix& m) {
	world = m;
}

void TerrainModel::Render()
{
	pTex->SetToContext(pSMP->GetContext());
	pModTerrain->SetToContext(pSMP->GetContext());
	pSMP->SendWorldAndMaterial(world, Vect(1, 1, 1), Vect(1, 1, 1), Vect(1, 1, 1, 100));
	pModTerrain->Render(pSMP->GetContext());
}
