/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    //Comprobamos si la sintaxis es correcta
    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    //Abrimos el socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
    {
        error("ERROR on binding");
    }
    //Escuchamos las peticiones de conexión de los clientes
    listen(sockfd, 2);
    clilen = sizeof(cli_addr);
    //Aceptamos la conexión
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
    {
        error("ERROR on accept");
    }
    bzero(buffer, 256);

    //APLICACIÓN
    while (1) //Bucle infinito
    {
        n = read(newsockfd, buffer, 255); //Leemos el mensaje del cliente
        if (n < 0)
        {
            error("ERROR reading from socket");
        }
        morse(newsockfd, buffer);
        sleep(1); //Esperamos 1 seg
    }
    return 0;
}

void morse(int newsockfd, char buffer[256])
{
    int n;
    char res[256 * 6] = " ";
    for (int i = 0; i < 256; i++)
    {
        //Traducimos el mensaje letra a letra
        letras(buffer[i], res);
    }
    //Informamos al cliente
    n = write(newsockfd, "I got your message: ", 20);
    if (n < 0)
    {
        error("ERROR writing to socket");
    }
    //Enviamos al cliente el texto codificado
    n = write(newsockfd, res, strlen(res));
    if (n < 0)
    {
        error("ERROR writing to socket");
    }
    //Reproducimos el mensaje morse
    for (int i = 0; i < strlen(res); i++)
    {
        switch (res[i])
        {
        case '.': //pitido corto
            //beep(750, 400);

            break;
        case '-': //pitido largo
            //beep(750, 800);
            break;
        }
    }
}

void letras(char letra, char res[])
{
    char aux[6];
    switch (letra)
    {
    case 'a':
        strcpy(aux, ".-");
        strcat(res, aux);
        break;
    case 'b':
        strcpy(aux, "-...");
        strcat(res, aux);
        break;
    case 'c':
        strcpy(aux, "-.-.");
        strcat(res, aux);
        break;
    case 'd':
        strcpy(aux, "-..");
        strcat(res, aux);
        break;
    case 'e':
        strcpy(aux, ".");
        strcat(res, aux);
        break;
    case 'f':
        strcpy(aux, "..-.");
        strcat(res, aux);
        break;
    case 'g':
        strcpy(aux, "--.");
        strcat(res, aux);
        break;
    case 'h':
        strcpy(aux, "....");
        strcat(res, aux);
        break;
    case 'i':
        strcpy(aux, "..");
        strcat(res, aux);
        break;
    case 'j':
        strcpy(aux, ".---");
        strcat(res, aux);
        break;
    case 'k':
        strcpy(aux, "-.-");
        strcat(res, aux);
        break;
    case 'l':
        strcpy(aux, ".-..");
        strcat(res, aux);
        break;
    case 'm':
        strcpy(aux, "--");
        strcat(res, aux);
        break;
    case 'n':
        strcpy(aux, "-.");
        strcat(res, aux);
        break;
    case 'o':
        strcpy(aux, "---");
        strcat(res, aux);
        break;
    case 'p':
        strcpy(aux, ".--.");
        strcat(res, aux);
        break;
    case 'q':
        strcpy(aux, "--.-");
        strcat(res, aux);
        break;
    case 'r':
        strcpy(aux, ".-.");
        strcat(res, aux);
        break;
    case 's':
        strcpy(aux, "...");
        strcat(res, aux);
        break;
    case 't':
        strcpy(aux, "-");
        strcat(res, aux);
        break;
    case 'u':
        strcpy(aux, "..-");
        strcat(res, aux);
        break;
    case 'v':
        strcpy(aux, "...-");
        strcat(res, aux);
        break;
    case 'w':
        strcpy(aux, ".--");
        strcat(res, aux);
        break;
    case 'x':
        strcpy(aux, "-..-");
        strcat(res, aux);
        break;
    case 'y':
        strcpy(aux, "-.--");
        strcat(res, aux);
        break;
    case 'z':
        strcpy(aux, "--..");
        strcat(res, aux);
        break;
    }
}