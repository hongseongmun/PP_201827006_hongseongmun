#define _CRT_SECURE_NO_WARNINGS

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "GameLoop.hpp"

#pragma comment(lib, "OpenGL32")

//static GLuint texName[2];
//
//float x = -0.8, x2 = -0.65, y = 0.10 , y2 = -0.10;
//float ex = 1.0, ex2 = 0.85, ey = 0.10, ey2 = -0.10;
//float ex_2 = 1.0, ex2_2 = 0.85, ey_2 = 0.10, ey2_2 = -0.10;
//
//bool isjumping = false;
//
//float power = 0.01, speed = 1;
//
//typedef struct tagBITMAPHEADER {
//    BITMAPFILEHEADER bf;
//    BITMAPINFOHEADER bi;
//    RGBQUAD hRGB[256];
//}BITMAPHEADER;
//
//void jumping() {
//    if (isjumping) {
//        if (y < 0.715) {
//            y += 0.04;
//            y2 += 0.04;
//        }
//        else isjumping = false;
//    }
//    if (!isjumping) {
//        if (y > 0.1) {
//            y -= power;
//            y2 -= power;
//        }
//    }
//    if (y2 < -0.1)
//    {
//        y = 0.10;
//        y2 = -0.10;
//    }
//}
//
//void Enemy2() {
//    
//    if (x <= ex_2 && x2 >= ex2_2 && y >= ey2_2 && y2 <= ey_2)
//    {
//        printf("11");
//    }
//    else if(ex_2 >= -1.0) {
//        ex_2 -= 0.02f * speed;
//            ex2_2 -= 0.02f * speed;
//    }
//    
//    if (ex_2 <= -1.0)
//    {
//        speed += 0.01;
//        ex_2 = 1.0;
//        ex2_2 = 0.85;
//    }
//    
//}
//
//void Enemy() {
//
//    if (x <= ex && x2 >= ex2 && y >= ey2 && y2 <= ey)
//    {
//        printf("11");
//    }
//    else if (ex >= -1.0) {
//        ex -= 0.015f * speed;
//        ex2 -= 0.015f * speed;
//    }
//
//    if (ex <= -1.0)
//    {
//        speed += 0.01;
//        ex = 1.0;
//        ex2 = 0.85;
//    }
//
//}
//
//BYTE* LoadBitmapFile(BITMAPHEADER* bitmapHeader, int* imgSize, const char* filename)
//{
//    FILE* fp = fopen(filename, "rb");	//������ �����б���� ����
//    if (fp == NULL)
//    {
//        printf("���Ϸε��� �����߽��ϴ�.\n");	//fopen�� �����ϸ� NULL���� ����
//        return NULL;
//    }
//    else
//    {
//        fread(&bitmapHeader->bf, sizeof(BITMAPFILEHEADER), 1, fp);	//��Ʈ��������� �б�
//        fread(&bitmapHeader->bi, sizeof(BITMAPINFOHEADER), 1, fp);	//��Ʈ��������� �б�
//        fread(&bitmapHeader->hRGB, sizeof(RGBQUAD), 256, fp);	//�����ȷ�Ʈ �б�
//
//        int imgSizeTemp = bitmapHeader->bi.biWidth * bitmapHeader->bi.biHeight;	//�̹��� ������ ���
//        *imgSize = imgSizeTemp;	// �̹��� ����� ���� ������ �Ҵ�
//
//        BYTE* image = (BYTE*)malloc(sizeof(BYTE) * imgSizeTemp);	//�̹���ũ�⸸ŭ �޸��Ҵ�
//        fread(image, sizeof(BYTE), imgSizeTemp, fp);//�̹��� ũ�⸸ŭ ���Ͽ��� �о����
//        fclose(fp);
//
//        return image;
//    }
//}
//
//
//void init(void)
//{
//    glClearColor(0.211, 0.211, 0.211, 0);
//
//    BITMAPHEADER originalHeader;	//��Ʈ���� ����κ��� ���Ͽ��� �о� ������ ����ü
//    int imgSize;
//
//    //�̹����� ũ�⸦ ������ ����
//    BYTE* image = LoadBitmapFile(&originalHeader, &imgSize, "123.bmp");
//
//    BYTE* image1 = LoadBitmapFile(&originalHeader, &imgSize, "sij2.bmp");
//
//
////��Ʈ�������� �о� ȭ�������� ����
//    if (image == NULL) return;        //���� �б⿡ �����ϸ� ���α׷� ����
//
//
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//    glGenTextures(2, texName);
//    glBindTexture(GL_TEXTURE_2D, texName[0]);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
//        GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//        GL_NEAREST);
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 920, 920, 0, GL_ALPHA, GL_BYTE, image);
//
//    glBindTexture(GL_TEXTURE_2D, texName[1]);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
//        GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//        GL_NEAREST);
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 920, 842, 0, GL_ALPHA, GL_BYTE, image1);
//
//}
//
//static void error_callback(int error, const char* description)
//{
//    fputs(description, stderr);
//}
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, GL_TRUE);
//    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
//        if(!isjumping && y <= 0.2) isjumping = true;
//    }
//    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
//        isjumping = false;
//        power = 0.08;
//    }
//    if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
//        power = 0.01;
//    }
//}

int main(void)
{
   HSM::GameLoop gLoop;
   gLoop.Run();
  //  GLFWwindow* window;
  //  glfwSetErrorCallback(error_callback);
  //  if (!glfwInit())
  //      exit(EXIT_FAILURE);
  //  window = glfwCreateWindow(720, 480, "Simple example", NULL, NULL);
  //  if (!window)
  //  {
  //      glfwTerminate();
  //      exit(EXIT_FAILURE);
  //  }

  //  glfwMakeContextCurrent(window);
  //  glfwSetKeyCallback(window, key_callback);

  //  glEnable(GL_BLEND);
  //  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //  init();

  //while (!glfwWindowShouldClose(window))
  //  {
  //      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //      glEnable(GL_TEXTURE_2D);
  //      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  //      glBindTexture(GL_TEXTURE_2D, texName[0]);

  //      glBegin(GL_QUADS);
  //      glTexCoord2f(0.035, 0.0); glVertex3f(x, y2, 0.0);
  //      glTexCoord2f(0.55, 0.0); glVertex3f(x2, y2, 0.0);
  //      glTexCoord2f(0.55, 0.5); glVertex3f(x2, y, 0.0);
  //      glTexCoord2f(0.035, 0.5); glVertex3f(x, y, 0.0);

  //      glEnd();

  //      glEnable(GL_TEXTURE_2D);
  //      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  //      glBindTexture(GL_TEXTURE_2D, texName[1]);

  //      glBegin(GL_QUADS);
  //      glTexCoord2f(0.035, 0.0); glVertex3f(ex, ey2, 0.0);
  //      glTexCoord2f(0.55, 0.0); glVertex3f(ex2, ey2, 0.0);
  //      glTexCoord2f(0.55, 0.5); glVertex3f(ex2, ey, 0.0);
  //      glTexCoord2f(0.035, 0.5); glVertex3f(ex, ey, 0.0);
  //      glEnd();

  //      glEnable(GL_TEXTURE_2D);
  //      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  //      glBindTexture(GL_TEXTURE_2D, texName[1]);

  //      glBegin(GL_QUADS);
  //      glTexCoord2f(0.035, 0.0); glVertex3f(ex_2, ey2_2, 0.0);
  //      glTexCoord2f(0.55, 0.0); glVertex3f(ex2_2, ey2_2, 0.0);
  //      glTexCoord2f(0.55, 0.5); glVertex3f(ex2_2, ey_2, 0.0);
  //      glTexCoord2f(0.035, 0.5); glVertex3f(ex_2, ey_2, 0.0);


  //      glEnd();
  //      jumping();
  //      Enemy();
  //      Enemy2();

  //      glFlush();
  //      glDisable(GL_TEXTURE_2D);

  //      glfwSwapBuffers(window);
  //      glfwPollEvents();
  //  }
  //  glfwDestroyWindow(window);
  //  glfwTerminate();

  //  exit(EXIT_SUCCESS);
}