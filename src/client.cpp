#include "client.h"

using namespace std;

Client::Client(){
    create_socket();
    PORT = 8050;

    address.sin_family = AF_INET;
    address.sin_port = htons( PORT );
    address_length = sizeof(address);
    if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr)<=0) { 
        cout<<"[ERROR] : Invalid address\n";
    }

    create_connection();
    
    file.open("client_text.txt", ios::out | ios::trunc | ios::binary);
    if(file.is_open()){
        cout<<"[LOG] : File Creted.\n";
    }
    else{
        cout<<"[ERROR] : File creation failed, Exititng.\n";
        exit(EXIT_FAILURE);
    }
}

void Client::create_socket(){
    if ((general_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        perror("[ERROR] : Socket failed.\n");
        exit(EXIT_FAILURE);
    }
    cout<<"[LOG] : Socket Created Successfully.\n";
}

void Client::create_connection(){
    if (connect(general_socket_descriptor, (struct sockaddr *)&address, sizeof(address)) < 0) { 
        perror("[ERROR] : connection attempt failed.\n");
        exit(EXIT_FAILURE);
    }
    cout<<"[LOG] : Connection Successfull.\n";
}

void Client::receive_file(){
    char buffer[1024] = {};
    int valread = read(general_socket_descriptor , buffer, 1024);
    cout<<"[LOG] : Data received "<<valread<<" bytes\n";
    cout<<"[LOG] : Saving data to file.\n";
    
    file<<buffer;
    cout<<"[LOG] : File Saved.\n";
}


int main(){
    Client C;
    C.receive_file();
    return 0;
}