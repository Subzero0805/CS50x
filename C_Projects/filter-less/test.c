#include <stdio.h>
#include <math.h>

int main()
{
    int a = 2;
    float b = a / 6.0;
    int c = round(b);
    printf("%f\n",b);
    printf("%i\n",c);
    return 0;
}

/*
            int curr_blue_total = copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j + 2].rgbtBlue
                + copy[i][j + 3].rgbtBlue + copy[i][j + 4].rgbtBlue + copy[i][j + 5].rgbtBlue
                + copy[i][j + 6].rgbtBlue + copy[i][j + 7].rgbtBlue + copy[i][j + 8].rgbtBlue;
            int curr_green_total = copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j + 2].rgbtGreen
                + copy[i][j + 3].rgbtGreen + copy[i][j + 4].rgbtGreen + copy[i][j + 5].rgbtGreen
                + copy[i][j + 6].rgbtGreen + copy[i][j + 7].rgbtGreen + copy[i][j + 8].rgbtGreen;
            int curr_red_total = copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j + 2].rgbtRed
                + copy[i][j + 3].rgbtRed + copy[i][j + 4].rgbtRed + copy[i][j + 5].rgbtRed
                + copy[i][j + 6].rgbtRed + copy[i][j + 7].rgbtRed + copy[i][j + 8].rgbtRed;
*/

/*
            int curr_blue_total = copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue
                + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue
                + copy[i - 1][j + 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue;
            int curr_green_total = copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen
                + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen
                + copy[i - 1][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen;
            int curr_red_total = copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed
                + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i + 1][j].rgbtRed
                + copy[i - 1][j + 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed;

            int curr_blue_total = copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue
                + copy[i][j - 2].rgbtBlue + copy[i][j + 2].rgbtBlue + copy[i][j - 3].rgbtBlue
                + copy[i][j + 3].rgbtBlue + copy[i][j - 4].rgbtBlue + copy[i][j + 4].rgbtBlue;
            int curr_green_total = copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen
                + copy[i][j + 2].rgbtGreen + copy[i][j - 2].rgbtGreen + copy[i][j + 3].rgbtGreen
                + copy[i][j - 3].rgbtGreen + copy[i][j - 4].rgbtGreen + copy[i][j + 4].rgbtGreen;
            int curr_red_total = copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed
                + copy[i][j + 2].rgbtRed + copy[i][j - 2].rgbtRed + copy[i][j - 3].rgbtRed
                + copy[i][j + 3].rgbtRed + copy[i][j - 4].rgbtRed + copy[i][j + 4].rgbtRed;
*/