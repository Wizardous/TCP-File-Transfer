#include "server.h"

using namespace std;

Server::Server(){
    create_socket();
    PORT = 8050;

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT );
    address_length = sizeof(address);

    bind_socket();
    set_listen_set();
    accept_connection();

    file.open("./Data/Server/server_text.txt", ios::in | ios::binary);
    if(file.is_open()){
        cout<<"[LOG] : File is ready to Transmit.\n";
    }
    else{
        cout<<"[ERROR] : File loading failed, Exititng.\n";
        exit(EXIT_FAILURE);
    }
}

void Server::create_socket(){
    if ((general_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        perror("[ERROR] : Socket failed");
        exit(EXIT_FAILURE);
    }
    cout<<"[LOG] : Socket Created Successfully.\n";
}

void Server::bind_socket(){
    if (bind(general_socket_descriptor, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("[ERROR] : Bind failed");
        exit(EXIT_FAILURE);
    }
    cout<<"[LOG] : Bind Successful.\n";
}

void Server::set_listen_set(){
    if (listen(general_socket_descriptor, 3) < 0) {
        perror("[ERROR] : Listen");
        exit(EXIT_FAILURE);
    }
    cout<<"[LOG] : Socket in Listen State (Max Connection Queue: 3)\n";
}

void Server::accept_connection(){
    if ((new_socket_descriptor = accept(general_socket_descriptor, (struct sockaddr *)&address, (socklen_t*)&address_length))<0) { 
        perror("[ERROR] : Accept");
        exit(EXIT_FAILURE);
    }
    cout<<"[LOG] : Connected to Client.\n";
}

void Server::transmit_file(){
    std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    cout<<"[LOG] : Transmission Data Size "<<contents.length()<<" Bytes.\n";

    cout<<"[LOG] : Sending...\n";

    int bytes_sent = send(new_socket_descriptor , contents.c_str() , contents.length() , 0 );
    cout<<"[LOG] : Transmitted Data Size "<<bytes_sent<<" Bytes.\n";

    cout<<"[LOG] : File Transfer Complete.\n";
}


int main(){
    Server S;
    S.transmit_file();
    return 0;
}
