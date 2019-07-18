#include "DXApp.h"
#include <windows.h>
#include <sstream>
#include <assert.h>
#include "d3dUtil.h"
#include <d3dcompiler.h>
#include "Model.h"
#include "ShaderColor.h"
#include "DirectXTex.h"
#include "Texture.h"
#include "FlatPlane.h"
#include "TerrainModel.h"
#include "GraphicObject_Color.h"
#include "GraphicObject_Texture.h"
#include "GraphicObject_ColorLight.h"
#include "GraphicObject_TextureLight.h"
#include "ShaderMultiPointlight.h"
#include "SkyCube.h"
#include "ShaderTexture.h"

void DXApp::InitDemo()
{
	//multi light shader for moon terrain
	pTex2 = new Texture(md3dDevice, L"../Assets/Textures/MoonTerrainTexture.tga", D3D11_FILTER_ANISOTROPIC);
	pShaderMultiLight = new ShaderMultiPointlight(md3dDevice);

	pShaderMultiLight->SetPointLightParameters(Vect(0, 30, 0), 100, .2 * Vect(0, 1, 0),
		.1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	pShaderMultiLight->SetPointLightParameters(Vect(10, 0, 0), 100, .2 * Vect(0, 1, 0),
		.1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	pShaderMultiLight->SetPointLightParameters(Vect(0, 0, 10), 100, .2 * Vect(0, 1, 0),
		.1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	pTerrain = new TerrainModel(md3dDevice, L"../Assets/Textures/HMtest.tga", pShaderMultiLight, pTex2, 16.0f, 220.0f, 0.0f, 1.0f, 1.0f, 5.0f, -20.0f, -15.0f);

	TerrainWorld = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	pTerrain->SetWorld(TerrainWorld);

	//earth model
	pTex1 = new Texture(md3dDevice, L"../Assets/Textures/EarthTexture.tga");
	pEarthModel = new Model(md3dDevice, "../Assets/Models/Earth.azul");
	
	pEarth = new GraphicObject_TextureLight(pShaderMultiLight, pEarthModel);
	pEarth->SetTexture(pTex1);
	EarthWorld = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	EarthTrans = Vect(-8.0f, 25.0f, 25.0f);

	pEarth->SetWorld(EarthWorld);

	//sky box
	pTex3 = new Texture(md3dDevice, L"../Assets/Textures/space-skybox.tga");

	pShaderTex = new ShaderTexture(md3dDevice);
	pSkyBox = new SkyCube(md3dDevice, pShaderTex, pTex3, 200.0f);

	SkyBoxWorld = Matrix(SCALE, 1.0f, 1.0f, 1.0f) * Matrix(TRANS, Vect(0.0f, -50.0f, 0.0f));

	pSkyBox->SetWorld(SkyBoxWorld);

	//ufo 1
	UFOcurr = 0;
	pTex4 = new Texture(md3dDevice, L"../Assets/Textures/ufo_texture.tga");
	pUFOModel = new Model(md3dDevice, "../Assets/Models/UFO.azul");
	pUFO1 = new GraphicObject_TextureLight(pShaderMultiLight, pUFOModel);
	pUFO1->SetTexture(pTex4);
	UFOWorld1 = Matrix(SCALE, 1.0f, 1.0f, 1.0f) * Matrix(ROT_X, -1.5708f) * Matrix(TRANS, Vect(6.7f, 8.0f, 2.0f));

	//ufo 2
	UFOWorld2 = Matrix(SCALE, 1.0f, 1.0f, 1.0f)  * Matrix(ROT_X, 0.5f) * Matrix(TRANS, Vect(0.0f, 0.0f, 10.6f));

	//crate 1
	pTex5 = new Texture(md3dDevice, L"../Assets/Textures/metalbox_texture.tga");
	pBox = new Model(md3dDevice, Model::UnitBoxRepeatedTexture, 0.5f);
	pCrate1 = new GraphicObject_TextureLight(pShaderMultiLight, pBox);
	pCrate1->SetTexture(pTex5);
	BoxWorld1 = Matrix(SCALE, 1.0f, 1.0f, 1.0f) * Matrix(ROT_X, -0.2f) * Matrix(TRANS, 2.0f, 0.3f, 8.0f);

	//crate 2
	BoxWorld2 = Matrix(SCALE, 1.0f, 1.0f, 1.0f) * Matrix(ROT_Z, 0.2f)  * Matrix(TRANS, -3.0f, 0.25f, 8.0f);

	//crate 3
	BoxWorld3 = Matrix(SCALE, 1.0f, 1.0f, 1.0f) * Matrix(ROT_Z, -0.4f)  * Matrix(TRANS, 1.5f, 0.4f, 7.0f);

	//pyramid 1
	pTex6 = new Texture(md3dDevice, L"../Assets/Textures/biohazard_texture.tga");
	pPyramidModel1 = new Model(md3dDevice, Model::UnitPyramid, 0.25f);
	pPyr1 = new GraphicObject_TextureLight(pShaderMultiLight, pPyramidModel1);
	pPyr1->SetTexture(pTex6);
	PyramidWorld1 = Matrix(SCALE, 1.0f, 1.0f, 1.0f) * Matrix(ROT_Z, 0.3f) * Matrix(TRANS, Vect(6.0f, 0.8f, 3.0f));

	//pyramid 2
	PyramidWorld2 = Matrix(SCALE, 1.0f, 1.0f, 1.0f) * Matrix(ROT_Z, 0.4f) * Matrix(TRANS, Vect(4.0f, 0.7f, 2.0f));

	//pyramid3
	PyramidWorld3 = Matrix(SCALE, 1.0f, 1.0f, 1.0f) * Matrix(ROT_X, 1.5708f) * Matrix(TRANS, Vect(5.2f, 0.7f, 1.5f));

	// Initialize the projection matrix
	mCam.setPerspective( 3.14159/3, mClientWidth / (float)mClientHeight, 1.0f, 1000.0f);
	mCam.setOrientAndPosition(Vect(0, 1, 0), Vect(0, 0, 0), Vect(0, 3, -5));

	// Initialize gimmicky mouse control values
	mTheta = .5;
	mPhi = 3.1415f / 8;
	mRadius = 6;

	mTimer.Reset();
}

void DXApp::UpdateScene()
{
	//bring earth back, then rotate, then apply the translation for rotating in place
	pEarth->SetWorld(TerrainWorld);
	EarthWorld *= Matrix(ROT_Y, 0.0003);
	pEarth->SetWorld(EarthWorld);
	Matrix EarthNew = EarthWorld;
	EarthNew *= Matrix(TRANS, EarthTrans);
	pEarth->SetWorld(EarthNew);

	//move UFO up and down as well the point light under it
	UFOWorld1 *= Matrix(TRANS, Vect(0.0f, UFOspeed, 0.0f));
	UFOcurr++;
	pUFO1->SetWorld(UFOWorld1);
	lightHeight += UFOspeed * 3;
	pShaderMultiLight->ChangeLightPos(1, Vect(10.0f, lightHeight * 5.0f, 0.0f));

	if (UFOcurr == UFOmove)
	{
		UFOspeed *= -1;
		UFOcurr = 0;
	}
	
	float camSpeed = 0.016f;
	if (GetKeyState('W') & 0x08000)
	{
		mCam.TranslateFwdBack(camSpeed);
	}
	else if (GetKeyState('S') & 0x08000)
	{
		mCam.TranslateFwdBack(-camSpeed);
	}

	if (GetKeyState('A') & 0x08000)
	{
		mCam.TranslateLeftRight(-camSpeed);
	}
	else if (GetKeyState('D') & 0x08000)
	{
		mCam.TranslateLeftRight(camSpeed);
	}

	float rotSpeed = 0.008f;
	if (GetKeyState(VK_LEFT) & 0x08000)
	{
		mCam.TurnLeftRight(rotSpeed);
	}
	else if (GetKeyState(VK_RIGHT) & 0x08000)
	{
		mCam.TurnLeftRight(-rotSpeed);
	}

	if (GetKeyState(VK_UP) & 0x08000)
	{
		mCam.TiltUpDown(rotSpeed);
	}
	else if (GetKeyState(VK_DOWN) & 0x08000)
	{
		mCam.TiltUpDown(-rotSpeed);
	}

	mCam.updateCamera();
}

void DXApp::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, VasA(BackgroundColor));
	md3dImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//needed for lights
	Vect eyepos;
	mCam.getPos(eyepos);
	//send the cam info and set to context
	pShaderMultiLight->PrepareRender(md3dImmediateContext, mCam.getViewMatrix(), mCam.getProjMatrix(), eyepos);

	//need different blue fog for planet
	pShaderMultiLight->SetFogParameters(10000.0f, 25.0f, Vect(0.0f, 0.0f, 0.0f));
	pShaderMultiLight->SendFogParameters();
	pEarth->Render();

	//terrain needs some fog
	pShaderMultiLight->SetFogParameters(5.0f, 20.0f, Vect(0.0f, 0.0f, 0.0f));
	pShaderMultiLight->SendFogParameters();
	pTerrain->Render();

	//ufos
	pUFO1->SetWorld(UFOWorld1);
	pUFO1->Render();
	pUFO1->SetWorld(UFOWorld2);
	pUFO1->Render();

	//crates
	pCrate1->SetWorld(BoxWorld1);
	pCrate1->Render();
	pCrate1->SetWorld(BoxWorld2);
	pCrate1->Render();
	pCrate1->SetWorld(BoxWorld3);
	pCrate1->Render();

	//pyramid
	pPyr1->SetWorld(PyramidWorld1);
	pPyr1->Render();
	pPyr1->SetWorld(PyramidWorld2);
	pPyr1->Render();
	pPyr1->SetWorld(PyramidWorld3);
	pPyr1->Render();

	//render skybox
	pShaderTex->PrepareRender(md3dImmediateContext, mCam.getViewMatrix(), mCam.getProjMatrix());
	pSkyBox->Render();

	//switches the display to show the now-finished back-buffer
	mSwapChain->Present(0, 0);
}


DXApp::DXApp(HWND hwnd)
{
	assert(hwnd);
	mhMainWnd = hwnd;

	BackgroundColor = Colors::MidnightBlue;

	md3dDevice = nullptr;
	md3dImmediateContext = nullptr;
	mSwapChain = nullptr;
	mRenderTargetView = nullptr;

	//get window data through the window handle
	RECT rc;
	BOOL err = GetClientRect(mhMainWnd, &rc);  // Seriously MS: Redifining BOOL as int? Confusing much?
	assert(err);

	//get width/hight
	mClientWidth = rc.right - rc.left;
	mClientHeight = rc.bottom - rc.top;

	//get window caption
	const int MAX_LABEL_LENGTH = 100; // probably overkill...
	WCHAR str[MAX_LABEL_LENGTH];
	GetWindowText(mhMainWnd, str, MAX_LABEL_LENGTH);
	mMainWndCaption = str;

	//initialize DX11
	this->InitDirect3D();

	//demo initialization
	this->InitDemo();
}

DXApp::~DXApp()
{
	delete pShaderTex;
	delete pShaderMultiLight;

	delete pEarth;
	delete pTerrain;
	delete pSkyBox;
	delete pUFO1;
	delete pCrate1;
	delete pPyr1;

	delete pEarthModel;
	delete pUFOModel;
	delete pBox;
	delete pPyramidModel1;

	delete pTex1;
	delete pTex2;
	delete pTex3;
	delete pTex4;
	delete pTex5;
	delete pTex6;

	ReleaseAndDeleteCOMobject(mRenderTargetView);
	ReleaseAndDeleteCOMobject(mpDepthStencilView);
	ReleaseAndDeleteCOMobject(mSwapChain);
	ReleaseAndDeleteCOMobject(md3dImmediateContext);

	//must be done BEFORE the device is released
	ReportLiveDXObjects();		//see http://masterkenth.com/directx-leak-debugging/ for details

	ReleaseAndDeleteCOMobject(md3dDevice);
}

void DXApp::ReportLiveDXObjects()
{
#ifdef _DEBUG
	HRESULT hr = S_OK;

	ID3D11Debug* debugDev;
	hr = md3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDev));

	debugDev->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	ReleaseAndDeleteCOMobject(debugDev);
#endif
}

void DXApp::InitDirect3D()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, nullptr, 0, D3D11_SDK_VERSION, &md3dDevice, nullptr, &md3dImmediateContext);
	assert(SUCCEEDED(hr));

	IDXGIDevice* dxgiDevice = nullptr;
	hr = md3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
	assert(SUCCEEDED(hr));

	IDXGIAdapter* adapter = nullptr;
	hr = dxgiDevice->GetAdapter(&adapter);
	assert(SUCCEEDED(hr));

	IDXGIFactory1* dxgiFactory1 = nullptr;
	hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory1));
	assert(SUCCEEDED(hr));

	ReleaseAndDeleteCOMobject(adapter);
	ReleaseAndDeleteCOMobject(dxgiDevice);

	//controls MSAA option:
	//4x count level garanteed for all DX11 
	//MUST be the same for depth buffer!
	DXGI_SAMPLE_DESC sampDesc;
	sampDesc.Count = 1;
	sampDesc.Quality = static_cast<UINT>(D3D11_CENTER_MULTISAMPLE_PATTERN);
	DXGI_MODE_DESC buffdesc;
	ZeroMemory(&buffdesc, sizeof(buffdesc));
	buffdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//next create

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;	
	sd.BufferDesc = buffdesc;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = mhMainWnd;
	sd.SampleDesc = sampDesc;
	sd.Windowed = TRUE;

	hr = dxgiFactory1->CreateSwapChain(md3dDevice, &sd, &mSwapChain);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(dxgiFactory1);

	//create a render target view		https://msdn.microsoft.com/en-us/library/windows/desktop/ff476582(v=vs.85).aspx
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	assert(SUCCEEDED(hr));;

	hr = md3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mRenderTargetView);
	ReleaseAndDeleteCOMobject(pBackBuffer);
	assert(SUCCEEDED(hr));

	//first fix what it means for triangles to be front facing.
	//requires setting a whole new rasterizer state
	D3D11_RASTERIZER_DESC rd;
	//rd.FillMode = D3D11_FILL_WIREFRAME;  // Also: D3D11_FILL_WIREFRAME
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = true; //true for RH forward facing
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = true;  
	rd.AntialiasedLineEnable = true;

	ID3D11RasterizerState* rs;
	md3dDevice->CreateRasterizerState(&rd, &rs);

	md3dImmediateContext->RSSetState(rs);
	ReleaseAndDeleteCOMobject(rs); //release this resource since it won't be changing  any further

	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = mClientWidth;
	descDepth.Height = mClientHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc = sampDesc;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	ID3D11Texture2D* pDepthStencil;
	hr = md3dDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	assert(SUCCEEDED(hr));

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0;;

	hr = md3dDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &mpDepthStencilView);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(pDepthStencil);

	//md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, nullptr);  // to use without depth stencil
	md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mpDepthStencilView);

	//setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)mClientWidth;
	vp.Height = (FLOAT)mClientHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	md3dImmediateContext->RSSetViewports(1, &vp);
}

void DXApp::CalculateFrameStats()
{

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	//compute averages over one second period.
	if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::wostringstream outs;
		outs.precision(6);
		outs << mMainWndCaption << L"    "
			<< L"FPS: " << fps << L"    "
			<< L"Frame Time: " << mspf << L" (ms)";
		SetWindowText(mhMainWnd, outs.str().c_str());

		//reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

void DXApp::FrameTick()
{
	mTimer.Tick();
	CalculateFrameStats();

	this->UpdateScene();
	this->DrawScene();
}

void DXApp::OnMouseDown(WPARAM btnState, int xval, int yval)
{
	if (btnState & MK_LBUTTON)
	{
		MousePos[x] = static_cast<float>(xval);
		MousePos[y] = static_cast<float>(yval);
	}
}

void DXApp::OnMouseUp(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseMove(WPARAM btnState, int xval, int yval)
{
	if (btnState & MK_LBUTTON)
	{
		float dx = 0.01f*(MousePos[x] - xval);
		float dy = 0.01f*(MousePos[y] - yval);

		//update angles based on input to orbit camera around box.
		mTheta += dx;
		mPhi -= dy;

		static float verticalMax = MATH_PI2 - 0.2f;

		if (mPhi > verticalMax)
			mPhi = verticalMax;
		else if (mPhi < -verticalMax)
			mPhi = -verticalMax;

		//build the view matrix using gimmicky trick
		Vect target = Vect(0, 0, 0, 0);
		Vect up = Vect(0, 1, 0, 0);
		Vect pos = Vect(0, 0, -mRadius) * Matrix(ROT_Y, mTheta) * Matrix(ROT_X, mPhi);
		mCam.setOrientAndPosition(up, target, pos);
	}

	MousePos[x] = static_cast<float>(xval);
	MousePos[y] = static_cast<float>(yval);
}

void  DXApp::OnMouseWheel(short delta)
{
	if (delta > 0)
	{
		mRadius -= 1;
	}
	else
	{
		mRadius += 1;
	}
}

HRESULT DXApp::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}
