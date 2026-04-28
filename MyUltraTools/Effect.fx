cbuffer cbPerObject
{
    float4x4 WVP;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 TexCoord : TEXCOORD;
    float4 Color : COLOR;
};

VS_OUTPUT VS(float4 inPos : POSITION, float2 inTexCoord : TEXCOORD, float4 inColor : COLOR)
{
    VS_OUTPUT output;

    output.Pos = mul(inPos, WVP);
    output.TexCoord = inTexCoord;
    output.Color = inColor;

    return output;
}

//float4 PS(VS_OUTPUT input) : SV_TARGET
//{
//    //return input.Color;
//    return ObjTexture.Sample(ObjSamplerState, input.TexCoord);
//}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
    float4 diffuse = ObjTexture.Sample(ObjSamplerState, input.TexCoord);
    
    clip(diffuse.a - .25);
    
    return diffuse;
}

//float4 PS(VS_OUTPUT input) : SV_TARGET
//{
//    return ObjTexture.Sample(ObjSamplerState, input.TexCoord);
//}