#include "Window.h"

Window::Window() : window(nullptr), context(nullptr)
{
	window = nullptr;
	context = nullptr;
}

Window::~Window()
{
	OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to intialize SDL" << std::endl;
		return false;
	}

	this->width = width_;
	this->height = height_;

	SetPreAttributes();

	window = SDL_CreateWindow(name_.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL);
	if (!window) {
		std::cout << "Failed to create the window" << std::endl;
		return false;
	}

	context = SDL_GL_CreateContext(window);
	SetPostAttributes();

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "Failed to create GLEW" << std::endl;
		return false;
	}
	glEnable(GL_DEPTH_TEST);
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	return true;
}

void Window::OnDestroy()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::GetWidth() const
{
	return 0;
}

int Window::GetHeight() const
{
	return 0;
}

SDL_Window* Window::GetWindow() const
{
	// If nullptr is used, then it will only show a white color because it's set to false
	// If we return window instead, then it will allow me to access the glColors and change the color

	return window;
}

void Window::SetPreAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;
}

void Window::SetPostAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}
