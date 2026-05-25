#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment (lib, "D3D10_1.lib")
#pragma comment (lib, "DXGI.lib")
#pragma comment (lib, "D2D1.lib")
#pragma comment (lib, "dwrite.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include <Windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>
#include <D3D10_1.h>
#include <DXGI.h>
#include <D2D1.h>
#include <sstream>
#include <dwrite.h>
#include <dinput.h>
#include <vector>

struct {
	HWND hWND = NULL;
	HRESULT hr;
	int Wight = GetSystemMetrics(SM_CXSCREEN)/2;
	int	Heignt = GetSystemMetrics(SM_CYSCREEN)/2;
	LPCSTR WndClassName = "3D REDACTOR";
}Window;

struct {
	DIMOUSESTATE mouseLastState;
	LPDIRECTINPUT8 DirectInput;
}ControlInput;

struct {
	XMMATRIX camView;
	XMMATRIX camProjection;
	XMVECTOR camStartPos;
	XMVECTOR camStartTarget;

	XMVECTOR camPosition;
	XMVECTOR camTarget;
	XMVECTOR camUp;
	XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMMATRIX camRotationMatrix;

	float moveLeftRight = 0.0f;
	float moveBackForward = 0.0f;
	float moveUp = 0.0f;

	float camYaw = 0.0f;
	float camPitch = 0.0f;
}Camera;

struct {
	XMMATRIX WVP;
	XMMATRIX World;
}WorldPos;

struct {
	double countsPerSecond = 0.0;
	__int64 CounterStart = 0;
	int frameCount = 0;
	int fps = 0;
	__int64 frameTimeOld = 0;
	double frameTime;

	void StartTimer()
	{
		LARGE_INTEGER frequencyCount;
		QueryPerformanceFrequency(&frequencyCount);

		Timer.countsPerSecond = double(frequencyCount.QuadPart);

		QueryPerformanceCounter(&frequencyCount);
		Timer.CounterStart = frequencyCount.QuadPart;
	}
	double GetTime()
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		return double(currentTime.QuadPart - Timer.CounterStart) / Timer.countsPerSecond;
	}
	double GetFrameTime()
	{
		LARGE_INTEGER currentTime;
		__int64 tickCount;
		QueryPerformanceCounter(&currentTime);

		tickCount = currentTime.QuadPart - Timer.frameTimeOld;
		Timer.frameTimeOld = currentTime.QuadPart;

		if (tickCount < 0.0f)
			tickCount = 0.0f;

		return float(tickCount) / Timer.countsPerSecond;
	}
}Timer;

struct {
	float rotx = 0;
	float roty = 0;
	float rotz = 0;
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	float scaleZ = 1.0f;
	float moveLeftRight = 0.0f;
	float moveBackForward = 0.0f;
	float moveUpDown = 0.0f;
	float camYaw = 0.0f;
	float camPitch = 0.0f;
	float camRoll = 0.0f;
}Movment;

struct  {
	XMMATRIX ResultOBJ;
	XMMATRIX Rotationx;
	XMMATRIX Rotationy;
	XMMATRIX Rotationz;
	XMMATRIX Scale;
	XMMATRIX Translation;
	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;
	int colormodr = 1;
	int colormodg = 1;
	int colormodb = 1;
}Property;

struct Light{
		Light()
		{
			ZeroMemory(this, sizeof(Light));
		}
		XMFLOAT3 dir;
		float pad1;
		XMFLOAT3 pos;
		float range;
		XMFLOAT3 att;
		float pad2;
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
};
struct VertexCol
{
	VertexCol() {};
	VertexCol(float x, float y, float z,
		float r, float g, float b, float a) : pos(x, y, z), color(r, g, b, a) {
	}

	XMFLOAT3 pos;
	XMFLOAT4 color;
};
struct VertexTex
{
	VertexTex() {};
	VertexTex(float x, float y, float z,
		float u, float v) : pos(x, y, z), texCoord(u, v) {
	}

	XMFLOAT3 pos;
	XMFLOAT2 texCoord;
};
struct VertexNormal
{
	VertexNormal() {}
	VertexNormal(float x, float y, float z,
		float u, float v,
		float nx, float ny, float nz)
		: pos(x, y, z), texCoord(u, v), normal(nx, ny, nz) {
	}

	XMFLOAT3 pos;
	XMFLOAT2 texCoord;
	XMFLOAT3 normal;
};

struct {
	struct cbPerObject
	{
		XMMATRIX  WVP;
		XMMATRIX  World;
	}cbPerObj;
	struct cbPerFrame
	{
		Light  light;
	}constbuffPerFrame;
}Cbuffers;

int NumSphereVertices;
int NumSphereFaces;
XMMATRIX sphereWorld;



enum MOD
{
	VERTEX_0,
	INDEX_0,
	CONSTANTA_0,
	RUSTER_0,
	TEXTURE_0,
	SAMPLER_0,
};


//typename BUFFER = D3D11_BUFFER_DESC,
//typename SAMPLER = D3D11_SAMPLER_DESC,
//typename RASTERIZER = D3D11_RASTERIZER_DESC,
//typename DEPTH_STENCIL = D3D11_DEPTH_STENCIL_DESC,
//typename SUBRESOURCE = D3D11_SUBRESOURCE_DATA,
//typename INPUT_ELEMENT = D3D11_INPUT_ELEMENT_DESC,
//typename VIEWPORT = D3D11_VIEWPORT,
//typename TEXTURE2D = D3D11_TEXTURE2D_DESC,
//typename BLEND = D3D11_BLEND_DESC,
//typename RENDER_TARGET_BLEND = D3D11_RENDER_TARGET_BLEND_DESC,
//typename IMAGE_LOAD_INFO = D3DX11_IMAGE_LOAD_INFO,
//typename SHADER_RESOURCE_VIEW = D3D11_SHADER_RESOURCE_VIEW_DESC


class D3DEX
{
private:
	//Создание константного буфера
	void CreateModuleDX(MOD mod,ID3D11Buffer** buf, UINT size = 0)
	{
		D3D11_BUFFER_DESC cbbd;
		ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));
		cbbd.Usage = D3D11_USAGE_DEFAULT;
		cbbd.ByteWidth = size;
		cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbbd.CPUAccessFlags = 0;
		cbbd.MiscFlags = 0;
		d3d11Device->CreateBuffer(&cbbd, NULL, buf);
	}
	//Создание текстуры
	void CreateModuleDX(MOD mod,ID3D11ShaderResourceView** buf, const char* namefile, UINT size = 0)
	{
		D3DX11CreateShaderResourceViewFromFile(d3d11Device, namefile, NULL, NULL, buf, NULL);
	}
	//Создание семплера
	void CreateModuleDX(MOD mod, ID3D11SamplerState** buf, UINT size = 0)
	{
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		d3d11Device->CreateSamplerState(&sampDesc, buf);
	}


private: //системы
	bool InitD2D_D3D101_DWrite(IDXGIAdapter1* Adapter) {

		Window.hr = D3D10CreateDevice1(Adapter, D3D10_DRIVER_TYPE_HARDWARE, NULL, D3D10_CREATE_DEVICE_DEBUG | D3D10_CREATE_DEVICE_BGRA_SUPPORT,
			D3D10_FEATURE_LEVEL_9_3, D3D10_1_SDK_VERSION, &d3d101Device);

		D3D11_TEXTURE2D_DESC sharedTexDesc;

		ZeroMemory(&sharedTexDesc, sizeof(sharedTexDesc));

		sharedTexDesc.Width = Window.Wight;
		sharedTexDesc.Height = Window.Heignt;
		sharedTexDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		sharedTexDesc.MipLevels = 1;
		sharedTexDesc.ArraySize = 1;
		sharedTexDesc.SampleDesc.Count = 1;
		sharedTexDesc.Usage = D3D11_USAGE_DEFAULT;
		sharedTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		sharedTexDesc.MiscFlags = D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;

		d3d11Device->CreateTexture2D(&sharedTexDesc, NULL, &sharedTex11);

		sharedTex11->QueryInterface(__uuidof(IDXGIKeyedMutex), (void**)&keyedMutex11);

		IDXGIResource* sharedResource10;
		HANDLE sharedHandle10;

		sharedTex11->QueryInterface(__uuidof(IDXGIResource), (void**)&sharedResource10);

		sharedResource10->GetSharedHandle(&sharedHandle10);

		sharedResource10->Release();

		IDXGISurface1* sharedSurface10;

		d3d101Device->OpenSharedResource(sharedHandle10, __uuidof(IDXGISurface1), (void**)(&sharedSurface10));

		sharedSurface10->QueryInterface(__uuidof(IDXGIKeyedMutex), (void**)&keyedMutex10);

		ID2D1Factory* D2DFactory;
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), (void**)&D2DFactory);

		D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties;

		ZeroMemory(&renderTargetProperties, sizeof(renderTargetProperties));

		renderTargetProperties.type = D2D1_RENDER_TARGET_TYPE_HARDWARE;
		renderTargetProperties.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);

		D2DFactory->CreateDxgiSurfaceRenderTarget(sharedSurface10, &renderTargetProperties, &D2DRenderTarget);

		sharedSurface10->Release();
		D2DFactory->Release();

		D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 0.0f, 1.0f), &Brush);

		DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&DWriteFactory));

		DWriteFactory->CreateTextFormat(
			L"Algerian",
			NULL,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			24.0f,
			L"en-us",
			&TextFormat
		);

		TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

		d3d101Device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);
		return true;
	}
	bool InitializeDirect3dApp(HINSTANCE hInstance) {

		DXGI_MODE_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

		bufferDesc.Width = Window.Wight;
		bufferDesc.Height = Window.Heignt;
		bufferDesc.RefreshRate.Numerator = 60;
		bufferDesc.RefreshRate.Denominator = 1;
		bufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;


		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = Window.hWND;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


		IDXGIFactory1* DXGIFactory;

		HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&DXGIFactory);

		// Use the first adapter	
		IDXGIAdapter1* Adapter;

		hr = DXGIFactory->EnumAdapters1(0, &Adapter);

		DXGIFactory->Release();

		hr = D3D11CreateDeviceAndSwapChain(Adapter, D3D_DRIVER_TYPE_UNKNOWN, NULL, D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT,
			NULL, NULL, D3D11_SDK_VERSION, &swapChainDesc, &SwapChain, &d3d11Device, NULL, &d3d11DevCon);

		InitD2D_D3D101_DWrite(Adapter);

		Adapter->Release();

		hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer11);
		hr = d3d11Device->CreateRenderTargetView(BackBuffer11, NULL, &renderTargetView);

		InitDepth();
		d3d11DevCon->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
		return true;
	};
	void InitD2DScreenTexture() {

		VertexNormal v[] =
		{
			// Front Face
			VertexNormal(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,-1.0f, -1.0f, -1.0f),
			VertexNormal(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f,-1.0f,  1.0f, -1.0f),
			VertexNormal(1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f,  1.0f, -1.0f),
			VertexNormal(1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f),
		};

		DWORD indices[] = {
			// Front Face
			0,  1,  2,
			0,  2,  3,
		};

		D3D11_BUFFER_DESC indexBufferDesc;
		ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(DWORD) * 2 * 3;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA iinitData;

		iinitData.pSysMem = indices;
		d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, &d2dIndexBuffer);


		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(VertexNormal) * 4;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData;

		ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
		vertexBufferData.pSysMem = v;
		d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &d2dVertBuffer);

		d3d11Device->CreateShaderResourceView(sharedTex11, NULL, &d2dTexture);
	}
	bool InitDirectInput(HINSTANCE hInstance) {
		DirectInput8Create(hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&ControlInput.DirectInput,
			NULL);
		
		ControlInput.DirectInput->CreateDevice(GUID_SysKeyboard,
			&DIKeyboard,
			NULL);

		ControlInput.DirectInput->CreateDevice(GUID_SysMouse,
			&DIMouse,
			NULL);

		DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
		DIKeyboard->SetCooperativeLevel(Window.hWND, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

		DIMouse->SetDataFormat(&c_dfDIMouse);
		DIMouse->SetCooperativeLevel(Window.hWND, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);

		return true;
	}
private: //создание
	void InitConstBuffer()
	{
		CreateModuleDX(CONSTANTA_0,&cbPerObjectBuffer, sizeof(Cbuffers.cbPerObj));
		CreateModuleDX(CONSTANTA_0,&cbPerFrameBuffer,  sizeof(Cbuffers.constbuffPerFrame));
	}
	void InitImageTexture()
	{
		CreateModuleDX(TEXTURE_0,&CubesTexture, "block.jpg");
		CreateModuleDX(SAMPLER_0,&CubesTexSamplerState);
	}
	void InitRasterized()
	{
		D3D11_RASTERIZER_DESC wfdesc;
		ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
		wfdesc.FillMode = D3D11_FILL_SOLID;
		wfdesc.CullMode = D3D11_CULL_NONE;
		wfdesc.AntialiasedLineEnable = TRUE;
		d3d11Device->CreateRasterizerState(&wfdesc, &WireFrame);
		d3d11DevCon->RSSetState(WireFrame);


		wfdesc.CullMode = D3D11_CULL_NONE;
		d3d11Device->CreateRasterizerState(&wfdesc, &RSCullNone);
		D3D11_DEPTH_STENCIL_DESC dssDesc;
		ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
		dssDesc.DepthEnable = true;
		dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		d3d11Device->CreateDepthStencilState(&dssDesc, &DSLessEqual);
	}
	void InitShaders()
	{

		D3DX11CompileFromFileA("Effect.fx", 0, 0, "VS", "vs_5_0", 0, 0, 0, &VS_Buffer, 0, 0);
		D3DX11CompileFromFileA("Effect.fx", 0, 0, "PS", "ps_5_0", 0, 0, 0, &PS_Buffer, 0, 0);
		D3DX11CompileFromFileA("Effect.fx", 0, 0, "D2D_PS", "ps_5_0", 0, 0, 0, &D2D_PS_Buffer, 0, 0);

		D3DX11CompileFromFileA("Effect.fx", 0, 0, "SKYMAP_VS", "vs_5_0", 0, 0, 0, &SKYMAP_VS_Buffer, 0, 0);
		D3DX11CompileFromFileA("Effect.fx", 0, 0, "SKYMAP_PS", "ps_5_0", 0, 0, 0, &SKYMAP_PS_Buffer, 0, 0);


		d3d11Device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);
		d3d11Device->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);
		d3d11Device->CreatePixelShader(D2D_PS_Buffer->GetBufferPointer(), D2D_PS_Buffer->GetBufferSize(), NULL, &D2D_PS);

		d3d11Device->CreateVertexShader(SKYMAP_VS_Buffer->GetBufferPointer(), SKYMAP_VS_Buffer->GetBufferSize(), NULL, &SKYMAP_VS);
		d3d11Device->CreatePixelShader(SKYMAP_PS_Buffer->GetBufferPointer(), SKYMAP_PS_Buffer->GetBufferSize(), NULL, &SKYMAP_PS);

		d3d11DevCon->VSSetShader(VS, 0, 0);
		d3d11DevCon->PSSetShader(PS, 0, 0);
	}
	void InitVertexBuffer()
	{
		VertexNormal v[] =
		{
			// Front Face
			VertexNormal(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,-1.0f, -1.0f, -1.0f),
			VertexNormal(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f,-1.0f,  1.0f, -1.0f),
			VertexNormal(1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f,  1.0f, -1.0f),
			VertexNormal(1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f),

			// Back Face
			VertexNormal(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f,-1.0f, -1.0f, 1.0f),
			VertexNormal(1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, -1.0f, 1.0f),
			VertexNormal(1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f),
			VertexNormal(-1.0f,  1.0f, 1.0f, 1.0f, 0.0f,-1.0f,  1.0f, 1.0f),

			// Top Face
			VertexNormal(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,-1.0f, 1.0f, -1.0f),
			VertexNormal(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f,-1.0f, 1.0f,  1.0f),
			VertexNormal(1.0f, 1.0f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  1.0f),
			VertexNormal(1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f),

			// Bottom Face
			VertexNormal(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f,-1.0f, -1.0f, -1.0f),
			VertexNormal(1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0f, -1.0f),
			VertexNormal(1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, -1.0f,  1.0f),
			VertexNormal(-1.0f, -1.0f,  1.0f, 1.0f, 0.0f,-1.0f, -1.0f,  1.0f),

			// Left Face
			VertexNormal(-1.0f, -1.0f,  1.0f, 0.0f, 1.0f,-1.0f, -1.0f,  1.0f),
			VertexNormal(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f,-1.0f,  1.0f,  1.0f),
			VertexNormal(-1.0f,  1.0f, -1.0f, 1.0f, 0.0f,-1.0f,  1.0f, -1.0f),
			VertexNormal(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f,-1.0f, -1.0f, -1.0f),

			// Right Face
			VertexNormal(1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0f, -1.0f),
			VertexNormal(1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 1.0f,  1.0f, -1.0f),
			VertexNormal(1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  1.0f,  1.0f),
			VertexNormal(1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, -1.0f,  1.0f),
		};

		D3D11_BUFFER_DESC vertexBufferDecs;
		ZeroMemory(&vertexBufferDecs, sizeof(D3D11_BUFFER_DESC));
		vertexBufferDecs.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDecs.ByteWidth = sizeof(VertexNormal) * 24;
		vertexBufferDecs.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDecs.CPUAccessFlags = 0;
		vertexBufferDecs.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData;
		ZeroMemory(&vertexBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
		vertexBufferData.pSysMem = v;

		d3d11Device->CreateBuffer(&vertexBufferDecs, &vertexBufferData, &SquareVertexBuffer);


		UINT stride = sizeof(VertexNormal);
		UINT offset = 0;
		d3d11DevCon->IASetVertexBuffers(0, 1, &SquareVertexBuffer, &stride, &offset);
	}
	void InitIndexBuffer()
	{
		DWORD indices[] = {
			// Front Face
			0,  1,  2,
			0,  2,  3,

			// Back Face
			4,  5,  6,
			4,  6,  7,

			// Top Face
			8,  9, 10,
			8, 10, 11,

			// Bottom Face
			12, 13, 14,
			12, 14, 15,

			// Left Face
			16, 17, 18,
			16, 18, 19,

			// Right Face
			20, 21, 22,
			20, 22, 23
		};

		D3D11_BUFFER_DESC indexBufferDecs;
		ZeroMemory(&indexBufferDecs, sizeof(D3D11_BUFFER_DESC));
		indexBufferDecs.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDecs.ByteWidth = sizeof(DWORD) * 12 * 3;
		indexBufferDecs.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDecs.CPUAccessFlags = 0;
		indexBufferDecs.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA indexBufferData;
		ZeroMemory(&indexBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
		indexBufferData.pSysMem = indices;

		d3d11Device->CreateBuffer(&indexBufferDecs, &indexBufferData, &SquareIndexBuffer);
		d3d11DevCon->IASetIndexBuffer(SquareIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}
	void InitLayoutModel()
	{
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL"   , 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		UINT numElement = ARRAYSIZE(layout);
		d3d11Device->CreateInputLayout(layout, numElement, VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), &VertLayout);
		d3d11DevCon->IASetInputLayout(VertLayout);
	}
	void InitViewPort()
	{
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = Window.Wight;
		viewport.Height = Window.Heignt;
		//new_
		viewport.MaxDepth = 1.0f;
		viewport.MinDepth = 0.0f;
		//new-

		d3d11DevCon->RSSetViewports(1, &viewport);
	}
	void InitDepth()
	{
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(D3D11_TEXTURE2D_DESC));
		depthStencilDesc.Width = Window.Wight;
		depthStencilDesc.Height = Window.Heignt;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		d3d11Device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
		d3d11Device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);
	}
	void InitCamera()
	{
		Camera.camStartPos = XMVectorSet(0.0f, 5.0f, -8.0f, 0.0f);
		Camera.camStartTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		Camera.camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		Camera.camView = XMMatrixLookAtLH(Camera.camStartPos, Camera.camStartTarget, Camera.camUp);
		Camera.camProjection = XMMatrixPerspectiveFovLH(0.4f * 3.14f, 1600./1400., 1.0f, 1000.0f);
	}
	void InitModBlending()
	{
		D3D11_RASTERIZER_DESC cmdesc;
		ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));

		cmdesc.FillMode = D3D11_FILL_SOLID;
		cmdesc.CullMode = D3D11_CULL_BACK;

		cmdesc.FrontCounterClockwise = true;
		d3d11Device->CreateRasterizerState(&cmdesc, &CCWcullMode);

		cmdesc.FrontCounterClockwise = false;
		d3d11Device->CreateRasterizerState(&cmdesc, &CWcullMode);


		D3D11_RASTERIZER_DESC rastDesc;
		ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
		rastDesc.FillMode = D3D11_FILL_SOLID;
		rastDesc.CullMode = D3D11_CULL_NONE;

		d3d11Device->CreateRasterizerState(&rastDesc, &noCull);
	}
	void InitBlendMaterial()
	{
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(blendDesc));

		D3D11_RENDER_TARGET_BLEND_DESC rtbd;
		ZeroMemory(&rtbd, sizeof(rtbd));

		rtbd.BlendEnable = true;
		rtbd.SrcBlend = D3D11_BLEND_SRC_COLOR;
		//rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		rtbd.DestBlend = D3D11_BLEND_BLEND_FACTOR;
		rtbd.BlendOp = D3D11_BLEND_OP_ADD;
		rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
		rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
		rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.RenderTarget[0] = rtbd;

		d3d11Device->CreateBlendState(&blendDesc, &Transparency);
	}
	void InitSunLight()
	{
		Light Light;
		Light.dir = XMFLOAT3(0.0f, 1.0f, 0.0f);
		Light.ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		Light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		Cbuffers.constbuffPerFrame.light = Light;
		d3d11DevCon->UpdateSubresource(cbPerFrameBuffer, 0, NULL, &Cbuffers.constbuffPerFrame, 0, 0);
		d3d11DevCon->PSSetConstantBuffers(0, 1, &cbPerFrameBuffer);
	}
	void InitPointLight()
	{
		Light Light;
		Light.pos = XMFLOAT3(1.0f, 1.0f, 0.0f);
		Light.range = 100.0f;
		Light.att = XMFLOAT3(1.0f, 0.2f, 0.0f);
		Light.ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
		Light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		Cbuffers.constbuffPerFrame.light = Light;
		d3d11DevCon->UpdateSubresource(cbPerFrameBuffer, 0, NULL, &Cbuffers.constbuffPerFrame, 0, 0);
		d3d11DevCon->PSSetConstantBuffers(0, 1, &cbPerFrameBuffer);
	}
	void InitShapeSphere(int LatLines, int LongLines)
	{
		NumSphereVertices = ((LatLines - 2) * LongLines) + 2;
		NumSphereFaces = ((LatLines - 3) * (LongLines) * 2) + (LongLines * 2);

		float sphereYaw = 0.0f;
		float spherePitch = 0.0f;

		std::vector<VertexNormal> vertices(NumSphereVertices);

		XMVECTOR currVertPos = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

		vertices[0].pos.x = 0.0f;
		vertices[0].pos.y = 0.0f;
		vertices[0].pos.z = 1.0f;

		for (DWORD i = 0; i < LatLines - 2; ++i)
		{
			spherePitch = (i + 1) * (3.14 / (LatLines - 1));
			auto Rotationx = XMMatrixRotationX(spherePitch);
			for (DWORD j = 0; j < LongLines; ++j)
			{
				sphereYaw = j * (6.28 / (LongLines));
				auto Rotationy = XMMatrixRotationZ(sphereYaw);
				currVertPos = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), (Rotationx * Rotationy));
				currVertPos = XMVector3Normalize(currVertPos);
				vertices[i * LongLines + j + 1].pos.x = XMVectorGetX(currVertPos);
				vertices[i * LongLines + j + 1].pos.y = XMVectorGetY(currVertPos);
				vertices[i * LongLines + j + 1].pos.z = XMVectorGetZ(currVertPos);
			}
		}

		vertices[NumSphereVertices - 1].pos.x = 0.0f;
		vertices[NumSphereVertices - 1].pos.y = 0.0f;
		vertices[NumSphereVertices - 1].pos.z = -1.0f;


		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(VertexNormal) * NumSphereVertices;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData;

		ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
		vertexBufferData.pSysMem = &vertices[0];
		d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &sphereVertBuffer);


		std::vector<DWORD> indices(NumSphereFaces * 3);

		int k = 0;
		for (DWORD l = 0; l < LongLines - 1; ++l)
		{
			indices[k] = 0;
			indices[k + 1] = l + 1;
			indices[k + 2] = l + 2;
			k += 3;
		}

		indices[k] = 0;
		indices[k + 1] = LongLines;
		indices[k + 2] = 1;
		k += 3;

		for (DWORD i = 0; i < LatLines - 3; ++i)
		{
			for (DWORD j = 0; j < LongLines - 1; ++j)
			{
				indices[k] = i * LongLines + j + 1;
				indices[k + 1] = i * LongLines + j + 2;
				indices[k + 2] = (i + 1) * LongLines + j + 1;

				indices[k + 3] = (i + 1) * LongLines + j + 1;
				indices[k + 4] = i * LongLines + j + 2;
				indices[k + 5] = (i + 1) * LongLines + j + 2;

				k += 6; // next quad
			}

			indices[k] = (i * LongLines) + LongLines;
			indices[k + 1] = (i * LongLines) + 1;
			indices[k + 2] = ((i + 1) * LongLines) + LongLines;

			indices[k + 3] = ((i + 1) * LongLines) + LongLines;
			indices[k + 4] = (i * LongLines) + 1;
			indices[k + 5] = ((i + 1) * LongLines) + 1;

			k += 6;
		}

		for (DWORD l = 0; l < LongLines - 1; ++l)
		{
			indices[k] = NumSphereVertices - 1;
			indices[k + 1] = (NumSphereVertices - 1) - (l + 1);
			indices[k + 2] = (NumSphereVertices - 1) - (l + 2);
			k += 3;
		}

		indices[k] = NumSphereVertices - 1;
		indices[k + 1] = (NumSphereVertices - 1) - LongLines;
		indices[k + 2] = NumSphereVertices - 2;

		D3D11_BUFFER_DESC indexBufferDesc;
		ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(DWORD) * NumSphereFaces * 3;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA iinitData;

		iinitData.pSysMem = &indices[0];
		d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, &sphereIndexBuffer);
	}
	void InitSkyBox()
	{
		//Tell D3D we will be loading a cube texture
		D3DX11_IMAGE_LOAD_INFO loadSMInfo;
		loadSMInfo.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

		//Load the texture
		ID3D11Texture2D* SMTexture = 0;
		D3DX11CreateTextureFromFile(d3d11Device, "skymap.dds",
			&loadSMInfo, 0, (ID3D11Resource**)&SMTexture, 0);

		//Create the textures description
		D3D11_TEXTURE2D_DESC SMTextureDesc;
		SMTexture->GetDesc(&SMTextureDesc);

		//Tell D3D We have a cube texture, which is an array of 2D textures
		D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
		SMViewDesc.Format = SMTextureDesc.Format;
		SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
		SMViewDesc.TextureCube.MipLevels = SMTextureDesc.MipLevels;
		SMViewDesc.TextureCube.MostDetailedMip = 0;

		//Create the Resource view
		d3d11Device->CreateShaderResourceView(SMTexture, &SMViewDesc, &smrv);

	}
private: // обновление сцены

private: //обновление графики
	void UpdateText(std::wstring text, int inInt)
	{
		keyedMutex11->ReleaseSync(0);

		keyedMutex10->AcquireSync(0, 5);

		D2DRenderTarget->BeginDraw();

		D2DRenderTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));

		std::wostringstream printString;
		printString << text << inInt;
		printText = printString.str();

		D2D1_COLOR_F FontColor = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f);

		Brush->SetColor(FontColor);

		D2D1_RECT_F layoutRect = D2D1::RectF(0, 0, Window.Wight, Window.Heignt);

		D2DRenderTarget->DrawText(
			printText.c_str(),
			wcslen(printText.c_str()),
			TextFormat,
			layoutRect,
			Brush
		);

		D2DRenderTarget->EndDraw();

		keyedMutex10->ReleaseSync(1);

		keyedMutex11->AcquireSync(1, 5);

		d3d11DevCon->OMSetBlendState(Transparency, NULL, 0xffffffff);

		//d3d11DevCon->PSSetShader(D2D_PS, 0, 0);

		WorldPos.WVP = XMMatrixIdentity();
		Cbuffers.cbPerObj.World = XMMatrixTranspose(WorldPos.WVP);
		Cbuffers.cbPerObj.WVP = XMMatrixTranspose(WorldPos.WVP);
		d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &Cbuffers.cbPerObj, 0, 0);
		d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
		d3d11DevCon->PSSetShaderResources(0, 1, &d2dTexture);
		d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);

		d3d11DevCon->RSSetState(CWcullMode);

		d3d11DevCon->DrawIndexed(6, 0, 0);
	}
	void UpdateLight()
	{
		Light Light;
		XMVECTOR lightVector = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

		lightVector = XMVector3TransformCoord(lightVector, Property.ResultOBJ);

		Light.pos.x = XMVectorGetX(lightVector);
		Light.pos.y = XMVectorGetY(lightVector);
		Light.pos.z = XMVectorGetZ(lightVector);
	}
	void UpdateBlend()
	{
		float blendFactor[] = { 0.1f, 0.1f, 0.1f, 0.2f };
		d3d11DevCon->OMSetBlendState(0, 0, 0xffffffff);
		d3d11DevCon->OMSetBlendState(Transparency, blendFactor, 0xffffffff);
	}
	void UpdateViewObj(XMMATRIX cubeWorld)
	{
		Camera.camStartPos = XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f);
		Camera.camStartTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		Camera.camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		WorldPos.World = XMMatrixIdentity();

		WorldPos.WVP = cubeWorld * Camera.camView * Camera.camProjection;
		Cbuffers.cbPerObj.World = XMMatrixTranspose(cubeWorld);
		Cbuffers.cbPerObj.WVP = XMMatrixTranspose(WorldPos.WVP);
		d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &Cbuffers.cbPerObj, 0, 0);
		d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);

		d3d11DevCon->PSSetShaderResources(0, 1, &CubesTexture);
		d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);

		d3d11DevCon->RSSetState(CCWcullMode);
		//d3d11DevCon->RSSetState(NULL);
		d3d11DevCon->DrawIndexed(36, 0, 0);
		d3d11DevCon->RSSetState(CWcullMode);
		//d3d11DevCon->RSSetState(noCull);
		d3d11DevCon->DrawIndexed(36, 0, 0);
	}
	void UpdateCamera()
	{
		Camera.camRotationMatrix = XMMatrixRotationRollPitchYaw(Camera.camPitch, Camera.camYaw, 0.0f);
		Camera.camTarget = XMVector3TransformCoord(Camera.DefaultForward, Camera.camRotationMatrix);
		Camera.camTarget = XMVector3Normalize(Camera.camTarget);

		XMMATRIX RotateYTempMatrix;
		RotateYTempMatrix = XMMatrixRotationY(Camera.camYaw);


		//режим полета
		if (true)
		{
		Camera.camUp = XMVector3TransformCoord(Camera.camUp, Camera.camRotationMatrix);
		Camera.camRight = XMVector3TransformCoord(Camera.DefaultRight, Camera.camRotationMatrix);
		Camera.camForward = XMVector3TransformCoord(Camera.DefaultForward, Camera.camRotationMatrix);
		Camera.camPosition += Camera.moveUp * Camera.camUp;
		Camera.moveUp = 0.0f;
		}
		else
		{
		Camera.camUp = XMVector3TransformCoord(Camera.camUp, RotateYTempMatrix);
		Camera.camRight = XMVector3TransformCoord(Camera.DefaultRight, RotateYTempMatrix);
		Camera.camForward = XMVector3TransformCoord(Camera.DefaultForward, RotateYTempMatrix);
		}

		Camera.camPosition += Camera.moveLeftRight * Camera.camRight;
		Camera.camPosition += Camera.moveBackForward * Camera.camForward;

		Camera.moveLeftRight = 0.0f;
		Camera.moveBackForward = 0.0f;

		Camera.camTarget += Camera.camPosition;

		Camera.camView = XMMatrixLookAtLH(Camera.camPosition, Camera.camTarget, Camera.camUp);
	}
	void UpdateInput(double time) {

		DIMOUSESTATE mouseState;

		BYTE KeyState[256];

		DIKeyboard->Acquire();
		DIMouse->Acquire();

		DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState);

		DIKeyboard->GetDeviceState(sizeof(KeyState), (LPVOID)&KeyState);

		if (KeyState[DIK_ESCAPE] & 0x80)
			PostMessage(Window.hWND, WM_DESTROY, 0, 0);

		float speed = 15.0f * time;

		if (KeyState[DIK_A] & 0x80)
		{
			Camera.moveLeftRight -= speed;
		}
		if (KeyState[DIK_D] & 0x80)
		{
			Camera.moveLeftRight += speed;
		}
		if (KeyState[DIK_W] & 0x80)
		{
			Camera.moveBackForward += speed;
		}
		if (KeyState[DIK_S] & 0x80)
		{
			Camera.moveBackForward -= speed;
		}
		if (KeyState[DIK_SPACE] & 0x80)
		{
			Camera.moveUp += speed;
		}
		if (KeyState[DIK_LCONTROL] & 0x80)
		{
			Camera.moveUp -= speed;
		}

		if ((mouseState.lX != ControlInput.mouseLastState.lX) || (mouseState.lY != ControlInput.mouseLastState.lY))
		{
			Camera.camYaw += ControlInput.mouseLastState.lX * 0.001f;
			Camera.camPitch += mouseState.lY * 0.001f;

			ControlInput.mouseLastState = mouseState;
		}

	};
	void UpdateSkyBox()
	{
		sphereWorld = XMMatrixIdentity();
		Property.Scale = XMMatrixScaling(5.0f, 5.0f, 5.0f);
		Property.Translation = XMMatrixTranslation(XMVectorGetX(Camera.camPosition), XMVectorGetY(Camera.camPosition), XMVectorGetZ(Camera.camPosition));
		sphereWorld = Property.Scale * Property.Translation;
		UINT stride = sizeof(VertexNormal);
		UINT offset = 0;
		d3d11DevCon->IASetIndexBuffer(sphereIndexBuffer, DXGI_FORMAT_R32_UINT, 0);  // ошибка в том что индексы обычного блока удаляются!!!!!! нужно сделать последовательность
		d3d11DevCon->IASetVertexBuffers(0, 1, &sphereVertBuffer, &stride, &offset);

		//Cbuffers.cbPerObj.WVP = sphereWorld * Camera.camView * Camera.camProjection;
		//Cbuffers.cbPerObj.WVP = XMMatrixTranspose(Cbuffers.cbPerObj.WVP);
		//Cbuffers.cbPerObj.World = XMMatrixTranspose(sphereWorld);
		//d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &Cbuffers.cbPerObj, 0, 0);
		//d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
		//d3d11DevCon->PSSetShaderResources(0, 1, &smrv);
		//d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);
	/*	d3d11DevCon->VSSetShader(SKYMAP_VS, 0, 0);
		d3d11DevCon->PSSetShader(SKYMAP_PS, 0, 0);
		d3d11DevCon->OMSetDepthStencilState(DSLessEqual, 0);
		d3d11DevCon->RSSetState(RSCullNone);
		d3d11DevCon->DrawIndexed(NumSphereFaces * 3, 0, 0);
		d3d11DevCon->VSSetShader(VS, 0, 0);*/
		//d3d11DevCon->OMSetDepthStencilState(NULL, 0);
	}
public:
	bool GetHR;

	D3DEX(HINSTANCE hInstance)
	{
		GetHR = InitializeDirect3dApp(hInstance);
		InitD2DScreenTexture();
		InitShapeSphere(10, 10);
		InitDirectInput(hInstance);
		InitConstBuffer();
		InitShaders();
		InitSkyBox();
		InitVertexBuffer();
		InitIndexBuffer();
		InitBlendMaterial();
		InitModBlending();
		InitImageTexture();
		InitCamera();
		//InitPointLight();
		InitRasterized();
		InitSunLight();
		InitLayoutModel();
		d3d11DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		InitViewPort();
	};
	

	void UpdateDX(double time)
	{
		if (GetAsyncKeyState('R')) // RESET FX IN JUST TIME
			InitShaders();

		UpdateInput(time);
		UpdateCamera();
		UpdateLight();



		Property.ResultOBJ = XMMatrixIdentity();

		XMVECTOR rotaxis = XMVectorSet(1.f, 0.0f, 0.0f, 0.0f);
		XMVECTOR rotayis = XMVectorSet(0.0f, 1.f, 0.0f, 0.0f);
		XMVECTOR rotazis = XMVectorSet(0.0f, 0.0f, 1.f, 0.0f);

		Property.Rotationx = XMMatrixRotationAxis(rotaxis, 0);
		Property.Rotationy = XMMatrixRotationAxis(rotayis, 0);
		Property.Rotationz = XMMatrixRotationAxis(rotayis, 0);

		Property.Translation = XMMatrixTranslation(0, -2, 0);

		Property.Scale = XMMatrixScaling(20.f, 1.f, 20.f);

		Property.ResultOBJ = Property.Translation * Property.Scale;


		D3DXCOLOR bgColor(Property.red, Property.green, Property.blue, 0.0f);
		d3d11DevCon->ClearRenderTargetView(renderTargetView, bgColor);
		d3d11DevCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);


		//UpdateSkyBox();



		UpdateBlend();
		UpdateViewObj(Property.ResultOBJ);
		UpdateText(L"   FPS: ", Timer.fps);
		SwapChain->Present(0, 0);
	};


	//испрвить индексный буфер а если быть точнее распределить такие части как:
	// создание 1 раз
	// обновление изменений на сцене
	// рендер графики последовательно и логично


	void CleanAPP() {
		SwapChain->SetFullscreenState(false, NULL);
		PostMessage(Window.hWND, WM_DESTROY, 0, 0);
		SwapChain->Release();
		d3d11Device->Release();
		d3d11DevCon->Release();
		SquareVertexBuffer->Release();
		SquareIndexBuffer->Release();
		VS->Release();
		PS->Release();
		VS_Buffer->Release();
		PS_Buffer->Release();
		VertLayout->Release();
		depthStencilView->Release();
		depthStencilBuffer->Release();
		cbPerObjectBuffer->Release();
		//WireFrame->Release();
		CubesTexture->Release();
		CubesTexSamplerState->Release();
		Transparency->Release();
		CCWcullMode->Release();
		CWcullMode->Release();
		noCull->Release();
		d3d101Device->Release();
		keyedMutex11->Release();
		keyedMutex10->Release();
		D2DRenderTarget->Release();
		Brush->Release();
		BackBuffer11->Release();
		sharedTex11->Release();
		DWriteFactory->Release();
		TextFormat->Release();
		d2dTexture->Release();
		cbPerFrameBuffer->Release();
		D2D_PS->Release();
		D2D_PS_Buffer->Release();

		DIKeyboard->Unacquire();
		DIMouse->Unacquire();
		ControlInput.DirectInput->Release();

		sphereIndexBuffer->Release();
		sphereVertBuffer->Release();
		SKYMAP_VS->Release();
		SKYMAP_PS->Release();
		SKYMAP_VS_Buffer->Release();
		SKYMAP_PS_Buffer->Release();
		smrv->Release();
		DSLessEqual->Release();
		RSCullNone->Release();
	};	
private:
	IDXGISwapChain* SwapChain;
	ID3D11Device* d3d11Device;
	ID3D11DeviceContext* d3d11DevCon;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11Buffer* SquareVertexBuffer;
	ID3D11Buffer* SquareIndexBuffer;
	ID3D11VertexShader* VS;
	ID3D11PixelShader* PS;
	ID3D10Blob* VS_Buffer;
	ID3D10Blob* PS_Buffer;
	ID3D11InputLayout* VertLayout;
	ID3D11Buffer* cbPerObjectBuffer;
	ID3D11RasterizerState* WireFrame;
	ID3D11ShaderResourceView* CubesTexture;
	ID3D11SamplerState* CubesTexSamplerState;
	ID3D11BlendState* Transparency;
	ID3D11RasterizerState* CCWcullMode;
	ID3D11RasterizerState* CWcullMode;
	ID3D11RasterizerState* noCull;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D10Device1* d3d101Device;
	IDXGIKeyedMutex* keyedMutex11;
	IDXGIKeyedMutex* keyedMutex10;
	ID2D1RenderTarget* D2DRenderTarget;
	ID2D1SolidColorBrush* Brush;
	ID3D11Texture2D* BackBuffer11;
	ID3D11Texture2D* sharedTex11;
	ID3D11Buffer* d2dVertBuffer;
	ID3D11Buffer* d2dIndexBuffer;
	ID3D11ShaderResourceView* d2dTexture;
	IDWriteFactory* DWriteFactory;
	IDWriteTextFormat* TextFormat;
	std::wstring printText;
	ID3D11Buffer* cbPerFrameBuffer;
	ID3D11PixelShader* D2D_PS;
	ID3D10Blob* D2D_PS_Buffer;

	IDirectInputDevice8* DIKeyboard;
	IDirectInputDevice8* DIMouse;

	ID3D11Buffer* sphereIndexBuffer;
	ID3D11Buffer* sphereVertBuffer;

	ID3D11VertexShader* SKYMAP_VS;
	ID3D11PixelShader* SKYMAP_PS;
	ID3D10Blob* SKYMAP_VS_Buffer;
	ID3D10Blob* SKYMAP_PS_Buffer;

	ID3D11ShaderResourceView* smrv;

	ID3D11DepthStencilState* DSLessEqual;
	ID3D11RasterizerState* RSCullNone;
};