#type vertex
#version 450 core

layout (location = 0) in vec3   a_Position;
layout (location = 1) in vec4   a_Color;
layout (location = 2) in vec2   a_TexCoord;
layout (location = 3) in float  a_TexIndex;
layout (location = 3) in float  a_TexIndex2;
layout (location = 4) in float  a_TilingFactor;

uniform mat4 u_ViewProjection;

out vec4    v_Color;
out vec2    v_TexCoord;
out float   v_TexIndex;
out float   v_TexIndex2;
out float   v_TilingFactor;

void main()
{
    v_Color = a_Color;
    v_TexCoord = a_TexCoord;
    v_TexIndex = a_TexIndex;
    v_TexIndex2 = a_TexIndex2;
    v_TilingFactor = a_TilingFactor;
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 450 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;
in float v_TexIndex2;
in float v_TilingFactor;

uniform vec4 u_Color;
uniform float u_TilingFactor;
uniform sampler2D u_Textures[32];

// All components are in the range [0…1], including hue.
vec3 rgb2hsv(vec4 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

void main()
{
    
    vec4 spriteCol = texture(u_Textures[1], v_TexCoord);
    vec3 hsv = rgb2hsv(texture(u_Textures[1],  v_TexCoord));
    vec4 palleteCol = texture(u_Textures[2],  vec2(1- hsv.x, 1-hsv.z));
	color = vec4(palleteCol.x,palleteCol.y,palleteCol.z,spriteCol.w);

}