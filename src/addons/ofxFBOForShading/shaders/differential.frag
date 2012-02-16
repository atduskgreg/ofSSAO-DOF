uniform sampler2D texture;
 
const float dx = 0.001953125;
const float dy = 0.001953125;
 
float peek(const in float x, const in float y)
{
  return texture2D(texture, vec2(x, y)).r;
}
 
void main (void)
{
  float x = gl_TexCoord[0].x;
  float y = gl_TexCoord[0].y;
  float b = peek(x, y);
  float d = abs(b - peek(x + dx, y))
          + abs(b - peek(x, y + dy));
  gl_FragColor = vec4(vec3(1.0 - d), 1.0);
}