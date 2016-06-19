#include <iostream>
#include "uri.h"

int main(int argc, char* argv[]) {
    try{
        Uri uri(argv[1]);
        std::cout << "scheme: " << uri.scheme() << std::endl;
        std::cout << "user: " << uri.user() << std::endl;
        std::cout << "password: " << uri.password() << std::endl;
        std::cout << "host: " << uri.host() << std::endl;
        std::cout << "port: " << uri.port() << std::endl;
        std::cout << "path: " << uri.path() << std::endl;
        std::cout << "query: " << uri.query() << std::endl;
        std::cout << "fragment: " << uri.fragment() << std::endl;
        std::cout << "uri: " << uri.uri() << std::endl;
    }catch (InvalidUriException& e){
        std::cout << "Invalid url: " << e.getMessage() << std::endl;
    }

    return 0;
}
