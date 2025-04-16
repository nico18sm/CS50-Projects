#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int k = 0; k < width; k++)
        {
            BYTE blue = image[i][k].rgbtBlue;
            BYTE green = image[i][k].rgbtGreen;
            BYTE red= image[i][k].rgbtRed;

            float average = (red + green + blue) / 3.0;
            BYTE gray = round(average);



            image[i][k].rgbtBlue = gray;
            image[i][k].rgbtGreen = gray;
            image[i][k].rgbtRed = gray;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int k = 0; k < width; k++)
        {
            int blue = image[i][k].rgbtBlue;
            int green = image[i][k].rgbtGreen;
            int red= image[i][k].rgbtRed;

            int sepiaRed = fmin(round(0.393 * red + 0.769 * green + 0.189 * blue), 255);
            int sepiaGreen = fmin(round(0.349 * red + 0.686 * green + 0.168 * blue), 255);
            int sepiaBlue = fmin(round(0.272 * red + 0.534 * green + 0.131 * blue), 255);

            image[i][k].rgbtBlue = sepiaBlue;
            image[i][k].rgbtGreen = sepiaGreen;
            image[i][k].rgbtRed = sepiaRed;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int k = 0; k < width / 2; k++)
        {
            int reflect = width - 1 - k;

            RGBTRIPLE temp = image[i][k];

            image[i][k] = image[i][reflect];
            image[i][reflect] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumBlue = 0, sumGreen = 0, sumRed = 0;
            int count = 0;

            // Iteriere über Nachbarpixel (3x3 Bereich)
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Prüfe, ob der Nachbar innerhalb des Bildes liegt
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumBlue += image[ni][nj].rgbtBlue;
                        sumGreen += image[ni][nj].rgbtGreen;
                        sumRed += image[ni][nj].rgbtRed;
                        count++;
                    }
                }
            }

            // Durchschnitt berechnen
            temp[i][j].rgbtBlue = round((float)sumBlue / count);
            temp[i][j].rgbtGreen = round((float)sumGreen / count);
            temp[i][j].rgbtRed = round((float)sumRed / count);
        }
    }

    // Änderungen zurück ins Originalbild übertragen
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}
