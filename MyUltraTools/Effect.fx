struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
};

VS_OUTPUT VS(float3 inPos : POSITION)
{
    VS_OUTPUT output;
    output.Pos = float4(inPos, 1.0f);
    return output;
}

float4 PS() : SV_Target
{
    
    return float4(0.0f, 0.0f, 1.0f, 1.0f);
}