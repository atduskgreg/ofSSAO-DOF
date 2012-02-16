void main()
{
//	gl_FrontColor = gl_Color;
//	gl_TexCoord[0] = gl_MultiTexCoord0;
//	gl_Position = ftransform();

	gl_FrontColor = gl_Color;
	gl_TexCoord[0] = gl_Vertex;
	gl_Position = vec4(gl_Vertex.xy * 2.0 - 1.0, 0.0, 1.0); 
}
