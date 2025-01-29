#ifndef CLIENT_H
#define CLIENT_H

#include<iostream>
#include<fstream>
#include<stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>


class Client{
    int PORT;
    int general_socket_descriptor;
    struct sockaddr_in address;
    int address_length;
    std::fstream file;

    public:
        Client();
        void create_socket();
        void create_connection();
        void receive_file();
};

#endif // CLIENT_H