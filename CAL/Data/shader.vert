#version 450

// Input parameters for position and uv
in vec4 position;
in vec2 texcoord;

// Uniforms for transforming the objects
uniform mat4 objToWorld;
uniform mat4 worldToCam;
uniform mat4 camToNDC;

// the texture coordinates
out vec2 vtexcoord;

// The function
void main(void) {
    gl_Position = camToNDC * worldToCam * objToWorld * position;
    vtexcoord = texcoord;
}
