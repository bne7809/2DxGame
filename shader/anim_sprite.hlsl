cbuffer Matrices : register(b0)
{
    float4x4 tex_mat;
    float4x4 mod_mat;
};

struct VSInput
{
    float4 vert : POSTEX;
};

struct VSOutput
{
    float2 tex_coord : TEXCOORD;
    float4 position  : SV_Position;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    float4 tex = mul(tex_mat, float4(input.vert.zw, 0.0f, 1.0f));
    output.tex_coord = tex.xy;

    output.position = mul(mod_mat, float4(input.vert.xy, 0.0f, 1.0f));

    return output;
}
