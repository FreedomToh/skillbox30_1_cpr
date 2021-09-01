#include <iostream>
#include <string>
#include <cpr/cpr.h>

class Requests {
private:
    std::string url;
    cpr::Response r;
public:
    Requests(const std::string &val) {
        if (val.length() == 0) return;

        this->url = val;
    }

    bool get() {
        if (this->url.length() == 0) return false;

        std::string tmp_url = this->url+"/get";
        r = cpr::Get(cpr::Url(tmp_url));

        if (r.status_code != 200) {
            this->getErrors();
            return false;
        }

        std::cout << r.text << std::endl;
        return true;
    }

    bool post(cpr::Payload &pl) {
        if (this->url.length() == 0) return false;

        std::string tmp_url = this->url+"/post";
        r = cpr::Post(cpr::Url(tmp_url), cpr::Payload(pl));

        if (r.status_code != 200) {
            this->getErrors();
            return false;
        }

        std::cout << r.text << std::endl;
        return true;
    }

    bool put(cpr::Payload &pl) {
        if (this->url.length() == 0) return false;

        std::string tmp_url = this->url+"/put";
        r = cpr::Put(cpr::Url(tmp_url), cpr::Payload(pl));

        if (r.status_code != 200) {
            this->getErrors();
            return false;
        }

        std::cout << r.text << std::endl;
        return true;
    }

    bool del(cpr::Payload &pl) {
        if (this->url.length() == 0) return false;

        std::string tmp_url = this->url+"/delete";
        r = cpr::Delete(cpr::Url(tmp_url), cpr::Payload(pl));

        if (r.status_code != 200) {
            this->getErrors();
            return false;
        }

        std::cout << r.text << std::endl;
        return true;
    }

    void getErrors() {
        if (r.status_code == 200) return;

        if (r.status_code == 0) {
            std::cerr << r.error.message << std::endl;
        } else if (r.status_code == 400) {
            std::cerr << "Error [" << r.status_code << "] making request" << std::endl;
        }
    }


};

int main() {
    std::cout << "CPR" << std::endl;

    Requests *r = new Requests("http://httpbin.org/");
    cpr::Payload pl = {{"Name", "Anton"},
                       {"City", "Krasnoyarsk"}};
    //r->get();
    while (true){
        std::string request;
        std::getline(std::cin, request);

        if (request == "ext" || request == "EXT") break;
        if (request == "get" || request == "GET") r->get();
        if (request == "post" || request == "POST") {
            r->post(pl);
        }
        if (request == "put" || request == "PUT") {
            r->put(pl);
        }
        if (request == "delete" || request == "PUT") {
            r->del(pl);
        }

        std::cin.clear();
    }

    delete r;
    return 0;
}
