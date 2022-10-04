#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int min = 255;

    // Iterating through all the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Averaging the RGB values
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;

    // Looping through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Multiply the value of each channel for the constant values to get the sepia filter

            sepiaRed = round((image[i][j].rgbtRed * 0.393) + (image[i][j].rgbtGreen * 0.769) + (image[i][j].rgbtBlue * 0.189));

            // Check if the value exceeds the 255 limit
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            sepiaGreen = round((image[i][j].rgbtRed * 0.349) + (image[i][j].rgbtGreen * 0.686) + (image[i][j].rgbtBlue * 0.168));

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            sepiaBlue = round((image[i][j].rgbtRed * 0.272) + (image[i][j].rgbtGreen * 0.534) + (image[i][j].rgbtBlue * 0.131));
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            // Apply the filter to the pixel
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;

        }

    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    int n = width / 2.0;
    RGBTRIPLE tmp[height][width];

    // Iterating through half of the image and exchanging the opposite pixels
    for (int i = 0; i < height; i++)
    {

        for (int j = 0, k = width - 1; j <= n - 1; j++, k--)
        {

            // The tmp image is used to copy the inverted pixels

            tmp[i][j].rgbtRed = image[i][k].rgbtRed;
            tmp[i][j].rgbtGreen = image[i][k].rgbtGreen;
            tmp[i][j].rgbtBlue = image[i][k].rgbtBlue;

            tmp[i][k].rgbtRed = image[i][j].rgbtRed;
            tmp[i][k].rgbtGreen = image[i][j].rgbtGreen;
            tmp[i][k].rgbtBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;

            image[i][k].rgbtRed = tmp[i][k].rgbtRed;
            image[i][k].rgbtGreen = tmp[i][k].rgbtGreen;
            image[i][k].rgbtBlue = tmp[i][k].rgbtBlue;


        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    float SumRed = 0.0;
    float SumGreen = 0.0;
    float SumBlue = 0.0;

    int r;
    int g;
    int b;

    int counter = 0;

    RGBTRIPLE copy_tmp[height][width];

    // Copy original image to temporary file for reading the pixel values
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            copy_tmp[row][column] = image[row][column];
        }
    }

    // Check each pixel
    for (int i = 0; i < height; i++)

    {
        for (int j = 0; j < width; j++)
        {
            // Iterate through each row and colomun behind and ahed the pixel
            for (int k = -1; k  < 2; k++)
            {

                for (int l = -1; l < 2; l++)
                {
                    // If out of borders continue the loop
                    if (k + i < 0 || k + i > height - 1 || l + j < 0 || l + j > width - 1)
                    {
                        continue;
                    }
                    // Sum of the RGB values
                    SumRed += copy_tmp[k + i][l + j].rgbtRed;
                    SumGreen += copy_tmp[k + i][l + j].rgbtGreen;
                    SumBlue += copy_tmp[k + i][l + j].rgbtBlue;
                    counter++;
                }

            }
            // Averaging the values
            r = round((SumRed / counter));
            g = round((SumGreen / counter));
            b = round((SumBlue / counter));

            // Assign the average values of the neighboring pixels
            image[i][j].rgbtRed = r;
            image[i][j].rgbtGreen = g;
            image[i][j].rgbtBlue = b;

            // Reset the counters
            counter = 0;
            SumRed = 0;
            SumGreen = 0;
            SumBlue = 0;

        }
    }


    return;
}



















