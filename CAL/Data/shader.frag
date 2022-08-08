#version 450

// The input texture coords
in vec2 vtexcoord;

// The texture to use
uniform sampler2D usamp;

// The color to output for the pixel
out vec4 fragColor;

// Main function
void main(void) {
    fragColor = texture(usamp, vtexcoord);
}