#include <string>
#include <exception>

class InvalidUriException {

public:
   InvalidUriException(const std::string& msg) : msg_(msg) {}
  ~InvalidUriException( ) {}

  std::string getMessage( ) const {return (msg_);}
private:
  std::string msg_;
};


class Uri {

    public:

        Uri(const std::string& uri);
        Uri(const Uri& other);
        ~Uri();
        
        std::string uri(); 
        std::string scheme() { return _scheme; }
        std::string user() { return _user; }
        std::string password() { return _password; }
        std::string host() { return _host; }
        std::string port() { return _port; }
        std::string path() { return _path; }
        std::string query() { return _query; }
        std::string fragment() { return _fragment; }

    private:
//scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
        std::string _scheme;
        std::string _user;
        std::string _password;
        std::string _host;
        std::string _port;
        std::string _path;
        std::string _query;
        std::string _fragment;
        
        int urlsplit(const std::string& uri);

};
