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
#pragma comment (lib, "libfbxsdk.lib")

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
#include <fstream>
#include <istream>
#include <fbxsdk.h>
#include <imgui.h>


bool nullbuffer_element[1] = {};
#define NULLBUFFER nullbuffer_element

struct {
	HWND hWND = NULL;
	HRESULT hr;
	int Wight = GetSystemMetrics(SM_CXSCREEN);
	int	Heignt = GetSystemMetrics(SM_CYSCREEN);
	bool Fullscreen = true;
	LPCSTR WndClassName = "3D REDACTOR";
}Window;

struct {
	DIMOUSESTATE mouseLastState;
	LPDIRECTINPUT8 DirectInput;
}ControlInput;

struct {
	XMMATRIX camView;
	XMMATRIX camProjection = XMMatrixPerspectiveFovLH(0.4f * 3.14f, 1600. / 1400., 1.0f, 1000.0f);
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
	XMMATRIX OBJBox;
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


struct Light
{
	Light()
	{
		ZeroMemory(this, sizeof(Light));
	}
	XMFLOAT3 pos;
	float range;
	XMFLOAT3 dir;
	float cone;
	XMFLOAT3 att;
	float pad2;
	XMFLOAT4 ambient;
	XMFLOAT4 diffuse;
}light;
struct Vertex
{

	Vertex() {}
	Vertex(float x, float y, float z,
		float u, float v,
		float nx, float ny, float nz
	)
		: pos(x, y, z), texCoord(u, v), normal(nx, ny, nz){
	}

	XMFLOAT3 pos;
	XMFLOAT2 texCoord;
	XMFLOAT3 normal;
};
struct Position
{
	Position() {}
	Position(float x, float y, float z) : x(x), y(y), z(z) {}

	float x;
	float y;
	float z;
};
struct Rotation
{
	Rotation() {}
	Rotation(float x, float y, float z) : x(x), y(y), z(z) {}

	float x;
	float y;
	float z;
};
struct Size
{
	Size() {}
	Size(float x, float y, float z) : x(x), y(y), z(z) {}

	float x;
	float y;
	float z;
};
struct Transparens
{
	Transparens() {}
	Transparens(float x, float y, float z, float a) : x(x), y(y), z(z), a(a) {}

	float x;
	float y;
	float z;
	float a;
};
struct Color
{
	Color() {}
	Color(float r, float g, float b, float a) : color(r, g, b, a) {}

	XMFLOAT4 color;
};

struct MaterialOBJ
{
	XMFLOAT3 ColorAround = {0.0f,0.0f,0.0f};
	XMFLOAT3 ColorDiffuse = {0.0f,0.0f,0.0f};
	XMFLOAT3 ColorEmission = {0.0f,0.0f,0.0f};
	XMFLOAT3 ColorKs = { 0.0f,0.0f,0.0f };
	float Transparensy = 0.0f;
	float Metallic = 0.0f;
	float Reflection = 0.0f;
	int ilumination = 0;
	std::wstring NameMaterial = L"NULL";
	ID3D11ShaderResourceView* meshSRVDiffuse = {nullptr};
	ID3D11ShaderResourceView* meshSRVNormal = {nullptr};
};
struct OBJ
{

	ID3D11Buffer* meshVertBuff = {nullptr};
	ID3D11Buffer* meshIndexBuff = {nullptr};
	UINT CountDrawIndex = {0};
	std::wstring NameObj = L"NULL";
};
struct ModelsOBJ
{
	std::vector<XMFLOAT2> SettingsDraw;
	std::vector<OBJ> Obj;
};
std::vector<MaterialOBJ> MaterialObj;
std::vector<ModelsOBJ> Models;

struct
{
	Position pos;

}obj_movment;

struct {
	struct cbPerObject
	{
		XMMATRIX  WVP;
		XMMATRIX  World;
	}cbPerObj;
	struct cbPerFrame
	{
		Light  light;
	}cbPerFrame;
	struct cbPerColor
	{
		XMFLOAT4 color;

	}cbPerColor;
}Cbuffers;

int NumSphereVertices;
int NumSphereFaces;
XMMATRIX sphereWorld;

Vertex Block_V[] = {
	// Front Face
	Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,-1.0f, -1.0f, -1.0f),
	Vertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f,-1.0f,  1.0f, -1.0f),
	Vertex(1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f,  1.0f, -1.0f),
	Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f),

	// Back Face
	Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f,-1.0f, -1.0f, 1.0f),
	Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, -1.0f, 1.0f),
	Vertex(1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f),
	Vertex(-1.0f,  1.0f, 1.0f, 1.0f, 0.0f,-1.0f,  1.0f, 1.0f),

	// Top Face
	Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,-1.0f, 1.0f, -1.0f),
	Vertex(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f,-1.0f, 1.0f,  1.0f),
	Vertex(1.0f, 1.0f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  1.0f),
	Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f),

	// Bottom Face
	Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f,-1.0f, -1.0f, -1.0f),
	Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0f, -1.0f),
	Vertex(1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, -1.0f,  1.0f),
	Vertex(-1.0f, -1.0f,  1.0f, 1.0f, 0.0f,-1.0f, -1.0f,  1.0f),

	// Left Face
	Vertex(-1.0f, -1.0f,  1.0f, 0.0f, 1.0f,-1.0f, -1.0f,  1.0f),
	Vertex(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f,-1.0f,  1.0f,  1.0f),
	Vertex(-1.0f,  1.0f, -1.0f, 1.0f, 0.0f,-1.0f,  1.0f, -1.0f),
	Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f,-1.0f, -1.0f, -1.0f),

	// Right Face
	Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0f, -1.0f),
	Vertex(1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 1.0f,  1.0f, -1.0f),
	Vertex(1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  1.0f,  1.0f),
	Vertex(1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, -1.0f,  1.0f),
};

DWORD Block_I[] = {
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

Vertex Plane_V[] = {
	// Front Face
	Vertex(
		-1.0f, -1.0f, -1.0f, 
		0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f
	),
	Vertex(
		-1.0f,  1.0f, -1.0f, 
		0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f
	),
	Vertex(
		1.0f,  1.0f, -1.0f, 
		1.0f, 0.0f, 
		1.0f,  1.0f, -1.0f
	),
	Vertex(
		1.0f, -1.0f, -1.0f, 
		1.0f, 1.0f, 
		1.0f, -1.0f, -1.0f
	),
};

DWORD Plane_I[] = {
	// Front Face
	0,  1,  2,
	0,  2,  3,
};

UINT stride = sizeof(Vertex);
UINT offset = 0;

enum MOD
{
	VERTEX_0,
	INDEX_0,
	CONSTANTA_0,
	RUSTER_0,
	RUSTER_1,
	RUSTER_2,
	RUSTER_3,
	TEXTURE_0,
	TEXTURE_1,
	SAMPLER_0,
	DEPTH_0,
	DEPTH_1,
	SH_VS0,
	SH_PS0,
	LAYER_0,
	LAYER_1,
	BLEND_0,

};
enum MOD_VISIBLE
{
	INSIDE_ONLY,
	OUTSIDE_ONLY,
	OUT_IN_SIDE,
	MODEL,
	NO_VISIBLE
};
enum MOD_ROTATION
{
	WORLD,
	LOCAL,
};
enum OBJECT
{
	SQUARE,
	PLANE,
	SPHERE,
	SKY_BOX,
	SPARK,
	MODEL_FBX,
	PARTICLES
};

class D3DEX
{
private:
	//Соединить нескольно модулей
	template<typename T, typename T2>
	void BindModuls(MOD mod,T** buf, T2** buf2)
	{
		if (mod == MOD::DEPTH_1)
		{
			d3d11Device->CreateDepthStencilView(*(ID3D11Texture2D**)buf, NULL, (ID3D11DepthStencilView**)buf2);
			return;
		}
		else if (mod == MOD::TEXTURE_1)
		{
			D3D11_TEXTURE2D_DESC SMTextureDesc;
			ZeroMemory(&SMTextureDesc, sizeof(D3D11_TEXTURE2D_DESC));
			(*(ID3D11Texture2D**)buf)->GetDesc(&SMTextureDesc);

			D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
			SMViewDesc.Format = SMTextureDesc.Format;
			SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
			SMViewDesc.TextureCube.MipLevels = SMTextureDesc.MipLevels;
			SMViewDesc.TextureCube.MostDetailedMip = 0;

			d3d11Device->CreateShaderResourceView(*(ID3D11Texture2D**)buf, &SMViewDesc, (ID3D11ShaderResourceView**)buf2);
			return;
		}
	}
	//Создание Семплера|Растеризатора|Глубины|Текстур|Смешение|
	template<typename T>
	void CreateModuleDX(MOD mod, T** buf, const char* namefile = "error.jpg")
	{
		if (mod == MOD::SAMPLER_0)
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
			d3d11Device->CreateSamplerState(&sampDesc, (ID3D11SamplerState**)buf);
			return;
		}

		else if (mod == MOD::RUSTER_0)
		{
			D3D11_RASTERIZER_DESC wfdesc;
			ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
			wfdesc.FillMode = D3D11_FILL_SOLID;
			wfdesc.CullMode = D3D11_CULL_NONE;
			wfdesc.AntialiasedLineEnable = TRUE;
			d3d11Device->CreateRasterizerState(&wfdesc, (ID3D11RasterizerState**)buf);
			return;
		}
		else if (mod == MOD::RUSTER_1)
		{
			D3D11_RASTERIZER_DESC cmdesc;
			ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
			cmdesc.FillMode = D3D11_FILL_SOLID;
			cmdesc.CullMode = D3D11_CULL_BACK;
			cmdesc.FrontCounterClockwise = true;
			d3d11Device->CreateRasterizerState(&cmdesc, (ID3D11RasterizerState**)buf);
			return;
		}
		else if (mod == MOD::RUSTER_2)
		{
			D3D11_RASTERIZER_DESC cmdesc;
			ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
			cmdesc.FillMode = D3D11_FILL_SOLID;
			cmdesc.CullMode = D3D11_CULL_BACK;
			cmdesc.FrontCounterClockwise = false;
			d3d11Device->CreateRasterizerState(&cmdesc, (ID3D11RasterizerState**)buf);
			return;
		}
		else if (mod == MOD::RUSTER_3)
		{
			D3D11_RASTERIZER_DESC cmdesc;
			ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
			cmdesc.FillMode = D3D11_FILL_SOLID;
			cmdesc.CullMode = D3D11_CULL_BACK;
			d3d11Device->CreateRasterizerState(&cmdesc, (ID3D11RasterizerState**)buf);
			return;
		}

		else if (mod == MOD::DEPTH_0)
		{
			D3D11_DEPTH_STENCIL_DESC dssDesc;
			ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
			dssDesc.DepthEnable = true;
			dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
			d3d11Device->CreateDepthStencilState(&dssDesc, (ID3D11DepthStencilState**)buf);
			return;
		}

		else if (mod == MOD::DEPTH_1)
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

			d3d11Device->CreateTexture2D(&depthStencilDesc, NULL, (ID3D11Texture2D**)buf);
		}

		else if (mod == MOD::TEXTURE_0)
		{
			D3DX11CreateShaderResourceViewFromFile(d3d11Device, namefile, NULL, NULL, (ID3D11ShaderResourceView**)buf, NULL);
		}
		else if (mod == MOD::TEXTURE_1)
		{
			D3DX11_IMAGE_LOAD_INFO loadSMInfo;
			loadSMInfo.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

			D3DX11CreateTextureFromFile(d3d11Device, namefile, &loadSMInfo, 0, (ID3D11Resource**)buf, 0);
		}

		else if (mod == MOD::BLEND_0)
		{
			D3D11_BLEND_DESC blendDesc;
			ZeroMemory(&blendDesc, sizeof(blendDesc));
			D3D11_RENDER_TARGET_BLEND_DESC rtbd;
			ZeroMemory(&rtbd, sizeof(rtbd));

			rtbd.BlendEnable = true;
			rtbd.SrcBlend = D3D11_BLEND_SRC_COLOR;
			rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			rtbd.DestBlend = D3D11_BLEND_BLEND_FACTOR;
			rtbd.BlendOp = D3D11_BLEND_OP_ADD;
			rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
			rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
			rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
			rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

			blendDesc.AlphaToCoverageEnable = false;
			blendDesc.RenderTarget[0] = rtbd;

			d3d11Device->CreateBlendState(&blendDesc, (ID3D11BlendState**)buf);
			return;
		}

	}
	//Создание Шейдера
	template<typename T>
	void CreateModuleDX(MOD mod, T** buf, LPCSTR NameShader, LPCSTR endpoint, ID3D10Blob** blob)
	{
		if (mod == MOD::SH_VS0)
		{
			D3DX11CompileFromFileA(NameShader, 0, 0, endpoint, "vs_5_0", 0, 0, 0, (ID3D10Blob**)blob, 0, 0);
			ID3D10Blob* pBlob = *(ID3D10Blob**)blob;
			d3d11Device->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, (ID3D11VertexShader**)buf);
		}
		else if (mod == MOD::SH_PS0)
		{
			D3DX11CompileFromFileA(NameShader, 0, 0, endpoint, "ps_5_0", 0, 0, 0, (ID3D10Blob**)blob, 0, 0);
			ID3D10Blob* pBlob = *(ID3D10Blob**)blob;
			d3d11Device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, (ID3D11PixelShader**)buf);
		}
	}
	//Создание Буферов
	template<typename T>
	void CreateModuleDX(MOD mod, T* v, UINT size, ID3D11Buffer** buf)
	{
		D3D11_BUFFER_DESC BufferDecs;
		D3D11_SUBRESOURCE_DATA BufferData;
		ZeroMemory(&BufferDecs, sizeof(D3D11_BUFFER_DESC));
		ZeroMemory(&BufferData, sizeof(D3D11_SUBRESOURCE_DATA));


		BufferDecs.Usage = D3D11_USAGE_DEFAULT;
		BufferDecs.CPUAccessFlags = 0;
		BufferDecs.MiscFlags = 0;
		BufferDecs.ByteWidth = size;

		if (mod == MOD::VERTEX_0)
		BufferDecs.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		else if (mod == MOD::INDEX_0)
		BufferDecs.BindFlags = D3D11_BIND_INDEX_BUFFER;
		else if (mod == MOD::CONSTANTA_0)
		{
			BufferDecs.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			d3d11Device->CreateBuffer(&BufferDecs, NULL, buf);
			return;
		}

		BufferData.pSysMem = v;

		d3d11Device->CreateBuffer(&BufferDecs, &BufferData, buf);
	}
	//Создание Слоев
	template<typename T>
	void CreateModuleDX(MOD mod, T** buf, ID3D10Blob* blob)
	{
		D3D11_INPUT_ELEMENT_DESC* temp = {};
		UINT size = {};

		if (mod = MOD::LAYER_0)
		{
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL"   , 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
			};
			temp = layout;
			size = ARRAYSIZE(layout);
		}
		else if (mod = MOD::LAYER_1)
		{
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};
			temp = layout;
			size = ARRAYSIZE(layout);
		}



		d3d11Device->CreateInputLayout(temp, size, blob->GetBufferPointer(), blob->GetBufferSize(), buf);
	}
	//Настройка шейдра для работы с объектами
	void SetModObject(ID3D11VertexShader* VS, ID3D11PixelShader* PS, ID3D11Buffer* BufferVER,ID3D11Buffer* BufferIND, ID3D11RasterizerState* RS, ID3D11InputLayout* Layout, ID3D11DepthStencilState* Depth = NULL)
	{
		d3d11DevCon->VSSetShader(VS, 0, 0);
		d3d11DevCon->PSSetShader(PS, 0, 0);
		d3d11DevCon->IASetVertexBuffers(0, 1, &BufferVER, &stride, &offset);
		d3d11DevCon->IASetIndexBuffer(BufferIND, DXGI_FORMAT_R32_UINT, 0);
		d3d11DevCon->RSSetState(RS);
		d3d11DevCon->IASetInputLayout(Layout);
		d3d11DevCon->OMSetDepthStencilState(Depth, 0);
	}

	void LoadObjModel(std::wstring filename)
	{
		std::wifstream fileIn(filename.c_str()); 
		std::wifstream fileInMtl;
		std::wstring meshMatLib;                 
		std::vector<XMFLOAT3> vertPos;
		std::vector<XMFLOAT3> vertNorm;
		std::vector<XMFLOAT2> vertTexCoord;
		std::vector<std::wstring> meshMaterials;
		wchar_t checkChar = '0';
		wchar_t checkCharMtl;
		std::vector<DWORD> index;
		std::vector<DWORD> indPos;
		std::vector<DWORD> indTex;
		std::vector<DWORD> indNorm;
		std::vector<Vertex> vertices;
		int n = 0;
		std::wstring temp_words;
		std::wstring meshMaterialsTemp = L"";
		std::wstring TempW = L"";
		ModelsOBJ model;
		OBJ obj;
		MaterialOBJ materialobj;
		float R, G, B;
		XMFLOAT3 TEMP;
		bool skip = true;

		while (fileIn)
		{
			if (skip == true && checkChar != 'o')
			{
				skip = false;
				checkChar = fileIn.get();
			}
			else
				skip = true;
			switch (checkChar)
			{
			case '#':
				{
					fileIn.ignore(1000, L'\n');
					break;
				}
			case 'm': 
				{
					std::wstring f_word = L"tllib ";
					getline(fileIn, temp_words);
					if (!temp_words.find(f_word))
					{
						meshMatLib = L"";
						for (int i = 0; i < temp_words.size(); i++)
						{
							if (i >= f_word.size())
								meshMatLib += temp_words[i];
						}

						fileInMtl.open(meshMatLib);
						while (fileInMtl)
						{
							checkCharMtl = fileInMtl.get();
							switch (checkCharMtl)
							{
								case '#':
								{
									fileInMtl.ignore(1000, L'\n');
									break;
								}
								case 'n':
								{
									std::wstring f_word = L"ewmtl ";
									getline(fileInMtl, temp_words);
									if (!temp_words.find(f_word))
									{
										TempW = L"";
										for (int i = 0; i < temp_words.size(); i++)
										{
											if (i >= f_word.size())
												TempW += temp_words[i];
										}
										materialobj.NameMaterial = TempW;
									}
									break;
								}
								case 'N':
								{
									checkCharMtl = fileInMtl.get();
									if (checkCharMtl == 's')
									{
										checkCharMtl = fileInMtl.get();
										if (checkCharMtl == ' ')
										{
											float Ns;
											fileInMtl >> Ns;
											materialobj.Metallic = Ns;
										}
									}
									else if (checkCharMtl == 'i')
									{
										checkCharMtl = fileInMtl.get();
										if (checkCharMtl == ' ')
										{
											float Ni;
											fileInMtl >> Ni;
											materialobj.Reflection = Ni;
										}
									}
									break;
								}
								case 'K':
								{
									checkCharMtl = fileInMtl.get();
									if (checkCharMtl == 'a')
									{
										checkCharMtl = fileInMtl.get();
										if (checkCharMtl == ' ')
										{
											fileInMtl >> R >> G >> B;
											TEMP.x = R;
											TEMP.y = G;
											TEMP.z = B;
											materialobj.ColorAround = TEMP;
										}
									}
									else if (checkCharMtl == 'd')
									{
										checkCharMtl = fileInMtl.get();
										if (checkCharMtl == ' ')
										{
											fileInMtl >> R >> G >> B;
											TEMP.x = R;
											TEMP.y = G;
											TEMP.z = B;
											materialobj.ColorDiffuse = TEMP;
										}
									}
									else if (checkCharMtl == 's')
									{
										checkCharMtl = fileInMtl.get();
										if (checkCharMtl == ' ')
										{
											fileInMtl >> R >> G >> B;
											TEMP.x = R;
											TEMP.y = G;
											TEMP.z = B;
											materialobj.ColorKs = TEMP;
										}
									}
									else if (checkCharMtl == 'e')
									{
										checkCharMtl = fileInMtl.get();
										if (checkCharMtl == ' ')
										{
											fileInMtl >> R >> G >> B;
											TEMP.x = R;
											TEMP.y = G;
											TEMP.z = B;
											materialobj.ColorEmission = TEMP;
										}
									}
									break;
								}
								case 'd':
								{
									checkCharMtl = fileInMtl.get();
									if (checkCharMtl == ' ')
									{
										float T;
										fileInMtl >> T;
										materialobj.Transparensy = T;
									}

									break;
								}
								case 'i':
								{
									std::wstring f_word = L"llum ";
									getline(fileInMtl, temp_words);
									if (!temp_words.find(f_word))
									{
										int il = 0;
										
										il = (int)temp_words[temp_words.size()-1] - 48;
										materialobj.ilumination = il;
									}
									
									checkCharMtl = fileInMtl.get();
									if (checkCharMtl != L'\n')
									{
										std::wstring f_word = L"ap_Kd ";
										getline(fileInMtl, temp_words);
										if (!temp_words.find(f_word))
										{
											TempW = L"";
											for (int i = 0; i < temp_words.size(); i++)
											{
												if (i >= f_word.size())
													TempW += temp_words[i];
											}

											ID3D11ShaderResourceView* tempMeshSRV;
											D3DX11CreateShaderResourceViewFromFileW(d3d11Device, TempW.c_str(),
												NULL, NULL, &tempMeshSRV, NULL);

											materialobj.meshSRVDiffuse = tempMeshSRV;
										}
									}
									
									MaterialObj.push_back(materialobj);
									materialobj.ColorAround = { 0.0f,0.0f,0.0f };
									materialobj.ColorDiffuse = { 0.0f,0.0f,0.0f };
									materialobj.ColorEmission = { 0.0f,0.0f,0.0f };
									materialobj.ColorKs = { 0.0f,0.0f,0.0f };
									materialobj.ilumination = {0};
									materialobj.meshSRVDiffuse = { nullptr };
									materialobj.meshSRVNormal = { nullptr };
									materialobj.Metallic = {0};
									materialobj.NameMaterial = {L"NULL"};
									materialobj.Reflection = {0};
									materialobj.Transparensy = {0};
									break;
								}
							default:
								break;
							}
						}
						fileInMtl.close();
						skip = true;
					}
					break;
				}
			case 'g':
				{
					checkChar = fileIn.get();
					if (checkChar == ' ')
					{
						getline(fileIn, temp_words);
						obj.NameObj = temp_words;
					}
					break;
				}
			case 'o':
			{
					checkChar = fileIn.get();
					if (checkChar == ' ')
					{
						getline(fileIn, temp_words);
						obj.NameObj = temp_words;
					}
					break;
			}
			case 'v': 
				{
					checkChar = fileIn.get();
					if (checkChar == ' ')
					{
						float vz, vy, vx;
						fileIn >> vx >> vy >> vz;
						vertPos.push_back(XMFLOAT3(vx*-1, vy, vz));
					}
					else if (checkChar == 't')
					{
						checkChar = fileIn.get();
						if (checkChar == ' ')
						{
							float vtcu, vtcv;
							fileIn >> vtcu >> vtcv;
							vertTexCoord.push_back(XMFLOAT2(vtcu, vtcv));
						}
					}
					else if (checkChar == 'n')
					{
						checkChar = fileIn.get();
						if (checkChar == ' ')
						{
							float vnx, vny, vnz;
							fileIn >> vnx >> vny >> vnz;
							vertNorm.push_back(XMFLOAT3(vnx * -1, vny, vnz));
						}
					}
					break;
				}
			case 's':
				{
					checkChar = fileIn.get();
					if (checkChar == ' ')
					{
						fileIn.ignore(1000, L'\n');
					}
					break;
				}
			case 'u':
				{
					std::wstring f_word = L"semtl ";
					getline(fileIn, temp_words);
					if (!temp_words.find(f_word))
					{
						while (true)
						{
								checkChar = fileIn.get();
							if (checkChar == L'f')
								checkChar = fileIn.get();
							else
								break;

							for (int i = 0; i < 3; i++)
							{
								std::wstring sss;
								fileIn >> sss;
								int a, b, c;
								swscanf_s(sss.c_str(), L"%d/%d/%d", &a, &b, &c);

								index.push_back(n);
								indPos.push_back(a - 1);
								indTex.push_back(b - 1);
								indNorm.push_back(c - 1);
								n++;
							}
							checkChar = fileIn.get();
						}

						if (checkChar == 'u')
							skip = false;

						Vertex tempVert;
						ID3D11Buffer* IndexBuffer;
						ID3D11Buffer* VertexBuffer;
						for (int j = 0; j < indPos.size(); j++)
						{
							tempVert.pos = vertPos[indPos[j]];
							tempVert.texCoord = vertTexCoord[indTex[j]];
							tempVert.normal = vertNorm[indNorm[j]];
							vertices.push_back(tempVert);
						}

						CreateModuleDX(VERTEX_0, &vertices[0], sizeof(Vertex) * vertices.size(), &VertexBuffer);
						CreateModuleDX(INDEX_0, &index[0], sizeof(DWORD) * index.size(), &IndexBuffer);
						obj.meshVertBuff = VertexBuffer;
						obj.meshIndexBuff = IndexBuffer;
						obj.CountDrawIndex = index.size();
						meshMaterialsTemp = L"";
						for (int i = 0; i < temp_words.size(); i++)
						{
							if (i >= f_word.size())
								meshMaterialsTemp += temp_words[i];
						}

						XMFLOAT2 TEMPfloat2;
						for (int i = 0; i < MaterialObj.size(); i++)
						{
							if (MaterialObj[i].NameMaterial == meshMaterialsTemp)
							{
								TEMPfloat2.x = i;

								if (MaterialObj[i].meshSRVDiffuse == nullptr)
									TEMPfloat2.y = 0;
								else
									TEMPfloat2.y = 1;

								break;
							}
						}
						model.SettingsDraw.push_back(TEMPfloat2);
						model.Obj.push_back(obj);

						n = 0;
						indPos.clear();
						indTex.clear();
						indNorm.clear();
						vertices.clear();
						index.clear();
						obj.CountDrawIndex = 0;
						obj.meshIndexBuff = {nullptr};
						obj.meshVertBuff = {nullptr};
						TEMPfloat2 = {0.0f,0.0f};
					}
					break;
				}
			default:
				break;
			}
		}
		fileIn.close();
		Models.push_back(model);
	}

private: //системы
	void CreateDirectInput(HINSTANCE hInstance) {

		DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&ControlInput.DirectInput,NULL);
		ControlInput.DirectInput->CreateDevice(GUID_SysKeyboard,&DIKeyboard,NULL);
		ControlInput.DirectInput->CreateDevice(GUID_SysMouse,&DIMouse,NULL);
		DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
		DIKeyboard->SetCooperativeLevel(Window.hWND, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		DIMouse->SetDataFormat(&c_dfDIMouse);
		DIMouse->SetCooperativeLevel(Window.hWND, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
	}
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

		CreateModuleDX(DEPTH_1, &depthStencilBuffer);
		BindModuls(DEPTH_1, &depthStencilBuffer, &depthStencilView);

		d3d11DevCon->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
		return true;
	};
	void SortModels()
	{
		OBJ objtemp;
		XMFLOAT2 xmfTemp;
		int xTemp;
		bool sort = false;

		for (int i = 0; i < Models.size(); i++)
		{
			sort = true;
			while (sort)
			{
				for (int j = 1; j < Models[i].SettingsDraw.size(); j++)
				{
					sort = false;
					if (Models[i].SettingsDraw[j-1].x > Models[i].SettingsDraw[j].x)
					{
						sort = true;
						xmfTemp = Models[i].SettingsDraw[j];
						Models[i].SettingsDraw[j] = Models[i].SettingsDraw[j-1];
						Models[i].SettingsDraw[j-1] = xmfTemp;

						objtemp = Models[i].Obj[j];
						Models[i].Obj[j] = Models[i].Obj[j-1];
						Models[i].Obj[j-1] = objtemp;
						break;
					}
				}
			}
		}
	}
private: //создание
	void InitShapeSphere(int LatLines, int LongLines)
	{
		NumSphereVertices = ((LatLines - 2) * LongLines) + 2;
		NumSphereFaces = ((LatLines - 3) * (LongLines) * 2) + (LongLines * 2);

		float sphereYaw = 0.0f;
		float spherePitch = 0.0f;

		std::vector<Vertex> vertices(NumSphereVertices);

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

		CreateModuleDX(VERTEX_0, &vertices[0], sizeof(Vertex) * NumSphereVertices, &sphereVertBuffer);
		CreateModuleDX(INDEX_0, &indices[0], sizeof(DWORD) * NumSphereFaces * 3, &sphereIndexBuffer);
	}
private: // обновление сцены
	void SetPointLight()
	{
		light.dir = XMFLOAT3(0.0f, 1.0f, 0.0f);
		light.pos = XMFLOAT3(1.0f, 1.0f, 0.0f);
		light.range = 100.0f;
		light.att = XMFLOAT3(1.0f, 0.2f, 0.0f);
		light.ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
		light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		Cbuffers.cbPerFrame.light = light;
		d3d11DevCon->UpdateSubresource(cbPerFrameBuffer, 0, NULL, &Cbuffers.cbPerFrame, 0, 0);
		d3d11DevCon->PSSetConstantBuffers(1, 1, &cbPerFrameBuffer);
	}
	void SetSunLight()
	{
		light.dir = XMFLOAT3(0.0f, 1.0f, 0.0f);
		light.ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		Cbuffers.cbPerFrame.light = light;

		d3d11DevCon->UpdateSubresource(cbPerFrameBuffer, 0, NULL, &Cbuffers.cbPerFrame, 0, 0);
		d3d11DevCon->PSSetConstantBuffers(1, 1, &cbPerFrameBuffer);
	}
	void SetSpotLight()
	{
		light.pos = XMFLOAT3(0.0f, 1.0f, 0.0f);
		light.dir = XMFLOAT3(0.0f, 0.0f, 1.0f);
		light.range = 1000.0f;
		light.cone = 20.0f;
		light.att = XMFLOAT3(0.4f, 0.02f, 0.0f);
		light.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
		light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		Cbuffers.cbPerFrame.light = light;
		d3d11DevCon->UpdateSubresource(cbPerFrameBuffer, 0, NULL, &Cbuffers.cbPerFrame, 0, 0);
		d3d11DevCon->PSSetConstantBuffers(1, 1, &cbPerFrameBuffer);
	}
	void SetViewPort(int Wight, int Heignt, int x, int y, float MaxD, float MinD) {
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
		viewport.TopLeftX = x;
		viewport.TopLeftY = y;
		viewport.Width = Wight;
		viewport.Height = Heignt;
		viewport.MaxDepth = 1.0f;
		viewport.MinDepth = 0.0f;
		d3d11DevCon->RSSetViewports(1, &viewport);
	}
	void SetTransform(Position pos, Rotation rot, Size size, XMMATRIX& obj, MOD_ROTATION mod)
	{
		if (mod == MOD_ROTATION::LOCAL)
		{
			obj = XMMatrixIdentity();
			obj = XMMatrixScaling(size.x, size.y, size.z)
				* XMMatrixRotationAxis(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), XMConvertToRadians(rot.x))
				* XMMatrixRotationAxis(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), XMConvertToRadians(rot.y))
				* XMMatrixRotationAxis(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), XMConvertToRadians(rot.z))
				* XMMatrixTranslation(pos.x, pos.y, pos.z);
		}
		else if (mod == MOD_ROTATION::WORLD)
		{
			obj = XMMatrixIdentity();
			obj = XMMatrixScaling(size.x, size.y, size.z)
				* XMMatrixTranslation(pos.x, pos.y, pos.z)
				* XMMatrixRotationAxis(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), XMConvertToRadians(rot.x))
				* XMMatrixRotationAxis(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), XMConvertToRadians(rot.y))
				* XMMatrixRotationAxis(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), XMConvertToRadians(rot.z));
		}

		WorldPos.World = XMMatrixIdentity();
		WorldPos.WVP = obj * Camera.camView * Camera.camProjection;
		Cbuffers.cbPerObj.World = XMMatrixTranspose(obj);
		Cbuffers.cbPerObj.WVP = XMMatrixTranspose(WorldPos.WVP);
		d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &Cbuffers.cbPerObj, 0, 0);
		d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
	}	
	void SetTransform(XMVECTOR pos, Size size, XMMATRIX& obj)
	{
		obj = XMMatrixIdentity();
		obj = XMMatrixScaling(size.x, size.y, size.z)
			* XMMatrixTranslationFromVector(pos);

		WorldPos.World = XMMatrixIdentity();
		WorldPos.WVP = obj * Camera.camView * Camera.camProjection;
		Cbuffers.cbPerObj.World = XMMatrixTranspose(obj);
		Cbuffers.cbPerObj.WVP = XMMatrixTranspose(WorldPos.WVP);
		d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &Cbuffers.cbPerObj, 0, 0);
		d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
	}
	//Name L"All" or L"NameObj"
	void SetModelOBJ(std::wstring NameObj, Position pos, MOD_ROTATION mod_rot, Rotation rot, Size size)
	{
		if (NameObj == L"All")
		{
			for (int i = 0; i < Models.size(); i++)
			{
				for (int j = 0; j < Models[i].Obj.size(); j++)
				{
					CreateObject(pos,mod_rot,rot,size,Models[i].Obj[j],MaterialObj[Models[i].SettingsDraw[j].x],Models[i].SettingsDraw[j].y);
				}
			}
		}
		else
		{
			for (int i = 0; i < Models.size(); i++)
			{
				for (int j = 0; j < Models[i].Obj.size(); j++)
				{
					if (Models[i].Obj[j].NameObj == NameObj)
						CreateObject(pos, mod_rot, rot, size, Models[i].Obj[j], MaterialObj[Models[i].SettingsDraw[j].x], Models[i].SettingsDraw[j].y);
				}
			}
		}

	}
private: //обновление графики
	void CrearViewPort()
	{
		D3DXCOLOR bgColor(Property.red, Property.green, Property.blue, 0.0f);
		d3d11DevCon->ClearRenderTargetView(renderTargetView, bgColor);
		d3d11DevCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);
	}
	void UpdateText(std::wstring text, int inInt)
	{
		d3d11DevCon->OMSetDepthStencilState(NULL, 0);
		d3d11DevCon->VSSetShader(VS, 0, 0);
		d3d11DevCon->IASetInputLayout(VertLayout);
		d3d11DevCon->IASetVertexBuffers(0, 1, &SquareVertexBuffer, &stride, &offset);
		d3d11DevCon->IASetIndexBuffer(SquareIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
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

		d3d11DevCon->RSSetState(CWcullMode);


		d3d11DevCon->PSSetShader(D2D_PS, 0, 0);
		WorldPos.WVP = XMMatrixIdentity();
		Cbuffers.cbPerObj.World = XMMatrixTranspose(WorldPos.WVP);
		Cbuffers.cbPerObj.WVP = XMMatrixTranspose(WorldPos.WVP);
		d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &Cbuffers.cbPerObj, 0, 0);
		d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
		d3d11DevCon->PSSetShaderResources(0, 1, &d2dTexture);
		d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);

		d3d11DevCon->DrawIndexed(6, 0, 0);
	}
	void BlendObject(ID3D11BlendState* Surface, Transparens Trans)
	{
		float blendFactor[] = { Trans.x, Trans.y, Trans.z, Trans.a };
		d3d11DevCon->OMSetBlendState(Surface, blendFactor, 0xffffffff);
	}
	void SetColor(Color color)
	{	
		Cbuffers.cbPerColor.color.x = color.color.x;
		Cbuffers.cbPerColor.color.y = color.color.y;
		Cbuffers.cbPerColor.color.z = color.color.z;
		Cbuffers.cbPerColor.color.w = color.color.w;
		d3d11DevCon->UpdateSubresource(cbPerColorBuffer, 0, NULL, &Cbuffers.cbPerColor, 0, 0);
		d3d11DevCon->PSSetConstantBuffers(2, 1, &cbPerColorBuffer);
	}
	void DrawViewObj(MOD_VISIBLE mod, ID3D11ShaderResourceView** tex, ID3D11SamplerState** sample, UINT size)
	{
		d3d11DevCon->PSSetShaderResources(0, 1, tex);
		d3d11DevCon->PSSetSamplers(0, 1, sample);

		if (mod == MOD_VISIBLE::OUTSIDE_ONLY)
		{
			d3d11DevCon->RSSetState(CWcullMode);
			d3d11DevCon->DrawIndexed(size, 0, 0);
			return;
		}
		else if (mod == MOD_VISIBLE::INSIDE_ONLY)
		{
			d3d11DevCon->RSSetState(CCWcullMode);
			d3d11DevCon->DrawIndexed(size, 0, 0);
			return;
		}
		else if (mod == MOD_VISIBLE::OUT_IN_SIDE)
		{
			d3d11DevCon->RSSetState(CCWcullMode);
			d3d11DevCon->DrawIndexed(size, 0, 0);
			d3d11DevCon->RSSetState(CWcullMode);
			d3d11DevCon->DrawIndexed(size, 0, 0);
			return;
		}
	}
	void UpdateCamera(bool fly, Position target)
	{
		Camera.camStartPos = XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f);
		Camera.camStartTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		Camera.camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		Camera.camRotationMatrix = XMMatrixRotationRollPitchYaw(Camera.camPitch, Camera.camYaw, 0.0f);
		Camera.camTarget = XMVector3TransformCoord(Camera.DefaultForward, Camera.camRotationMatrix);
		Camera.camTarget = XMVector3Normalize(Camera.camTarget);

		XMMATRIX RotateYTempMatrix;
		RotateYTempMatrix = XMMatrixRotationY(Camera.camYaw);

		//режим полета
		if (fly)
		{
		Camera.camUp = XMVector3TransformCoord(Camera.camUp, Camera.camRotationMatrix);
		Camera.camRight = XMVector3TransformCoord(Camera.DefaultRight, Camera.camRotationMatrix);
		Camera.camForward = XMVector3TransformCoord(Camera.DefaultForward, Camera.camRotationMatrix);
		}
		else
		{
		Camera.camUp = XMVector3TransformCoord(Camera.camUp, RotateYTempMatrix);
		Camera.camRight = XMVector3TransformCoord(Camera.DefaultRight, RotateYTempMatrix);
		Camera.camForward = XMVector3TransformCoord(Camera.DefaultForward, RotateYTempMatrix);
		}
		
		Camera.camPosition += target.x * Camera.camForward;
		Camera.camPosition += target.y * Camera.camRight;
		Camera.camPosition += target.z * Camera.camUp;

		Camera.moveUp = 0.0f;
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

		if (KeyState[DIK_LSHIFT] & 0x80)
		{
			speed = 100.0f * time;
		}
		if (KeyState[DIK_A] & 0x80)
		{
			Camera.moveLeftRight -= speed;
			obj_movment.pos.z -= speed;
		}
		if (KeyState[DIK_D] & 0x80)
		{
			Camera.moveLeftRight += speed;
			obj_movment.pos.z += speed;
		}
		if (KeyState[DIK_W] & 0x80)
		{
			Camera.moveBackForward += speed;
			obj_movment.pos.x += speed;
		}
		if (KeyState[DIK_S] & 0x80)
		{
			Camera.moveBackForward -= speed;
			obj_movment.pos.x -= speed;
		}
		if (KeyState[DIK_SPACE] & 0x80)
		{
			Camera.moveUp += speed;
			obj_movment.pos.y += speed;
		}
		if (KeyState[DIK_LCONTROL] & 0x80)
		{
			Camera.moveUp -= speed;
			obj_movment.pos.y -= speed;
		}

		if ((mouseState.lX != ControlInput.mouseLastState.lX) || (mouseState.lY != ControlInput.mouseLastState.lY))
		{
			Camera.camYaw += ControlInput.mouseLastState.lX * 0.001f;
			Camera.camPitch += mouseState.lY * 0.001f;

			ControlInput.mouseLastState = mouseState;
		}
	};
	void UpdateLightPosition()
	{
		light.range = 1000.0f;
		light.cone = 1.0f;
		light.att = XMFLOAT3(0.4f, 0.02f, 0.0f);
		light.ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		light.pos.x = XMVectorGetX(Camera.camPosition);
		light.pos.y = XMVectorGetY(Camera.camPosition);
		light.pos.z = XMVectorGetZ(Camera.camPosition);
		light.dir.x = XMVectorGetX(Camera.camTarget) - light.pos.x;
		light.dir.y = XMVectorGetY(Camera.camTarget) - light.pos.y;
		light.dir.z = XMVectorGetZ(Camera.camTarget) - light.pos.z;


		Cbuffers.cbPerFrame.light = light;
		d3d11DevCon->UpdateSubresource(cbPerFrameBuffer, 0, NULL, &Cbuffers.cbPerFrame, 0, 0);
		d3d11DevCon->PSSetConstantBuffers(1, 1, &cbPerFrameBuffer);
	}
private: 
	//создание объекта
	void CreateObject(OBJECT obj, Position pos, MOD_ROTATION mod_rot, Rotation rot, Size size, Color color, Transparens trans, MOD_VISIBLE Visible)
	{
		BlendObject(Transparency, trans);
		SetColor(color);
		if (obj == OBJECT::SQUARE)
		{
			SetModObject(VS, PS, SquareVertexBuffer, SquareIndexBuffer, WireFrame, VertLayout, NULL);
			SetTransform(pos, rot, size, Property.OBJBox, mod_rot);
			DrawViewObj(Visible, &CubesTexture, &CubesTexSamplerState, sizeof(Block_I));
		}
		else if (obj == OBJECT::SPHERE)
		{
			SetModObject(VS, PS, sphereVertBuffer, sphereIndexBuffer, WireFrame, VertLayout, NULL);
			SetTransform(pos, rot, size, Property.OBJBox, mod_rot);
			DrawViewObj(Visible, &CubesTexture, &CubesTexSamplerState, NumSphereFaces * 3);
		}
	}
	//создание объекта .obj
	void CreateObject(Position pos, MOD_ROTATION mod_rot, Rotation rot, Size size, OBJ object, MaterialOBJ Material, float Tex_noTex)
	{	
			Color color;
			color.color.x = Material.ColorDiffuse.x;
			color.color.y = Material.ColorDiffuse.y;
			color.color.z = Material.ColorDiffuse.z;
			color.color.w = Tex_noTex;
			Transparens trans;
			trans.x = 1 - Material.Transparensy;
			trans.y = 1 - Material.Transparensy;
			trans.z = 1 - Material.Transparensy;
			trans.a = 1 - Material.Transparensy;
			BlendObject(Transparency, trans);
			if (Tex_noTex == 1.0f)
			{
				d3d11DevCon->PSSetShaderResources(0, 1, &Material.meshSRVDiffuse);
				color.color.x = 1;
				color.color.y = 1;
				color.color.z = 1;
				color.color.w = 1;
				SetColor(color);
			}
			else
			{
			SetColor(color);
			}
				SetModObject(VS, PS, object.meshVertBuff, object.meshIndexBuff, NULL, NULL, NULL);
				SetTransform(pos, rot, size, meshWorld, mod_rot);
			d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);
			d3d11DevCon->RSSetState(WireFrame);
			d3d11DevCon->DrawIndexed(object.CountDrawIndex, 0, 0);
	}
	//СКАЙБОКС
	void CreateObject(OBJECT obj)
	{
		if (obj == OBJECT::SKY_BOX)
		{
			SetModObject(SKYMAP_VS, SKYMAP_PS, sphereVertBuffer, sphereIndexBuffer, WireFrame, VertSpeherLayout, DSLessEqual);
			SetTransform(Camera.camPosition, Size(1, 1, 1),sphereWorld);
			DrawViewObj(OUT_IN_SIDE, &smrv, &SpeherTexSamplerState, NumSphereFaces * 3);
		}
	}
public:
	bool GetHR;

	D3DEX(HINSTANCE hInstance)
	{
		std::locale::global(std::locale("C"));
		GetHR = InitializeDirect3dApp(hInstance);

		InitShapeSphere(10, 10);

		CreateDirectInput(hInstance);

		CreateModuleDX(CONSTANTA_0, NULLBUFFER, sizeof(Cbuffers.cbPerObj), &cbPerObjectBuffer);
		CreateModuleDX(CONSTANTA_0, NULLBUFFER, sizeof(Cbuffers.cbPerFrame), &cbPerFrameBuffer);
		CreateModuleDX(CONSTANTA_0, NULLBUFFER, sizeof(Cbuffers.cbPerColor), &cbPerColorBuffer);


		CreateModuleDX(SH_VS0, &VS, "Effect.fx", "VS", &VS_Buffer);
		CreateModuleDX(SH_PS0, &PS, "Effect.fx", "PS", &PS_Buffer);
		CreateModuleDX(SH_PS0, &D2D_PS, "Effect.fx", "D2D_PS", &D2D_PS_Buffer);
		CreateModuleDX(SH_VS0, &SKYMAP_VS, "Effect.fx", "SKYMAP_VS", &SKYMAP_VS_Buffer);
		CreateModuleDX(SH_PS0, &SKYMAP_PS, "Effect.fx", "SKYMAP_PS", &SKYMAP_PS_Buffer);


		CreateModuleDX(VERTEX_0, Plane_V, sizeof(Plane_V), &d2dVertBuffer);
		CreateModuleDX(INDEX_0, Plane_I, sizeof(Plane_I), &d2dIndexBuffer);
		CreateModuleDX(VERTEX_0, Block_V, sizeof(Block_V), &SquareVertexBuffer);
		CreateModuleDX(INDEX_0, Block_I, sizeof(Block_I), &SquareIndexBuffer);

		CreateModuleDX(BLEND_0, &Transparency);
		CreateModuleDX(TEXTURE_0, &CubesTexture, "block.jpg");
		CreateModuleDX(TEXTURE_1, &SMTexture, "skymap.dds");
		BindModuls(TEXTURE_1, &SMTexture, &smrv);

		CreateModuleDX(SAMPLER_0, &CubesTexSamplerState);
		CreateModuleDX(SAMPLER_0, &SpeherTexSamplerState);

		CreateModuleDX(RUSTER_0, &WireFrame);
		CreateModuleDX(RUSTER_0, &RSCullNone);
		CreateModuleDX(RUSTER_1, &CCWcullMode);
		CreateModuleDX(RUSTER_2, &CWcullMode);
		CreateModuleDX(RUSTER_3, &noCull);

		CreateModuleDX(DEPTH_0, &DSLessEqual);
		CreateModuleDX(LAYER_0, &VertLayout, VS_Buffer);
		CreateModuleDX(LAYER_1, &VertSpeherLayout, SKYMAP_VS_Buffer);
		d3d11Device->CreateShaderResourceView(sharedTex11, NULL, &d2dTexture);

		LoadObjModel(L"test.obj"); ///!!!!

		SortModels();
		SetViewPort(Window.Wight, Window.Heignt,0,0,1.f,0.f);
		//SetPointLight();
		//SetSunLight();
		//SetSpotLight();
		d3d11DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	};

	void UpdateDX(double time)		
	{   
		CrearViewPort();
		UpdateLightPosition();
		UpdateCamera(true, Position(Camera.moveBackForward, Camera.moveLeftRight, Camera.moveUp));
		//UpdateCamera(true, Position(obj_movment.pos.x, obj_movment.pos.y, obj_movment.pos.z));
		UpdateInput(time);

		test_timer += 50 * time;
		test_timer2 += 20 * time;
		
		SetModelOBJ(
			L"Cube",
			Position(0, 0, 0),
			LOCAL,
			Rotation(0, 0, 0),
			Size(1, 1, 1)
		);

		/*for (int i = 0; i < 700; i++)
		{
			SetModelOBJ(
				L"Suzanne",
				Position(i * 0.1f, i * 0.1f, 0),
				LOCAL,
				Rotation(0, 0, 0),
				Size(1, 1, 1)
			);
		}*/














		CreateObject(SKY_BOX); //SetModObject ВЛОЖЕН В СОЗДАНИЕ
		UpdateText(L"   FPS: ", Timer.fps);
		SwapChain->Present(0, 0);


		if(test_timer > 360)
			test_timer = 0;

		if (test_timer2 > 360)
			test_timer2 = 0;
	};


	void Clear()
	{
		SwapChain->SetFullscreenState(false, NULL);
		PostMessage(Window.hWND, WM_DESTROY, 0, 0);

		SwapChain->Release();
		d3d11Device->Release();
		d3d11DevCon->Release();
		renderTargetView->Release();
		SquareVertexBuffer->Release();
		SquareIndexBuffer->Release();
		VS->Release();
		PS->Release();
		VS_Buffer->Release();
		PS_Buffer->Release();
		VertLayout->Release();
		VertSpeherLayout->Release();
		cbPerObjectBuffer->Release();
		WireFrame->Release();
		CubesTexture->Release();
		CubesTexSamplerState->Release();
		SpeherTexSamplerState->Release();
		Transparency->Release();
		CCWcullMode->Release();
		CWcullMode->Release();
		noCull->Release();
		depthStencilView->Release();
		depthStencilBuffer->Release();
		d3d101Device->Release();
		keyedMutex11->Release();
		keyedMutex10->Release();
		D2DRenderTarget->Release();
		Brush->Release();
		BackBuffer11->Release();
		sharedTex11->Release();
		d2dVertBuffer->Release();
		d2dIndexBuffer->Release();
		d2dTexture->Release();
		DWriteFactory->Release();
		TextFormat->Release();
		cbPerFrameBuffer->Release();
		cbPerColorBuffer->Release();
		D2D_PS->Release();
		D2D_PS_Buffer->Release();
		sphereIndexBuffer->Release();
		sphereVertBuffer->Release();
		SKYMAP_VS->Release();
		SKYMAP_PS->Release();
		SKYMAP_VS_Buffer->Release();
		SKYMAP_PS_Buffer->Release();
		smrv->Release();
		DSLessEqual->Release();
		RSCullNone->Release();
		SMTexture->Release();
		DIKeyboard->Release();
		DIMouse->Release();
	};
private:
	IDXGISwapChain*				SwapChain;
	ID3D11Device*				d3d11Device;
	ID3D11DeviceContext*		d3d11DevCon;
	ID3D11RenderTargetView*		renderTargetView;
	ID3D11Buffer*				SquareVertexBuffer;
	ID3D11Buffer*				SquareIndexBuffer;
	ID3D11VertexShader*			VS;
	ID3D11PixelShader*			PS;
	ID3D10Blob*					VS_Buffer;
	ID3D10Blob*					PS_Buffer;
	ID3D11InputLayout*			VertLayout;
	ID3D11InputLayout*			VertSpeherLayout;
	ID3D11Buffer*				cbPerObjectBuffer;
	ID3D11RasterizerState*		WireFrame;
	ID3D11ShaderResourceView*	CubesTexture;
	ID3D11SamplerState*			CubesTexSamplerState;
	ID3D11SamplerState*			SpeherTexSamplerState;
	ID3D11BlendState*			Transparency;
	ID3D11RasterizerState*		CCWcullMode;
	ID3D11RasterizerState*		CWcullMode;
	ID3D11RasterizerState*		noCull;
	ID3D11DepthStencilView*		depthStencilView;
	ID3D11Texture2D*			depthStencilBuffer;
	ID3D10Device1*				d3d101Device;
	IDXGIKeyedMutex*			keyedMutex11;
	IDXGIKeyedMutex*			keyedMutex10;
	ID2D1RenderTarget*			D2DRenderTarget;
	ID2D1SolidColorBrush*		Brush;
	ID3D11Texture2D*			BackBuffer11;
	ID3D11Texture2D*			sharedTex11;
	ID3D11Buffer*				d2dVertBuffer;
	ID3D11Buffer*				d2dIndexBuffer;
	ID3D11ShaderResourceView*	d2dTexture;
	IDWriteFactory*				DWriteFactory;
	IDWriteTextFormat*			TextFormat;
	ID3D11Buffer*				cbPerFrameBuffer;
	ID3D11Buffer*				cbPerColorBuffer;
	ID3D11PixelShader*			D2D_PS;
	ID3D10Blob*					D2D_PS_Buffer;
	ID3D11Buffer*				sphereIndexBuffer;
	ID3D11Buffer*				sphereVertBuffer;
	ID3D11VertexShader*			SKYMAP_VS;
	ID3D11PixelShader*			SKYMAP_PS;
	ID3D10Blob*					SKYMAP_VS_Buffer;
	ID3D10Blob*					SKYMAP_PS_Buffer;
	ID3D11ShaderResourceView*	smrv;
	ID3D11DepthStencilState*	DSLessEqual;
	ID3D11RasterizerState*		RSCullNone;
	ID3D11Texture2D*			SMTexture;
	IDirectInputDevice8*		DIKeyboard;
	IDirectInputDevice8*		DIMouse;
	std::wstring printText;
	float test_timer = 0;
	float test_timer2 = 0;
	XMMATRIX meshWorld;
};