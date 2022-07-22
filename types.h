//
// Created by Kanstantin Kachanouski on 22.07.22.
//

#ifndef NGINX_LOGS_TO_MONGO_TYPES_H
#define NGINX_LOGS_TO_MONGO_TYPES_H
#include <string>

using std::string;

struct log_record {
    string remote_addr;
    string server_name;
    string remote_user;
    string time_local;
    string method;
    string path;
    string http_version;
    int status;
    long body_bytes_sent;
    string http_referer;
    string http_user_agent;
};

#endif //NGINX_LOGS_TO_MONGO_TYPES_H
