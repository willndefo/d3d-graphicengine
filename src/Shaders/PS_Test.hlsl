struct pixelIn
{
    float4 position : SV_POSITION;
};

float4 main(pixelIn input) : SV_TARGET
{
    return float4(1, 0, 0, 1);
}