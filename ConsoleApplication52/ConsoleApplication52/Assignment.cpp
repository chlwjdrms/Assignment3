#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

const int width = 1000;
const int height = 480;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

// scratched from https://courses.engr.illinois.edu/ece390/archive/archive-f2000/mp/mp4/anti.html
// see 'Rasterization' part.
void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawColorRect(const int& i2, const int& j2, const int& i3, const int& j3, const float& red, const float& green, const float& blue) {
	for (int i = i2; i <= i3; i++) {
		for (int j = j2; j <= j3; j++) {
			drawPixel(i, j, red, green, blue);
		}
	}
}

void drawCircle(const int& i4, const int& j4, const int& i5, const int& j5, const float& red, const float& green, const float& blue) {
	for (int i = i4; i <= i5; i++) {
		for (int j = j4; j <= j5; j++) {
			int r = (i5 - i4) / 2;
			int a = (i - 375)*(i - 375) + (j - 375)*(j - 375);
			if (a <= r*r && a >= (r - 3)*(r - 3)) {
				drawPixel(i, j, red, green, blue);
			}
		}
	}
}

void drawRect(const int& i6, const int& j6, const int& i7, const int& j7, const float& red, const float& green, const float& blue) {
	for (int i = i6; i <= i7; i++) {
		for (int j = j6; j <= j7; j++) {
			if (!(i > i6 + 2 && i < i7 - 2 && j > j6 + 2 && j < j7 - 2)) {
				drawPixel(i, j, red, green, blue);
			}
		}
	}
}

void drawTriangle(const int& i8, const int& j8, const int& i9, const int& j9, const float& red, const float& green, const float& blue) {
	int j = j8;

	for (int i = i8; i <= i9; i++) {
		drawPixel(i, j8, red, green, blue); //¹Øº¯

		if (i <= i8 + ((i9-i8 )/ 2)){
			j+=2;
			drawPixel(i, j, red, green, blue);
		}
		else {
			j-=2;
			drawPixel(i, j, red, green, blue);
		}
	}
}

void drawPanta(const int& i10, const int& j10, const int& i11, const int& j11, const float& red, const float& green, const float& blue) {
	int centeri = (i11 + i10) / 2; 
	int centerj = (j11 + j10) / 2;

	for (int j = j10; j <= j11; j++) {
		if (j == j10){
			for (int i = i10 + (i11 - i10) / 4; i <= i10 + (i11 - i10) * 3 / 4; i++){
				drawPixel(i, j, red, green, blue);
			}
		}
		else if (j > j10 && j <= centerj){
			drawPixel(centeri + (i11 - i10) / 4 + (j - j10) * 1 / 2, j, red, green, blue);
			drawPixel(centeri - (i11 - i10) / 4 - (j - j10) * 1 / 2, j, red, green, blue);
		}
		else{
			drawPixel(i11 - (j - centerj), j, red, green, blue);
			drawPixel(i10 + (j - centerj), j, red, green, blue);
		}
	}
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	const int i0 = 50, i1 = 200;
	const int j0 = 50, j1 = 200;

	const int i2 = 50, i3 = 200;
	const int j2 = 300, j3 = 450;

	const int i4 = 300, i5 = 450;
	const int j4 = 300, j5 = 450;

	const int i6 = 300, i7 = 450;
	const int j6 = 50, j7 = 200;

	const int i8 = 550, i9 = 700;
	const int j8 = 50, j9 = 200;

	const int i10 = 550, i11 = 700;
	const int j10 = 300, j11 = 450;

	for (int i = -3; i < 3; i++) {
		drawLine(i0, j0 + i, i1, j1 + i, 1.0f, 0.0f, 0.0f);
	}

	drawColorRect(i2, j2, i3, j3, 1.0f, 0.0f, 0.0f);

	drawCircle(i4, j4, i5, j5, 1.0f, 0.0f, 0.0f);

	drawRect(i6, j6, i7, j7, 1.0f, 0.0f, 0.0f);

	drawTriangle(i8, j8, i9, j9, 1.0f, 0.0f, 0.0f);

	drawPanta(i10, j10, i11, j11, 1.0f, 0.0f, 0.0f);




	//TODO: try moving object
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  //»ï°¢Çü ÁÂÇ¥
	float vertices[] =
	{
		0.0, 0.5, 0.0, //top corner
		-0.5, -0.5, 0.0, //bottom left corner
		0.5, -0.5, 0.0 //bottom right corner
	};

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}