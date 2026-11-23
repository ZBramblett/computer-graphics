#version 330 core

layout(location=0) out vec4 fragmentColor;

uniform vec3 diffuseComponent;
uniform vec3 specularComponent;
uniform vec4 cameraPos;
uniform float shininess;
uniform vec4 lightPosWorld[2];
uniform vec3 lightIntensity[2];

in vec4 normal;
in vec4 vertexWorldPos;

void main(void)
{
    vec4 n = normalize(normal);
    vec4 viewDir = normalize(cameraPos - vertexWorldPos);

    // adds up every light
    vec3 result = vec3(0.0);
    for (int i = 0; i < 2; ++i) {
        vec4 l = normalize(lightPosWorld[i] - vertexWorldPos);
        float lamLighting = max(0.0, dot(n, l));
        vec4 halfVector = normalize(l + viewDir);
        float blinnLighting = pow(max(0.0, dot(n, halfVector)), shininess);
        result += lightIntensity[i] * (diffuseComponent * lamLighting + specularComponent * blinnLighting);
    }

    fragmentColor = vec4(min(result, vec3(1.0)), 1.0);
}
