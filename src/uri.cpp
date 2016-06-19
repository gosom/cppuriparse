#include "uri.h"
#include <algorithm>
#include <iterator>
#include <set>

typedef std::string::const_iterator iterator_t;

const std::string scheme_chars ("abcdefghijklmnopqrstuvwxyz"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "0123456789"
                                "+.-");

bool isValidString(const std::string& s, const std::string& valid) {
    return std::string::npos == s.find_first_not_of(valid);
}


Uri::Uri(const std::string& uri) {
    if (urlsplit(uri) > 1)
        throw (InvalidUriException(uri));
}

Uri::~Uri() {
}

int Uri::urlsplit(const std::string& uri) {
    if (uri.size() == 0)
        return 1;

    iterator_t uri_end = uri.end(); 
    
    iterator_t proto_start = uri.begin();
    iterator_t proto_end = std::find(proto_start, uri_end, ':');
    if (proto_end != uri_end){
        _scheme.assign(proto_start, proto_end);
        if (!isValidString(_scheme, scheme_chars))
            throw(InvalidUriException("Invalid scheme: " + _scheme));
        // move forward 3 positions for the ://
        // the :// is not mandatory alhough for some schemes
        // buts let's pretend that
        proto_end += 3;
        if (proto_end >= uri_end)
            throw(InvalidUriException("Invalid uri: " + uri));
        iterator_t authority_end = std::find(proto_end, uri_end, '/');
        // now parse authority [username:password@host:port]
        iterator_t authentication_end = std::find(proto_end, authority_end, '@');
        iterator_t host_start, host_end;
        if (authentication_end != authority_end) { // we have user:passw
            iterator_t user_end = std::find(proto_end, authentication_end, ':');
            _user.assign(proto_end, user_end);
            _password.assign(user_end+1, authentication_end);
            host_start = authentication_end +1;
        }else {
            host_start = proto_end;
        }
        // now search if there is a port
        iterator_t port_start = std::find(host_start, authority_end, ':');
        if (port_start != authority_end) {
            _port.assign(port_start+1, authority_end);
            host_end = port_start;
        }else
            host_end = authority_end;
        _host.assign(host_start, host_end);
        // query and params now
        iterator_t params_start = std::find(authority_end, uri_end, '?');
        _path.assign(authority_end, params_start);
        iterator_t params_end;
        if (params_start != uri_end){
            params_end = std::find(params_start, uri_end, '#');
        }else
            params_end = uri_end;
        _query.assign(params_start+1, params_end);
        if (params_end != uri_end)
            _fragment.assign(params_end+1, uri_end);
        
    }else {
        return 2;
    }
    return 0;
}

std::string Uri::uri() {
    std::string uri = _scheme + "://";
    if (_user != "") {
        uri += _user;
        if (_password != "")
            uri += ":" + _password;
        uri += "@";
    }
    uri += _host;
    if (_port != "")
        uri += ":" + _port;
    uri += _path;
    if (_query != "")
        uri += "?" + _query;
    if (_fragment != "")
        uri += "#" + _fragment;
    return uri;
}

        
