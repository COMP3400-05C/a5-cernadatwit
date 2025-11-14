#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
/* 5 Categories:
- Uppercase letters
- Lower letters
- Numbers
- Space
- Others
    You are to use the OPEN sys call to open the file, & read the file using
    READ sys call. The buffer to use is provided, and you should not change this.
    Takes in the CLI argu and
*/
int main(int argc, char* argv[]) {
    if (argc != 2){
        fprintf(stderr, "USAGE: %s FILEIN\n",argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd == -1){
        printf("ERROR: %s not found\n",filename);
        return 1;
    }


    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];
    // TODO: Write a program that reads a file
    // in chunks of 8 bytes & 
    // COUNTS how many letters of each category that exists.
    int bytesRead;
    int upper=0,lower=0,number=0,space=0,others=0;

    while ((bytesRead = read(fd,buffer,BUFSIZE))>0){
        for (int i=0;i<bytesRead; i++){
            unsigned char c = buffer[i];
            if (isupper(c)) upper++;
            else if (islower(c)) lower++;
            else if (isdigit(c)) number++;
            else if (isspace(c)) space++;
            else others++;
        }
    }

    if (bytesRead < 0){
        perror("Error reading file");
        close(fd);
        return 1;
    }
    printf("Upper,%d\n", upper);
    printf("Lower,%d\n", lower);
    printf("Number,%d\n", number);
    printf("Space,%d\n", space);
    printf("Others,%d", others);

    close(fd);
    return 0;
}
