#include "socket_server.h"

int listen_fd, fdmax, newfd, nbytes, i, j, k;
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
                    fprintf(stderr, "Dead");
                    close(i);
                    FD_CLR(i, &master);
                } else {
                    //Recieved data would be dealt with here but I can't make flash send it for some reasons
                }
            }
        }
    }
}

void write_socket(char *str)
{
     //send data to erryone
    for(k = 0; k<= fdmax; k++)
    {
        if(FD_ISSET(k, &master))
        {
            if(k != listen_fd) //erryone except us
            {
                if(write(k, str, strlen(str)+1) == -1)
                {
                    fprintf(stderr, "Failed to write.");
                }
            }
        }
    }
}
