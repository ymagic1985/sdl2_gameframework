#version 410 core
//layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
//layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
//layout (location = 1) in vec2 aTexCoord; // the texture coords has attribute position 2

//out vec3 ourColor; // output a color to the fragment shader
out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;
//uniform mat4 vp;
/*
uniform float xoffset;
uniform float vsRed;
uniform float vsGreen;
uniform float vsBlue;
uniform float vsAlpha;
*/

//void main()
//{
//    gl_Position = vp * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    //ourColor = aColor; // set ourColor to the input color we got from the vertex data
//    TexCoord = aTexCoord;
//}

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;


uniform mat4 model;
uniform mat4 vp;

void main()
{
        FragPos = vec3(model * vec4(aPos, 1.0));
        Normal = mat3(transpose(inverse(model))) * aNormal;
	gl_Position = vp * model * vec4(FragPos, 1.0f);
        TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
