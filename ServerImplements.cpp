//
// Created by magshimim on 8.1.2020.
//

#include "ServerImplements.h"
/*
 * open server that accept one client every time.
 * */
void MySerialServer::open(int port,ClientHandler& clientHandler) {
    this->clientHandler = &clientHandler;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        throw "Could not create a socket";
    }
    this->socketfd = socketfd;

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    this->address = address;
    //the actual bind command

    if (bind(socketfd, (struct sockaddr *) &this->address, sizeof(this->address)) == -1) {
        // throw "Could not bind the socket to an IP";
        throw "Could not bind the socket to an IP";
    }


    //making socket listen to the port
    if (listen(this->socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        throw "Error during listening command";
    } else {
        std::cout<<"Server is now listening ..."<<std::endl;
    }


    startThread();
}


/*
 * accept one client and do operation according clientHandler
 * */
void MySerialServer::startThreadOPeration() {

    while (!side_server::stop) {

        // accepting a client
        int client_socket = accept(this->socketfd, (struct sockaddr *) &this->address,
                                   (socklen_t *) &this->address); // Return -1
        if (client_socket == -1) {
            throw "Error accepting client";
        }
        clientHandler->handleClient(this->socketfd, client_socket);
    }

}
/*
 * start thread of accepting clients
 * */
void MySerialServer::startThread() {
    acceptClient = std::thread(&MySerialServer::startThreadOPeration,this);
}
/*
 * destractor - close the socket and the thread
 * */
MySerialServer::~MySerialServer(){
    close(this->socketfd);
    if(acceptClient.joinable()){
        this->acceptClient.join();
    }
}