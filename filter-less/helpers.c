#include "helpers.h"
#include <math.h>

float more_than_255(float cal);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //for each column in the picture
    for (int i = 0; i < height; i++)
    {
        //for each row in the picture
        for (int j = 0; j < width; j++)
        {
            //total value of rgb
            int total_rgb = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            //average in order to keep brightness and create a shade of gray.
            int avg = round(total_rgb / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
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
            //retrive each color for a pixel
            int o_blue = image[i][j].rgbtBlue;
            int o_green = image[i][j].rgbtGreen;
            int o_red = image[i][j].rgbtRed;
            //turn each color into its Sepia colour using the provided formula
            float cal_Red = round((0.393 * o_red) + (0.769 * o_green) + (0.189 * o_blue));
            float cal_Green = round((0.349 * o_red) + (0.686 * o_green) + (0.168 * o_blue));
            float cal_Blue = round((0.272 * o_red) + (0.534 * o_green) + (0.131 * o_blue));
            //ensuring max num is between 0 and 255 for each colour.
            int sepiaBlue = round(more_than_255(cal_Blue));
            int sepiaGreen = round(more_than_255(cal_Green));
            int sepiaRed = round(more_than_255(cal_Red));
            //update the curr pixel with new Sepia RBG
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}
//function to check ensure max num is 255 for RBG vals
float more_than_255(float cal)
{
    if (cal > 255)
    {
        cal = 255;
        return cal;
    }
    return cal;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //for each coloumn and its relevant row
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, half_way = width / 2.0; j < half_way; j++)
        {
            //This is not required because image[i][j] IS ALREADY A POINTER
            /*RGBTRIPLE a = image[i][j];
            RGBTRIPLE b = image[i][width - j];*/
            //tmp stoes the orignal value of the first pixel.
            RGBTRIPLE tmp = image[i][j];
            //need a way to account for \0 at the end of an array
            image[i][j] = image[i][width -1  - j];
            image[i][width -1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    //create avg from the pixels in a 3 x 3 box with that pixel.
    for (int i =0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //when height and width are used in expressions for if()
            //remember that height - 1, width - 1 for the correct index value.
            if ( i == 0 && j == 0)
            { //Top left corner
                long curr_blue_total = 0;

                long curr_green_total = 0;

                long curr_red_total = 0;

                curr_blue_total = copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j + width].rgbtBlue + copy[i][j + width + 1].rgbtBlue;

                curr_green_total = copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j + width].rgbtGreen + copy[i][j + width + 1].rgbtGreen;

                curr_red_total = copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j + width].rgbtRed + copy[i][j + width + 1].rgbtRed;

                int curr_blue_avg = round(curr_blue_total / 4.0);

                int curr_green_avg = round(curr_green_total / 4.0);

                int curr_red_avg = round(curr_red_total / 4.0);

                image[i][j].rgbtRed = curr_red_avg;

                image[i][j].rgbtGreen = curr_green_avg;

                image[i][j].rgbtBlue = curr_blue_avg;

            }
            else if ( i == 0 && j == width - 1)
            { //Top right edge
                long curr_blue_total = 0;

                long curr_green_total = 0;

                long curr_red_total = 0;

                curr_blue_total = copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + width].rgbtBlue + copy[i][j + width - 1].rgbtBlue;

                curr_green_total = copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + width].rgbtGreen + copy[i][j + width - 1].rgbtGreen;

                curr_red_total = copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + width].rgbtRed + copy[i][j + width - 1].rgbtRed;

                int curr_blue_avg = round(curr_blue_total / 4.0);

                int curr_green_avg = round(curr_green_total / 4.0);

                int curr_red_avg = round(curr_red_total / 4.0);

                image[i][j].rgbtRed = curr_red_avg;

                image[i][j].rgbtGreen = curr_green_avg;

                image[i][j].rgbtBlue = curr_blue_avg;

            }
            else if ( i == height - 1 && j == 0)
            { //Bottom left edge
                long curr_blue_total = 0;

                long curr_green_total = 0;

                long curr_red_total = 0;

                curr_blue_total = copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - width].rgbtBlue + copy[i][j - width + 1].rgbtBlue;

                curr_green_total = copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - width].rgbtGreen + copy[i][j - width + 1].rgbtGreen;

                curr_red_total = copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - width].rgbtRed + copy[i][j - width + 1].rgbtRed;

                int curr_blue_avg = round(curr_blue_total / 4.0);

                int curr_green_avg = round(curr_green_total / 4.0);

                int curr_red_avg = round(curr_red_total / 4.0);

                image[i][j].rgbtRed = curr_red_avg;

                image[i][j].rgbtGreen = curr_green_avg;

                image[i][j].rgbtBlue = curr_blue_avg;
            }
            else if ( i == height - 1 && j == width - 1)
            { //Bottom right edge
                long curr_blue_total = 0;

                long curr_green_total = 0;

                long curr_red_total = 0;

                curr_blue_total = copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j - width].rgbtBlue + copy[i][j - width -1].rgbtBlue;

                curr_green_total = copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j - width].rgbtGreen + copy[i][j - width -1 ].rgbtGreen;

                curr_red_total = copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j - width].rgbtRed + copy[i][j - width -1].rgbtRed;

                int curr_blue_avg = round(curr_blue_total / 4.0);

                int curr_green_avg = round(curr_green_total / 4.0);

                int curr_red_avg = round(curr_red_total / 4.0);

                image[i][j].rgbtRed = curr_red_avg;

                image[i][j].rgbtGreen = curr_green_avg;

                image[i][j].rgbtBlue = curr_blue_avg;
            }
            else if ( i == 0 && j != 0)
            { //top row

                long curr_blue_total = 0;

                long curr_green_total = 0;

                long curr_red_total = 0;

                int n = -1;

                while ( n < 2)
                {

                    curr_blue_total += copy[i][j + n].rgbtBlue;

                    curr_blue_total += copy[i][j + n + width].rgbtBlue;

                    curr_green_total += copy[i][j + n].rgbtGreen;

                    curr_green_total += copy[i][j + n + width].rgbtGreen;

                    curr_red_total += copy[i][j + n].rgbtRed;

                    curr_red_total += copy[i][j + n + width].rgbtRed;

                    n++;
                }

                int curr_blue_avg = round(curr_blue_total / 6.0);

                int curr_green_avg = round(curr_green_total / 6.0);

                int curr_red_avg = round(curr_red_total / 6.0);

                image[i][j].rgbtRed = curr_red_avg;

                image[i][j].rgbtGreen = curr_green_avg;

                image[i][j].rgbtBlue = curr_blue_avg;
            }
            else if ( i == height -1 && j != 0)
            { //bottom row

                long curr_blue_total = 0;

                long curr_green_total = 0;

                long curr_red_total = 0;

                int n = -1;

                while ( n < 2)
                {
                    curr_blue_total += copy[i][j + n].rgbtBlue;

                    curr_blue_total += copy[i][j + n - width].rgbtBlue;

                    curr_green_total += copy[i][j + n].rgbtGreen;

                    curr_green_total += copy[i][j + n - width].rgbtGreen;

                    curr_red_total += copy[i][j + n].rgbtRed;

                    curr_red_total += copy[i][j + n - width].rgbtRed;

                    n++;
                }
                int curr_blue_avg = round(curr_blue_total / 6.0);

                int curr_green_avg = round(curr_green_total / 6.0);

                int curr_red_avg = round(curr_red_total / 6.0);

                image[i][j].rgbtRed = curr_red_avg;

                image[i][j].rgbtGreen = curr_green_avg;

                image[i][j].rgbtBlue = curr_blue_avg;
            }
            else if ( j == 0 && i != 0)
            { //left most column

                long curr_blue_total = 0;

                long curr_green_total = 0;

                long curr_red_total = 0;

                curr_blue_total = copy[i][j].rgbtBlue + copy[i][j - width].rgbtBlue + copy[i][j - width + 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j + width].rgbtBlue + copy[i][j + width + 1].rgbtBlue;

                curr_green_total = copy[i][j].rgbtGreen + copy[i][j - width].rgbtGreen + copy[i][j - width + 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j + width].rgbtGreen + copy[i][j + width + 1].rgbtGreen;

                curr_red_total = copy[i][j].rgbtRed + copy[i][j - width].rgbtRed + copy[i][j - width + 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j + width].rgbtRed + copy[i][j + width + 1].rgbtRed;

                int curr_blue_avg = round(curr_blue_total / 6.0);

                int curr_green_avg = round(curr_green_total / 6.0);

                int curr_red_avg = round(curr_red_total / 6.0);

                image[i][j].rgbtRed = curr_red_avg;

                image[i][j].rgbtGreen = curr_green_avg;

                image[i][j].rgbtBlue = curr_blue_avg;
            }
            else if (j == width - 1 && i != 0)
            { //right most column

                long curr_blue_total = 0;

                long curr_green_total = 0;

                long curr_red_total = 0;

                curr_blue_total = copy[i][j].rgbtBlue + copy[i][j - width].rgbtBlue + copy[i][j - width - 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + width].rgbtBlue + copy[i][j + width -1].rgbtBlue;

                curr_green_total = copy[i][j].rgbtGreen + copy[i][j - width].rgbtGreen + copy[i][j - width - 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + width].rgbtGreen + copy[i][j + width -1].rgbtGreen;

                curr_red_total = copy[i][j].rgbtRed + copy[i][j - width].rgbtRed + copy[i][j - width - 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + width].rgbtRed + copy[i][j + width -1].rgbtRed;

                int curr_blue_avg = round(curr_blue_total / 6.0);

                int curr_green_avg = round(curr_green_total / 6.0);

                int curr_red_avg = round(curr_red_total / 6.0);

                image[i][j].rgbtRed = curr_red_avg;

                image[i][j].rgbtGreen = curr_green_avg;

                image[i][j].rgbtBlue = curr_blue_avg;
            }

            else
            {

                long curr_blue_total = 0;

                long curr_green_total = 0;

                long curr_red_total = 0;

                int n = -1;

                while (n < 2)
                {
                    //middle
                    curr_blue_total += copy[i][j + n].rgbtBlue;
                    //above row
                    curr_blue_total += copy[i][j + n - width].rgbtBlue;
                    //below row
                    curr_blue_total += copy[i][j + n + width].rgbtBlue;
                    curr_green_total += copy[i][j + n].rgbtGreen;
                    curr_green_total += copy[i][j + n - width].rgbtGreen;
                    curr_green_total += copy[i][j + n + width].rgbtGreen;
                    curr_red_total += copy[i][j + n].rgbtRed;
                    curr_red_total += copy[i][j + n - width].rgbtRed;
                    curr_red_total += copy[i][j + n + width].rgbtRed;
                    n++;
                }
                int curr_blue_avg = round(curr_blue_total / 9.0);
                int curr_green_avg = round(curr_green_total / 9.0);
                int curr_red_avg = round(curr_red_total / 9.0);
                image[i][j].rgbtRed = curr_red_avg;
                image[i][j].rgbtGreen = curr_green_avg;
                image[i][j].rgbtBlue = curr_blue_avg;
            }
        }
    }
    return;
}