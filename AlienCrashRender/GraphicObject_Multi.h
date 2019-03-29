#ifndef _GraphicObject_Multi
#define _GraphicObject_Multi

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColor.h"
#include "ShaderBase.h"
#include "Texture.h"

enum class ShaderType{
	COL,
	COL_LIGHT,
	TEX_LIGHT
};

class GraphicObject_Multi : public GraphicObject_Base
{
	friend class ShaderTextureLight;
	friend class ShaderColorLight;
	friend class ShaderColor;

public:
	GraphicObject_Multi(const GraphicObject_Multi&) = delete;				 // Copy constructor
	GraphicObject_Multi(GraphicObject_Multi&&) = default;                    // Move constructor
	GraphicObject_Multi& operator=(const GraphicObject_Multi&) & = default;  // Copy assignment operator
	GraphicObject_Multi& operator=(GraphicObject_Multi&&) & = default;       // Move assignment operator
	~GraphicObject_Multi();		  											 // Destructor

	GraphicObject_Multi() = delete;

	void SetColor(const Vect& col, int meshnum, int shadernum);
	void SetWorld(const Matrix& m);
	void SetTexture(Texture* t, ID3D11Device* d3dDev);
	virtual void Render() override;

	GraphicObject_Multi(ShaderTextureLight* shader0, ShaderColorLight* shader1, ShaderColor* shader2, Model* mod);

private:
	//arbitrarily assign these indices
	ShaderTextureLight* pShaderTexLight; //0
	ShaderColorLight* pShaderColLight;   //1
	ShaderColor* pShaderCol;             //2

	Texture* tex;

	struct Mesh_Data {
		Vect Color;
		ShaderType st;
	};
	Mesh_Data* MeshColors;
	Matrix							World;

};

#endif _GraphicObject_TextureLight
