#define _CRT_SECURE_NO_WARNINGS

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "GameLoop.hpp"

#pragma comment(lib, "OpenGL32")


int main(void)
{
   HSM::GameLoop gLoop;
   gLoop.Run();
}
