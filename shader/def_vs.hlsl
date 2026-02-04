struct VSInput
{
    float2 vert : POSITION;
};

struct VSOutput
{
    float4 position  : SV_Position;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    output.position = float4(input.vert, 0.0f, 1.0f);

    return output;
}
