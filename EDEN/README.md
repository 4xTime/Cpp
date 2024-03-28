# EDEN

## Description
EDEN is an implementation of the cryptographic AES (Advanced Encryption Standard) algorithm. It allows for encrypting and decrypting text using various AES key lengths. It supports 128, 192, and 256-bit keys. The encryption function creates chunks of text of the required length and adds padding automatically if needed.

### Example Usage
1. Create an instance of the `EDEN` class by providing the desired AES key length, key, encryption/decryption type, and for CBC and CFB modes only, the initialization vector.
2. Use the `EncryptText` method to encrypt the text. Optionally, you can use `GetEncryptedTextAsString` to convert vector2UC to a string.
3. Use the `DecryptText` method to decrypt the encrypted text. Similarly to `EncryptText`, you can use `GetDecryptedTextAsString` to convert vectorUC to a string.

```cpp
#include "EDEN.h"
#include <iostream>

int main() {
    // Creating key that have 16 elemetns
    vectorUC key = {
        1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16
    };
    // Creating initialization vector that have 16 elemetns
    vectorUC iv = {
        1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16
    };

    // Creating an instance of the EDEN class
    EDEN eden(AESKeyLength::AES_128, key, edenType::CBC, iv);

    // Text to encrypt
    std::string plaintext = "Hello, world!";

    // Encrypting the text
    vector2UC Ecnrypted = eden.EncryptText(plaintext);
    // Get encrypted text as string
    std::string stringEncrypted = eden.GetEncryptedTextAsString(Ecnrypted);
    
    // Decrypting the text
    vectorUC Decrypted = eden.DecryptText(Ecnrypted);
    // Get decrypted text as string
    std::string stringDecrypted = eden.GetDecryptedTextAsString(Decrypted);
    
    // Remove padding from decrypted string
    std::string stringDecrpytedWithoutPadding = eden.RemovePaddingFromString(stringDecrypted);

    std::cout << "Original text: " << plaintext << std::endl;
    std::cout << "Encrypted text: " << stringEncrypted << std::endl;
    std::cout << "Decrypted text: " << stringDecrypted << std::endl;
    std::cout << "Decrypted text without padding: " << stringDecrpytedWithoutPadding << std::endl;

    return 0;
}
```
## IMPORTANT NOTES
 The project utilizes the AES library available at https://github.com/SergeyBel/AES.
 The AES.h and AES.cpp file contains the implementation of the AES algorithm, which is used in this application for encrypting and decrypting text.
 
## License
This code is provided under the MIT License. Feel free to use, modify, and distribute the code.