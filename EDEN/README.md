# EDEN

## Description

EDEN is an implementation of the cryptographic AES (Advanced Encryption Standard) algorithm. It allows for encrypting and decrypting text using various AES key lengths. Currently, it supports only 128-bit keys. The encryption function create chunks of text of the required length and add padding automatically if needed.

### Example Usage

1. Create an instance of the `EDEN` class by providing the desired AES key length and key.
2. Use the `EncryptText` method to encrypt the text.
3. Use the `DecryptText` method to decrypt the encrypted text.

```cpp
#include "EDEN.h"
#include <iostream>

int main() {
    // Creating key that have minimum 16 elemetns
    std::vector<unsigned char> key = {
    1, 2, 3, 4, 5, 6, 7,8,9,10,11,12,13,14,15,16
    };

    // Creating an instance of the EDEN class with a 128-bit key
    EDEN eden(AESKeyLength::AES_128,key);
    
    // Text to encrypt
    std::string plaintext = "Hello, world!";

    // Encrypting the text
    std::vector<std::vector<unsigned char>> encrypted = eden.EncryptText(plaintext);
    // Get encrypted text as string
    std::string string_encrypted = eden.GetEncryptedTextAsString(encrypted);

    // Decrypting the text
    std::vector<unsigned char>decrpyted = eden.DecryptText(encrypted);
    // Get decrypted text as string
    std::string string_decrypted = eden.GetDecryptedTextAsString(decrpyted);

    // Remove padding from decrypted string
    std::string string_decrpyted_without_padding = eden.RemovePaddingFromString(string_decrypted);

    std::cout << "Original text: " << plaintext << std::endl;
    std::cout << "Encrypted text: " << plaintext << std::endl;
    std::cout << "Decrypted text: " << string_decrypted << std::endl;
    std::cout << "Decrypted text without padding: " << string_decrpyted_without_padding << std::endl;

    return 0;
}
```
## IMPORTANT NOTES
 The project utilizes the AES library available at https://github.com/SergeyBel/AES.
 The AES.h file contains the implementation of the AES algorithm, which is used in this application for encrypting and decrypting text.
    
    
## Contributing

Contributions to enhance functionality or fix issues are welcome! Feel free to fork this repository, make changes, and submit a pull request.
## License
This code is provided under the MIT License. Feel free to use, modify, and distribute the code.