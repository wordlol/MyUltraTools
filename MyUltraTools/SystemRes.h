#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment (lib, "D3D10_1.lib")
#pragma comment (lib, "DXGI.lib")
#pragma comment (lib, "D2D1.lib")
#pragma comment (lib, "dwrite.lib")

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>
#include <D3D10_1.h>
#include <DXGI.h>
#include <D2D1.h>
#include <sstream>
#include <dwrite.h>



//OPENSPACE
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

void CleanAPP() {
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
};

LPCSTR WndClassName = "3D REDACTOR";
HWND hWND = NULL;
const int Wight = 800;
const int Heignt = 800;
HRESULT hr;


XMMATRIX WVP;
XMMATRIX World;
XMMATRIX camView;
XMMATRIX camProjection;
XMVECTOR camPosition;
XMVECTOR camTarget;
XMVECTOR camUp;


XMMATRIX XMMatrixPerspectiveFovLH
(FLOAT FovAngleY,
 FLOAT AspectRatio,
 FLOAT NearZ,
 FLOAT FarZ);


struct cbPerObject
{
	XMMATRIX  WVP;
	XMMATRIX  World;
}cbPerObj;

struct Light
{
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
}light;

struct cbPerFrame
{
	Light  light;
}constbuffPerFrame;


XMMATRIX cubeWorld;


XMMATRIX Rotation;
XMMATRIX Scale;
XMMATRIX Translation;
float rot = 0.01f;


float red = 0.0f;
float green = 0.0f;
float blue = 0.0f;
int colormodr = 1;
int colormodg = 1;
int colormodb = 1;


double countsPerSecond = 0.0;
__int64 CounterStart = 0;
int frameCount = 0;
int fps = 0;
__int64 frameTimeOld = 0;
double frameTime;

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

//ФУНКЦИИ
void StartTimer()
{
	LARGE_INTEGER frequencyCount;
	QueryPerformanceFrequency(&frequencyCount);

	countsPerSecond = double(frequencyCount.QuadPart);

	QueryPerformanceCounter(&frequencyCount);
	CounterStart = frequencyCount.QuadPart;
}
double GetTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return double(currentTime.QuadPart - CounterStart) / countsPerSecond;
}
double GetFrameTime()
{
	LARGE_INTEGER currentTime;
	__int64 tickCount;
	QueryPerformanceCounter(&currentTime);

	tickCount = currentTime.QuadPart - frameTimeOld;
	frameTimeOld = currentTime.QuadPart;

	if (tickCount < 0.0f)
		tickCount = 0.0f;

	return float(tickCount) / countsPerSecond;
}


