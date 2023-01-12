#include "logging.h"

int main(int argc, char **argv) {
    
    char[256] register_pipe_name = argv[1];
    char[256] pipe_name = argv[2];
    char[52] box_name = argv[3];
    
    fprintf(stderr, "usage: sub <register_pipe_name> <box_name>\n");
    WARN("unimplemented"); // TODO: implement
    return -1;
}
