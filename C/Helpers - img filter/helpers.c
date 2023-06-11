#include "helpers.h"
#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include "float.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg, sum;
    for (int row = 0; row < height; row++)
    {
        for (int colum = 0; colum < width; colum++)
        {
            avg = round((image[row][colum].rgbtGreen + image[row][colum].rgbtBlue + image[row][colum].rgbtRed) / (float) 3);

            image[row][colum].rgbtGreen = avg;
            image[row][colum].rgbtBlue = avg;
            image[row][colum].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    // if ODD - middle dont move
    if (width % 2 != 0)
    {
        for (int row = 0; row < height; row++)
        {
            for (int colum = 0; colum < width / 2; colum++)
            {
                if (colum != width / 2)
                {
                    temp = image[row][colum];
                    image[row][colum] = image[row][width - colum - 1];
                    image[row][width - colum - 1] = temp;
                }
            }
        }
    }
    // if EVEN - change all
    else
    {
        for (int row = 0; row < height; row++)
        {
            for (int colum = 0; colum < width / 2; colum++)
            {
                temp = image[row][colum];
                image[row][colum] = image[row][width - colum - 1];
                image[row][width - colum - 1] = temp;
            }
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // average of the ORIGINAL value of the pixels around it
    int avgR, avgG, avgB, counter;

    // make a copy of the original image for the calculations

    RGBTRIPLE copy[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copy[h][w] = image[h][w];
        }
    }

    // go across the image
    for (int linha = 0; linha < height; linha++)
    {
        for (int coluna = 0; coluna < width; coluna++)
        {
            // initialize the variables and reset them to 0
            avgR = 0;
            avgG = 0;
            avgB = 0;
            counter = 0;
            // go across the pixels around
            for (int row = -1; row < 2; row++)
            {
                for (int column = -1; column < 2; column++)
                {
                    if (linha + row < 0 || coluna + column < 0 || linha + row >= height || coluna + column >= width)
                    {

                    }
                    else
                    {
                        avgR += copy[linha + row][coluna + column].rgbtRed;
                        avgG += copy[linha + row][coluna + column].rgbtGreen;
                        avgB += copy[linha + row][coluna + column].rgbtBlue;
                        counter ++;
                    }
                }
            }
            image[linha][coluna].rgbtRed = round(avgR / (float) counter);
            image[linha][coluna].rgbtGreen = round(avgG / (float) counter);
            image[linha][coluna].rgbtBlue = round(avgB / (float) counter);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // average of the ORIGINAL value of the pixels arount it
    float avgXR, avgXG, avgXB, avgYR, avgYG, avgYB;
    float roundR, roundG, roundB;

    // declate the Gx matrix
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    // declare the Gy matrix
    int gy[3][3] = {{-1, -2, -1}, { 0,  0,  0}, { 1,  2,  1}};

    // make copy of the original image
    RGBTRIPLE copy[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copy[h][w] = image[h][w];
        }
    }

    // go across the image
    for (int linha = 0; linha < height; linha++)
    {
        for (int coluna = 0; coluna < width; coluna++)
        {
            avgXR = 0, avgXG = 0, avgXB = 0, avgYR = 0, avgYG = 0, avgYB = 0, roundR = 0, roundG = 0, roundB = 0;

            for (int row = -1; row < 2; row++)
            {
                for (int col = -1; col < 2; col++)
                {
                    if (linha + row < 0 || coluna + col < 0 || linha + row >= height || coluna + col >= width)
                    {

                    }
                    else
                    {
                        // sum of the X axis
                        avgXR += gx[row + 1][col + 1] * copy[linha + row][coluna + col].rgbtRed;
                        avgXG += gx[row + 1][col + 1] * copy[linha + row][coluna + col].rgbtGreen;
                        avgXB += gx[row + 1][col + 1] * copy[linha + row][coluna + col].rgbtBlue;

                        // sum of the Y axis
                        avgYR += gy[row + 1][col + 1] * copy[linha + row][coluna + col].rgbtRed;
                        avgYG += gy[row + 1][col + 1] * copy[linha + row][coluna + col].rgbtGreen;
                        avgYB += gy[row + 1][col + 1] * copy[linha + row][coluna + col].rgbtBlue;
                    }
                }
            }


            roundR = round(sqrt(pow(avgXR, 2) + pow(avgYR, 2)));
            roundG = round(sqrt(pow(avgXG, 2) + pow(avgYG, 2)));
            roundB = round(sqrt(pow(avgXB, 2) + pow(avgYB, 2)));


            if (roundR > 255)
            {
                roundR = 255;
            }
            if (roundG > 255)
            {
                roundG = 255;
            }
            if (roundB > 255)
            {
                roundB = 255;
            }

            image[linha][coluna].rgbtRed = roundR;
            image[linha][coluna].rgbtGreen = roundG;
            image[linha][coluna].rgbtBlue = roundB;
        }
    }

    return;
}
