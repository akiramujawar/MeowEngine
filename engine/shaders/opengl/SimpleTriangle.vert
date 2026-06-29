uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    const vec4 vertices[3] = vec4[](
            vec4(-1.0, -1.0, 5.0, 1.0),
            vec4( 1.0, -1.0, 5.0, 1.0),
            vec4( 0.0,  1.0, 5.0, 1.0)
    );

    vec4 world = vertices[gl_VertexID];
    vec4 view = u_view * world;
    gl_Position = u_projection * view;
}