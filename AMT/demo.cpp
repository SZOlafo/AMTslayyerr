#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

class demo {
public:

	void drawRectangle(GLfloat a, GLfloat b, GLfloat c, GLfloat d, GLfloat elevation) {

		GLfloat vertices[] =
		{
			a,	//lewy dolny róg
			b,	//prawy dolny róg
			c,	//lewy górny
			d	//prawy górny
		};

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4x4 proj = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(1920 / 1080), 0.1f, 100.0f);
	}
};

