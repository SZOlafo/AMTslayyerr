

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<thread>
#include<functional>
#include<vector>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include"AntGrunt.h"






const unsigned int width = 1920;
const unsigned int height = 1080;
std::vector<AntGrunt> enemies;


// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-100.0f, 0.0f,  100.0f,     0.5f, 0.5f, 0.5f,    0.0f, 1.0f, // Lewy górny
	-100.0f, 0.0f, -100.0f,     0.5f, 0.5f, 0.5f,    0.0f, 0.0f, // Lewy dolny
	 100.0f, 0.0f, -100.0f,     0.5f, 0.5f, 0.5f,    1.0f, 0.0f, // Prawy dolny
	 100.0f, 0.0f,  100.0f,     0.5f, 0.5f, 0.5f,    1.0f, 1.0f  // Prawy górny
	 /*-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	  0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	  0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	  0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f*/
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Pierwszy trójk¹t
	0, 2, 3  // Drugi trójk¹t
	/*0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4*/
};
CustomMutex AntIDLEmtx;
AntGrunt grunt1({ 10.0f,0.0f,10.0f}, AntIDLEmtx, enemies);
AntGrunt grunt2({ 50.0f,0.0f,10.0f}, AntIDLEmtx,enemies);



int main()
{
	enemies.push_back(grunt1);
	enemies.push_back(grunt2);
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "AMT Slayer", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);


	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	std::thread AntGrunt1Thread(std::bind(&AntGrunt::AntGruntLoop, &grunt1));
	std::thread AntGrunt2Thread(std::bind(&AntGrunt::AntGruntLoop, &grunt2));
	

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	VAO VAO2;
	VAO2.Bind();
	VBO VBO2(grunt1.coordinates, sizeof(grunt1.coordinates));
	EBO EBO2(grunt1._indices, sizeof(grunt1._indices));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	VAO VAO3;
	VAO3.Bind();
	VBO VBO3(grunt2.coordinates, sizeof(grunt2.coordinates));
	EBO EBO3(grunt2._indices, sizeof(grunt2._indices));
	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();


	/*
	* I'm doing this relative path thing in order to centralize all the resources into one folder and not
	* duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
	* folder and then give a relative path from this folder to whatever resource you want to get to.
	* Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
	*/

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Texture
	

	// Original code from the tutorial
	Texture brickTex("floor_tex.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);

	Texture AntGruntTex("amt-dangerous-ant.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	AntGruntTex.texUnit(shaderProgram, "tex1", 0);

	Texture AntGruntTex2("mruwa-czerwona.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	AntGruntTex.texUnit(shaderProgram, "tex2", 0);



	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 50.0f, 0.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(120.0f, 0.1f, 1000.0f, shaderProgram, "camMatrix");

		// Binds texture so that is appears in rendering
		brickTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		VAO1.Unbind();
		brickTex.Unbind();

		AntGruntTex.Bind();
		VBO2.Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(grunt1.coordinates), grunt1.coordinates);
		VBO2.Unbind();

		VAO2.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(grunt1._indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		VAO2.Unbind();
		AntGruntTex.Unbind();

		AntGruntTex2.Bind();
		VBO3.Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(grunt2.coordinates), grunt2.coordinates);
		VBO3.Unbind();

		VAO3.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(grunt2._indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		VAO3.Unbind();
		AntGruntTex2.Unbind();
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
		
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}