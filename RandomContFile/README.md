# Random Content File Generator (RCF)

## Overview
The Random Content File Generator (RCF) is a C++ class designed to generate a file with unique random strings of specified length. The class prevents duplicate entries and includes a developer menu for debugging purposes.

## Features
- Generates a file with unique random strings of specified length.
- Option to display a developer menu for monitoring statistics and debugging.
- Automatically measures and outputs the time taken for the operation upon destruction.

## Usage

### Initialization
To use the `RandContFile` class, include the "RCF.h" header file and create an instance of the `RandContFile` class.

```cpp
#include "RCF.h"

// Example usage
const char* filePath = "output.txt";
uint32_t stringLength = 10;
uint32_t devMenuOn = 1;

RandContFile rcf(filePath, stringLength, devMenuOn);
```

### Destructor
The class automatically measures and outputs the time taken for the operation upon destruction.

```cpp
~RandContFile();
```

### Random Content Generation
The `RandContFile` class generates a file with unique random strings of a specified length.

```cpp
RandContFile::RandContFile(const char* PATH, uint32_t String_Length, uint32_t DevMenuOn = 1);
```

### Developer Menu
The `DEV_MENU` method provides a developer menu for monitoring statistics and debugging.

```cpp
void RandContFile::DEV_MENU(string& combination_send_to_file, double& number_of_remaining_possible_combinations, double& summary_combinations, uint64_t& number_of_new_words, uint64_t& number_of_words_skiped);
```

## Example

```cpp
#include "RCF.h"

int main() {
    const char* filePath = "output.txt";
    uint32_t stringLength = 10;
    uint32_t devMenuOn = 1;

    RandContFile rcf(filePath, stringLength, devMenuOn);

    return 0;
}
```

## License
This code is provided under the [MIT License](https://github.com/4xTime/Cpp/blob/main/LICENSE). Feel free to use, modify, and distribute the code.