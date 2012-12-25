float4x4 World;
float4x4 View;
float4x4 Projection;

float4 AmbientColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
float AmbientIntensity = 0.1f;

float4x4 WorldInverseTranspose; // the transpose of the inverse of the world matrix

float3 DiffuseLightDirection = float3(1.0f, 0.0f, 0.0f);
float4 DiffuseColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
float DiffuseIntensity = 1.0f;

float Shininess = 200;  // 光泽度, 值越大光斑越小, 表面反射性越强, 能量越集中. 金属在 100~500, 镜子趋于无穷大
float4 SpecularColor = float4(1, 1, 1, 1);    
float SpecularIntensity = 1;    // Lower intensities will result in dimmer highlights.
float3 ViewVector = float3(1, 0, 0);

struct VertexShaderInput
{
    float4 Position : POSITION0;
    float4 Normal : NORMAL0;
};

struct VertexShaderOutput
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
    float3 Normal : TEXCOORD0;
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

    output.Normal = normal;

    return output;
}

float4 PixelShaderFunction(VertexShaderOutput input) : COLOR0
{
    float3 light = normalize(DiffuseLightDirection);
    float3 normal = normalize(input.Normal);
    float3 r = normalize(2 * dot(light, normal) * normal - light);  // 反射后方向
    float3 v = normalize(mul(normalize(ViewVector), World));    // 观察方向

    float dotProduct = dot(r, v);   // 反射方向和观察方向的夹角 cos
    // 漫反射越暗 length(input.Color) 越小, 镜面反射越暗
    float4 specular = SpecularIntensity * SpecularColor * max(pow(dotProduct, Shininess), 0) * length(input.Color);

    return saturate(input.Color + AmbientColor * AmbientIntensity + specular);
}

technique Specular
{
    pass Pass1
    {
        VertexShader = compile vs_2_0 VertexShaderFunction();
        PixelShader = compile ps_2_0 PixelShaderFunction();
    }
}
