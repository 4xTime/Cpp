#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>     
#include <cstdlib> 
#include <cmath>

#define RES_X 800
#define RES_Y 600

struct Point {
    float x;
    float y;
};

class game {
public:
    virtual void SpriteMove(sf::Vector2f CurrPos, sf::Sprite Sprite, sf::FloatRect Bouds) {};
    void LoadFireBallSprite();
    sf::Vector2f UpdateFireBallPos(sf::Vector2f CurrPos, sf::Sprite Sprite);
    sf::FloatRect NewFireballBounds;

    void UpdateScore();
    void ResetScore();

    sf::Texture fireball_texture;
    sf::Sprite fireball_sprite;
    sf::Text text;
    sf::Font font;

    bool IsAlive = false;
    int Score = 0;
protected:
    Point ScreenDistPoint{ RES_X,RES_Y };
    bool gameIsAlive = false;
    int RNG(int from, int to);
    float CalcDist(const Point& a, const Point& b);

    void SetNewScaleAndBounds(sf::Sprite& PlayerSprite, sf::FloatRect& newPlayerBounds, sf::Vector2f newSize);

    float EnemyShipBackToPosAndPanicSpeed = 0.05f;
    float PlayerShipSpeed = 0.05f;
    float FireBallSpeed = 0.10f;
};

class Player : public game {
public:
    sf::Sprite PlayerSprite;
    sf::Texture PlayerTexture;
    sf::Vector2f CurrPos;
    sf::FloatRect newPlayerBounds;

    void PlayerSpriteMove(sf::Vector2f& CurrPos, sf::Sprite& Sprite, sf::FloatRect& Bouds);
    void LoadPlayerModel(const char* PATH);
    void ResetPlayerPos();
};

class Enemy : public Player {
public:
    sf::Sprite EnemySprite;
    sf::Texture EnemyTexture;
    sf::Vector2f CurrPos;
    sf::FloatRect newPlayerBounds;

    sf::Texture enemy_fireball_texture;
    sf::Sprite enemy_fireball_sprite;
    sf::FloatRect EnemyNewFireballBounds;

    bool Enemy_fireball_IsAlive = false;
    float EnemyShipSpeed = 0.05f;
    bool DrawSprite = false;

    bool ReturnY = false;
    bool bounce_effect = false;
    int SafeDist = game::RNG(130, 230);

    sf::Vector2f enemy_UpdateFireBallPos(sf::Vector2f CurrPos, sf::Sprite Sprite);
    void EnemyAI(sf::Sprite Player, bool& reset, bool IsAlive, sf::Sprite PlayerFireball);
    void LoadEnemyShip(const char* PATH);
    void EnemyLoadFireBallSprite();
    void ResetEnemyPos();
    void EnemyShootAction(sf::Sprite Player, bool& reset);
};