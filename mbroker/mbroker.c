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


#define BUFFER_SIZE (128)


int main(int argc, char **argv) {
    if(argc != 3){
        return -1;
    }
    
    
    char register_pipe_name[256];

    strncpy(register_pipe_name, argv[1], 256);
    int max_sessions = atoi(argv[2]);

    if (unlink(register_pipe_name) != 0 && errno != ENOENT) {
        fprintf(stderr, "[ERR]: unlink(%s) failed: %s\n", register_pipe_name,
                strerror(errno));
        return -1;
    }

    // Create pipe
    if (mkfifo(register_pipe_name, 0640) != 0) {
        fprintf(stderr, "[ERR]: mkfifo failed: %s\n", strerror(errno));
        return -1;
    }

    int rx = open(register_pipe_name, O_RDONLY);
    if (rx == -1) {
        fprintf(stderr, "[ERR]: open failed: %s\n", strerror(errno));
        return -1;
    }
    char register_request[289];
    if(read(rx , register_request, 289) == -1){
        return -1;
    }
    close(rx);

    

    return 0;
}
