#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through matrix using nested for-loop
    for(int i = 0; i < height; i++){

        for(int j = 0; j < width; j++){
            //formula to calculate greyscale
            uint8_t grey = round((image[i][j].rgbtGreen + image[i][j].rgbtBlue + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtBlue = grey;
            image[i][j].rgbtRed = grey;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            // original colors
            int originalRed   = image[j][i].rgbtRed;
            int originalGreen = image[j][i].rgbtGreen;
            int originalBlue  = image[j][i].rgbtBlue;

            // calculate sepia values
            int sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            image[j][i].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[j][i].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[j][i].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int j = 0; j < height; j++)
    {
        // iterate through first half
        for (int i = 0; i < width / 2; i++)
        {
            RGBTRIPLE temp = image[j][i];
            image[j][i] = image[j][width - 1 - i];
            image[j][width - 1 - i] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp[height][width];
    // temp so you dont reuse blurred pixels
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            temp[j][i] = image[j][i];
        }
    }
     for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {

            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;

            // 3x3 neighborhood
            for (int dj = -1; dj <= 1; dj++) {
                for (int di = -1; di <= 1; di++) {

                    int nj = j + dj;
                    int ni = i + di;

                    if (nj >= 0 && nj < height && ni >= 0 && ni < width) {
                        sumRed   += temp[nj][ni].rgbtRed;
                        sumGreen += temp[nj][ni].rgbtGreen;
                        sumBlue  += temp[nj][ni].rgbtBlue;
                        count++;
                    }
                }
            }
            // apply
          image[j][i].rgbtRed   = round((float) sumRed / count);
          image[j][i].rgbtGreen = round((float) sumGreen / count);
          image[j][i].rgbtBlue  = round((float) sumBlue / count);
        }
     }


    return;
}
