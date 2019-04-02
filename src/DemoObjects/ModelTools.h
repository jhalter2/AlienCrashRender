#ifndef _ModelTools
#define _ModelTools

#include "Vect.h"

struct StandardVertex;
struct TriangleByIndex;

class ModelTools
{

public:
	static void CreateUnitBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri);
	static void CreateUnitBoxRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri, float& scale);
	static void CreateUnitPyramid(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri, float& scale);
	static void CreateUnitBoxSixFacesTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri);
};



#endif _ModelTools
