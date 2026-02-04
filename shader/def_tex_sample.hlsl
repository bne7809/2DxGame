Texture2D image : register(t0);
SamplerState image_sampler : register(s0);

struct PSInput
{
    float2 tex_coord : TEXCOORD;
};

float4 main(PSInput input) : SV_Target
{
    return image.Sample(image_sampler, input.tex_coord);
}
