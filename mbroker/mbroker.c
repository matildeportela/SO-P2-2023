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
    strncpy(register_pipe_name, argv[2], 256);
    int max_sessions = atoi(argv[1]);

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
    // while (true) {
    //     char buffer[BUFFER_SIZE];
    //     ssize_t ret = read(rx, buffer, BUFFER_SIZE - 1);
    //     if (ret == 0) {
    //         // ret == 0 indicates EOF
    //         fprintf(stderr, "[INFO]: pipe closed\n");
    //         return 0;
    //     } else if (ret == -1) {
    //         // ret == -1 indicates error
    //         fprintf(stderr, "[ERR]: read failed: %s\n", strerror(errno));
    //         exit(EXIT_FAILURE);
    //     }

    //     fprintf(stderr, "[INFO]: received %zd B\n", ret);
    //     buffer[ret] = 0;
    //     fputs(buffer, stdout);
    // }

    // close(rx);





    fprintf(stderr, "usage: mbroker <pipename>\n");
    WARN("unimplemented"); // TODO: implement
    return -1;
}
