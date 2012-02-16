varying vec2 texCoord;

void main()
{
	texCoord = vec2(gl_Vertex.xy);
	gl_Position = vec4(gl_Vertex.xy * 2.0 - 1.0, 0.0, 1.0);
}
