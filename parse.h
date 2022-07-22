//
// Created by consta
//

#ifndef NGINX_LOGS_TO_MONGO_PARSE_H
#define NGINX_LOGS_TO_MONGO_PARSE_H

#include <string>
#include <list>

#define REGEX_OVERALL "^(\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})\\ \\-\\ (.+)\\ \\[(.+)\\]\\ \\\"(.+)\\\"\\ (\\d{3})\\ (.+)\\ \\\"(.+)\\\"\\ \\\"(.+)\\\"$"
#define REGEX_HTTP_PATH "(\\w+)\\ (.+)\\ HTTP\\/(\\d\\.\\d)"

struct log_record {
    std::string remote_addr;
    std::string server_name;
    std::string remote_user;
    std::string time_local;
    std::string method;
    std::string path;
    std::string http_version;
    int status;
    long body_bytes_sent;
    std::string http_referer;
    std::string http_user_agent;
};

extern log_record parse_line(std::string line);

extern std::list<std::string> load_file(std::string filename);

#endif //NGINX_LOGS_TO_MONGO_PARSE_H
