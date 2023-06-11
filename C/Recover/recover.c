#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // Ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: one image allowed.\n");
        return 1;
    }

    
    // 1 Open - reading information from the raw file
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }
    
    // Declaring the pointer, new img
    FILE *img = NULL;
    // buffer of size 512 bytes
    BYTE buffer[512];
    // name of the new file
    char imageName[8];
    // counter for the filename
    int counter = 0;
    // set a flag to know if we found a new image
    bool flag = false;
    
    while (fread(buffer, sizeof(buffer), 1, file) == 1)
    {
        // check header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if true closes the image, a new one is found
            if (flag == true)
            {
                fclose(img);
            }
            else
            {
                flag = true;
            }
            
            // set the name of the new image, based on the counter
            sprintf(imageName, "%03i.jpg", counter);
            // open the new image and starts writing in it
            img = fopen(imageName, "w");
            counter += 1;
        }
        if (flag == true)
        {
            // starts writing the new image, based on the pointer of the buffer, providing the data for de img
            fwrite(&buffer, sizeof(buffer), 1, img);
        }
    }
    
    fclose(img);
    fclose(file);
    
    return 0;

    


    /* JPEG always start by four bytes: 0xff | 0xd8 | 0xff | 0xe* => where * change from 0 to f
    pattern at the beginning of any 512 byte block
    each JPEG starts with a distinct header
    next after one JPEG ends the next begins

    2 Read - for reading the files use:
    fread(<data>, <sizeof>, <number>, <inptr>);
    data: pointer to where to store data you're reading -- arr for example
    size: size of each element to read -- the full block perhaps? 512 bytes chunk
    number: number of elements to read --
    inptr: FILE * to read from -- the file i'm reading

    Check when the fread reached the end of a file, example: if im reading 255 elements, but at some moment, it reached just 200, it means, maybe, the file ended

    3 Check - After reading one block, check:
    - buffer[0] == 0xff -- buffer stands for <data>, where is storing the new data
    - buffer[1] == 0xd8
    - buffer[2] == 0xff
    - buffer[3] == 0xe* => where * from 0 to f => (buffer[3] & 0xf0) == 0xe0
    => look at the first four bits of this 8-bit byte and set the remaining four bits to 0

    4 Make a New JPEG
    - Filenames: ###.jpg, starting at 000.jpg
    Named in crescent order - set a counter
    OR...
    sprintf(filename, "%03i.jpg", 2); // %03i > print a integer with 3 digits | final params is the number you want to substitute - in this case it will be 002.jpg

    after finding a pattern, making a new file, open that file so you can begin writing
    FILE *img = fopen(filename, "w");
    fwrite(data, size, number, outptr);
    data: pointer to bytes that will be written to file - the file i'm reading
    size: size of each element to write -- number of bytes in each element that you're going to write to the file
    number: number of elements to write
    outptr: FILE * to write to -- the jpeg i just opened to writing




    1 - Open memory card
        Repeat until end of card:
            Read 512 bytes into a buffer -- using fread
            If start of new JPEG
                If first JPEG
                    ... file 000
                Else
                    ... close the file been writing, so can open up new file
            Else
                If already found JPEG
                    Keep writing to it - is the next 512 bytes block
        Close any remaining files



    */

}
