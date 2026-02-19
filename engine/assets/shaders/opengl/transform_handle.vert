//
// Created by Akira Mujawar on 18/02/26.
//

// these set using alVertexAttribPointer at the time of shader pipeline instance

// repsents the vertices of transform handles
layout(location = 0) in vec3 l_vertex;

// represents a given axis
layout(location = 1) in int l_axis;

// represents axis lines, position arrow-heads, scale cubes, rotation rings
layout(location = 2) in int l_handle_type;

// these are set at runtime at the time of rendering
uniform mat4 u_view;
uniform mat4 u_projection;
uniform vec3 u_cameraPosition;
uniform vec3 u_handlePosition;
uniform mat4 u_handleRotation;
uniform float u_handleScale;

// flat is like a const. it would pass same value towards fragment shader without interpolation
flat out int o_f_axis;
flat out int o_f_handle_type;

void main() {
    o_f_axis = l_axis;
    o_f_handle_type = l_handle_type;

    // constant screen size
    float dist = length(u_cameraPosition - u_handlePosition);
    float scale = dist * u_handleScale;

    // apply rotation (mat4), position (vec3), scale (float)
    vec4 localPosition = u_handleRotation * vec4(l_vertex * scale, 1.0);

    // convert to world position vec3
    vec3 worldPos = u_handlePosition + localPosition.xyz;

    // project the points
    gl_Position = u_projection * u_view * vec4(worldPos, 1.0);
}