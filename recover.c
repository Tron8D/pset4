#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
#define SIZE 512

int main(int argc, char *argv[]){
    
    // ensure proper usage
    if(argc != 2){
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 1;
    }

    //open files
    FILE *inFile = fopen(argv[1], "r");
    FILE *outFile = NULL;
    
    if (outFile != NULL)
    {
        fprintf(stderr, "Could not open outFile");
        return 2;
    }
    
    if (inFile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    //create buffer
    BYTE *buffer = malloc(SIZE);

    if(buffer == NULL){
        fprintf(stderr, "Could not create buffer.\n");
        return 3;
    }

    //name new file
    char newFile[8];

    int image = 0;
    
    while(fread(buffer, SIZE, 1, inFile) == 1){
        
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1)){
            sprintf(newFile, "%03d.jpg", image);
            image++;
            
            if(outFile == NULL){
                outFile = fopen(newFile, "w");
                fwrite(buffer, SIZE, 1, outFile);
            } else{
                fclose(outFile);
                outFile = fopen(newFile, "w");
                fwrite(buffer, SIZE, 1, outFile);
            }

        } else if(outFile != NULL)
                fwrite(buffer, SIZE, 1, outFile);
    }
    
    fclose(outFile);
    fclose(inFile);
    free(buffer);
    
    return 0;
}