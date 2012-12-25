float4x4 World;
float4x4 View;
float4x4 Projection;

float3 CameraPosition;

Texture SkyBoxTexture;
samplerCUBE SkyBoxSampler = sampler_state
{
   texture = <SkyBoxTexture>;
   magfilter = LINEAR;
   minfilter = LINEAR;
   mipfilter = LINEAR;
   AddressU = Mirror;
   AddressV = Mirror;
};

struct VertexShaderInput
{
    float4 Position : POSITION0;
};

struct VertexShaderOutput
{
    float4 Position : POSITION0;
    // Used to look up the appropriate value in the skybox cubemap.
    // cubemap 纹理不是一般的 UV 纹理, 它是 float3 并用 texCUBE 采样
    float3 TextureCoordinate : TEXCOORD0;
};

VertexShaderOutput VertexShaderFunction(VertexShaderInput input)
{
    VertexShaderOutput output;

    float4 worldPosition = mul(input.Position, World);
    float4 viewPosition = mul(worldPosition, View);
    output.Position = mul(viewPosition, Projection);

    // 计算 cubemap 纹理
    // The texture coordinate is determined by finding the vector between the camera position and the vertex's position.
    float4 VertexPosition = mul(input.Position, World);
    output.TextureCoordinate = VertexPosition - CameraPosition;

    return output;
}

float4 PixelShaderFunction(VertexShaderOutput input) : COLOR0
{
    float4 color = texCUBE(SkyBoxSampler, normalize(input.TextureCoordinate));
    color.a = 1;
    return color;
}

technique Skybox
{
    pass Pass1
    {
        AlphaBlendEnable = TRUE;
        DestBlend = INVSRCALPHA;    // DstColor.rgb * (1 - SrcColor.alpha)
        SrcBlend = SRCALPHA;        // SrcColor.rgb * SrcColor.alpha

        VertexShader = compile vs_2_0 VertexShaderFunction();
        PixelShader = compile ps_2_0 PixelShaderFunction();
    }
}
