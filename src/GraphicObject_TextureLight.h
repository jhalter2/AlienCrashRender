#ifndef _GraphicObject_TextureLight
#define _GraphicObject_TextureLight

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColor.h"

class ShaderTextureLight;
class ShaderMultiPointlight;
class Texture;

class GraphicObject_TextureLight : public GraphicObject_Base
{
public:
	GraphicObject_TextureLight(const GraphicObject_TextureLight&) = delete;				 // Copy constructor
	GraphicObject_TextureLight(GraphicObject_TextureLight&&) = default;                    // Move constructor
	GraphicObject_TextureLight& operator=(const GraphicObject_TextureLight&) & = default;  // Copy assignment operator
	GraphicObject_TextureLight& operator=(GraphicObject_TextureLight&&) & = default;       // Move assignment operator
	~GraphicObject_TextureLight();		  											 // Destructor

	GraphicObject_TextureLight() = delete;

	void SetColor(const Vect& col);
	void SetColor(const Vect& col, int meshnum);
	void SetWorld(const Matrix& m);
	void SetTexture(Texture* tex);
	virtual void Render() override;

	GraphicObject_TextureLight(ShaderTextureLight* shader, Model* mod);
	GraphicObject_TextureLight(ShaderMultiPointlight* shader, Model* mod);

private:
	Texture* pTex;
	ShaderTextureLight* pShaderL;
	ShaderMultiPointlight* pShaderMulti;
	Vect* MeshColors;
	Matrix World;
	int meshCount;
};

#endif _GraphicObject_TextureLight


