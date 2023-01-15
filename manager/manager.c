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
#include <stdint.h>

char* concatenate(const char* str1, const char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char* result = malloc(len1 + len2 + 1);
    memcpy(result, str1, len1);
    memcpy(result + len1, str2, len2 + 1);
    return result;
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
    fill_string(register_pipe_name, argv[1], 256);
    char pipe_name[256];
    fill_string(pipe_name, argv[2], 256);
   
    
    
    

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
        fill_string(box_name, argv[4], 32);
        char request_1[2];
        memcpy(request_1, "3",1);
        char request[257];
        memcpy(request, concatenate(request_1,pipe_name), 257);
        
        if(write(register_pipe,  concatenate(request,box_name), 289) == -1){
            return -1;
        }
    }
    else if (strncmp( argv[3] , "remove",6) == 0) {
        
        char box_name[32];  
        fill_string(box_name, argv[4], 32);
        
        char request_1[2];
        memcpy(request_1, "5",1);
        printf("%s\n", request_1);
        char request[257];
        memcpy(request, concatenate(request_1,pipe_name), 257);
       
        if(write(register_pipe,  concatenate(request,box_name), 289) == -1){
            return -1;
        }
    } 
    else if (strncmp( argv[3] , "list",4) == 0) {
        char request_1[2];
        memcpy(request_1, "7",1);
        char request[257];  
        memcpy(request, concatenate(request_1,pipe_name), 257);
        if(write(register_pipe,  request, 257) == -1){
            return -1;
        }
        

        
    } 
    else {
        print_usage();
        close(register_pipe);
        return -1;
    }
    uint8_t code;
    int manager_file = open(pipe_name, O_RDONLY);
    if(read(manager_file, code, 1) == -1){
        return -1;
    }

    int32_t return_code;
    if(read(manager_file, return_code, 1) == -1){
        return -1;
    }

    char error_message[1024];
    if(read(manager_file, error_message, 1024) == -1){
        return -1;
    }

    close(register_pipe);
    return 0;

}
