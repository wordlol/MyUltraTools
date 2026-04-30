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
#include <dinput.h>

//OPENSPACE
LPCSTR WndClassName = "3D REDACTOR";
HWND hWND = NULL;
const int Wight = 1600;
const int Heignt = 1400;
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


XMMATRIX Rotationx;
XMMATRIX Rotationy;
XMMATRIX Rotationz;
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


float rotx = 0;
float roty = 0;
float scaleX = 1.0f;
float scaleY = 1.0f;


XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
XMVECTOR DefaultUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
XMVECTOR DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
XMVECTOR camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
XMVECTOR camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

XMMATRIX camRotationMatrix;
XMMATRIX groundWorld;

float moveLeftRight = 0.0f;
float moveBackForward = 0.0f;

float camYaw = 0.0f;
float camPitch = 0.0f;


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


