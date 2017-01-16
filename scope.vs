#version 410 core
in float vertex;

out vec4 vertPosition;
//out vec4 vertColor;

void main( void )
{
    
    //vertColor = vec4( 0.0, 1.0, 0.0, 1.0 );
    vertPosition =  vec4(
                        (gl_VertexID/256.0)-1.0,
                        (vertex/2048.0)-1.0,
                        //(vertex/65535),
                        0.0,
                        1.0
                    );
    
}
