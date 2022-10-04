#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// This program takes pieces from any book and rates the readability level based on the Coleman-Liau index

int main(void)
{
    // Functions declarations
    float count_letters(string text);
    float count_words(string text);
    float count_sentences(string text);
    int get_grade(float letters, float words, float sentences);

    // Prompts input for text sample
    string text = get_string("Text: \n");

    // Creates the variable grade using the get_grade function
    int grade = get_grade(count_letters(text), count_words(text), count_sentences(text));

    // Prints result
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}

// Count letters in the text
float count_letters(string text)
{
    float letters = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Checks if the char is alphabetical
        if (isalpha(text[i]))
        {
            letters++;
        }

    }
    return letters;
}

// Count the words in the text
float count_words(string text)

{
    float words = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isspace(text[i]))
        {
            words++;
        }

    }
    return words + 1;
}

// Count the sentences in the text
float count_sentences(string text)

{
    float sentences = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }
    return sentences;
}

// Apply the index formula
int get_grade(float letters, float words, float sentences)

{
    float L = (letters / words) * 100;
    float S = (sentences / words) * 100;
    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    int grade = round(index);
    return grade;
}




