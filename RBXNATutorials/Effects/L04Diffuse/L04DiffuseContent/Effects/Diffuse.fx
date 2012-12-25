float4x4 World;
float4x4 View;
float4x4 Projection;

float4 AmbientColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
float AmbientIntensity = 0.1f;

float4x4 WorldInverseTranspose; // the transpose of the inverse of the world matrix

float3 DiffuseLightDirection = float3(1.0f, 0.0f, 0.0f);
float4 DiffuseColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
float DiffuseIntensity = 1.0f;

struct VertexShaderInput
{
    float4 Position : POSITION0;
    float4 Normal : NORMAL0;
};

struct VertexShaderOutput
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
};

VertexShaderOutput VertexShaderFunction(VertexShaderInput input)
{
    VertexShaderOutput output;

    float4 worldPosition = mul(input.Position, World);
    float4 viewPosition = mul(worldPosition, View);
    output.Position = mul(viewPosition, Projection);

    // takes the normal and transforms it in such a way that the normal is now relative to where the object is in the world.
    float4 normal = mul(input.Normal, WorldInverseTranspose);
    float lightIntensity = dot(normal, DiffuseLightDirection);
    // saturate: take a color and ensure that it has values between 0 and 1 for each of the components.
    output.Color = saturate(DiffuseColor * DiffuseIntensity * lightIntensity);

    return output;
}

float4 PixelShaderFunction(VertexShaderOutput input) : COLOR0
{
    return saturate(input.Color + AmbientColor * AmbientIntensity);
}

technique Diffuse
{
    pass Pass1
    {
        VertexShader = compile vs_2_0 VertexShaderFunction();
        PixelShader = compile ps_2_0 PixelShaderFunction();
    }
}
