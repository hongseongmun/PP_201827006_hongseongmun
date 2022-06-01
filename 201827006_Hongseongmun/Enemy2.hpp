#pragma once
#include "Player.hpp"
#include <stdio.h>

namespace HSM
{
    class Enemy2
    {
    public:
        float ex_2 , ex2_2, ey_2, ey2_2;
        float speed2;

        Enemy2()
        {
            ex_2 = 1.0;
            ex2_2 = 0.85;
            ey_2 = 0.10;
            ey2_2 = -0.10;
            speed2 = 1.2;

        }
        ~Enemy2() {}
    };
}