varying vec2 texCoord;
//varying vec2 dTexCoord; 
//varying vec2 cTexCoord;

void main(void) {
	
	//dTexCoord = vec2(gl_Vertex.xy);
	texCoord = vec2(gl_Vertex.xy);
	gl_Position = vec4(gl_Vertex.xy * 2.0 - 1.0, 0.0, 1.0); 

//	dTexCoord = gl_MultiTexCoord0.xy;
//	texCoord = gl_MultiTexCoord0.xy;
//	gl_Position = ftransform();

	
//	cTexCoord = vec2(gl_Vertex.xy / 2.0 + 1.0); //no
//	cTexCoord = gl_MultiTexCoord0.xy; // no
	
}