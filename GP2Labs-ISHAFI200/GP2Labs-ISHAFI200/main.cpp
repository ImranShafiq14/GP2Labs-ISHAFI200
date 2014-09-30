//Header files
#include <iostream>
#include "Vertex.h"

//header for SDL2 functionality
#include <gl\glew.h>
#include <SDL.h>

#include <SDL_opengl.h>
#include <gl\GLU.h>

//Global variables go here 
//Pointer to our SDL Windows
SDL_Window * window;
//SDL GL Context
SDL_GLContext glcontext = NULL;

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

Vertex triangleData[] = { { 0.0f, 1.0f, 0.0f, //x,y,x
						1.0f, 0.0f, 0.0f, 1.0f }, //r,g,b,a

						{ -1.0f, -1.0f, 0.0f, //x,y,z
						0.0f, 1.0f, 0.0f, 1.0f }, //r,g,b,a

						{ 1.0f, -1.0f, 0.0f, //x,y,x
						0.0f, 0.0f, 1.0f, 1.0f } }; //r,g,b,a




GLuint triangleVBO;


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
	glDeleteBuffers(1, &triangleVBO);
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Function to initialise OpenGL
void initOpenGL()
{
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


	//Chnage to project matrix mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Calculate perspective matrix, using glu library functions
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

//Switch to ModelView
glMatrixMode(GL_MODELVIEW);

//Reset using the Identity Matrix
glLoadIdentity();
}

//Function to draw
void render()
{
	//Set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	/*
	//Make the new VBO active. Repeat here as a sanity check (may have changed since initialisation)
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//Establish its 3 coordinates per vertex with zero stride (space between elements) in array and contain floating point numbers
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	//Establish array contains vertices (not normals, colours, texture coords etc)
	glEnableClientState(GL_VERTEX_ARRAY);
	*/


	//Make the new VBO active. Repeat here as a sanity check (may have changed since initialisation)
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//the 3 parameter is now filled out, the pipeline needs to know the size of each vertex 
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);
	//The last parameter basically says that the colours start 3 floats into each element of the array
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (void**)(3 * sizeof(float)));

	//Establish array contains vertices & colours
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(triangleData) / sizeof(Vertex));


	//Make the new VBO active. Repeat here as a sanity check (may have changed since initialisation)
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//the 3 parameter is now filled out, the pipeline needs to know the size of each vertex 
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);
	//The last parameter basically says that the colours start 3 floats into each element of the array
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (void**)(3 * sizeof(float)));

	//Establish array contains vertices & colours
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(triangleData) / sizeof(Vertex));



	/*
	//Make the new VBO active. Repeat here as a sanity check (may have changed since initialisation)
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//Establish its 3 coordinates per vertex with zero stride (space between elements) in array and contain floating point numbers
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	//Establish array contains vertices (not normals, colours, texture coords etc)
	glEnableClientState(GL_VERTEX_ARRAY);
	*/


	//Switch to ModelView
	glMatrixMode(GL_MODELVIEW);
	//Reset using Identity Matrix
	glLoadIdentity();
	//Translate to -6.0f on z-axis
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0f, 0.0, 1.0, 0.0);
	glTranslatef(1.1f, 0.0f, -6.0f);
	//Actually draw the triangle, giving the number of vertices provided
	glDrawArrays(GL_TRIANGLES, 0, sizeof(triangleData) / (3 * sizeof(float)));
	
	//Reset using Identity Matrix
	glLoadIdentity();
	//Translate to -6.0f on z-axis
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0f, 0.0, 1.0, 0.0);
	glTranslatef(-1.1f, 0.0f, -6.0f);
	//Actually draw the triangle, giving the number of vertices provided
	glDrawArrays(GL_TRIANGLES, 0, sizeof(triangleData) / (3 * sizeof(float)));


	//required to swap the front and back buffer
	SDL_GL_SwapWindow(window);
}


void initGeometry()
{
	//Create buffer
	glGenBuffers(1, &triangleVBO);
	//Make the new VBO active
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//Copy Vertex Data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);
}

//Function to update game state
void update()
{

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
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);

	//Call our InitOpenGL Function
	initOpenGL();
	//Call our initGeometry Function
	initGeometry();
	//Set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);

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



