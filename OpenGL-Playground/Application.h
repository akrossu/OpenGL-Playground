#pragma once

struct GLFWwindow;

class Application {
public:
	Application(int width, int height);
	~Application();
	void run();

private:
	int width, height;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void initWindow();
	void initOpenGL();

	GLFWwindow* window = nullptr;
};