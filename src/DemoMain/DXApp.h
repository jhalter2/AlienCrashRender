#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "ShaderColor.h"
#include "ShaderColorLight.h"
#include "ShaderTexture.h"
#include "ShaderTextureLight.h"

class Model;
class Texture;
class FlatPlane;
class TerrainModel;
class GraphicObject_Color;
class ShaderTexture;
class GraphicObject_Texture;
class GraphicObject_ColorLight;
class GraphicObject_TextureLight;
class ShaderMultiPointlight;
class SkyCube;

class DXApp : public Align16
{
private:	
	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;

	// DX application elements
	ID3D11Device* md3dDevice;
	ID3D11DeviceContext* md3dImmediateContext;
	IDXGISwapChain* mSwapChain;
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11DepthStencilView* mpDepthStencilView; 

	GameTimer mTimer;
	std::wstring mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// Demo specific additions
	Camera mCam;

	Model* pEarthModel;
	Model* pUFOModel;
	Model* pBox;
	Model* pPyramidModel1;

	Matrix EarthWorld;	
	Matrix TerrainWorld;
	Matrix SkyBoxWorld;
	Matrix UFOWorld1;
	Matrix UFOWorld2;
	Matrix BoxWorld1;
	Matrix BoxWorld2;
	Matrix BoxWorld3;
	Matrix PyramidWorld1;
	Matrix PyramidWorld2;
	Matrix PyramidWorld3;

	ShaderTexture* pShaderTex;
	ShaderMultiPointlight* pShaderMultiLight;

	GraphicObject_TextureLight* pEarth;
	GraphicObject_TextureLight* pUFO1;
	GraphicObject_TextureLight* pCrate1;
	GraphicObject_TextureLight* pPyr1;

	TerrainModel* pTerrain;
	SkyCube* pSkyBox;

	Texture* pTex1;
	Texture* pTex2;
	Texture* pTex3;
	Texture* pTex4;
	Texture* pTex5;
	Texture* pTex6;

	Vect EarthTrans;
	Vect MousePos;		
	float mTheta;
	float mPhi;
	float mRadius;
	
	const int UFOmove = 360;
	float UFOspeed = 0.003f;
	float lightHeight = 0.000f;
	int UFOcurr;
public:
	DXApp(HWND hwnd);
	virtual ~DXApp();
	
	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);


};

#endif _DXApp
