#ifndef _ShaderMultiPointlight
#define _ShaderMultiPointlight

#include "ShaderBase.h"
#include "Matrix.h"
#include <list>
struct ID3D11Buffer;
struct ID3D11Device;

class Texture;

class ShaderMultiPointlight : public ShaderBase
{

public:
	ShaderMultiPointlight(const ShaderMultiPointlight&) = delete;				 // Copy constructor
	ShaderMultiPointlight(ShaderMultiPointlight&&) = default;                    // Move constructor
	ShaderMultiPointlight& operator=(const ShaderMultiPointlight&) & = default;  // Copy assignment operator
	ShaderMultiPointlight& operator=(ShaderMultiPointlight&&) & = default;       // Move assignment operator
	~ShaderMultiPointlight();		  							         // Destructor

	ShaderMultiPointlight(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters(const Vect& eyepos);
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));

	void PrepareRender(ID3D11DeviceContext* devcon, const Matrix& view, const Matrix& proj, const Vect& eyepos);
	//allows changing values on specific lights, using indices beginning with 0
	void ChangeLightPos(const int& ind, const Vect& pos);
	void ChangeLightAtten(const int& ind, const Vect& att);
	void SetFogParameters(const float& fStart, const float& fRange, const Vect& fColor);
	void SendFogParameters();
private:
	void SetFogParameters();
	struct Material
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};

	struct PhongADS
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};

	struct PointLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		float Range;
	};

	PointLight PointLightData1;

	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer*  mpBufferCamMatrices;

	struct Data_WorldAndMaterial
	{
		Matrix World;
		Matrix WorlInv;
		Material Mat;
	};

	ID3D11Buffer*	mpBuffWordAndMaterial;

	struct Data_LightParams
	{
		PointLight PntLight[3];
		Vect EyePosWorld;
	};

	ID3D11Buffer*  mpBufferLightParams;

	PointLight Lightlist[3];
	int index;

	struct Data_FogParameters
	{
		float FogStart;	// anything closer than FogStart will have no fog
		float FogRange;	// fog contribution increases linearly until full fog at dist = FogStart + Range
		Vect FogColor;
	};

	Data_FogParameters dFp;
	ID3D11Buffer* mpBufferFogParams;
};

#endif _ShaderTextureLight


