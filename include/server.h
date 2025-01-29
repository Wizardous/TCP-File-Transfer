#ifndef SERVER_H
#define SERVER_H

#include<iostream>
#include<fstream>
#include<stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>


class Server{
    int PORT;
    int general_socket_descriptor;
    struct sockaddr_in address;
    int new_socket_descriptor;
    int address_length;
    std::fstream file;

    public:
        Server();
        void create_socket();
        void bind_socket();
        void set_listen_set();
        void accept_connection();
        void transmit_file();
};

#endif // SERVER_H