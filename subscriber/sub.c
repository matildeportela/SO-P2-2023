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


char fillString(char string, int tamanho){
    char size[tamanho];
    memset(size, "/0", tamanho);
    memset(size, string, sizeof(string));
    return size;

}



int main(int argc, char **argv) {
    
    if(argc =! 4){
        return -1;
    }
   
    char register_pipe_name[256];
    strncpy(register_pipe_name, argv[1], 256);
    char pipe_name[256];
    strncpy(pipe_name, argv[2], 256);
    char box_name[32] = argv[3];
    strncpy(box_name, argv[3], 32);


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
    char strngcat[512] = strncat(fillString(register_pipe_name, 256), fillString(pipe_name, 256), 512);
    char final_register[544] = strncat(strngcat, fillString(box_name, 32), 544);
    write(register_pipe, final_register, 544);
    close(register_pipe);


    int rx = open(pipe_name, O_RDONLY);
    if (rx == -1) {
        fprintf(stderr, "[ERR]: open failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);



    


    fprintf(stderr, "usage: sub <register_pipe_name> <box_name>\n");
    WARN("unimplemented"); // TODO: implement
    return -1;
}
