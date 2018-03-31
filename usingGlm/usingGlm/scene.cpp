#include "scene.h"
#include "ggl.h"
#include "utils.h"

GLuint vbo;
GLuint program;
GLuint positionLocation, modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation;
glm::mat4 modelMatrix, viewMatrix, projectionMatrix;
glm::vec3 cameraPos(10.0f, 10.0f, 10.0f);

void Init() 
{
	float data[] = 
	{
		-0.2f, -0.2f, -0.6f, 1.0f,
		0.2f, -0.2f, -0.6f, 1.0f,
		0.0f, 0.2f, -0.6f, 1.0f,
	};
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	int fileSize = 0;
	GLuint vsShader = CompileShader(GL_VERTEX_SHADER, "Res/test.vs");
	GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, "Res/test.fs");
	program = CreateProgram(vsShader, fsShader);
	glDeleteShader(vsShader);
	glDeleteShader(fsShader);
	positionLocation = glGetAttribLocation(program, "position");
	modelMatrixLocation = glGetUniformLocation(program, "ModelMatrix");
	viewMatrixLocation = glGetUniformLocation(program, "ViewMatrix");
	projectionMatrixLocation = glGetUniformLocation(program, "ProjectionMatrix");
	viewMatrix = glm::mat4(1.0f); //glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -0.6f, 0.0f));
}

void SetViewPortSize(float width, float height) 
{
	projectionMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
	//projectionMatrix = glm::mat4(1.0f);;
}

void Draw() 
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(positionLocation);
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(0);
}