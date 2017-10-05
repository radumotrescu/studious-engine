#version 330 core
    in vec2 position;
	
	out vec4 pos;

    //in vec3 color;

    //out vec3 colorV;

    void main()
    {
        //colorV = color;
        gl_Position = vec4(position, 0.0, 1.0);
		pos=gl_Position;
    }