#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif
uniform vec3  u_color;

//varying lowp vec4 col;

void main()
{
   gl_FragColor = vec4(u_color,1);
}
