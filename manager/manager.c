#include "logging.h"


static void print_usage() {
    fprintf(stderr, "usage: \n"
                    "   manager <register_pipe_name> create <box_name>\n"
                    "   manager <register_pipe_name> remove <box_name>\n"
                    "   manager <register_pipe_name> list\n");
}

int main(int argc, char **argv) {
    if(argc =! 4){
        return -1;
    }
    if(argv[0] != "sub"){
        return -1;
    }
    
    switch(
    
    case("create"):
    char[52] box_name = argv[3];
    //function create box_name
    
    case("remove"):
    char[52] box_name = argv[3];
    //function remove box_name

    default:
    char[256] register_pipe_name = argv[1];
    char[256] pipe_name = argv[2];
    

    print_usage();
    WARN("unimplemented"); // TODO: implement
    return -1;
    )
}
