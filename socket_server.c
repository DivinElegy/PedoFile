#include "socket_server.h"

int listen_fd, fdmax, newfd, nbytes, i;
char buf[256];
fd_set master;
fd_set read_fds;
struct timeval tv;
 
void start_socket_server(int port)
{
    struct sockaddr_in servaddr;
 
    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    bzero( &servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(port);

    tv.tv_sec = 0;
    tv.tv_usec = 100;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(listen_fd, 10);
 
    FD_SET(listen_fd, &master);
    fdmax = listen_fd;
}

void update_clients()
{
    read_fds = master;
    select(fdmax+1, &read_fds, NULL, NULL, &tv);

    for(i = 0; i<= fdmax; i++)
    {
        if (FD_ISSET(i, &read_fds))
        {
            if (i == listen_fd)  //new connection
            {
                newfd = accept(listen_fd, (struct sockaddr *) NULL, NULL);

		if (newfd != -1)
                {
                    fprintf(stderr, "New connection!");
                    FD_SET(newfd, &master);

                    if (newfd > fdmax) {
                        fdmax = newfd;
                    }
                }
            } else {
                nbytes = recv(i, buf, sizeof buf, 0);

                if(nbytes <= 0)
                {
                    fprintf(stderr, "Ded");
                    close(i);
                    FD_CLR(i, &master);
                }
            }
         }
     }
}

void write_socket(char *str)
{
     //send data to erryone
    for(i = 0; i<= fdmax; i++)
    {
        if(FD_ISSET(i, &master))
        {
            if(i != listen_fd) //erryone except us
            {
                write(i, str, strlen(str)+1);
            }
        }
    }
}
