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



int main(int argc, char **argv) {
    
    if(argc != 4){
        fprintf(stderr, "usage: pub <register_pipe_name> <pipe_name> <box_name>\n");
        return -1;
    }

    char register_pipe_name[256];
    memcpy(register_pipe_name, fillString(argv[1], 256), 256);
    char pipe_name[256];
    memcpy(pipe_name, fillString(argv[2], 256), 256);
    char box_name[32];
    memcpy(box_name, fillString(argv[3], 32), 32);

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

    char opcode[289];
    memcpy(opcode, "2",1);
    memcpy(opcode+1,fillString(pipe_name, 256),256);
    memcpy(opcode+257,fillString(box_name, 32) , 32);
    if(write(register_pipe, opcode, 289) == -1){
        close(register_pipe);
        return -1;
    }
    

    


    int rx = open(pipe_name, O_RDONLY);
    if (rx == -1) {
        fprintf(stderr, "[ERR]: open failed: %s\n", strerror(errno));
        close(register_pipe);
        return -1;
    }
    
    char message_from_publisher[1024];
    if(read(rx, message_from_publisher, 1024 ) == -1){
        close(register_pipe);
        return -1;
    }


    close(register_pipe);
    return 0;

}
