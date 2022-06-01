#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Enemy2.hpp"

#pragma comment(lib, "OpenGL32")

using namespace std;

namespace HSM
{
	static GLuint texName[3];

	class GameLoop
	{
	private:
		bool gameReady= true;
		bool _isGameRunning = false;
		bool gameEnd = false;

		Player p;
		Enemy e;
		Enemy2 e2;
		GLFWwindow* window;

	public:
		typedef struct tagBITMAPHEADER {
			BITMAPFILEHEADER bf;
			BITMAPINFOHEADER bi;
			RGBQUAD hRGB[256];
		}BITMAPHEADER;

		GameLoop()
		{
			gameReady = true;
			_isGameRunning = false;
			gameEnd = false;
		}
		~GameLoop() {}

		BYTE* LoadBitmapFile(BITMAPHEADER* bitmapHeader, int* imgSize, const char* filename)
		{
			FILE* fp = fopen(filename, "rb");	//파일을 이진읽기모드로 열기
			if (fp == NULL)
			{
				printf("파일로딩에 실패했습니다.\n");	//fopen에 실패하면 NULL값을 리턴
				return NULL;
			}
			else
			{
				fread(&bitmapHeader->bf, sizeof(BITMAPFILEHEADER), 1, fp);	//비트맵파일헤더 읽기
				fread(&bitmapHeader->bi, sizeof(BITMAPINFOHEADER), 1, fp);	//비트맵인포헤더 읽기
				fread(&bitmapHeader->hRGB, sizeof(RGBQUAD), 256, fp);	//색상팔렛트 읽기

				int imgSizeTemp = bitmapHeader->bi.biWidth * bitmapHeader->bi.biHeight;	//이미지 사이즈 계산
				*imgSize = imgSizeTemp;	// 이미지 사이즈를 상위 변수에 할당

				BYTE* image = (BYTE*)malloc(sizeof(BYTE) * imgSizeTemp);	//이미지크기만큼 메모리할당
				fread(image, sizeof(BYTE), imgSizeTemp, fp);//이미지 크기만큼 파일에서 읽어오기
				fclose(fp);

				return image;
			}
		}

		void init(void)
		{
			glClearColor(0.211, 0.211, 0.211, 0);

			BITMAPHEADER originalHeader;	//비트맵의 헤더부분을 파일에서 읽어 저장할 구조체
			int imgSize;

			//이미지의 크기를 저장할 변수
			BYTE* image = LoadBitmapFile(&originalHeader, &imgSize, "123.bmp");

			BYTE* image1 = LoadBitmapFile(&originalHeader, &imgSize, "sij2.bmp");

			BYTE* image2 = LoadBitmapFile(&originalHeader, &imgSize, "11.bmp");

			BYTE* image3 = LoadBitmapFile(&originalHeader, &imgSize, "GameStart.bmp");

			//비트맵파일을 읽어 화소정보를 저장
			if (image == NULL) return;        //파일 읽기에 실패하면 프로그램 종료

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			glGenTextures(4, texName);
			glBindTexture(GL_TEXTURE_2D, texName[0]);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 920, 920, 0, GL_ALPHA, GL_BYTE, image);

			glBindTexture(GL_TEXTURE_2D, texName[1]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 920, 842, 0, GL_ALPHA, GL_BYTE, image1);

			glBindTexture(GL_TEXTURE_2D, texName[2]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 502, 303, 0, GL_ALPHA, GL_BYTE, image2);

		}

		static void error_callback(int error, const char* description)
		{
			fputs(description, stderr);
		}
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(window, GL_TRUE);
		}

		void Run() 
		{
			glfwSetErrorCallback(error_callback);
			if (!glfwInit())
				exit(EXIT_FAILURE);
			window = glfwCreateWindow(1280, 720, "Simple example", NULL, NULL);
			if (!window)
			{
				glfwTerminate();
				exit(EXIT_FAILURE);
			}

			glfwMakeContextCurrent(window);
			glfwSetKeyCallback(window, key_callback);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			init();

			
			
				while (!glfwWindowShouldClose(window))
				{

					Input();
					Update();
					Render();
				}
				glfwDestroyWindow(window);
				glfwTerminate();

				exit(EXIT_SUCCESS);
			
		}

		void Stop() {}

	private:
		void Input()
		{
			if (GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState(VK_SPACE) & 0x8001)
			{
				if (!_isGameRunning)
				{
					_isGameRunning = true;
					gameReady = false;
				}
				if(_isGameRunning)
				p.KeySpacePressedEvent();
			}

			if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8001)
			{
				if (_isGameRunning)
				p.KeyDwonArrowPressedEvent();
			}
			else
			{
				if (_isGameRunning)
				p.KeyDwonArrowUnpressedEvent();
			}
		}

		void Update() {
		
			if (_isGameRunning)
			{
			if (p.isjumping) {
				if (p.y < 0.715) {
					p.y += 0.04;
					p.y2 += 0.04;
				}
				else p.isjumping = false;
			}
			if (!p.isjumping) {
				if (p.y > 0.1) {
					p.y -= p.power;
					p.y2 -= p.power;
				}
			}
			if (p.y2 < -0.1)
			{
				p.y = 0.10;
				p.y2 = -0.10;
			}

			if (p.x <= e.ex && p.x2 >= e.ex2 && p.y >= e.ey2 && p.y2 <= e.ey)
			{
				printf("GameOver");
				_isGameRunning = false;
			}
			else if (e.ex >= -1.0) {
				e.ex -= 0.015f * e.speed;
				e.ex2 -= 0.015f * e.speed;
			}

			if (e.ex <= -1.0)
			{
				e.speed += 0.01;
				e.ex = 1.0;
				e.ex2 = 0.85;
			}

			if (p.x <= e2.ex_2 && p.x2 >= e2.ex2_2 && p.y >= e2.ey2_2 && p.y2 <= e2.ey_2)
			{
				printf("GameOver");
				_isGameRunning = false;
			}
			else if (e2.ex_2 >= -1.0) {
				e2.ex_2 -= 0.015f * e2.speed2;
				e2.ex2_2 -= 0.015f * e2.speed2;
			}

			if (e2.ex_2 <= -1.0)
			{
				e2.speed2 += 0.01;
				e2.ex_2 = 1.0;
				e2.ex2_2 = 0.85;
			}
		}
	}

		void Render()
		{
			if (gameReady)
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				glEnable(GL_TEXTURE_2D);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				glBindTexture(GL_TEXTURE_2D, texName[2]);

				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, 1.0);
				glTexCoord2f(1.0, 0.0); glVertex2f(-1.0, -1.0);
				glTexCoord2f(1.0, 1.0); glVertex2f(1.0, -1.0);
				glTexCoord2f(0.0, 1.0); glVertex2f(1.0, 1.0);
				glEnd();
			}
			if (!_isGameRunning && !gameReady)
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				glEnable(GL_TEXTURE_2D);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				glBindTexture(GL_TEXTURE_2D, texName[2]);

				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, 1.0);
				glTexCoord2f(0.0, 1.0); glVertex2f(-1.0, -1.0);
				glTexCoord2f(1.0, 1.0); glVertex2f(1.0, -1.0);
				glTexCoord2f(1.0, 0.0); glVertex2f(1.0, 1.0);
				glEnd();
			}


			if (_isGameRunning)
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				glEnable(GL_TEXTURE_2D);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				glBindTexture(GL_TEXTURE_2D, texName[0]);

				glBegin(GL_QUADS);
				glTexCoord2f(0.035, 0.0); glVertex3f(p.x, p.y2, 0.0);
				glTexCoord2f(0.55, 0.0); glVertex3f(p.x2, p.y2, 0.0);
				glTexCoord2f(0.55, 0.5); glVertex3f(p.x2, p.y, 0.0);
				glTexCoord2f(0.035, 0.5); glVertex3f(p.x, p.y, 0.0);

				glEnd();

				glEnable(GL_TEXTURE_2D);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				glBindTexture(GL_TEXTURE_2D, texName[1]);

				glBegin(GL_QUADS);
				glTexCoord2f(0.035, 0.0); glVertex3f(e.ex, e.ey2, 0.0);
				glTexCoord2f(0.55, 0.0); glVertex3f(e.ex2, e.ey2, 0.0);
				glTexCoord2f(0.55, 0.5); glVertex3f(e.ex2, e.ey, 0.0);
				glTexCoord2f(0.035, 0.5); glVertex3f(e.ex, e.ey, 0.0);
				glEnd();

				glEnable(GL_TEXTURE_2D);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				glBindTexture(GL_TEXTURE_2D, texName[1]);

				glBegin(GL_QUADS);
				glTexCoord2f(0.035, 0.0); glVertex3f(e2.ex_2, e2.ey2_2, 0.0);
				glTexCoord2f(0.55, 0.0); glVertex3f(e2.ex2_2, e2.ey2_2, 0.0);
				glTexCoord2f(0.55, 0.5); glVertex3f(e2.ex2_2, e2.ey_2, 0.0);
				glTexCoord2f(0.035, 0.5); glVertex3f(e2.ex_2, e2.ey_2, 0.0);

				glEnd();
			}
				glFlush();
				glDisable(GL_TEXTURE_2D);

				glfwSwapBuffers(window);
				glfwPollEvents();
			}
	};
}