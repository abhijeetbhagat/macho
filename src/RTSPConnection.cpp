#include "../include/RtpConnection.h"
#include <iostream>

RTSPConnection::RTSPConnection(const std::string& server, uint16_t port) : _server(server), _port(port){ 
}

RTSPConnection::~RTSPConnection(){
}


