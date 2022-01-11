#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <cstdlib>

//using namespace std;
using namespace sf;

class Memory
{

private:
    RectangleShape bc;
    float speed{ 500.f };

    Vector2f gridSize;
    Vector2i offset{ 436, 181 };

    RectangleShape selector;
    Vector2i selectorCoord;

    std::map<int, std::map<int, RectangleShape>> keyboard;
    std::vector<Vector2i> coords;

    std::vector<CircleShape> lights;

    int nbRow{ 4 };
    int nbColumn{ 4 };

    float timer{ 0.0f };
    float timerLight{ 0.0f };
    float keyTime{ 0.0f };
    float timerGood{ 0.0f };
    float timerWrong{ 0.0f };

    int nbRound{ 5 };
    int currentRound{ 1 };
    bool isOnGuessPart{ false };
    bool done{ false };
    int i{ 1 };
    int j{ 1 };
    bool isValid{ false };
    bool isWrong{ false };
    bool add{ true };
    bool place{ false };

    Vector2f direction;
    Vector2f normailizeDir;
    Vector2f velocity;

    bool isPlaced{ false };
    bool display{ false };

    SoundBuffer m_bufferComplete;
    Sound m_soundComplete;

    SoundBuffer m_bufferFail;
    Sound m_soundFail;

public:
    Memory();
    ~Memory() = default;

    virtual void Update(const float& _dt, RenderWindow& _window);
    virtual void Render(RenderWindow& _target);

    bool Get_Win() { return done; }
};

