#ifdef GL_ES
// Set default precision to medium
//precision mediump int;
//precision mediump float;
#endif

uniform mat4 mpv_matrix;

attribute vec3  a_position;
attribute float a_scolor;

////attribute vec2 a_texcoord;
float buf;

varying vec3 v_color;

//! [0]
void main()
{
    //Calculate vertex position in screen space
    gl_Position = mpv_matrix * vec4(a_position,1);
    //u_selectcolor=u_selectcolor+0.00001;
    buf=a_scolor;

    v_color.r=floor(buf/(255.0*255.0));
    buf-=v_color.r*(255.0*255.0);
    v_color.r/=255.0;

    v_color.g=floor(buf/(255.0));
    buf-=v_color.g*(255.0);
    v_color.g/=255.0;

    v_color.b=buf/(255.0);
    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    //v_texcoord = a_texcoord;
}
//! [0]
