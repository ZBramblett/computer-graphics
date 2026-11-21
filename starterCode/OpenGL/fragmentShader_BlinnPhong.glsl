#version 330 core

layout(location=0) out vec4 fragmentColor;

uniform vec3 diffuseComponent;
uniform vec3 specularComponent;
uniform vec4 cameraPos;
uniform float shininess;
uniform vec4 lightPosWorld;

in vec4 normal;
in vec4 vertexWorldPos;

void main(void)
{
    vec4 n = normalize(normal);
    vec4 l = normalize(lightPosWorld - vertexWorldPos);

    float lamLighting = max(0.0, dot(n, l));
    vec4 viewDir = normalize((cameraPos - vertexWorldPos));
    vec4 halfVector = normalize((l + viewDir));
    float blinnLighting = pow(max(0.0, dot(n, halfVector)), shininess);
    vec3 diffuseShading = vec3( diffuseComponent.r * lamLighting, diffuseComponent.g * lamLighting, diffuseComponent.b * lamLighting );
    vec3 phongShading = diffuseShading + vec3(specularComponent.r * blinnLighting, specularComponent.g * blinnLighting, specularComponent.b * blinnLighting);
    fragmentColor = vec4(phongShading, 1.0);
}