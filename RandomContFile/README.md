# Random Content File Generator (RCF)

## Overview
The Random Content File Generator (RCF) is a C++ class designed to generate a file with random strings of specified length. The class prevent duplicate entries and includes a developer menu for debugging purposes.

## Features
- Generates a file with random strings of specified length.
- Option to skip duplicate entries.
- Developer menu for debugging and monitoring statistics.

## Usage

### Initialization
To use the RCF class, include the "RCF.h" header file and create an instance of the `RandContFile` class.

```cpp
#include "RCF.h"

// Example usage
const char* filePath = "output.txt";
uint32_t wordsToGenerate = 100;
uint32_t stringLength = 10;
uint32_t devMenuOn = 1;

RandContFile rcf(filePath, wordsToGenerate, stringLength, devMenuOn);
```

### Destructor
The class automatically measures and outputs the time taken for the operation upon destruction.

```cpp
~RandContFile();
```

### Random String Generation
The `RSTR` method generates a random string of a specified length.

```cpp
string RandContFile::RSTR(int String_lenght);
```

### Developer Menu
The `DEV_MENU` method provides a developer menu for monitoring statistics and debugging.

```cpp
void RandContFile::DEV_MENU(string& FB, string& SB, uint64_t& SCO, uint64_t& NCO, uint64_t& SSCO);
```

## Example

```cpp
#include "RCF.h"

int main() {
    const char* filePath = "output.txt";
    uint32_t wordsToGenerate = 100;
    uint32_t stringLength = 10;
    uint32_t devMenuOn = 1;

    RandContFile rcf(filePath, wordsToGenerate, stringLength, devMenuOn);

    return 0;
}
```

## License
This code is provided under the [MIT License](https://github.com/4xTime/Cpp/blob/main/LICENSE). Feel free to use, modify, and distribute the code.