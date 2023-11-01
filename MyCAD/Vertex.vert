#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
//layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
//out vec2 TexCoords;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   FragPos = (model * vec4(aPos, 1.0)).xyz;
   // 乘逆矩阵的转置，解决不均匀缩放时的法向量改变问题
   Normal = mat3(transpose(inverse(model))) * aNormal;
   //TexCoords = aTexCoords;
}