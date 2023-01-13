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

void send_msg(int tx, char const *str) {
    size_t len = strlen(str);
    size_t written = 0;

    while (written < len) {
        ssize_t ret = write(tx, str + written, len - written);
        if (ret < 0) {
            fprintf(stderr, "[ERR]: write failed: %s\n", strerror(errno));
            return -1;
        }

        written += ret;
    }
}

char* fillString(char string[], int tamanho){
    char* size[tamanho];
    memset(size, "\0", tamanho);
    memset(size, string, sizeof(string));
    return size;

}


int main(int argc, char **argv) {
    if (argc != 4){
        return -1;
    }

    char register_pipe_name_uncompleted[256];
    strcpy(register_pipe_name_uncompleted, argv[1]);
    char register_pipe_name[256] = fillString(register_pipe_name_uncompleted, 256);
    char pipe_name_uncompleted[256];
    strcpy(pipe_name_uncompleted, argv[2]);
    char pipe_name[256] = fillString(pipe_name_uncompleted, 256);
    char box_name_uncompleted[32];
    strcpy(box_name_uncompleted, argv[3]);
    char box_name[32] = fillString(box_name_uncompleted, 32);



    
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
    char strngcat[257] = strncat("1",fillString(pipe_name, 256),257);
    char final_register[289] = strncat(strngcat,fillString(box_name, 32) , 289);
    write(register_pipe, final_register, 289);
    close(register_pipe);

    

    int tx = open(pipe_name, O_WRONLY);
    if (tx == -1) {
        fprintf(stderr, "[ERR]: open failed: %s\n", strerror(errno));
        return -1;
    }
    char publisher_message[1024];
    while(scanf("%1024s", publisher_message) != EOF){
        
    }
    char publisher_message_final[1024];
    if(strlen(publisher_message) != 1024){
        strcpy(publisher_message_final, fillString(publisher_message, 1024));
        
    }
    if(write(tx, publisher_message_final, 1024) == -1){
        return -1;
    }
    close(tx);

    return 0;
}