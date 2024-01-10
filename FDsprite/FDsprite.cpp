#include<SFML/Graphics.hpp>
#include <iostream>

class Tick{
private:
    sf::Clock T_clock;
    const int T_cylce;
public:
    Tick(const int cylce) : T_cylce(cylce) {};
    int get_tick() { return T_clock.getElapsedTime().asMilliseconds(); }
    void tick_restart_after_cycle() { if (T_clock.getElapsedTime().asMilliseconds() >= T_cylce) { T_clock.restart(); } }
};

class FDsprite{
private:
    sf::Texture backgroundTexture[256];
    int FD_number_of_sprites = 0;


    int FD_change_sprite_idle_from = 0;
    int FD_change_sprite_idle_to = 0;
    int FD_change_sprite_idle_current = 0;

public:
    sf::Sprite sprite[256];
    int FD_sprite_index = 0;

    void Load(std::string sprite_table[],int number_of_sprites) {
        FD_number_of_sprites = number_of_sprites;
        std::vector<sf::Sprite> sprite_buffer;

        for (int i = 0; i < FD_number_of_sprites; ++i) {
            if (!backgroundTexture[i].loadFromFile(sprite_table[i])) {
                std::cout << "ERROR WHILE LOADING FDSPRITE" << std::endl;
                return;
            }
            sprite[i].setTexture(backgroundTexture[i]);
        }
    }

    void change_sprite_between(int from,int to,int cycle,Tick& tick) {
        if (tick.get_tick() >= cycle) {
            FD_change_sprite_idle_from = from;
            FD_change_sprite_idle_to = to;
          

            if (FD_change_sprite_idle_current != FD_change_sprite_idle_to && FD_change_sprite_idle_current >= FD_change_sprite_idle_from)
                FD_change_sprite_idle_current++;
            else
                FD_change_sprite_idle_current = FD_change_sprite_idle_from;


            FD_sprite_index = FD_change_sprite_idle_current;


            tick.tick_restart_after_cycle();


            if (FD_change_sprite_idle_current > FD_change_sprite_idle_to)
                FD_change_sprite_idle_current = FD_change_sprite_idle_from;

        }
    }

    void set_pos(float x, float y, int direction = 0) {
        for (int i = 0; i < FD_number_of_sprites; i++) {
            sprite[i].setPosition(x, y);
        }
        FD_sprite_index = direction;
    }

    void change_sprite_between_while_set_pos(int from,int to,int cycle,Tick& tick,float x, float y, int direction = 0) {
        set_pos(x, y, direction);
        if (FD_change_sprite_idle_from != from) {
            cycle = 0;
            change_sprite_between(from, to, cycle, tick);
        }
        else {
            change_sprite_between(from, to, cycle, tick);
        }
        FD_sprite_index = FD_change_sprite_idle_current;
    }

    sf::Vector2f get_curr_pos() {
        return sprite[0].getPosition();
    }
};