#include "logging.h"

int main(int argc, char **argv) {
    
    char[256] register_pipe_name = argv[1];
    char[256] pipe_name = argv[2];
    char[52] box_name = argv[3];

    fprintf(stderr, "usage: pub <register_pipe_name> <box_name>\n");
    WARN("unimplemented"); // TODO: implement
    return -1;
}


int main(int argc, char **argv) {

    char[256] register_pipe_name = argv[1];
    char[256] pipe_name = argv[2];
    char[52] box_name = argv[3];

    if (argc < 4) {
        return -1;
    }
    
    // remove pipe if it does exist
    if (unlink(FIFO_PATHNAME) != 0 && errno != ENOENT) {
        fprintf(stderr, "[ERR]: unlink(%s) failed: %s\n", FIFO_PATHNAME,
                strerror(errno));
        exit(EXIT_FAILURE);
    }

    // create pipe
    if (mkfifo(FIFO_PATHNAME, 0640) != 0) {
        fprintf(stderr, "[ERR]: mkfifo failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // open pipe for writing
    // this waits for someone to open it for reading
    int tx = open(FIFO_PATHNAME, O_WRONLY);
    if (tx == -1) {
        fprintf(stderr, "[ERR]: open failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];

    ssize_t ret;

    char *second_pipe = argv[1];
    // sends the pipename to the other side
    send_msg(tx, second_pipe);

    // needs to wait for the other pipe is created
    sleep(1);

    // open pipe for reading
    // this waits for someone to open it for writing
    int rx = open(second_pipe, O_RDONLY);
    if (rx == -1) {
        fprintf(stderr, "[ERR]: open failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // The parent is likes classic rock:
    // https://www.youtube.com/watch?v=lrpXArn3hII
    send_msg(tx, "Tell me now\n");
    ret = read(rx, buffer, BUFFER_SIZE - 1);
    buffer[ret] = 0;
    fputs(buffer, stdout);

    send_msg(tx, "Is he good to you?\n");
    ret = read(rx, buffer, BUFFER_SIZE - 1);
    buffer[ret] = 0;
    fputs(buffer, stdout);

    send_msg(tx, "Can you make you the meals that I do?\n");
    ret = read(rx, buffer, BUFFER_SIZE - 1);
    buffer[ret] = 0;
    fputs(buffer, stdout);

    fprintf(stderr, "[INFO]: closing pipe\n");
    close(tx);
    close(rx);

    unlink(FIFO_PATHNAME);

    fprintf(stderr, "usage: sub <register_pipe_name> <box_name>\n");
    WARN("unimplemented"); // TODO: implement
    return -1;
}
