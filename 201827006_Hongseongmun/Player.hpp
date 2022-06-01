#pragma once

namespace HSM
{
    class Player {
    public:
        float x, x2, y, y2;
        bool isjumping;
        float power;


        Player()
        {
            isjumping = false;
            power = 0.01;

            x = -0.8;
            x2 = -0.65;
            y = 0.10;
            y2 = -0.10;
        }
        ~Player() {}

        void KeySpacePressedEvent()
        {
            if (!isjumping && y <= 0.2)
                isjumping = true;
        }

        void KeyDwonArrowPressedEvent()
        {
            isjumping = false;
            power = 0.08;
        }

        void KeyDwonArrowUnpressedEvent()
        {
            power = 0.01;
        }

    };
}