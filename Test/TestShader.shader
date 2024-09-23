#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
out vec2 v_uv;

void main()
{
   gl_Position = position;
   v_uv = uv;
};

#shader fragment
#version 330 core
out vec4 color;
in vec2 v_uv;
uniform sampler2D u_Texture;

void main()
{
   color = texture(u_Texture,v_uv);
};