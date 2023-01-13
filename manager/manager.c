#include "logging.h"
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


char* fillString(char string[], int tamanho){
    char* size[tamanho];
    memset(size, "\0", tamanho);
    memset(size, string, sizeof(string));
    return size;

}


static void print_usage() {
    fprintf(stderr, "usage: \n"
                    "   manager <register_pipe_name> create <box_name>\n"
                    "   manager <register_pipe_name> remove <box_name>\n"
                    "   manager <register_pipe_name> list\n");
}

int main(int argc, char **argv) {
    char register_pipe_name_uncompleted[256];
    strcpy(register_pipe_name_uncompleted, argv[1]);
    char register_pipe_name[256] = fillString(register_pipe_name_uncompleted, 256);
    char pipe_name_uncompleted[256];
    strcpy(pipe_name_uncompleted, argv[2]);
    char pipe_name[256] = fillString(pipe_name_uncompleted, 256);
    
    

    if (unlink(pipe_name) != 0 && errno != ENOENT) {
        fprintf(stderr, "[ERR]: unlink(%s) failed: %s\n", pipe_name,
                strerror(errno));
        return -1;
    }

    if (mkfifo(pipe_name, 0640) != 0) {
        fprintf(stderr, "[ERR]: mkfifo failed: %s\n", strerror(errno));
        return -1;

    }
    int register_pipe = open(register_pipe_name, O_WRONLY );


    if (strncmp( argv[3], "create",6) == 0) {
        char box_name_uncompleted[32];  
        strcpy(box_name_uncompleted, argv[4]);
        char box_name[32] = fillString(box_name_uncompleted, 32);
        char strngcat[257] = strncat("3",fillString(pipe_name, 256),257);
        char final_register[289] = strncat(strngcat,fillString(box_name, 32) , 289);
        write(register_pipe, final_register, 289);
        close(register_pipe);
    
    }
    else if (strncmp( argv[3] , "remove",6) == 0) {
        char box_name_uncompleted[32];  
        strcpy(box_name_uncompleted, argv[4]);
        char box_name[32] = fillString(box_name_uncompleted, 32);
        char strngcat[257] = strncat("5",fillString(pipe_name, 256),257);
        char final_register[289] = strncat(strngcat,fillString(box_name, 32) , 289);
        write(register_pipe, final_register, 289);
        close(register_pipe);
    

        
    } 
    else if (strncmp( argv[3] , "list",4) == 0) {
        char final_register[257] = strncat("7",pipe_name , 257);

        write(register_pipe, final_register, 257);
        close(register_pipe);

        
    } 
    else {
        print_usage();
        return -1;
    }
    return 0;

}
