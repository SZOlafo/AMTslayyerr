

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
#include <barrier>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include"AntGrunt.h"
#include "Player.h"
#include "Sphere.h"
#include "Crosshair.h"





const unsigned int width = 1920;
const unsigned int height = 1080;

CustomMutex AntIDLEmtx;
CustomMutex projectileMtx;
std::barrier sync(5);

std::vector<AntGrunt> enemies;
std::vector<VAO> antsVAO;
std::vector<VBO> antsVBO;
std::vector<EBO> antsEbo;
CustomMutex spawnMtx;
int AID = 0;
int* globalAntId = &AID;
int SID = 0;
int* globalSID = &SID;
std::vector<Sphere> AntProjectiles;
glm::vec3 pos = { 0.0f, 20.0f, 0.0f };
bool firing = false;
int pistolCounter = -1;

//gracz
Player player(pos, AntIDLEmtx, enemies);
float playerHegiht = 25.0f;
float playerWidth = 20.0f;
int* playerHp = &player._hp;
float hpPercantage = float(player._hp);
glm::vec3 cameraPos = { -1000.0f,-1000.0f,-1000.0f };
glm::vec3 shotPos = { -1000.0f,-1000.0f,-1000.0f };



// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-100.0f, 0.0f,  100.0f,     0.5f, 0.5f, 0.5f,    0.0f, 1.0f, // Lewy g�rny
	-100.0f, 0.0f, -100.0f,     0.5f, 0.5f, 0.5f,    0.0f, 0.0f, // Lewy dolny
	 100.0f, 0.0f, -100.0f,     0.5f, 0.5f, 0.5f,    1.0f, 0.0f, // Prawy dolny
	 100.0f, 0.0f,  100.0f,     0.5f, 0.5f, 0.5f,    1.0f, 1.0f  // Prawy g�rny
	 /*-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	  0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	  0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	  0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f*/
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Pierwszy tr�jk�t
	0, 2, 3  // Drugi tr�jk�t
	/*0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4*/
};

// HP display
GLfloat hpVertices[] = {
	// Positions    // Texture Coords
	0.95f, -0.92f, 0.0f,
	0.95f, -0.95f, 0.0f,
	0.92f, -0.92f, 0.0f,
	0.92f, -0.95f, 0.0f
};
GLfloat pistolVertices[] =
{
	// Positions        // Texture Coords
	0.48f, -0.10f, 0.0f,  0.25f, 1.0f, // Top Right
	0.48f, -0.60f, 0.0f,  0.25f, 0.5f, // Bottom Right
	0.08f, -0.60f, 0.0f, 0.0f, 0.5f, // Bottom Left
	0.08f, -0.10f, 0.0f, 0.05f, 1.0f  // Top Left 
};
GLfloat pistolVerticesF0[] =
{
	// Positions        // Texture Coords
	0.40f, -0.10f, 0.0f,  0.5f, 1.0f,//0.25f, 1.0f, // Top Right
	0.40f, -0.60f, 0.0f,  0.5f, 0.5f,//0.25f, 0.5f, // Bottom Right
	0.00f, -0.60f, 0.0f, 0.25f, 0.5f,//0.0f, 0.5f, // Bottom Left
	0.00f, -0.10f, 0.0f, 0.25f, 1.0f//0.05f, 1.0f  // Top Left 
};
GLfloat pistolVerticesF1[] =
{
	// Positions        // Texture Coords
	0.40f, -0.10f, 0.0f,  0.75f, 1.0f,//0.25f, 1.0f, // Top Right
	0.40f, -0.60f, 0.0f,  0.75f, 0.5f,//0.25f, 0.5f, // Bottom Right
	0.00f, -0.60f, 0.0f, 0.5f, 0.5f,//0.0f, 0.5f, // Bottom Left
	0.00f, -0.10f, 0.0f, 0.5f, 1.0f//0.05f, 1.0f  // Top Left 
};
GLfloat pistolVerticesF2[] =
{
	// Positions        // Texture Coords
	0.40f, -0.10f, 0.0f,  1.0f, 1.0f,//0.25f, 1.0f, // Top Right
	0.40f, -0.60f, 0.0f,  1.0f, 0.5f,//0.25f, 0.5f, // Bottom Right
	0.00f, -0.60f, 0.0f, 0.75f, 0.5f,//0.0f, 0.5f, // Bottom Left
	0.00f, -0.10f, 0.0f, 0.75f, 1.0f//0.05f, 1.0f  // Top Left 
};
GLfloat crossHairVertices[] =
{
	// Positions        // Texture Coords
	0.05f, 0.05f, 0.0f,		1.0f, 1.0f,
	0.05f, -0.05f, 0.0f,	1.0f, 0.0f,
	-0.05f, -0.05f, 0.0f,	0.0f, 0.0f,
	-0.05f, 0.05f, 0.0f,	0.0f, 1.0f
};

GLuint pistolIndices[] =
{
	0, 1, 3, // First Triangle
	1, 2, 3  // Second Triangle
};



AntGrunt grunt1({ -99.0f,0.0f,99.0f }, AntIDLEmtx, enemies, globalAntId, player._position, AntProjectiles, globalSID, projectileMtx, playerWidth, playerHegiht, playerHp, antsVAO, antsVBO, antsEbo, spawnMtx,firing, cameraPos, shotPos, sync);
AntGrunt grunt2({ 99.0f,0.0f,99.0f }, AntIDLEmtx, enemies, globalAntId, player._position, AntProjectiles, globalSID, projectileMtx, playerWidth, playerHegiht, playerHp, antsVAO, antsVBO, antsEbo, spawnMtx,firing, cameraPos, shotPos, sync);
AntGrunt grunt3({ 99.0f,0.0f,-99.0f }, AntIDLEmtx, enemies, globalAntId, player._position, AntProjectiles, globalSID, projectileMtx, playerWidth, playerHegiht, playerHp, antsVAO, antsVBO, antsEbo, spawnMtx,firing, cameraPos, shotPos, sync);
AntGrunt grunt4({ -99.0f,0.0f,-99.0f }, AntIDLEmtx, enemies, globalAntId, player._position, AntProjectiles, globalSID, projectileMtx, playerWidth, playerHegiht, playerHp, antsVAO, antsVBO, antsEbo, spawnMtx,firing, cameraPos, shotPos, sync);

int main()
{
	std::cout << *globalAntId << std::endl;
	enemies.push_back(grunt1);
	enemies.push_back(grunt2);
	enemies.push_back(grunt3);
	enemies.push_back(grunt4);
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
	Shader pistolShader("pistol.vert", "pistol.frag");

	std::thread AntGrunt1Thread(std::bind(&AntGrunt::AntGruntLoop, &grunt1));
	std::thread AntGrunt2Thread(std::bind(&AntGrunt::AntGruntLoop, &grunt2));
	std::thread AntGrunt3Thread(std::bind(&AntGrunt::AntGruntLoop, &grunt3));
	std::thread AntGrunt4Thread(std::bind(&AntGrunt::AntGruntLoop, &grunt4));


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

	//grunt3
	VAO VAO4;
	VAO4.Bind();
	VBO VBO4(grunt3.coordinates, sizeof(grunt3.coordinates));
	EBO EBO4(grunt3._indices, sizeof(grunt3._indices));
	VAO4.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO4.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO4.LinkAttrib(VBO4, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO4.Unbind();
	VBO4.Unbind();
	EBO4.Unbind();
	//grunt 4
	VAO VAO5;
	VAO5.Bind();
	VBO VBO5(grunt4.coordinates, sizeof(grunt4.coordinates));
	EBO EBO5(grunt4._indices, sizeof(grunt4._indices));
	VAO5.LinkAttrib(VBO5, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO5.LinkAttrib(VBO5, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO5.LinkAttrib(VBO5, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO5.Unbind();
	VBO5.Unbind();
	EBO5.Unbind();
	VAO hpVAO;
	hpVAO.Bind();

	VBO hpVBO(hpVertices, sizeof(hpVertices));
	EBO hpEBO(indices, sizeof(indices));

	hpVAO.LinkAttrib(hpVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	hpVAO.LinkAttrib(hpVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	hpVAO.Unbind();
	hpVBO.Unbind();
	hpEBO.Unbind();
	// Texture

	Texture pistolTex("giwera.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	pistolTex.texUnit(shaderProgram, "texPistol", 0);
	Texture crosshairTex("crossH.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	crosshairTex.texUnit(shaderProgram, "texCross",0);

	// Original code from the tutorial
	Texture brickTex("floor_tex.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);
	// Generates Vertex Array Object and binds it for the pistol
	VAO VAOp;
	VAOp.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBOp(pistolVertices, sizeof(pistolVertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBOp(pistolIndices, sizeof(pistolIndices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAOp.LinkAttrib(VBOp, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VAOp.LinkAttrib(VBOp, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAOp.Unbind();
	VBOp.Unbind();
	EBOp.Unbind();

	// Generates Vertex Array Object and binds it for the pistol WHEN FIRING
	VAO VAOpf0;
	VAOpf0.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBOpf0(pistolVerticesF0, sizeof(pistolVerticesF0));
	// Generates Element Buffer Object and links it to indices
	EBO EBOpf0(pistolIndices, sizeof(pistolIndices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAOpf0.LinkAttrib(VBOpf0, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VAOpf0.LinkAttrib(VBOpf0, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAOpf0.Unbind();
	VBOpf0.Unbind();
	EBOpf0.Unbind();

	// frame 2
	VAO VAOpf1;
	VAOpf1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBOpf1(pistolVerticesF1, sizeof(pistolVerticesF1));
	// Generates Element Buffer Object and links it to indices
	EBO EBOpf1(pistolIndices, sizeof(pistolIndices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAOpf1.LinkAttrib(VBOpf1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VAOpf1.LinkAttrib(VBOpf1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAOpf1.Unbind();
	VBOpf1.Unbind();
	EBOpf1.Unbind();
	//frame 3
	VAO VAOpf2;
	VAOpf2.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBOpf2(pistolVerticesF2, sizeof(pistolVerticesF2));
	// Generates Element Buffer Object and links it to indices
	EBO EBOpf2(pistolIndices, sizeof(pistolIndices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAOpf2.LinkAttrib(VBOpf1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VAOpf2.LinkAttrib(VBOpf1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAOpf2.Unbind();
	VBOpf2.Unbind();
	EBOpf2.Unbind();

	//crosshair
	VAO VAOc;
	VAOc.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBOc(crossHairVertices, sizeof(crossHairVertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBOc(pistolIndices, sizeof(pistolIndices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAOc.LinkAttrib(VBOc, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VAOc.LinkAttrib(VBOc, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAOc.Unbind();
	VBOc.Unbind();
	EBOc.Unbind();

	Texture AntGruntTex("mruwa-czerwona.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	AntGruntTex.texUnit(shaderProgram, "tex1", 0);

	Texture AntGruntTex2("mruwa-czerwona.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	AntGruntTex.texUnit(shaderProgram, "tex2", 0);

	glm::vec3 initialPosition = glm::vec3(10.0f, 20.0f, 10.0f);
	glm::vec3 positionChange = glm::vec3(0.05f, 0.0f, 0.0f);
	Sphere sphere(initialPosition, positionChange, globalSID, AntProjectiles, player._position, playerWidth, playerHegiht, playerHp);
	AntProjectiles.push_back(sphere);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Creates camera object
	Camera camera(width, height, pos, player, firing);

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

		hpVAO.Bind();
		//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		hpVAO.Unbind();



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

		AntGruntTex.Bind();
		VBO4.Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(grunt3.coordinates), grunt3.coordinates);
		VBO4.Unbind();
		VAO4.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(grunt3._indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		VAO4.Unbind();
		AntGruntTex.Unbind();

		AntGruntTex.Bind();
		VBO5.Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(grunt4.coordinates), grunt4.coordinates);
		VBO5.Unbind();
		VAO5.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(grunt4._indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		VAO5.Unbind();
		AntGruntTex.Unbind();

		glm::mat4 orthoProjection = glm::ortho(-1.0f, 1.0f, -1.0f * height / width, 1.0f * height / width, -1.0f, 1.0f);
		// Draw the pistol sprite
		glDisable(GL_DEPTH_TEST); // Disable depth test to ensure pistol is always on top
		pistolShader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(pistolShader.ID, "orthoProjection"), 1, GL_FALSE, glm::value_ptr(orthoProjection));
		pistolTex.Bind();
		if (firing == false) {
			
		}
		else {
			
			shotPos = camera.getShotDirection();
			shotPos = glm::normalize(shotPos);
			cameraPos = camera.Position;
			pistolCounter = 0;
			firing = !firing;
			//std::cout << shotPos[0] << " " << shotPos[1] << " " << shotPos[2] << std::endl;
			/*for (int i = 0; i < enemies.size(); i++) {
				bool hit = enemies[i].shotCollision(camera.Position, shotPos);
				if (hit == true) {
					std::cout << "MELKA" << std::endl;
					enemies[i].shot();
					break;
				}
			}*/
		}
		switch (pistolCounter) {
		case 0:
			VAOpf0.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			VAOpf0.Unbind();
			pistolCounter++;
			break;
		case 1:
			VAOpf0.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			VAOpf0.Unbind();
			pistolCounter++;
			break;
		case 2:
			VAOpf0.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			VAOpf0.Unbind();
			pistolCounter++;
			break;
		case 3:
			VAOpf0.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			VAOpf0.Unbind();
			pistolCounter++;
			break;
		case 4:
			VAOpf0.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			VAOpf0.Unbind();
			pistolCounter++;
			break;
		case 5:
			VAOpf0.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			VAOpf0.Unbind();
			pistolCounter++;
			break;
		default:
			VAOp.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			VAOp.Unbind();
			break;
		}
		pistolTex.Unbind();
		crosshairTex.Bind();
		VAOc.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		VAOc.Unbind();
		crosshairTex.Unbind();

		
		
		glEnable(GL_DEPTH_TEST); // Re-enable depth test

		


		//Rendering spheres
		//sphereShader.Activate();
		for (int i = 0; i < AntProjectiles.size(); i++) {
			//AntProjectiles[i].draw();
		}
		//crosshair.render(crosshairShader);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
		//sync.arrive_and_wait();
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