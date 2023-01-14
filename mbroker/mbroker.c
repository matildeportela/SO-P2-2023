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


char* fillString(char* string, size_t tamanho){
    if(sizeof(string) < tamanho){
        for(int i = sizeof(string); i < tamanho; i++ ){
            string[i] = '\0';
        
        }
    }
    
    return string;

}


int main(int argc, char **argv) {
    if(argc != 3){
        fprintf(stderr, "usage: mbroker <pipename>\n");
        return -1;
    }
    
    
    char register_pipe_name[256];



    strcpy(register_pipe_name,fillString(argv[1], 256));



    //int max_sessions = atoi(argv[2]);

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
        
    close(rx);
    
    uint8_t opcode;
    char opcode_char;
    char named_pipe[256];
    char box_name[32];
    int return_code;
    char error_message[1034];
    char c;


    read(rx, &opcode_char, 1);
    opcode = (uint8_t) opcode_char;
    
    switch (opcode)
    {
    case(1):
    //pedido de registo de publisher
        if (read(rx ,named_pipe, 256) == -1)
            return -1;
        if (read(rx, box_name, 32) == -1)
            return -1;
        //pcq_enqueue();


    break;

    case(2):
    //pedido de registo de subscriber
        if (read(rx,named_pipe, 256) == -1)
            return -1;
        if (read(rx, box_name, 32) == -1)
            return -1;
    
    break;

    case(3):
    //pedido de criação de caixa
        if (read(rx,named_pipe, 256) == -1)
            return -1;
        if (read(rx, box_name, 32) == -1)
            return -1;
        
    break;

    case(4):
    //resposta ao pedido de criação de caixa
        //return_code é 0 (sucesso) ou 1 (ERRO)
        if (read(rx, &c, 1) == -1)
            return -1;
        return_code = atoi(&c);
        if (read(rx, error_message, 1024) == -1)
            return -1;
        
    
    break;

    case(5):
    //pedido de remoção de caixa
        if (read(rx, named_pipe, 256) == -1)
            return -1;
        if (read(rx, box_name, 32) == -1)
            return -1;
    
    break;

    case(6):
    //resposta ao pedido de remoção de caixa
        //return_code é 0 (sucesso) ou 1 (ERRO)
        if (read(rx, &return_code, 1) == -1)
            return -1;
        if (read(rx, error_message, 1024) == -1)
            return -1;

    break;

    case(7):
    //pedido de listagem de caixas
        if (read(rx, named_pipe, 256) == -1)
            return -1;

    break;

    case(8):
    //resposta à listagem de caixas vem em várias mensagens
    //DUVIDA: meio confuso perguntar ao prof?????
    break;
    }
    



    return 0;
}
