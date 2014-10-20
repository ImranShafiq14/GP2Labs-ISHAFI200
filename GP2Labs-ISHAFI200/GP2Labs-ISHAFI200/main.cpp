//Header files
#include <iostream>
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"

//header for SDL2 functionality
#include <gl\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include <SDL_ttf.h>

//maths headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef _DEBUG && WIN32
const std::string ASSET_PATH = "assets";
#else
const std::string ASSET_PATH = "assets";
#endif

const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";
const std::string FONT_PATH = "/fonts";

//Global variables go here 
//Pointer to our SDL Windows
SDL_Window * window;
//SDL GL Context
SDL_GLContext glcontext = NULL;

GLuint shaderProgram = 0;

//matrices
mat4 viewMatrix;
mat4 projMatrix;
mat4 worldMatrix;

//Triangle 1 Vetex positions
//Triangle 1 Vertex 1
float triangle1vertex1PosX = 0.1f;
float triangle1vertex1PosY = 1.0f;
float triangle1vertex1PosZ = 0.0f;
//Triangle 1 Vertex 2 
float triangle1vertex2PosX = 0.1f;
float triangle1vertex2PosY = -1.0f;
float triangle1vertex2PosZ = 0.0f;
//Triangle 1 Vertex 3
float triangle1vertex3PosX = 1.1f;
float triangle1vertex3PosY = -1.0f;
float triangle1vertex3PosZ = 0.0f;

//Triangle 2 Vetex positions
//Triangle 2 Vertex 1
float triangle2vertex1PosX = -0.1f;
float triangle2vertex1PosY = 1.0f;
float triangle2vertex1PosZ = 0.0f;
//Triangle 2 Vertex 2 
float triangle2vertex2PosX = -0.1f;
float triangle2vertex2PosY = -1.0f;
float triangle2vertex2PosZ = 0.0f;
//Triangle 2 Vertex 3
float triangle2vertex3PosX = -1.1f;
float triangle2vertex3PosY = -1.0f;
float triangle2vertex3PosZ = 0.0f;


//Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
bool running = true;

/*float triangleData[] = { 0.0f, 1.0f, 0.0f, // Top
-1.0f, -1.0f, 0.0f, // Bottom Left
1.0f, -1.0f, 0.0f }; //Bottom Right
*/

/*Vertex triangleData[] = { { 0.0f, 1.0f, 0.0f, //x,y,z
1.0f, 0.0f, 0.0f, 1.0f }, //r,g,b,a

{ -1.0f, -1.0f, 0.0f, //x,y,z
0.0f, 1.0f, 0.0f, 1.0f }, //r,g,b,a

{ 1.0f, -1.0f, 0.0f, //x,y,z
0.0f, 0.0f, 1.0f, 1.0f } }; //r,g,b,a
*/


Vertex triangleData[] = {
	//Front
		{ vec3(-0.5f, 0.5f, 0.5f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Left

		{ vec3(-0.5f, -0.5f, 0.5f), vec2(0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f) }, //Bottom Left

		{ vec3(0.5f, -0.5f, 0.5f), vec2(1.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right

		{ vec3(0.5f, 0.5f, 0.5f), vec2(1.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Right

		//Back
		{ vec3(-0.5f, 0.5f, -0.5f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Left

		{ vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f) }, //Bottom Left

		{ vec3(0.5f, -0.5f, -0.5f), vec2(1.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right

		{ vec3(0.5f, 0.5f, -0.5f), vec2(1.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Right

		//Left
		{ vec3(-0.5f, 0.5f, -0.5f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Left

		{ vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f) }, //Bottom Left

		{ vec3(-0.5f, -0.5f, 0.5f), vec2(1.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right

		{ vec3(-0.5f, 0.5f, 0.5f), vec2(1.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Right

		//Right
		{ vec3(0.5f, 0.5f, 0.5f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Left

		{ vec3(0.5f, -0.5f, 0.5f), vec2(0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f) }, //Bottom Left

		{ vec3(0.5f, -0.5f, -0.5f), vec2(1.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right

		{ vec3(0.5f, 0.5f, -0.5f), vec2(1.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Right

		//Top
		{ vec3(-0.5f, 0.5f, -0.5f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Left

		{ vec3(-0.5f, 0.5f, 0.5f), vec2(0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f) }, //Bottom Left

		{ vec3(0.5f, 0.5f, 0.5f), vec2(1.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right

		{ vec3(0.5f, 0.5f, -0.5f), vec2(1.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Right

		//Bottom
		{ vec3(-0.5f, -0.5f, 0.5f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Left

		{ vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f) }, //Bottom Left

		{ vec3(0.5f, -0.5f, -0.5f), vec2(1.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right

		{ vec3(0.5f, -0.5f, 0.5f), vec2(1.0f, 0.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) }, //Top Right
};

GLuint indices[] = {
	//Front
	0, 1, 2,
	0, 3, 2,

	//Left
	4, 5, 1,
	4, 1, 0,

	//Right
	3, 7, 2,
	7, 6, 2,

	//Bottom
	1, 5, 2,
	6, 2, 1,

	//Top
	5, 0, 7,
	5, 7, 3,

	//Back
	4, 5, 6,
	4, 7, 6
};


GLuint triangleVBO;
GLuint triangleEBO;
GLuint VAO;
GLuint texture = 0;
GLuint fontTexture = 0;

//Global functions
void InitWindow(int width, int height, bool fullscreen)
{
	//Create a window 
	window = SDL_CreateWindow("Lab 1",		//window title
		SDL_WINDOWPOS_CENTERED,		//x position, centered
		SDL_WINDOWPOS_CENTERED,		//y position, centered
		width,				//width, in pixels
		height,				//height, in pixels
		SDL_WINDOW_OPENGL		//flags
		);
}

//Used to cleanup once we exit
void CleanUp()
{
	glDeleteTextures(1, &fontTexture);
	glDeleteTextures(1, &texture);
	//glDeleteTextures(1, &fontTexture);
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &triangleEBO);
	glDeleteBuffers(1, &triangleVBO);
	glDeleteVertexArrays(1, &VAO);
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Function to initialise OpenGL
void initOpenGL()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Create OpenGL Context
	glcontext = SDL_GL_CreateContext(window);
	//Something went wrong in creating the context, if it is still NULL
	if (!glcontext)
	{
		std::cout << "Error Creating OpenGL Context" << SDL_GetError() << std::endl;
	}

	//Smooth shading
	glShadeModel(GL_SMOOTH);

	//clear the background to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Clear the depth buffer to 1.0
	glClearDepth(1.0f);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	//The depth test to use
	glDepthFunc(GL_LEQUAL);

	//Turn on best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/*Problem: glewInit failed, something is seriously wrong*/
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}
}

//Function to set/reset viewport
void setViewport(int width, int height)
{
	//screen ration
	GLfloat ratio;

	//make sure height is always above 0
	if (height == 0)
	{
		height = 1;
	}

	//calculate screen ration
	ratio = (GLfloat)width / (GLfloat)height;

	//Setup viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

//Function to draw
void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
	glBindVertexArray(VAO);

	glUseProgram(shaderProgram);
	GLint MVPLocation = glGetUniformLocation(shaderProgram, "MVP");
	mat4 MVP = projMatrix*viewMatrix*worldMatrix;
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));

	GLuint texture0Location = glGetUniformLocation(shaderProgram, "texture0");
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glUniform1i(texture0Location, 0);

	//Tell the shader that 0 is the position element
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)sizeof(vec3));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec2)));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	SDL_GL_SwapWindow(window);
}


void initGeometry()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Create buffer
	glGenBuffers(1, &triangleVBO);
	//Make the new VBO active
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//Copy Vertex Data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);


	//Create buffer
	glGenBuffers(1, &triangleEBO);
	//Make the new EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
	//Copy Index Data to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void initGeometryFromTexture(GLuint textureID)
{
	int width, height;

	glBindTexture(GL_TEXTURE_2D, textureID);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

	Vertex spriteData[] = {
			{ vec3(0.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) }, //Top Left

			{ vec3(0.0f, height, 0.0f), vec2(0.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Left

			{ vec3(width, height, 0.0f), vec2(1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right

			{ vec3(width, 0.0f, 0.0f), vec2(1.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) } //Top Right
	};

	GLuint spriteIndices[] = {
		0, 1, 2,
		0, 3, 2,
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &triangleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), spriteData, GL_STATIC_DRAW);

	glGenBuffers(1, &triangleEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), spriteIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)sizeof(vec3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec2)));
}

void createShader()
{
	GLuint vertexShaderProgram = 0;
	std::string vsPath = ASSET_PATH + SHADER_PATH + "/textureVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);

	GLuint fragmentShaderProgram = 0;
	std::string fsPath = ASSET_PATH + SHADER_PATH + "/textureFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);
	glLinkProgram(shaderProgram);
	checkForLinkErrors(shaderProgram);

	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);

	glBindAttribLocation(shaderProgram, 0, "vertexPosition");
	glBindAttribLocation(shaderProgram, 1, "vertexTexCoords");
	glBindAttribLocation(shaderProgram, 2, "vertexColour");
}

void createTexture()
{
	std::string texturePath = ASSET_PATH + TEXTURE_PATH + "/texture.png";
	texture = loadTextureFromFile(texturePath);
}

void createFontTexture()
{
	std::string fontPath = ASSET_PATH + FONT_PATH + "/OratorStd.otf";
	fontTexture = loadTextureFromFont(fontPath, 64, "Hello!");
}

//Function to update game state
void update()
{
	//projMatrix = glm::perspective(45.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	projMatrix = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, 0.1f, 100.0f);

	viewMatrix = glm::lookAt(vec3(0.0f, 0.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	
	worldMatrix = glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
}

//Main Method - Entry Point
int main(int argc, char * arg[])
{
	// init everything - SDL, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init" << SDL_GetError() << std::endl;
		return -1;
	}
	if (TTF_Init() == -1)
	{
		std::cout << "ERROR TFF_Init: " << TTF_GetError();
	}
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);

	//Call our InitOpenGL Function
	initOpenGL();
	//Call our initGeometry Function
	initGeometry();
	//Set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);

	createShader();
	createTexture();
	createFontTexture();
	initGeometryFromTexture(fontTexture);
	SDL_Event event;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			//Get event type
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
			{
				//set our boolean which controls the game loop to false
				running = false;
			}

			if (event.type == SDL_KEYDOWN)
			{
				//If left key is pressed, move both triangles to the left by a value of 0.1 using their X coordinates
				if (event.key.keysym.sym == SDLK_LEFT)
				{
					//Move triangle 1 vertices along X-axis
					triangle1vertex1PosX -= 0.1f;
					triangle1vertex2PosX -= 0.1f;
					triangle1vertex3PosX -= 0.1f;

					//Move triangle 2 vertices along X-axis
					triangle2vertex1PosX -= 0.1f;
					triangle2vertex2PosX -= 0.1f;
					triangle2vertex3PosX -= 0.1f;
				}

				//If right key is pressed, move both triangles to the right by a value of 0.1 using their X coordinates
				if (event.key.keysym.sym == SDLK_RIGHT)
				{
					//Move triangle 1 vertices along X-axis
					triangle1vertex1PosX += 0.1f;
					triangle1vertex2PosX += 0.1f;
					triangle1vertex3PosX += 0.1f;

					//Move triangle 2 vertices along X-axis
					triangle2vertex1PosX += 0.1f;
					triangle2vertex2PosX += 0.1f;
					triangle2vertex3PosX += 0.1f;
				}

				//If up key is pressed, move both triangles up by a value of 0.1 using their Y coordinates
				if (event.key.keysym.sym == SDLK_UP)
				{
					//Move triangle 1 vertices along Y-axis
					triangle1vertex1PosY += 0.1f;
					triangle1vertex2PosY += 0.1f;
					triangle1vertex3PosY += 0.1f;

					//Move triangle 2 vertices along Y-axis
					triangle2vertex1PosY += 0.1f;
					triangle2vertex2PosY += 0.1f;
					triangle2vertex3PosY += 0.1f;
				}

				//If down key is pressed, move both triangles down by a value of 0.1 using their Y coordinates
				if (event.key.keysym.sym == SDLK_DOWN)
				{
					//Move triangle 1 vertices along Y-axis
					triangle1vertex1PosY -= 0.1f;
					triangle1vertex2PosY -= 0.1f;
					triangle1vertex3PosY -= 0.1f;

					//Move triangle 2 vertices along Y-axis
					triangle2vertex1PosY -= 0.1f;
					triangle2vertex2PosY -= 0.1f;
					triangle2vertex3PosY -= 0.1f;
				}
			}
		}

		update();
		render();
	}

	CleanUp();
	return 0;
}





