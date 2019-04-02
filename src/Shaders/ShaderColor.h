#ifndef _ShaderColor
#define _ShaderColor

#include "ShaderBase.h"
#include "Matrix.h"

struct ID3D11Buffer;
struct ID3D11Device;

class ShaderColor : public ShaderBase
{
public:
	ShaderColor(const ShaderColor&) = delete;
	ShaderColor(ShaderColor&&) = default;
	ShaderColor& operator=(const ShaderColor&) & = default;
	ShaderColor& operator=(ShaderColor&&) & = default;
	~ShaderColor();	

	ShaderColor(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendWorldColor(const Matrix& world, const Vect& col);

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

#endif _ShaderColor
