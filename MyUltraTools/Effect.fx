struct Light
{
    float3 dir;
    float3 pos;
    float range;
    float3 att;
    float4 ambient;
    float4 diffuse;
};

cbuffer cbPerObject
{
    float4x4 WVP;
    float4x4 World;
};

cbuffer cbPerFrame
{
    Light light;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 worldPos : POSITION;
    float2 TexCoord : TEXCOORD;
    float3 normal : NORMAL;
};

VS_OUTPUT VS(float4 inPos : POSITION, float2 inTexCoord : TEXCOORD, float3 normal : NORMAL)
{
    VS_OUTPUT output;
    output.Pos = mul(inPos, WVP);
    output.normal = mul(normal, World);
    output.worldPos = mul(inPos, World);
    output.TexCoord = inTexCoord;

    return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
    input.normal = normalize(input.normal);

    float4 diffuse = ObjTexture.Sample(ObjSamplerState, input.TexCoord);
    
    clip(diffuse.a - .25);

    float3 finalColor = float3(0.0f, 0.0f, 0.0f);
    
    float3 lightToPixelVec = light.pos - input.worldPos;
        
    float d = length(lightToPixelVec);
    
    float3 finalAmbient = diffuse * light.ambient;

    if (d > light.range)
        return float4(finalAmbient, diffuse.a);
        
    lightToPixelVec /= d;
    
    float howMuchLight = dot(lightToPixelVec, input.normal);

    if (howMuchLight > 0.0f)
    {
        finalColor += howMuchLight * diffuse * light.diffuse;
        
        finalColor /= light.att[0] + (light.att[1] * d) + (light.att[2] * (d * d));
    }
        
    finalColor = saturate(finalColor + finalAmbient);
    
    return float4(finalColor, diffuse.a);
}

float4 D2D_PS(VS_OUTPUT input) : SV_TARGET
{
    input.normal = normalize(input.normal);

    float4 diffuse = ObjTexture.Sample(ObjSamplerState, input.TexCoord);

    return diffuse;
}

//float4 PS(VS_OUTPUT input) : SV_TARGET
//{
//    input.normal = normalize(input.normal);

//    float4 diffuse = ObjTexture.Sample(ObjSamplerState, input.TexCoord);
//    clip(diffuse.a - .25);
//    float3 finalColor;

//    finalColor = diffuse * light.ambient;
//    finalColor += saturate(dot(light.dir, input.normal) * light.diffuse * diffuse);
//    return float4(finalColor, diffuse.a);
//}

//float4 PS(VS_OUTPUT input) : SV_TARGET
//{
//    float4 diffuse = ObjTexture.Sample(ObjSamplerState, input.TexCoord);
    
//    clip(diffuse.a - .25);
    
//    return diffuse;
//}

//float4 PS(VS_OUTPUT input) : SV_TARGET
//{
//    return input.Color;
//}

//float4 PS(VS_OUTPUT input) : SV_TARGET
//{
//    return ObjTexture.Sample(ObjSamplerState, input.TexCoord);
//}