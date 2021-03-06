//Header files
#include <iostream>

//header for SDL2 functionality
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


	//Switch to ModelView
	glMatrixMode(GL_MODELVIEW);
	//Reset using Identity Matrix
	glLoadIdentity();
	//Translate to -5.0f on z-axis
	glTranslatef(0.0f, 0.0f, -5.0f);
	//Begin drawing triangles
	glBegin(GL_TRIANGLES);
	/*glColor3f(1.0f, 0.0f, 0.0f);  //Colour the vertices
	glVertex3f(0.1f, 1.0f, 0.0f);  //Top
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.1f, -1.0f, 0.0f);  //Bottom Left
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.1f, -1.0f, 0.0f);  //Bottom Right


	glColor3f(1.0f, 0.0f, 0.0f);  //Colour the vertices
	glVertex3f(-0.1f, 1.0f, 0.0f);  //Top
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.1f, -1.0f, 0.0f);  //Bottom Left
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.1f, -1.0f, 0.0f);  //Bottom Right
	*/

	glColor3f(1.0f, 0.0f, 0.0f);  //Colour the vertices
	glVertex3f(triangle1vertex1PosX, triangle1vertex1PosY, triangle1vertex1PosZ);  //Top
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(triangle1vertex2PosX, triangle1vertex2PosY, triangle1vertex2PosZ);  //Bottom Left
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(triangle1vertex3PosX, triangle1vertex3PosY, triangle1vertex3PosZ);  //Bottom Right


	glColor3f(1.0f, 0.0f, 0.0f);  //Colour the vertices
	glVertex3f(triangle2vertex1PosX, triangle2vertex1PosY, triangle2vertex1PosZ);  //Top
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(triangle2vertex2PosX, triangle2vertex2PosY, triangle2vertex2PosZ);  //Bottom Left
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(triangle2vertex3PosX, triangle2vertex3PosY, triangle2vertex3PosZ);  //Bottom Right

	glEnd();
	
	//required to swap the front and back buffer
	SDL_GL_SwapWindow(window);
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



