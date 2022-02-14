/*=============================================================================
 |  Purpose: Encrypting a plaintext file using the Vignere Cipher algorithm.
 |
 |  Creator: Harry James Hocker
 |  Date: October 2, 2021
 |  Language: C
 |
 |  To Compile: gcc -o cipher cipher.c
 |
 |  To Execute: ./cipher kX.txt pX.txt
 |               where kX.txt is the key text file
 |               where pX.txt is the plaintext file
 |
 |  Note: All input files must be 8-bit ASCII format.
 |
 +=============================================================================*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 512
#define PAD 'x'
#define WIDTH 80

char key[MAX];
char plain[MAX];
char cipher[MAX];

// fill all arrays to the EMPTY value
void initializeArrays(void)
{
    for (int i = 0; i < MAX; i++) {
        key[i] = -1;
        plain[i] = PAD;
        cipher[i] = PAD;
    }
    return;
}

// find the length of any array
int getLength(char array[MAX])
{
    int i;
    for (i = 1; i <= MAX; i++) {
        if (array[i] == -1) return i;
    }
    return i;
}

// given the array input, format into a proper output
int checkInput(char* character)
{
    char c = *character;
    if (c >= 'a' && c <= 'z' ) {
        return 1;
    }
    else if (c >= 'A' && c <= 'Z') {
        *character += 32;
        return 1;
    }
    return 0;
}

// take file and return the array form of the file
void createFileArray(FILE* file, char* destination)
{
    char c; int i = 0;
    // while the file has content AND the interval is not out of bounds, add to index
    while ((c=fgetc(file)) != EOF && i < MAX) {
        if (checkInput(&c)) {
            destination[i] = c;
            i++;
        }
    }
}

// the standard encryption algorithm based on the Vigenere Cipher
void performEncryption(void)
{
    int keyIndex = 0;
    int index = 0;
    while (index < MAX) {
        if (key[keyIndex] == -1) keyIndex = 0;
        cipher[index] = ((key[keyIndex] + plain[index] - 194)%26) + 97;
        index++; keyIndex++;
    }
    return;
}

void printAll(int keyLength)
{
    printf("\n\n");
    printf("Vigenere Key:\n");
    for (int i = 0; i < keyLength; i++) {
        if (i % WIDTH == 0) printf("\n");
        printf("%c", key[i]);
    }
    printf("\n\n\n");
    printf("Plaintext:\n");
    for (int j = 0; j < MAX; j++) {
        if (j % WIDTH == 0) printf("\n");
        printf("%c", plain[j]);
    }
    printf("\n\n\n");
    printf("Ciphertext:\n");
    for (int k = 0; k < MAX; k++) {
        if (k % WIDTH == 0) printf("\n");
        printf("%c", cipher[k]);
    }
}

int main(int argc, const char * argv[])
{
    FILE* file;
    
    // make sure there are enough arguments else quit program
    if (argc < 2) {
        printf("NOT ENOUGH ARGUMENTS\n");
        return -1;
    }

    // make the global arrays full of padding
    initializeArrays();
    
    // read key from file into static array
    file = fopen(argv[1], "r");
    if (file == NULL) return -1;
    createFileArray(file, key);
    fclose(file);
    
    // read plaintext and store into static array
    file = fopen(argv[2], "r");
    if (file == NULL) return -1;
    createFileArray(file, plain);
    fclose(file);
    
    // find the length of the key
    int keyLength = getLength(key);
    
    // finally, do the math function here to encrypt the actual data
    performEncryption();
    
    // print out all the arrays
    printAll(keyLength);
    
    /*---------save the ciphertext to a text file---------
    file = fopen("output.txt", "w");
    for (int i = 0; i < MAX; i++) {
        if (i % WIDTH == 0 && i != 0) fprintf(file, "\n");
        fprintf(file, "%c", cipher[i]);
    }
    fclose(file);
    +----------------------------------------------------*/
    
    return 0;
}
