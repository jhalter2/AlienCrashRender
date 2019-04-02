#ifndef _FlatPlane
#define _FlatPlane

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class FlatPlane 
{
private:
	Model* pPlane;

public:
	FlatPlane(const FlatPlane&) = delete;
	FlatPlane(Model&&) = delete;
	FlatPlane& operator=(const FlatPlane&) & = delete;
	FlatPlane& operator=(FlatPlane&&) & = delete;
	~FlatPlane();

	FlatPlane(ID3D11Device* dev, float size, float hrep, float vrep);

	void Render(ID3D11DeviceContext* context);

};

#endif _FlatPlane
