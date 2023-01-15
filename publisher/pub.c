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





char* concatenate(const char* str1, const char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char* result = malloc(len1 + len2 + 1);
    memcpy(result, str1, len1);
    memcpy(result + len1, str2, len2 + 1);
    return result;
}

int main(int argc, char **argv) {
    if (argc != 4){
        return -1;
    }

    char register_pipe_name[256];
    fill_string(register_pipe_name, argv[1], 256);
    char pipe_name[256];
    fill_string(pipe_name, argv[2], 256);
    char box_name[32];
    fill_string(box_name, argv[3], 32);
    
    



    
    if (unlink(pipe_name) != 0 && errno != ENOENT) {
        fprintf(stderr, "[ERR]: unlink(%s) failed: %s\n", pipe_name,
                strerror(errno));
        return -1;
    }

    if (mkfifo(pipe_name, 0640) == -1) {
        fprintf(stderr, "[ERR]: mkfifo failed: %s\n", strerror(errno));
        return -1;

    }

    int register_pipe = open(register_pipe_name, O_WRONLY );
    char request_1[2];
    memcpy(request_1, "1",1);
    char request[257];
    memcpy(request, concatenate(request_1,pipe_name), 257);
    if(write(register_pipe,  concatenate(request,box_name), 289) == -1){
        return -1;
    }
    

    

    int publisher_pipe = open(pipe_name, O_WRONLY);
    if (publisher_pipe == -1) {
        fprintf(stderr, "[ERR]: open failed: %s\n", strerror(errno));
        close(register_pipe);
        return -1;
    }
    char publisher_message_scanned[1024];
    
    while(scanf("%1023s", publisher_message_scanned) != EOF){
        
    }
    char publisher_message_final[1025];
    char scanned_size[1024];
    memcpy(publisher_message_final, "9", 1);
    memcpy(publisher_message_final + 1, fill_string(scanned_size, publisher_message_scanned, 1024), 1024);
    

    if(write(publisher_pipe, publisher_message_final, 1025) == -1){
        return -1;
    }
    close(publisher_pipe);
    close(register_pipe);

    return 0;
}