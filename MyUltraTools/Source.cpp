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
HRESULT hr;

//new_
ID3D11Buffer* triangleVertBuffer;
ID3D11VertexShader* VS;
ID3D11PixelShader* PS;
ID3D10Blob* VS_Buffer;
ID3D10Blob* PS_Buffer;
ID3D11InputLayout* VertLayout;
//new-

float red = 0.0f;
float green = 0.0f;
float blue = 0.0f;
int colormodr = 1;
int colormodg = 1;
int colormodb = 1;

//new_
struct Vertex
{
	Vertex() {};
	Vertex(float x, float y, float z) : pos(x, y, z) {}

	XMFLOAT3 pos;
};

void InitLayout()
{
	//ID3D11Device::CreateInputLayout;
	//ID3D11Device::CreateBuffer;
	//ID3D11DeviceContext::IAGetVertexBuffers;
	//ID3D11DeviceContext::IASetInputLayout;
	//ID3D11DeviceContext::IASetPrimitiveTopology;
	//ID3D11DeviceContext::Draw;
	//ID3D11DeviceContext::RSSetViewports;
	//ID3D11DeviceContext::OMSetRenderTargets;
	//IDXGISwapChain::Present;
}
//new-

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

	d3d11DevCon->OMSetRenderTargets(1, &renderTargetView, NULL);
	return true;
};

void CleanUp() {
	SwapChain->Release();
	d3d11Device->Release();
	d3d11DevCon->Release();
	triangleVertBuffer->Release();
	VS->Release();
	PS->Release();
	VS_Buffer->Release();
	PS_Buffer->Release();
	VertLayout->Release();
};

bool InitScene() { 
	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	UINT numElement = ARRAYSIZE(layout);

	hr = D3DX11CompileFromFileA("vs_ef.fx", 0, 0, "VS", "vs_5_0", 0, 0, 0, &VS_Buffer, 0, 0);
	hr = D3DX11CompileFromFileA("ps_ef.fx", 0, 0, "PS", "ps_5_0", 0, 0, 0, &PS_Buffer, 0, 0);
	
	d3d11Device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);
	d3d11Device->CreatePixelShader (PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);

	d3d11DevCon->VSSetShader(VS, 0, 0);
	d3d11DevCon->PSSetShader(PS, 0, 0);
	

	Vertex v[] =
	{
		Vertex( 0.0f,  0.5f,  0.5f),
		Vertex( 0.5f, -0.5f,  0.5f),
		Vertex(-0.5f, -0.5f,  0.5f),
	};
	

	D3D11_BUFFER_DESC vertexBufferDecs;
	ZeroMemory(&vertexBufferDecs, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDecs.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDecs.ByteWidth = sizeof(Vertex) * 3;
	vertexBufferDecs.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDecs.CPUAccessFlags = 0;
	vertexBufferDecs.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	vertexBufferData.pSysMem = v;


	hr = d3d11Device->CreateBuffer(&vertexBufferDecs, &vertexBufferData, &triangleVertBuffer);


	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	d3d11DevCon->IAGetVertexBuffers(0, 1, &triangleVertBuffer, &stride, &offset);


	hr = d3d11Device->CreateInputLayout(layout, numElement, VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), &VertLayout);
	d3d11DevCon->IASetInputLayout(VertLayout);


	d3d11DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = Wight;
	viewport.Height = Heignt;


	d3d11DevCon->RSSetViewports(1,&viewport);

	return true; 
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
};

void DrawScene() {
	D3DXCOLOR bgColor(red, 0.0f, 0.0f, 0.0f);

	d3d11DevCon->ClearRenderTargetView(renderTargetView, bgColor);

	d3d11DevCon->Draw(3,0);

	SwapChain->Present(0, 0);
};

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
