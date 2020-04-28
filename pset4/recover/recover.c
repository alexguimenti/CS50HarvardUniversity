#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t BYTE; // Declaring Byte as an unsigned integer 8 BIT !

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    
    
    
    // Create outfile for picture
    FILE *img = NULL;
    
    // Create buffer and filename arrays
    unsigned char buffer[512] = {0};
    
    char filename[8];
    
    
    
    bool start = false;
    int counter = 0;
    while (fread(buffer, 512, 1, file) == 1)
    {
        //printf("%u\n\n\n", buffer[0]);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // start of a jpeg
        {
            if (counter > 1) // If File is open, close the pointer
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", counter); // Create file name
            img = fopen(filename, "w"); // Create new file pointer
            fwrite(&buffer, sizeof(buffer), 1, img); // Write buffer to the image
            counter++;
        }
        else
        {
            if (img) // Found JPEG
            {
                fwrite(&buffer, sizeof(buffer), 1, img); // Write buffer to the image
            }
        }
    }
    printf("Counter: %i\n\n", counter);
}
