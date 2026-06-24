//
// Created by Akira Mujawar on 18/02/26.
//

flat in int o_f_axis;
flat in int o_f_handle_type;

// 0 = lines, 1 = position, 2 = scale, 3 = rotation
// we will use this in future to highlight a selected part while interation (on click n hold)
uniform int u_selectedAxis;

out vec4 o_fragColor;

vec3 getAxisColor(int pAxis) {
    if (pAxis == 0) {
        return vec3(0.9, 0.2, 0.2); // red x
    }
    if (pAxis == 1) {
        return vec3(0.2, 0.85, 0.25); // green y
    }
    else {
        return vec3(0.2, 0.45, 0.95); // blue z
    }
}

void main() {
    float alpha = 1.0;
    vec3 color = getAxisColor(o_f_axis);

    // add transparancy to rotation handles
    if(o_f_handle_type == 3) {
        alpha = 0.85;
    }

    // dim the remaining axis when a selected axis is being clicked
    if(o_f_axis != u_selectedAxis && u_selectedAxis != -1) {
        alpha = 0.2;
    }

    o_fragColor = vec4(color, alpha);
}