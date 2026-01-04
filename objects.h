#pragma once


unsigned int triangleFaces[] = {
		0, 1, 2
};

float box1coords[] = {
	-8, -10, 10,
	-8, -8, 10,
	8, -10, 10,
	8, -8, 10,
	-8, -10, 15,
	-8, -8, 15,
	8, -10, 15,
	8, -8, 15,
};

float box2coords[] = {
	-2, 4, 12,
	-2, 8, 12,
	2, 4, 12,
	2, 8, 12,
	-2, 4, 16,
	-2, 8, 16,
	2, 4, 16,
	2, 8, 16
};

unsigned int boxFaces[] = {
	0, 1, 2,
	1, 2, 3,
	0, 1, 4,
	1, 4, 5,
	2, 3, 6,
	3, 6, 7,
	4, 5, 6,
	5, 6, 7,
	1, 3, 5,
	3, 5, 7,
	0, 2, 4,
	2, 4, 6
};

float rectangle1coords[] = {
	5, -5, 5,
	5, 5, 5,
	5, -5, 10,
	5, 5, 10
};

float rectangle2coords[] = {
	-5, -5, 5,
	-5, 5, 5,
	-5, -5, 10,
	-5, 5, 10
};

unsigned int rectangleFaces[] = {
	0, 1, 2,
	3, 2, 1
};


float verticesTest[] = {
	-0.5f, -0.5f, 1.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, -1.0f
};

/* leaving this here for now in case something breaks and I need it lol
unsigned int VAO;
glGenVertexArrays(1, &VAO);
glBindVertexArray(VAO);

unsigned int VBO;
glGenBuffers(1, &VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// GL_STREAM_DRAW (set once drawn few times)
// GL_STATIC_DRAW (set once drawn often - UI?)
// GL_DYNAMIC_DRAW (changed often drawn often)

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

glBindBuffer(GL_ARRAY_BUFFER, 0);
*/

/*
// setup shaders
unsigned int vertexShader, fragmentShader;
if (!load_compile_shader(GL_VERTEX_SHADER, "basic.vert", vertexShader)) { return 1; }
if (!load_compile_shader(GL_FRAGMENT_SHADER, "basic.frag", fragmentShader)) { return 1; }

// attach & link shader program
unsigned int shaderProgram;
if (!attach_link_program({ vertexShader, fragmentShader }, shaderProgram)) { return 1; }
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);

glUseProgram(shaderProgram);
*/

/*
float triangle1coords[] = {
	0, 0, 10,
	0, 2, 10,
	-2, 5, 10
};

float triangle2coords[] = {
	0, 0, 15,
	0, 2, 15,
	2, 2, 15
};
*/

