# SFML FDsprite and Tick Classes

This project provides two classes, `Tick` and `FDsprite`, designed to facilitate handling ticks and managing sprites in SFML-based applications.

## Tick Class

The `Tick` class allows for easy management of time cycles.

### Usage

To create a `Tick` object, use the constructor:

```cpp
Tick myTick(cycle);
```

- `cycle`: an const integer representing the cycle duration in milliseconds.

#### Member Functions

- `int get_tick()`: Retrieves the current tick count in milliseconds.
- `void tick_restart_after_cycle()`: Restarts the tick timer after completing the specified cycle.

## FDsprite Class

The `FDsprite` class helps in loading and managing sprites.

### Usage

To use the `FDsprite` class, follow these steps:

1. Create an instance of `FDsprite`.
2. Load sprites using the `Load` method:

```cpp
FDsprite mySprites;
std::string spritePaths[] = { "sprite1.png", "sprite2.png", /*...*/ };
int numberOfSprites = /*...*/; // Number of sprites in the spritePaths array
mySprites.Load(spritePaths, numberOfSprites);
```

3. Manipulate sprites using member functions like `change_sprite_between` and `set_pos`.

#### Member Functions

- `void Load(std::string sprite_table[], int number_of_sprites)`: Loads sprites from the provided paths into the `FDsprite` object.
- `void change_sprite_between(int from, int to, int cycle, Tick& tick)`: Changes the sprite between specified indices based on a cycle duration managed by a `Tick` object.
- `void set_pos(float x, float y, int direction = 0)`: Sets the position of all sprites to the provided x and y coordinates, with an optional direction parameter.
- `sf::Vector2f get_curr_pos()`: Retrieves the current position of the first sprite.

## Example Usage

Here's an example demonstrating how to use these classes:

```cpp
// Create a Tick object with a cycle of 1000 milliseconds
Tick myTick(1000);

// Create an FDsprite object
FDsprite mySprites;

// Load sprite paths and specify the number of sprites
std::string spritePaths[] = { "sprite1.png", "sprite2.png", /*...*/ };
int numberOfSprites = /*...*/;
mySprites.Load(spritePaths, numberOfSprites);

// Manipulate sprites based on ticks
mySprites.change_sprite_between(0, 5, 500, myTick);
mySprites.set_pos(100.0f, 100.0f);
```

## Contributing

Contributions to enhance functionality or fix issues are welcome! Feel free to fork this repository, make changes, and submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.