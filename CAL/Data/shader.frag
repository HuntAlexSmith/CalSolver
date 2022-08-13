#version 450

// The input texture coords
in vec2 vtexcoord;

// The texture to use
uniform sampler2D usamp;

// Uniforms for tint and alpha
uniform vec3 tint;
uniform float alpha;

// The color to output for the pixel
out vec4 fragColor;

// Main function
void main(void) {
    vec4 finalColor = texture(usamp, vtexcoord);
    finalColor += vec4(tint.x, tint.y, tint.z, 0.0f);
    finalColor.a = alpha;
    fragColor = finalColor;
}