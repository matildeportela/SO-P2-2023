#include "logging.h"


static void print_usage() {
    fprintf(stderr, "usage: \n"
                    "   manager <register_pipe_name> create <box_name>\n"
                    "   manager <register_pipe_name> remove <box_name>\n"
                    "   manager <register_pipe_name> list\n");
}

int main(int argc, char **argv) {
    if(argc != 4){
        print_usage();
        return -1;
    }
    
    char register_pipe_name[256];
    char pipe_name[256];
    char box_name[32];

    strcpy(register_pipe_name, argv[1]);
    strcpy(pipe_name, argv[2]);
    strcpy(box_name, argv[3]);
    
    if (strcmp(pipe_name, "create") == 0) {
        // function create box_name
    } else if (strcmp(pipe_name, "remove") == 0) {
        // function remove box_name
    } else if (strcmp(pipe_name, "list") == 0) {
        // function list
    } else {
        print_usage();
        return -1;
    }
    WARN("unimplemented"); // TODO: implement
    return -1;

}
