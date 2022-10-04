#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Functions definitions

typedef uint8_t BYTE;

#define BLOCK_SIZE 512

bool inputcheck(int argc);

bool isJPEG(BYTE *buffer, int *pjpegcounter);

bool isfirst(int *pjpegcounter);

char *get_filename(char *filename, int *pjpegcounter);

bool isWriting(int *pjpegcounter);


// Program to recover JPEG from erased SD card
// Part of the CS50 course
// Coded by Giulio Bracci

int main(int argc, char *argv[])
{
    inputcheck(argc);

    FILE *input_img = fopen(argv[1], "r");

    if (input_img == NULL)
    {
        printf("Invalid file\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];

    int jpegcounter = -1;

    int *pjpegcounter = &jpegcounter;

    char *filename = malloc(8 * (sizeof(char)));

    FILE *image_recovered = NULL;


    // Read 512 bytes into buffer
    while (fread(buffer, 1, BLOCK_SIZE, input_img) == BLOCK_SIZE)
    {

        // Check if the start of a new JPEG
        if (isJPEG(buffer, pjpegcounter) == true)
        {
            // If first JPEG
            if (isfirst(pjpegcounter) == true)
            {
                // Open the image and initialize the name counter
                image_recovered = fopen(get_filename(filename, pjpegcounter), "w");

                // Check for pointer  NULL
                if (image_recovered == NULL)
                {
                    printf("Error opening the file\n");
                }
                fwrite(buffer, 1, BLOCK_SIZE, image_recovered);


            }
            else
            {
                // Close previous JPEG
                if (fclose(image_recovered) != 0)
                {
                    printf("Can't close the image\n");
                }
                // Open new file and update filename
                image_recovered = fopen(get_filename(filename, pjpegcounter), "w");
                // Start writing
                fwrite(buffer, 1, BLOCK_SIZE, image_recovered);
            }

        }

        else if (image_recovered != NULL)
        {
            // Keep writing
            fwrite(buffer, 1, BLOCK_SIZE, image_recovered);
        }

    }

    free(filename);
    fclose(image_recovered);
    fclose(input_img);
    return 0;

}






bool inputcheck(int argc)
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return false;
    }
    return true;
}

bool isJPEG(BYTE *buffer, int *pjpegcounter)
{

    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
    {
        printf("JPEG found! \n");
        *pjpegcounter += 1;
        return true;
    }
    else
    {
        return false;
    }

}

bool isfirst(int *pjpegcounter)
{
    if (*pjpegcounter  <= 0)
    {
        printf("first JPEG found\n");
        return true;
    }
    else
    {
        return false;
    }

}

char *get_filename(char *filename, int *pjpegcounter)
{
    sprintf(filename, "%03i.jpg", *pjpegcounter);
    return filename;
}


bool isWriting(int *pjpegcounter)

{
    if (*pjpegcounter >= 0)
    {
        return true;
    }
    return false;
}









