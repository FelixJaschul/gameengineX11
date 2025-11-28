#pragma once

namespace Engine::Input
{
    class Movement
    {
        public:
        Movement();
        ~Movement();

        void Forward();
        void Backward();
        void Right();
        void Left();

        void Up();
        void Down();

        void turnLeft();
        void turnRight();
        void turnUp();
        void turnDown();
    };
}