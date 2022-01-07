uniform sampler2D tex;
uniform vec2 iResolution;
in vec4 f_color;
in vec2 f_uv;
in vec3 f_coord;
out vec4 fragColor;

void main(void)
{
    vec4 sampled_color = texture(tex, f_uv);
    vec4 vertex_color = f_color;
    vec4 blend = vec4(1.0, 1.0, 1.0, 1.0);

    fragColor = sampled_color * vertex_color * blend;
    //fragColor = vec4(0.0, 0.0, 0.0, 1.0);
}