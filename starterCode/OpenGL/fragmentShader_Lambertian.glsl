#version 330 core

layout(location=0) out vec4 fragmentColor;

uniform vec3 diffuseComponent;
uniform vec4 lightPosWorld[2];
uniform vec3 lightIntensity[2];

in vec4 normal;
in vec4 vertexWorldPos;

void main(void)
{
    vec4 n = normalize(normal);

    // adds up every light
    vec3 result = vec3(0.0);
    for (int i = 0; i < 2; ++i) {
        vec4 l = normalize(lightPosWorld[i] - vertexWorldPos);
        float val = max(0.0, dot(n, l));
        result += diffuseComponent * lightIntensity[i] * val;
    }

    fragmentColor = vec4(min(result, vec3(1.0)), 1.0);
}
