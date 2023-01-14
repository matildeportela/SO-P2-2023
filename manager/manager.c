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


char* fillString(char* string, size_t tamanho){
    if(sizeof(string) < tamanho){
        for(int i = sizeof(string); i < tamanho; i++ ){
            string[i] = '\0';
        
        }
    }

    
    return string;

}





static void print_usage() {
    fprintf(stderr, "usage: \n"
                    "   manager <register_pipe_name> create <box_name>\n"
                    "   manager <register_pipe_name> remove <box_name>\n"
                    "   manager <register_pipe_name> list\n");
}

int main(int argc, char **argv) {
    if(argc != 4 && argc != 5){
        print_usage();
        return -1;
    }
    char register_pipe_name[256];
    memcpy(register_pipe_name, fillString(argv[1], 256), 256);

    char pipe_name[256];
    memcpy(pipe_name, fillString(argv[2], 256), 256);
    
    
    

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
        char box_name[32];  
        memcpy(box_name, fillString(argv[4], 32), 32);
        char request[289];
        memcpy(request, "3",1);
        memcpy(request+1,fillString(pipe_name, 256),256);
        memcpy(request+257,fillString(box_name, 32) , 32);
        if(write(register_pipe, request, 289) == -1){
            close(register_pipe);
            return -1;
        }
    }
    else if (strncmp( argv[3] , "remove",6) == 0) {
        char box_name[32];  
        memcpy(box_name, fillString(argv[4], 32), 32);
        char request[289];
        memcpy(request, "5",1);
        memcpy(request+1,fillString(pipe_name, 256),256);
        memcpy(request+257,fillString(box_name, 32) , 32);
        if(write(register_pipe, request, 289) == -1){
            close(register_pipe);
            return -1;
        }
    } 
    else if (strncmp( argv[3] , "list",4) == 0) {
        char request[257];
        memcpy(request, "7", 1);
        memcpy(request + 1, pipe_name , 256);

        if(write(register_pipe, request, 257) == -1){
            close(register_pipe);
            return -1;
        }
        

        
    } 
    else {
        print_usage();
        close(register_pipe);
        return -1;
    }
    close(register_pipe);
    return 0;

}
