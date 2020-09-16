#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif
attribute vec3 a_position;
uniform mat4 mpv_matrix;
uniform float u_scale;

//! [0]
void main()
{
    // Calculate vertex position in screen space
    gl_Position = mpv_matrix * vec4(a_position*u_scale,1);

}
//! [0]
