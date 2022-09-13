#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    //Comprobamos que la sintaxis es correcta
    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    //Abrimos el socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    //Conectamos con el servidor
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR connecting");
    }
    while (1) //Bucle infinito
    {
        printf("Please enter the message: ");
        bzero(buffer, 256);
        fgets(buffer, 255, stdin); //Carga el valor de la entrada en el buffer
        n = write(sockfd, buffer, strlen(buffer)); //Escribimos en el socket la entrada
        if (n < 0)
        {
            error("ERROR writing to socket");
        }
        bzero(buffer, 256); //Vaciamos el buffer
        n = read(sockfd, buffer, 255); //Leemos la respuesta del seridor
        if (n < 0)
        {
            error("ERROR reading from socket");
        }
        printf("%s\n", buffer); //Mostramos por pantalla la respuesta
    }
    return 0;
}
