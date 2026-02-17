#version 330 core

uniform vec2 u_resolution;
uniform float u_time;

out vec4 FragColor;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

#define M_PI 3.1415926535897932384626433832795

void main() {
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;
    float t = u_time;

    vec3 color = vec3(
        sin(uv.x * (M_PI*2) + t + 4.188) * 0.5 + 0.5,
        sin(uv.x * (M_PI*2) + t + 2.094) * 0.5 + 0.5,
        sin(uv.x * (M_PI*2) + t) * 0.5 + 0.5
    );

    FragColor = vec4(color, 0.5) * texture(u_Texture, v_TexCoord);
}
