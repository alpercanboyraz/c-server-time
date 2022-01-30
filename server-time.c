#include<stdio.h>
#include<string.h>    // for strlen
#include<sys/socket.h>
#include<arpa/inet.h> // for inet_addr
#include<unistd.h>    // for write
#include<stdlib.h>
int main(int argc, char *argv[])
{
    int socket_desc , new_socket , c;
    struct sockaddr_in server , client;
    char *message;
    char return_message[1000]; 
    char substr[1000];
    char final_str[1000];
    
    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        puts("Could not create socket");
        return 1;
}
     
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);
     
    // Bind
    if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("Bind failed");
        return 1;
    }
    puts("Socket is binded");
     
    // Listen
    listen(socket_desc, 3);
     
    // Accept and incoming connection
    puts("Waiting for incoming connections...");
    
    c = sizeof(struct sockaddr_in);
    
    while( new_socket = 
           accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c) )
    {
        puts("Connection accepted");
        message = "Hello client, I received your connection. See you\n\n";
        write(new_socket, message, strlen(message));
        
        int inputSize = recv(new_socket, return_message , 1000 , 0)-2;
        
        char new_input[inputSize + 1];
        int l = 0;
        
        for (l = 9; l < inputSize; l++)
        {
            new_input[l-9] = return_message[l];
        }
        new_input[l-9] = '\0';
       
        if(return_message[0] == 'G' && (return_message[1]) == 'E' && (return_message[2]) == 'T' && (return_message[3]) == '_' && (return_message[4]) == 'D'
        && (return_message[5]) == 'A' && (return_message[6]) == 'T' && (return_message[7]) == 'E'){
            
            
            substr[0] = 'd';
            substr[1] = 'a';
            substr[2] = 't';
            substr[3] = 'e';
           
            substr[4] = ' ';
            substr[5] = '+';
            substr[6] = '\"';

         
            strcat(substr,new_input);
            strcat(substr,"\"");
           
           
        }       
        else{
            char false_str[] = "Incorrect Request";    
            puts(false_str);
        }


         //printf("%s\n",substr);
        FILE *fp;
        int status;
        char path[1000];


        fp = popen(substr, "r");
        if (fp == NULL){

            perror("fp");
            exit(1);

        }
        char *readPath;
        char final_out[1000];
       
        while (fgets(path, 1000, fp) != NULL){
            //strcpy(final_out,readPath);
            
            for (int i = 0; i < strlen(path); i++)
            {
                final_out[i] = path[i];
            }
        }
        
        final_out[strlen(final_out)] = '\0';
        int control = 1;
        for(int k = 0;k<strlen(final_out); k++){
            if(final_out[k] == '%'){
                printf("INCORRECT\n");
                control = 0;
                return 1;
            }
           }
        if(control == 1){
            printf("%s",final_out);
        }
    }  
    close(new_socket);
    close(socket_desc);
    return 0;
    }


