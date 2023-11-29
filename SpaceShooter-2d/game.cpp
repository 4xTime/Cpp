#include "game.h"


void Player::LoadPlayerModel(const char* PATH) {
    if (!this->PlayerTexture.loadFromFile(PATH)) {
        return;
    }

    this->PlayerSprite.setTexture(this->PlayerTexture);

    sf::Vector2f newSize(50.f, 50.f);
    Player::SetNewScaleAndBounds(this->PlayerSprite, this->newPlayerBounds, newSize);

    sf::Vector2f newPos(this->PlayerSprite.getPosition().x / 2, RES_Y / 2);
    this->PlayerSprite.setPosition(newPos);


    sf::Vector2f FCurrPos(this->PlayerSprite.getPosition().x, this->PlayerSprite.getPosition().y);
    this->CurrPos = FCurrPos;
}

void game::SetNewScaleAndBounds(sf::Sprite& PlayerSprite, sf::FloatRect& newPlayerBounds, sf::Vector2f newSize) {
    PlayerSprite.setScale(newSize.x / PlayerSprite.getLocalBounds().width, newSize.y / PlayerSprite.getLocalBounds().height);


    newPlayerBounds = PlayerSprite.getGlobalBounds();
    newPlayerBounds.width += newSize.x / PlayerSprite.getLocalBounds().width;
    newPlayerBounds.height += newSize.y / PlayerSprite.getLocalBounds().height;
}


void Player::PlayerSpriteMove(sf::Vector2f& CurrPos, sf::Sprite& Sprite, sf::FloatRect& Bouds) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && CurrPos.x > 0) {
        CurrPos.x -= this->PlayerShipSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && CurrPos.x < RES_X - Bouds.width) {
        CurrPos.x += this->PlayerShipSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && CurrPos.y > 0) {
        CurrPos.y -= this->PlayerShipSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && CurrPos.y < RES_Y - Bouds.height) {
        CurrPos.y += this->PlayerShipSpeed;
    }
    Sprite.setPosition(CurrPos);
}
void game::LoadFireBallSprite() {
    if (!this->fireball_texture.loadFromFile("sprites\\player_fireball.png")) {
        return;
    }

    this->fireball_sprite.setTexture(fireball_texture);

    sf::Vector2f newSize(45.f, 45.f);
    game::SetNewScaleAndBounds(this->fireball_sprite, this->NewFireballBounds, newSize);
}
sf::Vector2f game::UpdateFireBallPos(sf::Vector2f CurrPos, sf::Sprite Sprite) {
    sf::Vector2f newPos = CurrPos;
    newPos.x += FireBallSpeed;
    if (newPos.x > RES_X - Sprite.getLocalBounds().width) {
        game::IsAlive = false;
    }
    return newPos;
}

sf::Vector2f Enemy::enemy_UpdateFireBallPos(sf::Vector2f CurrPos, sf::Sprite Sprite) {
    sf::Vector2f newPos = CurrPos;
    newPos.x -= game::FireBallSpeed;

    if (newPos.x < 0) {
        Enemy::Enemy_fireball_IsAlive = false;
    }
    return newPos;
}

void Enemy::LoadEnemyShip(const char* PATH) {
    if (!this->EnemyTexture.loadFromFile(PATH)) {
        return;
    }

    this->EnemySprite.setTexture(this->EnemyTexture);

    sf::Vector2f newSize(50.f, 50.f);
    game::SetNewScaleAndBounds(this->EnemySprite, this->newPlayerBounds, newSize);

    sf::Vector2f newPos(this->EnemySprite.getPosition().x + (RES_X - 50), RES_Y / 2);
    this->EnemySprite.setPosition(newPos);


    sf::Vector2f FCurrPos(this->EnemySprite.getPosition().x, this->EnemySprite.getPosition().y);
    this->CurrPos = FCurrPos;
}

int game::RNG(int from, int to) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomNumber = from + (std::rand() % (to - from + 1));
    return randomNumber;
}


float game::CalcDist(const Point& a, const Point& b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}

void game::UpdateScore() {
    game::text.setFont(game::font);
    game::text.setString(std::to_string(game::Score));
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setPosition(RES_X / 2, 0);
}

void Enemy::EnemyLoadFireBallSprite() {
    if (!this->enemy_fireball_texture.loadFromFile("sprites\\enemy_fireball.png")) {
        return;
    }

    this->enemy_fireball_sprite.setTexture(enemy_fireball_texture);

    sf::Vector2f newSize(45.f, 45.f);
    game::SetNewScaleAndBounds(this->enemy_fireball_sprite, this->EnemyNewFireballBounds, newSize);
}

void Enemy::EnemyAI(sf::Sprite Player, bool& reset, bool IsAlive, sf::Sprite PlayerFireball) {
    float X_POS = Enemy::EnemySprite.getPosition().x;
    float Y_POS = Enemy::EnemySprite.getPosition().y;

    float PlayerPosX = Player.getPosition().x;
    float PlayerPosY = Player.getPosition().y;

    //If the user starts the game for the first time, the opponent's position equals the player's position on the Y-axis,
    //meaning they stand opposite each other.
    if (game::gameIsAlive == false) { Y_POS = PlayerPosY; }
    game::gameIsAlive = true;

    // Stores player's and opponent's positions in a Point structure.
    Point PLAYER{ PlayerPosX,  PlayerPosY };
    Point SHIP{ X_POS, Y_POS };

    float dist = game::CalcDist(PLAYER, SHIP);

    if (IsAlive == true) {
        float PlayerFireballPosX = PlayerFireball.getPosition().x;
        float PlayerFireballPosY = PlayerFireball.getPosition().y;

        // Stores bullet's and opponent's positions in a Point structure.
        Point Fireball{ PlayerFireballPosX,PlayerFireballPosY };
        Point Enemy_ship_point{ X_POS,Y_POS };


        float dist_to_fireball = game::CalcDist(Fireball, Enemy_ship_point);

        //If the bullet is in front of the opponent, the AI decides whether to move up or down to avoid the bullet.
        if (PlayerFireballPosX < X_POS && dist_to_fireball < 100) {
            //up
            if (std::abs(Y_POS - 1) < std::abs(Y_POS - 600)) {
                Y_POS += game::EnemyShipBackToPosAndPanicSpeed + 0.10f;
            }
            // down
            else {
                Y_POS -= game::EnemyShipBackToPosAndPanicSpeed + 0.10f;
            }
        }
    }
    //To maintain the player's position on the Y-axis.
    if (Y_POS != PlayerPosY && IsAlive == false) {
        if (PlayerPosY > Y_POS) {
            Y_POS += game::EnemyShipBackToPosAndPanicSpeed;
        }
        if (PlayerPosY < Y_POS) {
            Y_POS -= game::EnemyShipBackToPosAndPanicSpeed;
        }
    }

    //Checks if the enemy ship is in a safe position; if so, the enemy moves forward.
    if (dist > SafeDist && bounce_effect == false) {
        X_POS -= Enemy::EnemyShipSpeed;
    }
    else {
        bounce_effect = true;
        X_POS += EnemyShipSpeed;
        if (dist > 550) { bounce_effect = false; }
    }
    if (X_POS > (RES_X - Enemy::EnemySprite.getGlobalBounds().width)) {
        SafeDist -= 10;
        X_POS -= EnemyShipSpeed + EnemyShipSpeed;
        bounce_effect = false;
    }
    if (X_POS + 50 < RES_X - Enemy::EnemySprite.getGlobalBounds().width) { SafeDist = 230; }
    Enemy::EnemySprite.setPosition(X_POS, Y_POS);

    Enemy::EnemyShootAction(Player, reset);
}

void Enemy::EnemyShootAction(sf::Sprite Player, bool& reset) {
    if (Enemy::Enemy_fireball_IsAlive == false) {
        Enemy::enemy_fireball_sprite.setPosition(Enemy::EnemySprite.getPosition().x, Enemy::EnemySprite.getPosition().y);
        Enemy::Enemy_fireball_IsAlive = true;
    }

    sf::Vector2f newPos = Enemy::enemy_UpdateFireBallPos(Enemy::enemy_fireball_sprite.getPosition(), Enemy::enemy_fireball_sprite);
    Enemy::enemy_fireball_sprite.setPosition(newPos);
    if (Enemy::enemy_fireball_sprite.getGlobalBounds().intersects(Player.getGlobalBounds()) && Enemy::Enemy_fireball_IsAlive == true) {
        Enemy::Enemy_fireball_IsAlive = false;
        Enemy::DrawSprite = false;
        reset = true;
    }
    else {
        Enemy::DrawSprite = true;
    }
}

void Player::ResetPlayerPos() {
    Player::CurrPos.x = 0;
    Player::CurrPos.y = RES_Y / 2;
}
void Enemy::ResetEnemyPos() { Enemy::EnemySprite.setPosition((RES_X - 50), RES_Y / 2); }

void game::ResetScore() { game::Score = 0; }