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


int main(int argc, char **argv) {
    if(argc != 3){
        fprintf(stderr, "usage: mbroker <pipename>\n");
        return -1;
    }
    
    
    char register_pipe_name[256];
    fill_string(register_pipe_name, argv[1], 256);

    //int max_sessions = atoi(argv[2]);

    if (unlink(argv[1]) != 0 && errno != ENOENT) {
        fprintf(stderr, "[ERR]: unlink(%s) failed: %s\n", argv[1],
                strerror(errno));
        return -1;
    }

    // Create pipe
    if (mkfifo(argv[1], 0640) != 0) {
        fprintf(stderr, "[ERR]: mkfifo failed: %s\n", strerror(errno));
        return -1;
    }

    int register_pipe = open(argv[1], O_RDONLY);
    if (register_pipe == -1) {
        fprintf(stderr, "[ERR]: open failed: %s\n", strerror(errno));
        return -1;
    }
    tfs_init(NULL);
        

    
    uint8_t opcode;
    char opcode_char[2];
    char named_pipe[256];
    char box_name[32];
    
    
    


    if (read(register_pipe, opcode_char, 1) == -1){
        return -1;
    }
    
    opcode = (uint8_t)strtoul(opcode_char, NULL, 0);
    switch (opcode)
    {
    case(1):
    //pedido de registo de publisher
        if (read(register_pipe ,named_pipe, 256) == -1)
            return -1;
        if (read(register_pipe, box_name, 32) == -1)
            return -1;
        
        //pcq_enqueue();


    break;

    case(2):
    //pedido de registo de subscriber
        if (read(register_pipe,named_pipe, 256) == -1)
            return -1;
        if (read(register_pipe, box_name, 32) == -1)
            return -1;
        
        
    
    break;

    case(3):
    //pedido de criação de caixa
        ssize_t box_request_pipe = read(register_pipe, named_pipe, 256);
        ssize_t box_request_box = read(register_pipe, box_name, 32);
        if (box_request_box != -1 && box_request_pipe != -1){
            int fd = tfs_open(box_name, O_CREAT);
            if(fd != -1){
                int answer_manager = open(named_pipe, O_WRONLY);
                char code[2];
                memcpy(code, "4", 1);
                char return_code[2];
                memcpy(return_code, concatenate(code, "1"), 2);
                char error_message[1024];
                fill_string(error_message, "", 1024);
                char final_message[1026];
                memcpy(final_message, concatenate(return_code, error_message), 1026);

                if(write(answer_manager,final_message, 1026) == -1){
                    return -1;
                }

            }
            else{
                int answer_manager = open(named_pipe, O_WRONLY);
                char code[2];
                memcpy(code, "4", 1);
                char return_code[2];
                memcpy(return_code, concatenate(code, "1"), 2);
                char error_message[1024];
                fill_string(error_message, "the box did not open\n", 1024);
                char final_message[1026];
                memcpy(final_message, concatenate(return_code, error_message), 1026);

                if(write(answer_manager,final_message, 1026) == -1){
                    return -1;
                }
            
            }
        }    
        else{
            int answer_manager = open(named_pipe, O_WRONLY);
                char code[2];
                memcpy(code, "4", 1);
                char return_code[2];
                memcpy(return_code, concatenate(code, "1"), 2);
                char error_message[1024];
                fill_string(error_message, "the pipe was not read correctly", 1024);
                char final_message[1026];
                memcpy(final_message, concatenate(return_code, error_message), 1026);

                if(write(answer_manager,final_message, 1026) == -1){
                    return -1;
                };
        }
        
        
    
    break;

    case(5):
    //pedido de remoção de caixa
        if (read(register_pipe, named_pipe, 256) == -1)
            return -1;
        if (read(register_pipe, box_name, 32) == -1)
            return -1;
        int request_result = tfs_unlink(box_name);
        if(request_result == -1){
            //implementar mensagem de resposta ao pedido
            
        }
        
    
    break;

    // case(6):
    // //resposta ao pedido de remoção de caixa
    //     //return_code é 0 (sucesso) ou 1 (ERRO)
    //     if (read(register_pipe, &return_code, 1) == -1)
    //         return -1;
    //     if (read(register_pipe, error_message, 1024) == -1)
    //         return -1;

    // break;

    // case(7):
    // //pedido de listagem de caixas
    //     if (read(register_pipe, named_pipe, 256) == -1)
    //         return -1;

    // break;

    // case(8):
    // //resposta à listagem de caixas vem em várias mensagens
    // //DUVIDA: meio confuso perguntar ao prof?????
    // break;

    default:
        return -1;
    }

    
        

    
    


    
    return 0;
}   

