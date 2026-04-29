#pragma once
#include "DirectEngine.h"
//Управление сценой

void UpdateScene(double time) {
	/*red += colormodr * 0.00008f;
	green += colormodg * 0.00005f;
	blue += colormodb * 0.00001f;*/

	if (red >= 1.0f || red <= 0.0f)
		colormodr *= -1;
	if (green >= 1.0f || green <= 0.0f)
		colormodg *= -1;
	if (blue >= 1.0f || blue <= 0.0f)
		colormodb *= -1;

	//Keep the cubes rotating
	rot += 2.0f * time;
	if (rot > 6.28f)
		rot = 0.0f;

	//Reset cube1World
	cubeWorld = XMMatrixIdentity();

	//Define cube1's world space matrix
	XMVECTOR rotaxis = XMVectorSet(0.0f, 0.2f, 0.0f, 0.0f);
	Rotation = XMMatrixRotationAxis(rotaxis, rot);
	Translation = XMMatrixTranslation(1.0f, 0.1f, 0.2f);
	Scale = XMMatrixScaling(1.f, 1.f, 1.f);

	cubeWorld = Translation * Rotation * Scale;
};