#include "ModelTools.h"
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"


/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 8;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(-0.5f, -0.5f, -0.5f, Colors::Black);
	pVerts[1].set(-0.5f, +0.5f, -0.5f, Colors::Lime);
	pVerts[2].set(+0.5f, +0.5f, -0.5f, Colors::Yellow);
	pVerts[3].set(+0.5f, -0.5f, -0.5f, Colors::Red );
	pVerts[4].set(-0.5f, -0.5f, +0.5f, Colors::Blue);
	pVerts[5].set(-0.5f, +0.5f, +0.5f, Colors::Cyan);
	pVerts[6].set(+0.5f, +0.5f, +0.5f, Colors::White);
	pVerts[7].set(+0.5f, -0.5f, +0.5f, Colors::Magenta);

	// back face
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	// front face
	pTriList[2].set(4, 6, 5);
	pTriList[3].set(4, 7, 6);

	// left face
	pTriList[4].set(4, 5, 1);
	pTriList[5].set(4, 1, 0);

	// right face
	pTriList[6].set(3, 2, 6);
	pTriList[7].set(3, 6, 7);

	// top face
	pTriList[8].set(1, 5, 6);
	pTriList[9].set(1, 6, 2);

	// bottom face
	pTriList[10].set(4, 0, 3);
	pTriList[11].set(4, 3, 7);
}

void ModelTools::CreateUnitBoxRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri, float& scale)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(scale, scale, scale,        1, 0,   0, 0, 1, 1, 1, 1, 0);
	pVerts[vind + 1].set(-scale, scale, scale,   0, 0,   0, 0, 1, 1, 1, 1, 0);
	pVerts[vind + 2].set(-scale, -scale, scale,  0, 1,   0, 0, 1, 1, 1, 1, 0);
	pVerts[vind + 3].set(scale, -scale, scale,   1, 1,   0, 0, 1, 1, 1, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);	     
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);    
													     
	// Back											     
	vind += 4;										     
	tind += 2;										     
	pVerts[vind].set(scale, scale, -scale,       0, 0,   0, 0, -1, 1, 1, 1, 1);
	pVerts[vind + 1].set(-scale, scale, -scale,  1, 0,   0, 0, -1, 1, 1, 1, 1);
	pVerts[vind + 2].set(-scale, -scale, -scale, 1, 1,   0, 0, -1, 1, 1, 1, 1);
	pVerts[vind + 3].set(scale, -scale, -scale,  0, 1,   0, 0, -1, 1, 1, 1, 1);
	pTriList[tind].set(vind + 2, vind + 1, vind);	     
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);    
													     
	// Left											     
	vind += 4;										     
	tind += 2;										     
	pVerts[vind].set(scale, scale, -scale,       1, 0,   1, 0, 0, 1, 1, 1, 2);
	pVerts[vind + 1].set(scale, scale, scale,    0, 0,   1, 0, 0, 1, 1, 1, 2);
	pVerts[vind + 2].set(scale, -scale, scale,   0, 1,   1, 0, 0, 1, 1, 1, 2);
	pVerts[vind + 3].set(scale, -scale, -scale,  1, 1,   1, 0, 0, 1, 1, 1, 2);
	pTriList[tind].set(vind, vind + 1, vind + 2);	     
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);    
													     
	// Right										     
	vind += 4;										     
	tind += 2;										     
	pVerts[vind].set(-scale, scale, scale,       1, 0,   -1, 0, 0, 1, 1, 1, 3);
	pVerts[vind + 1].set(-scale, scale, -scale,  0, 0,   -1, 0, 0, 1, 1, 1, 3);
	pVerts[vind + 2].set(-scale, -scale, -scale, 0, 1,   -1, 0, 0, 1, 1, 1, 3);
	pVerts[vind + 3].set(-scale, -scale, scale,  1, 1,   -1, 0, 0, 1, 1, 1, 3);
	pTriList[tind].set(vind, vind + 1, vind + 2);	     
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);    
													     
	// Top											     
	vind += 4;										     
	tind += 2;										     
	pVerts[vind].set(scale, scale, -scale,      1, 0,    0, 1, 0, 1, 1, 1, 4);
	pVerts[vind + 1].set(-scale, scale, -scale, 0, 0,    0, 1, 0, 1, 1, 1, 4);
	pVerts[vind + 2].set(-scale, scale, scale,  0, 1,    0, 1, 0, 1, 1, 1, 4);
	pVerts[vind + 3].set(scale, scale, scale,   1, 1,    0, 1, 0, 1, 1, 1, 4);
	pTriList[tind].set(vind, vind + 1, vind + 2);	     
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);    
													     
	// Bottom										     
	vind += 4;										     
	tind += 2;										     
	pVerts[vind].set(scale, -scale, scale,       1, 0,   0, -1, 0, 1, 1, 1, 5);
	pVerts[vind + 1].set(-scale, -scale, scale,  0, 0,   0, -1, 0, 1, 1, 1, 5);
	pVerts[vind + 2].set(-scale, -scale, -scale, 0, 1,   0, -1, 0, 1, 1, 1, 5);
	pVerts[vind + 3].set(scale, -scale, -scale,  1, 1,   0, -1, 0, 1, 1, 1, 5);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitPyramid(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri, float& scale) {
	nverts = 25;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	// Setting up faces
	int vind = 0;
	int tind = 0;
	Vect v1;
	Vect v2;
	Vect v3;
	Vect v4;
	Vect v5 = Vect(0.0f, scale, 0.0f);
	// Forward
	v1 = (v5 - Vect(-scale, -scale, scale));
	v2 = (v5 - Vect(scale, -scale, scale));
	v3 = v2.cross(v1);
	v4 = v3.getNorm();
	pVerts[vind].set(scale, scale, scale, 1, 0,       v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 0);
	pVerts[vind + 1].set(-scale, scale, scale, 0, 0,  v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 0);
	pVerts[vind + 2].set(-scale, -scale, scale, 0, 1, v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 0);
	pVerts[vind + 3].set(scale, -scale, scale, 1, 1,  v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 0);
	pVerts[vind + 4].set(0, scale, 0, 0.5, 0, v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 0);
	pTriList[tind].set(vind + 4, vind + 2, vind + 3);

	// Back
	vind += 5;
	tind += 1;
	v1 = (v5 - Vect(-scale, -scale, -scale));
	v2 = (v5 - Vect(scale, -scale, -scale));
	v3 = v2.cross(v1);
	v4 = v3.getNorm();
	pVerts[vind].set(scale, scale, -scale, 0, 0,        v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 1);
	pVerts[vind + 1].set(-scale, scale, -scale, 1, 0,   v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 1);
	pVerts[vind + 2].set(-scale, -scale, -scale, 1, 1,  v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 1);
	pVerts[vind + 3].set(scale, -scale, -scale, 0, 1,   v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 1);
	pVerts[vind + 4].set(0, scale, 0, 0.5, 0,   v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 1);
	pTriList[tind].set(vind + 3, vind + 2, vind + 4);

	// Left
	vind += 5;
	tind += 1;
	v1 = (v5 - Vect(scale, -scale, scale));
	v2 = (v5 - Vect(scale, -scale, -scale));
	v3 = v1.cross(v2);
	v4 = v3.getNorm();
	pVerts[vind].set(scale, scale, -scale, 1, 0,      v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 2);
	pVerts[vind + 1].set(scale, scale, scale, 0, 0,   v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 2);
	pVerts[vind + 2].set(scale, -scale, scale, 0, 1,  v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 2);
	pVerts[vind + 3].set(scale, -scale, -scale, 1, 1, v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 2);
	pVerts[vind + 4].set(0, scale, 0, 0.5, 0, v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 2);
	pTriList[tind].set(vind + 4, vind + 2, vind + 3);

	// Right
	vind += 5;
	tind += 1;
	v1 = (v5 - Vect(-scale, -scale, -scale));
	v2 = (v5 - Vect(-scale, -scale, scale));
	v3 = v2.cross(v1);
	v4 = v3.getNorm();
	pVerts[vind].set(-scale, scale, scale, 1, 0,        v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 3);
	pVerts[vind + 1].set(-scale, scale, -scale, 0, 0,   v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 3);
	pVerts[vind + 2].set(-scale, -scale, -scale, 0, 1,  v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 3);
	pVerts[vind + 3].set(-scale, -scale, scale, 1, 1,   v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 3);
	pVerts[vind + 4].set(0, scale, 0, 0.5, 0,   v4.X(), v4.Y(), v4.Z(), 1, 1, 1, 3);
	pTriList[tind].set(vind + 4, vind + 2, vind + 3);

	// Bottom
	vind += 5;
	tind += 1;
	pVerts[vind].set(scale, -scale, scale, 1, 0,       0, -1, 0, 1, 1, 1, 4);
	pVerts[vind + 1].set(-scale, -scale, scale, 0, 0,  0, -1, 0, 1, 1, 1, 4);
	pVerts[vind + 2].set(-scale, -scale, -scale, 0, 1, 0, -1, 0, 1, 1, 1, 4);
	pVerts[vind + 3].set(scale, -scale, -scale, 1, 1,  0, -1, 0, 1, 1, 1, 4);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitBoxSixFacesTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri) {
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 0.25, 0.625);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0.25, 0.375);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 0.375);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 0, 0.625);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.50, 0.625);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.50, 0.375);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75, 0.375);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75, 0.625);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.50, 0.625);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0.25, 0.625);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0.25, 0.875);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.50, 0.875);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 0.25, 0.375);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.50, 0.375);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.50, 0.125);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 0.25, 0.125);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.50, 0.625);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.50, 0.375);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0.25, 0.375);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 0.25, 0.625);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0.625);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 1, 0.375);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75, 0.375);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75, 0.625);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}
