#pragma once
#include "Player.hpp"
#include <stdio.h>

namespace HSM
{

    class Enemy
    {
	public:
		float ex, ex2, ey, ey2;
		float speed;

		Enemy()
		{
            ex = 1.0;
            ex2 = 0.85;
            ey = 0.10;
            ey2 = -0.10;
            speed = 1.0; 
		}
		~Enemy() {}
	};
}