#include <iostream>
#include <string>
#include "ServerImplements.h"
using namespace std;



int main() {
    MySerialServer serialServer;
    ClientHandler* clientHandler = new GetMatrix <string, string>();
    try{
        serialServer.open(5600, *clientHandler);
    } catch( const char* e){
        cout<<e<<endl;
    }

    std::cout << "Hello, World!" << std::endl;

    return 0;
}
