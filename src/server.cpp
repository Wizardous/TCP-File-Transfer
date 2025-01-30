#include "server.h"
#include "logging.h"

using namespace std;

Server::Server(){
    Logger logger;

    PORT = 8050;

    logger.debug("PORT: ", PORT);

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT );
    address_length = sizeof(address);

    create_socket();
    bind_socket();
    set_listen_set();
    accept_connection();

    file.open("./Data/Server/server_text.txt", ios::in | ios::binary);
    if(file.is_open()){
        logger.info("File is ready to Transmit.");
    }
    else{
        logger.error("File loading failed, Exititng.");
        exit(-1);
    }
}

void Server::create_socket(){
    Logger logger;
    if ((general_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        perror("[ERROR] : Socket failed");
        exit(EXIT_FAILURE);
    }
    logger.info("Socket Created Successfully.");
}

void Server::bind_socket(){
    Logger logger;
    if (bind(general_socket_descriptor, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("[ERROR] : Bind failed");
        exit(EXIT_FAILURE);
    }
    logger.info("Bind Successful.");
}

void Server::set_listen_set(){
    Logger logger;
    if (listen(general_socket_descriptor, 3) < 0) {
        perror("[ERROR] : Listen");
        exit(EXIT_FAILURE);
    }
    logger.info("Socket in Listen State (Max Connection Queue: 3)");
}

void Server::accept_connection(){
    Logger logger;
    if ((new_socket_descriptor = accept(general_socket_descriptor, (struct sockaddr *)&address, (socklen_t*)&address_length))<0) { 
        perror("[ERROR] : Accept");
        exit(EXIT_FAILURE);
    }
    logger.info("Connected to Client.");
}

void Server::transmit_file(){
    Logger logger;
    std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    logger.info("Transmission Data Size {} Bytes.", contents.length());
    logger.info("Sending file...");

    int bytes_sent = send(new_socket_descriptor , contents.c_str() , contents.length() , 0 );
    logger.info("Transmitted Data Size {} Bytes.", bytes_sent);
    logger.info("File Transfer Complete.");
}


int main(){
    Server S;
    S.transmit_file();
    return 0;
}
