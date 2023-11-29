#include<SFML/Graphics.hpp>
#include "game.h"

int main() {
    bool Reset = false;
    game GM;
    GM.LoadFireBallSprite();
    if (!GM.font.loadFromFile("C:\\Windows\\Fonts\\impact.ttf")) { return -1; }

    sf::RenderWindow GameWindow(sf::VideoMode(RES_X, RES_Y), "SpaceShooter.exe");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("sprites\\backgorund.jpg")) {
        return -1;
    }

    sf::Sprite backgorund;
    backgorund.setTexture(backgroundTexture);


    Player PL;
    PL.LoadPlayerModel("sprites\\player_ship.png");
    Enemy EN;
    EN.LoadEnemyShip("sprites\\enemy_ship.png");
    EN.EnemyLoadFireBallSprite();


    while (GameWindow.isOpen()) {
        sf::Event event;
        while (GameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                GameWindow.close();
            }
        }
        GameWindow.clear();
        GameWindow.draw(backgorund);

        PL.PlayerSpriteMove(PL.CurrPos, PL.PlayerSprite, PL.newPlayerBounds);

        GameWindow.draw(PL.PlayerSprite);
        GameWindow.draw(EN.EnemySprite);

        EN.EnemyAI(PL.PlayerSprite, Reset, GM.IsAlive, GM.fireball_sprite);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || GM.IsAlive == true) {
            if (GM.IsAlive == false) {
                GM.fireball_sprite.setPosition(PL.CurrPos.x, PL.CurrPos.y);
            }

            GM.IsAlive = true;
            sf::Vector2f newPos = GM.UpdateFireBallPos(GM.fireball_sprite.getPosition(), GM.fireball_sprite);
            GM.fireball_sprite.setPosition(newPos);

            if (GM.fireball_sprite.getGlobalBounds().intersects(EN.EnemySprite.getGlobalBounds()) && GM.IsAlive == true) {
                EN.EnemySprite.setPosition(RES_X - 50, RES_Y / 2);
                GM.IsAlive = false;
                GM.Score++;
            }
            else {
                GameWindow.draw(GM.fireball_sprite);
            }
        }
        if (EN.DrawSprite == true) { GameWindow.draw(EN.enemy_fireball_sprite); }
        if (Reset == true) {
            Reset = false;
            EN.ResetEnemyPos();
            PL.ResetPlayerPos();
            GM.ResetScore();
        }
        GM.UpdateScore();
        GameWindow.draw(GM.text);
        GameWindow.display();
    }
}