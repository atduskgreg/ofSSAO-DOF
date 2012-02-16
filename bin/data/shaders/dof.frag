uniform sampler2D bgl_RenderedTexture;
uniform sampler2D bgl_DepthTexture;
uniform float focus;  // this value comes from ReadDepth script.
uniform float aspectratiox;
uniform float aspectratioy;
uniform float blurclamp;  // max blur amount
uniform float bias; //aperture - bigger values for shallower depth of field
 
void main()
{
 
        float aspectratio = aspectratiox/aspectratioy;
        vec2 aspectcorrect = vec2(1.0,aspectratio);
       
        vec4 depth1   = texture2D(bgl_DepthTexture,gl_TexCoord[0].xy );
 
        float factor = ( depth1.x - focus );
         
        vec2 dofblur = vec2 (clamp( factor * bias, -blurclamp, blurclamp ));
 
 
        vec4 col = vec4(0.0);
       
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy);
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.0,0.4 )*aspectcorrect) * dofblur);
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.15,0.37 )*aspectcorrect) * dofblur);
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.29,0.29 )*aspectcorrect) * dofblur);
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.37,0.15 )*aspectcorrect) * dofblur);       
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.4,0.0 )*aspectcorrect) * dofblur);   
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.37,-0.15 )*aspectcorrect) * dofblur);       
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.29,-0.29 )*aspectcorrect) * dofblur);       
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.15,-0.37 )*aspectcorrect) * dofblur);
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.0,-0.4 )*aspectcorrect) * dofblur); 
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.15,0.37 )*aspectcorrect) * dofblur);
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.29,0.29 )*aspectcorrect) * dofblur);
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.37,0.15 )*aspectcorrect) * dofblur); 
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.4,0.0 )*aspectcorrect) * dofblur); 
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.37,-0.15 )*aspectcorrect) * dofblur);       
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.29,-0.29 )*aspectcorrect) * dofblur);       
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.15,-0.37 )*aspectcorrect) * dofblur);
       
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.15,0.37 )*aspectcorrect) * dofblur*0.9);
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.37,0.15 )*aspectcorrect) * dofblur*0.9);           
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.37,-0.15 )*aspectcorrect) * dofblur*0.9);           
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.15,-0.37 )*aspectcorrect) * dofblur*0.9);
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.15,0.37 )*aspectcorrect) * dofblur*0.9);
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.37,0.15 )*aspectcorrect) * dofblur*0.9);            
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.37,-0.15 )*aspectcorrect) * dofblur*0.9);   
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.15,-0.37 )*aspectcorrect) * dofblur*0.9);   
       
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.29,0.29 )*aspectcorrect) * dofblur*0.7);
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.4,0.0 )*aspectcorrect) * dofblur*0.7);       
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.29,-0.29 )*aspectcorrect) * dofblur*0.7);   
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.0,-0.4 )*aspectcorrect) * dofblur*0.7);     
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.29,0.29 )*aspectcorrect) * dofblur*0.7);
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.4,0.0 )*aspectcorrect) * dofblur*0.7);     
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.29,-0.29 )*aspectcorrect) * dofblur*0.7);   
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.0,0.4 )*aspectcorrect) * dofblur*0.7);
                         
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.29,0.29 )*aspectcorrect) * dofblur*0.4);
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.4,0.0 )*aspectcorrect) * dofblur*0.4);       
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.29,-0.29 )*aspectcorrect) * dofblur*0.4);   
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.0,-0.4 )*aspectcorrect) * dofblur*0.4);     
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.29,0.29 )*aspectcorrect) * dofblur*0.4);
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.4,0.0 )*aspectcorrect) * dofblur*0.4);     
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( -0.29,-0.29 )*aspectcorrect) * dofblur*0.4);   
        col += texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy + (vec2( 0.0,0.4 )*aspectcorrect) * dofblur*0.4);       
                       
        gl_FragColor = col/41.0;
        gl_FragColor.a = 1.0;
}
 