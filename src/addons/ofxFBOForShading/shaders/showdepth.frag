// showdepth.frag

//uniform sampler2DRect depth;
// 
//void main(void)
//{
//  gl_FragColor = texture2DRect(depth, gl_TexCoord[0].xy);
////  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
//}
 
uniform sampler2D depth;

varying vec2 dTexCoord;

void main(void)
{
  gl_FragColor = texture2D(depth, dTexCoord.xy);
//  gl_FragColor = texture2D(depth, gl_TexCoord[0].xy);
//  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}