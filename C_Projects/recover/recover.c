#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCKSIZE 512

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // ensure the correct amount of arguments has been submitted
    if (argc > 2 || argc < 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //Open the file and ensure it exsists
    FILE *corfile = fopen(argv[1], "r");
    if (corfile == NULL)
    {
        printf("Could not open.\n");
        return 2;
    }

    //Creating a buffer to enable us to read through the data
    BYTE buffer[BLOCKSIZE];

    // setting up a counter variable to enable naming of img files.
    int i = 0;

    // the new file we will write into
    char filename[8];
    FILE *image;

    while (fread(buffer, BLOCKSIZE, 1, corfile))
    {
        //checking for the image header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if we already at an image, then we will need to stop writing to the image by closing it
            if (i != 0)
            {
                fclose(image);
            }
            //writing to a new image
            sprintf(filename, "%03i.jpg", i);
            image = fopen(filename, "w");
            fwrite(buffer, BLOCKSIZE, 1, image);
            i++;
        }
        // if it is not a header, check if counter is not zero
        // we can write into our current image file.
        else if (i > 0)
        {
            fwrite(buffer, BLOCKSIZE, 1, image);
        }
    }

}