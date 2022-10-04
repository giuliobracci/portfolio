#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// This program enciphers a given string with a key like Caesar did

// Main function with an argument count and an array of strings
int main(int argc, string argv[])
{
    // Functions declarations
    void encript(string plaintext, int key);

    bool only_digits(string s);

    // argv[1] contains the string with the num key
    string s = argv[1];

    while (argc != 2 || only_digits(s) == false)
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }
    // Converting the key from char to int
    int key = atoi(argv[1]);

    // Getting the text to convert
    string plaintext = get_string("plaintext: ");

    // Encripting and outputting the text
    encript(plaintext, key);

}
// Checks is the arg are only digits
bool only_digits(string s)
{
    bool digits;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isdigit(s[i]))
        {
            digits = true;
        }
        else
        {
            digits = false;
        }
    }
    return digits;
}
// Function to print the encripted text
void encript(string plaintext, int key)
{
    char encripted;
    printf("ciphertext: ");

    for (int i = 0, lenght = strlen(plaintext); i < lenght; i++)
    {

        if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            encripted = (((plaintext[i] - 'a') + key) % 26) + 'a';
            printf("%c", encripted);
        }
        else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            encripted = (((plaintext[i] - 'A') + key) % 26) + 'A';
            printf("%c", encripted);
        }
        else
        {
            encripted = plaintext[i];
            printf("%c", encripted);
        }
    }
    printf("\n");

}
