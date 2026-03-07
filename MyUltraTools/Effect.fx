struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

VS_OUTPUT VS(float3 inPos : POSITION, float4 col : COLOR)
{
    VS_OUTPUT output;
    output.Pos = float4(inPos, 1.0f);
    output.Color = col;
    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    return input.Color;
}