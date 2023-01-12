#include "logging.h"

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    fprintf(stderr, "usage: mbroker <pipename>\n");
    WARN("unimplemented"); // TODO: implement
    return -1;

        //int opcode;
        //int fd;
    
    // while(1) {
    //     tfs_read(fd,  &opcode,  sizeof(opcode));
        
    //     switch (opcode)
    //     {
    //     case (1):
    //         // read 
    //         break;
        
    //     default:
    //         break;
    //     }
    // }

}