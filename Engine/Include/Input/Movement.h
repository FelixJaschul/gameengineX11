#pragma once

namespace Engine::Input
{
    class Movement
    {
        public:
        explicit Movement();
        ~Movement() = default;

        void Right() const;
        void Left() const;

        void Up() const;
        void Down() const;

        private:
        int m_speed;
    };
}