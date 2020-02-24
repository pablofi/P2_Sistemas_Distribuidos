//Practica 2 Sockeets, Sistemas Distribuidos
//Pablo Martinez Tellez

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, new_socket1, valread, valread1;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Saludos desde el Server de 2 mensajes";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
   {
	perror("socket failed");
	exit(EXIT_FAILURE);
   }

   //forcefully attaching socket to the port 8080
   if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
   {
	perror("setsockopt");
	exit(EXIT_FAILURE);   
   }
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons( PORT );

   //fORCEFFFFULLY ATTACHING SOCKET TO THE PORT 8080
   if (bind(server_fd , (struct sockaddr *)&address , sizeof(address))<0)
   {
      perror("bind failed");
      exit(EXIT_FAILURE);
   }
   if (listen(server_fd, 3) < 0)
   {
     perror("listen");
     exit(EXIT_FAILURE);
   }
   if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
   {
     perror("accept");
     exit(EXIT_FAILURE);
   }
   if ((new_socket1 = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
   {
     perror("accept");
     exit(EXIT_FAILURE);
   }
   valread = read( new_socket , buffer , 1024);
   valread1 = read( new_socket1, buffer,1024 );
   printf("%s\n", buffer);
   send(new_socket , hello , strlen(hello) , 0);
   printf("Hola, mensaje 1 enviado\n");
   send(new_socket1, hello, strlen(hello), 0);
   printf("Hola, mensaje 2 enviado\n");
   return 0;
}
