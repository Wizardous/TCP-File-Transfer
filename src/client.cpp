#include "client.h"
#include "logging.h"

using namespace std;

Client::Client(){
    Logger logger;

    create_socket();
    PORT = 8050;
    logger.debug("PORT: ", PORT);

    address.sin_family = AF_INET;
    address.sin_port = htons( PORT );
    address_length = sizeof(address);
    if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr)<=0) { 
        logger.error("Invalid address");
    }

    create_connection();
    
    file.open("client_text.txt", ios::out | ios::trunc | ios::binary);
    if(file.is_open()){
        logger.info("File downloaded.");
    }
    else{
        logger.error("File creation failed, Exititng.");
        exit(-1);
    }
}

void Client::create_socket(){
    Logger logger;

    if ((general_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        perror("[ERROR] : Socket failed.\n");
        exit(EXIT_FAILURE);
    }
    logger.info("Socket Created Successfully.");
}

void Client::create_connection(){
    Logger logger;

    if (connect(general_socket_descriptor, (struct sockaddr *)&address, sizeof(address)) < 0) { 
        perror("[ERROR] : connection attempt failed.\n");
        exit(EXIT_FAILURE);
    }
    logger.info("Connection Successfull.");
}

void Client::receive_file(){
    Logger logger;
    
    char buffer[1024] = {};
    int valread = read(general_socket_descriptor , buffer, 1024);
    logger.info("Data received {} bytes.", valread);
    logger.info("Saving data to file.");
    
    file<<buffer;
    logger.info("File Saved.");
}


int main(){
    Client C;
    C.receive_file();
    return 0;
}