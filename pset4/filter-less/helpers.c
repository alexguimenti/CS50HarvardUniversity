#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get average
            int average = 0;
            int dividend = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue);
            int divisor = 3;
            
            //change values
            average = (dividend + (divisor / 2)) / divisor;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][j].rgbtRed;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{   
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get new values
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;
            // sepa tones
            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            // round number
            sepiaRed += 0.5;
            sepiaGreen += 0.5;
            sepiaBlue += 0.5;
            
            // check number and substitte
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = (int)sepiaRed;
            }
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // make temp array
        int line0[width];
        int line1[width];
        int line2[width];
        for (int j = 0; j < width; j++)
        {
            // get values
            line0[j] = image[i][j].rgbtRed;
            line1[j] = image[i][j].rgbtGreen;
            line2[j] = image[i][j].rgbtBlue;
            //printf("%i\n\n", image[i][j].rgbtBlue);
        }
        
        // substitute 
        for (int j = 0; j < width; j++)
        {
            int c = width - 1;
            image[i][j].rgbtRed = line0[c - j];
            image[i][j].rgbtGreen = line1[c - j];
            image[i][j].rgbtBlue = line2[c - j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int temp = 0;
    int counter = 0;
    float sumRed;
    float sumGreen;
    float sumBlue;
    //make temp array
    RGBTRIPLE(*imageT)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    
    for (int i = 0; i < height; i++)
    {
        // get values
        for (int j = 0; j < width; j++)
        {
            counter = 1;
            sumRed = (float)image[i][j].rgbtRed;
            sumGreen = (float)image[i][j].rgbtGreen;
            sumBlue = (float)image[i][j].rgbtBlue;
            
            // check conditions of i and j
            if (i - 1 >= 0 && j - 1 >= 0 && i - 1 < height && j - 1 < width)
            {
                sumRed += image[i - 1][j - 1].rgbtRed;
                sumGreen += image[i - 1][j - 1].rgbtGreen;
                sumBlue += image[i - 1][j - 1].rgbtBlue;
                counter++;
            }
            if (i - 1 >= 0 && j >= 0 && i - 1 < height && j < width)
            {
                sumRed += image[i - 1][j].rgbtRed;
                sumGreen += image[i - 1][j].rgbtGreen;
                sumBlue += image[i - 1][j].rgbtBlue;
                counter++;
            }
            if (i - 1 >= 0 && j + 1 >= 0 && i - 1 < height && j + 1 < width)
            {
                sumRed += image[i - 1][j + 1].rgbtRed;
                sumGreen += image[i - 1][j + 1].rgbtGreen;
                sumBlue += image[i - 1][j + 1].rgbtBlue;
                counter++;
            }
            if (i >= 0 && j - 1 >= 0)
            {
                sumRed += image[i][j - 1].rgbtRed;
                sumGreen += image[i][j - 1].rgbtGreen;
                sumBlue += image[i][j - 1].rgbtBlue;
                counter++;
            }
            if (i >= 0 && j + 1 >= 0 && j + 1 < width)
            {
                sumRed += image[i][j + 1].rgbtRed;
                sumGreen += image[i][j + 1].rgbtGreen;
                sumBlue += image[i][j + 1].rgbtBlue;
                counter++;
            }
            if (i + 1 >= 0 && j - 1 >= 0 && i + 1 < height)
            {
                sumRed += image[i + 1][j - 1].rgbtRed;
                sumGreen += image[i + 1][j - 1].rgbtGreen;
                sumBlue += image[i + 1][j - 1].rgbtBlue;
                counter++;
            }
            if (i + 1 >= 0 && j >= 0 && i + 1 < height)
            {
                sumRed += image[i + 1][j].rgbtRed;
                sumGreen += image[i + 1][j].rgbtGreen;
                sumBlue += image[i + 1][j].rgbtBlue;
                counter++;
            }
            if (i + 1  >= 0 && j + 1 >= 0 && i + 1 < height && j + 1 < width)
            {
                sumRed += image[i + 1][j + 1].rgbtRed;
                sumGreen += image[i + 1][j + 1].rgbtGreen;
                sumBlue += image[i + 1][j + 1].rgbtBlue;
                counter++;
            }
            // check if is corner
            if (counter == 4)
            {
                imageT[i][j].rgbtRed = (sumRed / 4) + 0.5;
                imageT[i][j].rgbtGreen = (sumGreen / 4) + 0.5;
                imageT[i][j].rgbtBlue = (sumBlue  / 4) + 0.5;
            }
            // check if is edge
            if (counter == 6)
            {
                imageT[i][j].rgbtRed = (sumRed / 6) + 0.5;
                imageT[i][j].rgbtGreen = (sumGreen / 6) + 0.5;
                imageT[i][j].rgbtBlue = (sumBlue / 6) + 0.5;
            }
            // check if is middle
            if (counter == 9)
            {
                imageT[i][j].rgbtRed = (sumRed / 9) + 0.5;
                imageT[i][j].rgbtGreen = (sumGreen / 9) + 0.5;
                imageT[i][j].rgbtBlue = (sumBlue / 9) + 0.5;
            }
        }
    }
    // change values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageT[i][j];
        }
    }
    return;
}