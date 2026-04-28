#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>


LPCSTR WndClassName = "3D REDACTOR";
HWND hWND = NULL;

const int Wight = 800;
const int Heignt = 800;

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

ID3D11DepthStencilView* depthStencilView;
ID3D11Texture2D* depthStencilBuffer;

//матрицы
XMMATRIX WVP;
XMMATRIX World;
XMMATRIX camView;
XMMATRIX camProjection;

XMVECTOR camPosition;
XMVECTOR camTarget;
XMVECTOR camUp;

XMMATRIX XMMatrixPerspectiveFovLH
(
	FLOAT FovAngleY,
	FLOAT AspectRatio,
	FLOAT NearZ,
	FLOAT FarZ
);

struct cbPerObject
{
	XMMATRIX  WVP;
};
cbPerObject cbPerObj;

XMMATRIX cube1World;
XMMATRIX cube2World;

XMMATRIX Rotation;
XMMATRIX Scale;
XMMATRIX Translation;
float rot = 0.01f;


HRESULT hr;

float red = 0.0f;
float green = 0.0f;
float blue = 0.0f;
int colormodr = 1;
int colormodg = 1;
int colormodb = 1;

struct VertexCol
{
	VertexCol() {};
	VertexCol(float x, float y, float z,
		float r, float g, float b, float a) : pos(x, y, z), color(r,g,b,a) {}

	XMFLOAT3 pos;
	XMFLOAT4 color;
};
struct VertexTex
{
	VertexTex() {};
	VertexTex(float x, float y, float z, 
		float u, float v) : pos(x, y, z), texCoord(u,v) {
	}

	XMFLOAT3 pos;
	XMFLOAT2 texCoord;
};

void InitImageTexture()
{
	hr = D3DX11CreateShaderResourceViewFromFile(d3d11Device, "block.jpg",
		NULL, NULL, &CubesTexture, NULL);

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = d3d11Device->CreateSamplerState(&sampDesc, &CubesTexSamplerState);

}
void InitRasterized()
{
	D3D11_RASTERIZER_DESC wfdesc;
	ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
	wfdesc.FillMode = D3D11_FILL_WIREFRAME;
	wfdesc.CullMode = D3D11_CULL_NONE;
	wfdesc.AntialiasedLineEnable = TRUE;
	hr = d3d11Device->CreateRasterizerState(&wfdesc, &WireFrame);
	d3d11DevCon->RSSetState(WireFrame);
}
void InitShaders()
{
	hr = D3DX11CompileFromFileA("Effect.fx", 0, 0, "VS", "vs_5_0", 0, 0, 0, &VS_Buffer, 0, 0);
	hr = D3DX11CompileFromFileA("Effect.fx", 0, 0, "PS", "ps_5_0", 0, 0, 0, &PS_Buffer, 0, 0);

	d3d11Device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);
	d3d11Device->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);

	d3d11DevCon->VSSetShader(VS, 0, 0);
	d3d11DevCon->PSSetShader(PS, 0, 0);
}
void InitVertexBuffer()
{
	/*VertexCol v[] =
	{
		VertexCol(-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
		VertexCol(-1.0f, +1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f),
		VertexCol(+1.0f, +1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
		VertexCol(+1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
		VertexCol(-1.0f, -1.0f, +1.0f, 0.0f, 1.0f, 1.0f, 1.0f),
		VertexCol(-1.0f, +1.0f, +1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
		VertexCol(+1.0f, +1.0f, +1.0f, 1.0f, 0.0f, 1.0f, 1.0f),
		VertexCol(+1.0f, -1.0f, +1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
	};*/

	VertexTex v[] =
	{
		// Front Face
		VertexTex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		VertexTex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
		VertexTex(1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
		VertexTex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
		// Back Face
		VertexTex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f),
		VertexTex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
		VertexTex(1.0f,  1.0f, 1.0f, 0.0f, 0.0f),
		VertexTex(-1.0f,  1.0f, 1.0f, 1.0f, 0.0f),
		// Top Face
		VertexTex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f),
		VertexTex(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f),
		VertexTex(1.0f, 1.0f,  1.0f, 1.0f, 0.0f),
		VertexTex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f),
		// Bottom Face
		VertexTex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
		VertexTex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		VertexTex(1.0f, -1.0f,  1.0f, 0.0f, 0.0f),
		VertexTex(-1.0f, -1.0f,  1.0f, 1.0f, 0.0f),
		// Left Face
		VertexTex(-1.0f, -1.0f,  1.0f, 0.0f, 1.0f),
		VertexTex(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f),
		VertexTex(-1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
		VertexTex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
		// Right Face
		VertexTex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		VertexTex(1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
		VertexTex(1.0f,  1.0f,  1.0f, 1.0f, 0.0f),
		VertexTex(1.0f, -1.0f,  1.0f, 1.0f, 1.0f),
	};


	D3D11_BUFFER_DESC vertexBufferDecs;
	ZeroMemory(&vertexBufferDecs, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDecs.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDecs.ByteWidth = sizeof(VertexTex) * 24;
	vertexBufferDecs.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDecs.CPUAccessFlags = 0;
	vertexBufferDecs.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	vertexBufferData.pSysMem = v;

	hr = d3d11Device->CreateBuffer(&vertexBufferDecs, &vertexBufferData, &SquareVertexBuffer);


	UINT stride = sizeof(VertexTex);
	UINT offset = 0;
	d3d11DevCon->IASetVertexBuffers(0, 1, &SquareVertexBuffer, &stride, &offset);


}
void InitIndexBuffer()
{

	//DWORD indices[] = {
	//	// front face
	//	0, 1, 2,
	//	0, 2, 3,

	//	// back face
	//	4, 6, 5,
	//	4, 7, 6,

	//	// left face
	//	4, 5, 1,
	//	4, 1, 0,

	//	// right face
	//	3, 2, 6,
	//	3, 6, 7,

	//	// top face
	//	1, 5, 6,
	//	1, 6, 2,

	//	// bottom face
	//	4, 0, 3,
	//	4, 3, 7
	//};

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

	hr = d3d11Device->CreateBuffer(&indexBufferDecs, &indexBufferData, &SquareIndexBuffer);
	d3d11DevCon->IASetIndexBuffer(SquareIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
}
void InitLayoutModel()
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	UINT numElement = ARRAYSIZE(layout);
	hr = d3d11Device->CreateInputLayout(layout, numElement, VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), &VertLayout);
	d3d11DevCon->IASetInputLayout(VertLayout);
}
void InitViewPort()
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = Wight;
	viewport.Height = Heignt;
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
	depthStencilDesc.Width = Wight;
	depthStencilDesc.Height = Heignt;
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
void InitConstBuffer()
{
	D3D11_BUFFER_DESC cbbd;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbPerObject);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	hr = d3d11Device->CreateBuffer(&cbbd, NULL, &cbPerObjectBuffer);
}
void InitCamera()
{
	camPosition = XMVectorSet(0.0f, 3.0f, -8.0f, 0.0f);
	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
	camProjection = XMMatrixPerspectiveFovLH(0.4f * 3.14f, (float)Wight / (float)Heignt, 1.0f, 1000.0f);
}
void UpdateViewObj(XMMATRIX cubeWorld)
{
	camPosition = XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f);
	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	World = XMMatrixIdentity();

	WVP = cubeWorld * camView * camProjection;
	cbPerObj.WVP = XMMatrixTranspose(WVP);
	d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
	d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);

	d3d11DevCon->PSSetShaderResources(0, 1, &CubesTexture);
	d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);

	d3d11DevCon->DrawIndexed(36, 0, 0);
}


bool InitializeDirect3dApp(HINSTANCE hInstance) {

	DXGI_MODE_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = Wight;
	bufferDesc.Height = Heignt;
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
	swapChainDesc.OutputWindow = hWND;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &swapChainDesc, &SwapChain, &d3d11Device, NULL, &d3d11DevCon);

	ID3D11Texture2D* BackBuffer;
	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
	hr = d3d11Device->CreateRenderTargetView(BackBuffer, NULL, &renderTargetView);
	BackBuffer->Release();

	InitDepth();//<-- new
	d3d11DevCon->OMSetRenderTargets(1, &renderTargetView, depthStencilView);//<-- new
	return true;
};

bool InitScene() { 
	//InitRasterized();
	InitImageTexture();
	InitConstBuffer();
	InitCamera();
	InitShaders();
	InitVertexBuffer();
	InitIndexBuffer();
	InitLayoutModel();
	d3d11DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	InitViewPort();

	return true; 
};


void DrawScene() {
	if (GetAsyncKeyState('R')) // RESET FX IN JUST TIME
	{
	InitShaders();
	}

	D3DXCOLOR bgColor(red, 0.0f, 0.0f, 0.0f);
	d3d11DevCon->ClearRenderTargetView(renderTargetView, bgColor);
	d3d11DevCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);

	//UpdateViewObj(cube1World);
	UpdateViewObj(cube2World);
	SwapChain->Present(0, 0);
};

void UpdateScene() {
		red += colormodr * 0.00005f;
		green += colormodg * 0.00002f;
		blue += colormodb * 0.00001f;

		if (red >= 1.0f || red <= 0.0f)
			colormodr *= -1;
		if (green >= 1.0f || green <= 0.0f)
			colormodg *= -1;
		if (blue >= 1.0f || blue <= 0.0f)
			colormodb *= -1;

		//Keep the cubes rotating
		rot += .0001f;
		if (rot > 6.28f)
			rot = 0.0f;

		//Reset cube1World
		cube1World = XMMatrixIdentity();

		//Define cube1's world space matrix
		XMVECTOR rotaxis = XMVectorSet(0.1f, 0.0f, 0.0f, 0.0f);
		XMVECTOR rotaxis2 = XMVectorSet(0.0f, 0.1f, 0.0f, 0.0f);
		Rotation = XMMatrixRotationAxis(rotaxis, rot);
		Translation = XMMatrixTranslation(0.0f, 0.0f, 4.0f);

		//Set cube1's world space using the transformations
		cube1World = Translation * Rotation;

		//Reset cube2World
		cube2World = XMMatrixIdentity();

		//Define cube2's world space matrix
		Rotation = XMMatrixRotationAxis(rotaxis2, -rot);
		Scale = XMMatrixScaling(1.7f, 1.7f, 1.7f);

		//Set cube2's world space matrix
		cube2World = Rotation * Scale;
};


void CleanUp() {
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
	WireFrame->Release();
	CubesTexture->Release();
	CubesTexSamplerState->Release();
};

// Window app
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_KEYDOWN:
			if (wparam == VK_ESCAPE)
			{
				if (MessageBox(0, "Are you sure you want to exit?",
					"Really?", MB_YESNO | MB_ICONQUESTION) == IDYES)
					DestroyWindow(hwnd);
			}
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
};

bool InitializeWindow(HINSTANCE hinstance, int ShowWind, int wignt, int heignt, bool windowed)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hinstance;
	wc.hIcon = LoadIcon(NULL,IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WndClassName;
	
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "ERROR REGISTER WINDOW", "Error", MB_OK);
		return false;
	}

	hWND = CreateWindowEx(
		NULL,
		WndClassName,
		"3D REDACTOR",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		Wight, Heignt,
		NULL, NULL,
		hinstance,
		NULL
	);

	if (!hWND)
	{
		MessageBox(NULL, "ERROR CREATE WINDOW", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	ShowWindow(hWND, ShowWind);
	UpdateWindow(hWND);
	return true;
};

int MassegeLoop() {
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if(PeekMessage(&msg, NULL,0,0,PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			
			UpdateScene();
			DrawScene();
		}
	}
		return (int)msg.wParam;
};

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE rhinstance, LPSTR lpstr, int nshowcmd)
{
	if (!InitializeWindow(hinstance, nshowcmd, Wight, Heignt, true))
	{
		MessageBox(0, "Window Create - error", "Error", MB_OK);
		return 0;
	}

	if (!InitializeDirect3dApp(hinstance))
	{
		MessageBox(0, "DIRECT3D Create - error", "Error", MB_OK);
		return 0;
	}

	if (!InitScene())
	{
		MessageBox(0, "Scene Create - error", "Error", MB_OK);
		return 0;
	}

	MassegeLoop();
	CleanUp();

	return 0;
}