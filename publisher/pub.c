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
#include <signal.h>


char* fillString(char* string, size_t tamanho){
    if(sizeof(string) < tamanho){
        for(int i = sizeof(string); i < tamanho; i++ ){
            string[i] = '\0';
        
        }
    }
    
    return string;

}



int main(int argc, char **argv) {
    if (argc != 4){
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
    char request[289];
    memcpy(request, "1",1);
    memcpy(request+1,fillString(pipe_name, 256),256);
    memcpy(request+257,fillString(box_name, 32) , 32);
    if(write(register_pipe, request, 289) == -1){
        return -1;
    }
    

    

    int publisher_pipe = open(pipe_name, O_WRONLY);
    if (publisher_pipe == -1) {
        fprintf(stderr, "[ERR]: open failed: %s\n", strerror(errno));
        close(register_pipe);
        return -1;
    }
    char publisher_message[1025];
    while(scanf("%1023s", publisher_message) != EOF){
        
    }
    memcpy(publisher_message, "9", 1);
    memcpy(publisher_message + 1, fillString(publisher_message, 1024), 1024);
    

    if(write(publisher_pipe, publisher_message, 1025) == -1){
        return -1;
    }
    close(publisher_pipe);
    close(register_pipe);

    return 0;
}