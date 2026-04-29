#pragma once
#include "UserAPP.h"

//Управление отрисовкой

void UpdateBlend()
{
	float blendFactor[] = { 0.1f, 0.1f, 0.1f, 0.2f };
	d3d11DevCon->OMSetBlendState(0, 0, 0xffffffff);
	d3d11DevCon->OMSetBlendState(Transparency, blendFactor, 0xffffffff);
}
void UpdateViewObj(XMMATRIX cubeWorld)
{
	camPosition = XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f);
	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	World = XMMatrixIdentity();

	WVP = cubeWorld * camView * camProjection;
	cbPerObj.World = XMMatrixTranspose(cubeWorld);
	cbPerObj.WVP = XMMatrixTranspose(WVP);
	d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
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


void DrawScene() {

	if (GetAsyncKeyState('R')) // RESET FX IN JUST TIME
	{
		InitShaders();
	}

	D3DXCOLOR bgColor(red, green, blue, 0.0f);
	d3d11DevCon->ClearRenderTargetView(renderTargetView, bgColor);
	d3d11DevCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);

	UpdateBlend();
	UpdateViewObj(cubeWorld);
	InitText(L"   FPS: ", fps);

	SwapChain->Present(0, 0);
};
