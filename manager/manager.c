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


static void print_usage() {
    fprintf(stderr, "usage: \n"
                    "   manager <register_pipe_name> create <box_name>\n"
                    "   manager <register_pipe_name> remove <box_name>\n"
                    "   manager <register_pipe_name> list\n");
}

int main(int argc, char **argv) {
    char register_pipe_name[256];
    char pipe_name[256];
    char box_name[32];
    strcpy(register_pipe_name, argv[1]);
    strcpy(pipe_name, argv[2]);
    strcpy(box_name, argv[4]);

    


    if (strncmp( argv[3], "create",6) == 0) {
        

        
    } 
    else if (strncmp( argv[3] , "remove",6) == 0) {
        
    } 
    else if (strncmp( argv[3] , "list",4) == 0) {
        
    } 
    else {
        print_usage();
        return -1;
    }
    return 0;

}
