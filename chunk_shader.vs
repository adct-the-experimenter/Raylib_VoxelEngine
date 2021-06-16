#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in float vertexColor;

uniform mat4 mvp;

out vec2 fragTexCoord;
out vec4 fragColor;

void main() {
    fragTexCoord = vertexTexCoord;
    fragColor = vec4(vertexColor, vertexColor, vertexColor, 1.0);
    
    gl_Position = mvp*vec4(vertexPosition, 1.0);
}