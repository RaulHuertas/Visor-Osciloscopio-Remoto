#version 410 core
//in vec4 geomColor;
out vec4 fragColor;

// entry point
//
void main( void )
{
	// pass through interpolated vertex color.
    //fragColor = geomColor;
    fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
