float4x4 World;
float4x4 View;
float4x4 Projection;
float4x4 WorldInverseTranspose;

float4 AmbientColor = float4(1, 1, 1, 1);
float AmbientIntensity = 0.1;

float3 DiffuseLightDirection = float3(1, 0, 0);
float4 DiffuseColor = float4(1, 1, 1, 1);
float DiffuseIntensity = 1.0;

float Shininess = 200;
float4 SpecularColor = float4(1, 1, 1, 1);
float SpecularIntensity = 1;
float3 ViewVector = float3(1, 0, 0);

float Transparency = 0.5;

texture ModelTexture;
sampler2D textureSampler = sampler_state {
    Texture = (ModelTexture);
    MinFilter = Linear;
    MagFilter = Linear;
    AddressU = Clamp;
    AddressV = Clamp;
};

struct VertexShaderInput
{
    float4 Position : POSITION0;
    float4 Normal : NORMAL0;
    float2 TextureCoordinate : TEXCOORD0;
};

struct VertexShaderOutput
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
    float3 Normal : TEXCOORD0;
    float2 TextureCoordinate : TEXCOORD1;
};

VertexShaderOutput VertexShaderFunction(VertexShaderInput input)
{
    VertexShaderOutput output;

    float4 worldPosition = mul(input.Position, World);
    float4 viewPosition = mul(worldPosition, View);
    output.Position = mul(viewPosition, Projection);

    float4 normal = normalize(mul(input.Normal, WorldInverseTranspose));
    float lightIntensity = dot(normal, DiffuseLightDirection);
    output.Color = saturate(DiffuseColor * DiffuseIntensity * lightIntensity);

    output.Normal = normal;

    output.TextureCoordinate = input.TextureCoordinate;
    return output;
}

float4 PixelShaderFunction(VertexShaderOutput input) : COLOR0
{
    float3 light = normalize(DiffuseLightDirection);
    float3 normal = normalize(input.Normal);
    float3 r = normalize(2 * dot(light, normal) * normal - light);
    float3 v = normalize(mul(normalize(ViewVector), World));
    float dotProduct = dot(r, v);

    float4 specular = SpecularIntensity * SpecularColor * max(pow(dotProduct, Shininess), 0) * length(input.Color);

    float4 textureColor = tex2D(textureSampler, input.TextureCoordinate);
    textureColor.a = 1;

    float4 color = saturate(textureColor * (input.Color) + AmbientColor * AmbientIntensity + specular);
    color.a = Transparency;
    return color;
}

// Also, just to give you an idea of how to use this, you could create a shader that has multiple passes in it. In the first pass, render the entire scene as you usually do, but anything that has any transparency (alpha value < 1), set it to 0, so that it doesn't get rendered at all. In the second pass, do the same thing, but this time, anything that is completely opaque (alpha value == 1), set the value to 0, and render everything else with their proper alpha values. With this approach, all of the solid objects will be drawn first, and anything that is transparent will show the solid objects through it.

technique Technique1
{
    pass Pass1
    {
        AlphaBlendEnable = TRUE;
        // there are two colors: the color that is already there (the background color, or destination color) and the color that we just created (sometimes referred to as the source color).
        // we want the source color to be multiplied by the alpha value of the color, which, in this case, represents the transparency, and the destination color will be multiplied by one minus the alpha value of the color we just created.
        DestBlend = INVSRCALPHA;    // DstColor.rgb * (1 - SrcColor.alpha)
        SrcBlend = SRCALPHA;        // SrcColor.rgb * SrcColor.alpha
        VertexShader = compile vs_2_0 VertexShaderFunction();
        PixelShader = compile ps_2_0 PixelShaderFunction();
    }
}
