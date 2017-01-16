#version 410 core
layout(points) in;
layout(line_strip, max_vertices = 2) out;

// input position and color
in vec4 vertPosition[];
//in vec4 vertColor[];

//out gl_PerVertex {
//    vec4 gl_Position;
//};
//out vec4 geomColor;

void main() {

    gl_Position = vertPosition[0];
    //geomColor = vertColor[0];
    EmitVertex();
    gl_Position = vec4(vertPosition[0].x, 0.0, vertPosition[0].z, vertPosition[0].w);
    //geomColor = vertColor[0];
    EmitVertex();
    EndPrimitive();
    
}
