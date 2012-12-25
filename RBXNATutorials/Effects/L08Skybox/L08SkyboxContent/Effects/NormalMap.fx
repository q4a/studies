float4x4 World;
float4x4 View;
float4x4 Projection;

float4 AmbientColor = float4(1, 1, 1, 1);
float AmbientIntensity = 0.1;

float4x4 WorldInverseTranspose; // the transpose of the inverse of the world matrix

float3 DiffuseLightDirection = float3(1, 0, 0);
float4 DiffuseColor = float4(1, 1, 1, 1);
float DiffuseIntensity = 1;

float Shininess = 200;  // 光泽度, 值越大光斑越小, 表面反射性越强, 能量越集中. 金属在 100~500, 镜子趋于无穷大
float4 SpecularColor = float4(1, 1, 1, 1);
float SpecularIntensity = 1;    // Lower intensities will result in dimmer highlights.
float3 ViewVector = float3(1, 0, 0);

texture ModelTexture;
sampler2D textureSampler = sampler_state {
    Texture = (ModelTexture);
    MagFilter = Linear;
    MinFilter = Linear;
    AddressU = Clamp;
    AddressV = Clamp;
};

float BumpConstant = 1;
texture NormalMap;
sampler2D bumpSampler = sampler_state {
    Texture = (NormalMap);
    MinFilter = Linear;
    MagFilter = Linear;
    AddressU = Wrap;
    AddressV = Wrap;
};

struct VertexShaderInput
{
    float4 Position : POSITION0;
    float3 Normal : NORMAL0;
    // These go along with the normal, and tell us how the surface is oriented.
    // We won't have to worry about calculating these, though, because the Model class and XNA will take care of them for us.
    // 有些模型含有 Tangent 和 Binormal, 有些则没有, 和模型格式和导出选项有关. 可以让 XNA 自动生成 (会覆盖已有的属性值)
    // 如果没有这两个属性, 当使用该 shader 时会报错:
    // The current vertex declaration does not include all the elements required by the current vertex shader. Tangent0 is missing.
    // A tangent vector points directly along the surface.
    float3 Tangent : TANGENT0;  // 切线
    // The binormal vector will also point along the surface, but it will be perpendicular to the tangent vector.
    // the binormal vector is the cross product of the normal and tangent vectors.
    float3 Binormal : BINORMAL0;    // 次法线/副法线
    float2 TextureCoordinate : TEXCOORD0;
};

struct VertexShaderOutput
{
    // Notice that we have gotten rid of the Color field, which was used for the diffuse lighting color.
    // This is because we will need to do this calculation on a pixel by pixel basis in the pixel shader, rather than in the vertex shader.
    // float4 Color : COLOR0;

    float4 Position : POSITION0;
    float2 TextureCoordinate : TEXCOORD0;
    float3 Normal : TEXCOORD1;
    float3 Tangent : TEXCOORD2;
    float3 Binormal : TEXCOORD3;
};

VertexShaderOutput VertexShaderFunction(VertexShaderInput input)
{
    VertexShaderOutput output;

    float4 worldPosition = mul(input.Position, World);
    float4 viewPosition = mul(worldPosition, View);
    output.Position = mul(viewPosition, Projection);

    output.Normal = normalize(mul(input.Normal, WorldInverseTranspose));
    output.Tangent = normalize(mul(input.Tangent, WorldInverseTranspose));
    output.Binormal = normalize(mul(input.Binormal, WorldInverseTranspose));

    output.TextureCoordinate = input.TextureCoordinate;

    return output;
}

float4 PixelShaderFunction(VertexShaderOutput input) : COLOR0
{
    // Calculate the normal, including the information in the bump map
    //  we pull out the normal information from the normal map.
    // We subtract 0.5 from each component so that our values are centered around 0.
    // We then multiply it by our BumpConstant amount, which will stretch it out appropriately.
    float3 bump = BumpConstant * (tex2D(bumpSampler, input.TextureCoordinate) - (0.5, 0.5, 0.5));
    // 新法线是旧法线 + 法线贴图中数据的合成. binormal 副法线/次法线
    // We then add in an amount based on the values in the normal map, factored in with the tangent and binormal vectors.
    float3 bumpNormal = input.Normal + (bump.x * input.Tangent + bump.y * input.Binormal);
    bumpNormal = normalize(bumpNormal);

    // Calculate the diffuse light component with the bump map normal
    // 用凹凸贴图/法线贴图计算所得法线 bumpNormal 来计算 diffuse 光照
    float diffuseIntensity = dot(normalize(DiffuseLightDirection), bumpNormal);
    if (diffuseIntensity < 0)
        diffuseIntensity = 0;

    // Calculate the specular light component with the bump map normal
    float3 light = normalize(DiffuseLightDirection);
    float3 r = normalize(2 * dot(light, bumpNormal) * bumpNormal - light);
    float3 v = normalize(mul(normalize(ViewVector), World));
    float dotProduct = dot(r, v);

    float4 specular = SpecularIntensity * SpecularColor * max(pow(dotProduct, Shininess), 0) * diffuseIntensity;

    // Calculate the texture color
    float4 textureColor = tex2D(textureSampler, input.TextureCoordinate);
    textureColor.a = 1;

    // Combine all of these values into one (including the ambient light)
    return saturate(textureColor * (diffuseIntensity) + AmbientColor * AmbientIntensity + specular);
}

technique BumpMapped
{
    pass Pass1
    {
        VertexShader = compile vs_2_0 VertexShaderFunction();
        PixelShader = compile ps_2_0 PixelShaderFunction();
    }
}
