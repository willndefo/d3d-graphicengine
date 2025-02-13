struct vertexIn
{
    float3 position : POSITION;
};

struct vertexOut
{
    float4 position : SV_POSITION;
};

vertexOut main(vertexIn input)
{
    vertexOut output;
    output.position = float4(input.position, 1.0f);

    return output;
}