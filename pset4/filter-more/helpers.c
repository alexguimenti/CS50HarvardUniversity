#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // aux variables
    int sumRedX;
    int sumRedY;
    int sumGreenX;
    int sumGreenY;
    int sumBlueX;
    int sumBlueY;
    int counter;
    // temp array
    RGBTRIPLE(*imageT)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        
        // get values
        for (int j = 0; j < width; j++)
        {
            // set variables to zero
            counter = 0;
            sumRedX = 0;
            sumRedY = 0;
            sumGreenX = 0;
            sumGreenY = 0;
            sumBlueX = 0;
            sumBlueY = 0;
            
            // check each condition 
            // 1
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                counter++;
                sumRedX += (-1 * image[i - 1][j - 1].rgbtRed);
                sumRedY += (-1 * image[i - 1][j - 1].rgbtRed);
                sumGreenX += (-1 * image[i - 1][j - 1].rgbtGreen);
                sumGreenY += (-1 * image[i - 1][j - 1].rgbtGreen);
                sumBlueX += (-1 * image[i - 1][j - 1].rgbtBlue);
                sumBlueY += (-1 * image[i - 1][j - 1].rgbtBlue);
            }
            // 2
            if (i - 1 >= 0)
            {
                counter++;
                sumRedX += (0 * image[i - 1][j].rgbtRed);
                sumRedY += (-2 * image[i - 1][j].rgbtRed);
                sumGreenX += (0 * image[i - 1][j].rgbtGreen);
                sumGreenY += (-2 * image[i - 1][j].rgbtGreen);
                sumBlueX += (0 * image[i - 1][j].rgbtBlue);
                sumBlueY += (-2 * image[i - 1][j].rgbtBlue);
            }
            // 3
            if (i - 1 >= 0 && j + 1 < width)
            {
                counter++;
                sumRedX += (1 * image[i - 1][j + 1].rgbtRed);
                sumRedY += (-1 * image[i - 1][j + 1].rgbtRed);
                sumGreenX += (1 * image[i - 1][j + 1].rgbtGreen);
                sumGreenY += (-1 * image[i - 1][j + 1].rgbtGreen);
                sumBlueX += (1 * image[i - 1][j + 1].rgbtBlue);
                sumBlueY += (-1 * image[i - 1][j + 1].rgbtBlue);
            }
            // 4
            if (j - 1 >= 0)
            {
                counter++;
                sumRedX += (-2 * image[i][j - 1].rgbtRed);
                sumRedY += (0 * image[i][j - 1].rgbtRed);
                sumGreenX += (-2 * image[i][j - 1].rgbtGreen);
                sumGreenY += (0 * image[i][j - 1].rgbtGreen);
                sumBlueX += (-2 * image[i][j - 1].rgbtBlue);
                sumBlueY += (0 * image[i][j - 1].rgbtBlue);
            }
            // 5
            if (j + 1 < width)
            {
                counter++;
                sumRedX += (2 * image[i][j + 1].rgbtRed);
                sumRedY += (0 * image[i][j + 1].rgbtRed);
                sumGreenX += (2 * image[i][j + 1].rgbtGreen);
                sumGreenY += (0 * image[i][j + 1].rgbtGreen);
                sumBlueX += (2 * image[i][j + 1].rgbtBlue);
                sumBlueY += (0 * image[i][j + 1].rgbtBlue);
            }
            // 6
            if (i + 1 < height && j - 1 >= 0)
            {
                counter++;
                sumRedX += (-1 * image[i + 1][j - 1].rgbtRed);
                sumRedY += (1 * image[i + 1][j - 1].rgbtRed);
                sumGreenX += (-1 * image[i + 1][j - 1].rgbtGreen);
                sumGreenY += (1 * image[i + 1][j - 1].rgbtGreen);
                sumBlueX += (-1 * image[i + 1][j - 1].rgbtBlue);
                sumBlueY += (1 * image[i + 1][j - 1].rgbtBlue);
            }
            // 7
            if (i + 1 < height)
            {
                counter++;
                sumRedX += (0 * image[i + 1][j].rgbtRed);
                sumRedY += (2 * image[i + 1][j].rgbtRed);
                sumGreenX += (0 * image[i + 1][j].rgbtGreen);
                sumGreenY += (2 * image[i + 1][j].rgbtGreen);
                sumBlueX += (0 * image[i + 1][j].rgbtBlue);
                sumBlueY += (2 * image[i + 1][j].rgbtBlue);
            }
            // 8
            if (i + 1 < height && j + 1 < width)
            {
                counter++;
                sumRedX += (1 * image[i + 1][j + 1].rgbtRed);
                sumRedY += (1 * image[i + 1][j + 1].rgbtRed);
                sumGreenX += (1 * image[i + 1][j + 1].rgbtGreen);
                sumGreenY += (1 * image[i + 1][j + 1].rgbtGreen);
                sumBlueX += (1 * image[i + 1][j + 1].rgbtBlue);
                sumBlueY += (1 * image[i + 1][j + 1].rgbtBlue);
            }
            
            // get result for each color
            int valueRed = sqrt(pow(sumRedX, 2) + pow(sumRedY, 2)) + 0.5;
            int valueGreen = sqrt(pow(sumGreenX, 2) + pow(sumGreenY, 2)) + 0.5;
            int valueBlue = sqrt(pow(sumBlueX, 2) + pow(sumBlueY, 2)) + 0.5;
            
            // check limit
            if (valueRed <= 255)
            {
                imageT[i][j].rgbtRed = valueRed;
            }
            else
            {
                imageT[i][j].rgbtRed = 255;
            }
            if (valueGreen <= 255)
            {
                imageT[i][j].rgbtGreen = valueGreen;
            }
            else
            {
                imageT[i][j].rgbtGreen = 255;
            }
            if (valueBlue <= 255)
            {
                imageT[i][j].rgbtBlue = valueBlue;
            }
            else
            {
                imageT[i][j].rgbtBlue = 255;
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
