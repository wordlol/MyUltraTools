struct Light
{
    float3 pos;
    float range;
    float3 dir;
    float cone;
    float3 att;
    float4 ambient;
    float4 diffuse;
};

cbuffer cbPerObject : register(b0)
{
    float4x4 WVP;
    float4x4 World;
};

cbuffer cbPerFrame : register(b1)
{
    Light light;
};

cbuffer cbPerColor : register(b2)
{
    float4 color;
};


Texture2D ObjTexture;
SamplerState ObjSamplerState;
TextureCube SkyMap;

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 TexCoord : TEXCOORD;
    float3 normal : NORMAL;
    float4 worldPos : POSITION;
};

struct SKYMAP_VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 texCoord : TEXCOORD;
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

SKYMAP_VS_OUTPUT SKYMAP_VS(float4 inPos : POSITION, float3 inTexCoord : TEXCOORD)
{
    SKYMAP_VS_OUTPUT output;
    
    output.Pos = mul(float4(inPos.xyz, 1.0f), WVP).xyww;
    output.texCoord = inPos;

    return output;
}


float4 PS(VS_OUTPUT input) : SV_TARGET
{
    input.normal = normalize(input.normal);
    float4 diffuse;
    
    if (color.w == 1.0f)
        diffuse = ObjTexture.Sample(ObjSamplerState, input.TexCoord);
    else
        diffuse = float4(color.rgb, 1.0f);
    
    clip(diffuse.a - .25);
    float3 finalColor = float3(0.0f, 0.0f, 0.0f);
    
    float3 lightToPixelVec = light.pos - input.worldPos;
        
    float d = length(lightToPixelVec);

    float3 finalAmbient = diffuse * light.ambient;

    if (d > light.range)
        return float4(finalAmbient, diffuse.a);
      
    lightToPixelVec /= d;

    float howMuchLight = dot(lightToPixelVec, input.normal);

    finalColor += diffuse * light.diffuse;
    finalColor /= (light.att[0] + (light.att[1] * d)) + (light.att[2] * (d * d));
    finalColor *= pow(max(dot(-lightToPixelVec, light.dir), 0.0f), light.cone);
    finalColor = saturate(finalColor + finalAmbient);
    
    return float4(finalColor, diffuse.a);
}





//float4 PS(VS_OUTPUT input) : SV_TARGET
//{
//    input.normal = normalize(input.normal);
    
//    float3 lightToPixelVec = light.pos - input.worldPos;
    
//    float4 diffuse = ObjTexture.Sample(ObjSamplerState, input.TexCoord);
//    clip(diffuse.a - .25);
//    float3 finalColor;
    
//    finalColor = diffuse * light.ambient;
//    finalColor += saturate(dot(light.dir, input.normal) * light.diffuse * diffuse);

//    return float4(finalColor * float3(color.rgb), diffuse.a);
//}

float4 SKYMAP_PS(SKYMAP_VS_OUTPUT input) : SV_Target
{
    return SkyMap.Sample(ObjSamplerState, input.texCoord);
}

float4 D2D_PS(VS_OUTPUT input) : SV_TARGET
{
    input.normal = normalize(input.normal);

    float4 diffuse = ObjTexture.Sample(ObjSamplerState, input.TexCoord);

    return diffuse;
}

