#ifndef _ShaderTexture
#define _ShaderTexture

#include "ShaderBase.h"
#include "Matrix.h"

class Texture;
struct ID3D11Buffer;
struct ID3D11Device;

class ShaderTexture : public ShaderBase
{
public:
	ShaderTexture(const ShaderTexture&) = delete;				 // Copy constructor
	ShaderTexture(ShaderTexture&&) = default;                    // Move constructor
	ShaderTexture& operator=(const ShaderTexture&) & = default;  // Copy assignment operator
	ShaderTexture& operator=(ShaderTexture&&) & = default;       // Move assignment operator
	~ShaderTexture();		  							         // Destructor

	ShaderTexture(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendWorldColor(const Matrix& world, const Vect& col);

	void PrepareRender(ID3D11DeviceContext* devcon, const Matrix& view, const Matrix& proj);
private:
	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer*           mpBufferCamMatrices;

	struct Data_WorldColor
	{
		Matrix World;
		Vect Color;
	};

	ID3D11Buffer*           mpBuffWordColor;
};

#endif ShaderTexture

