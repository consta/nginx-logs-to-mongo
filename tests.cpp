//
// Created by Kanstantin Kachanouski on 21.07.22.
//
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include "types.h"
#define REGEX_OVERALL "^(\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})\\ \\-\\ (.+)\\ \\[(.+)\\]\\ \\\"(.+)\\\"\\ (\\d{3})\\ (.+)\\ \\\"(.+)\\\"\\ \\\"(.+)\\\"$"
#define REGEX_HTTP_PATH "(\\w+)\\ (.+)\\ HTTP\\/(\\d\\.\\d)"


using std::string;
using std::list;
using std::cout;
using std::endl;
using std::cerr;


log_record parse_line(string line) {
    log_record r;
    std::regex rgx_overall (REGEX_OVERALL);
    std::regex rgx_http_path (REGEX_HTTP_PATH);

    std::smatch m_overall;
    std::smatch m_http_path;
    if(std::regex_search(line, m_overall, rgx_overall)) {
        r.remote_addr = string(m_overall[1].str());
        r.remote_user = string(m_overall[2].str());
        r.time_local = string(m_overall[3].str());

        string path_string = string(m_overall[4].str());
        if (std::regex_search(path_string, m_http_path, rgx_http_path)) {
            r.method = m_http_path[1].str();
            r.path = m_http_path[2].str();
            r.http_version = m_http_path[3].str();
        }
        else {
            r.path = path_string;
        }

        std::istringstream ss(m_overall[5].str());
        ss >> r.status;

        ss.str(m_overall[6].str());
        ss >> r.body_bytes_sent;

        r.http_referer = string(m_overall[7].str());
        r.http_user_agent = string(m_overall[8].str());
    }
    else {
        cerr << "Failed to parse record [" << line << "]" << endl;
    }
    return r;
}

list<string> load_file(string filename) {
    list<string> result = std::list<std::string>();

    std::ifstream infile( filename);
    if (infile.is_open()) {
        for (std::string line; std::getline(infile, line);) {
            result.push_back(line);
        }
        infile.close();
    }
    else {
        cerr << "Failed to open the file " << filename << endl;
    }

    return result;
}

TEST_CASE("nginx log parsed", "[parsing the log]") {
    list<string> lines = load_file("../resources/access.log");
    list<log_record> records = list<log_record>();
    for (string line: lines) {
        log_record r = parse_line(line);
        records.push_back(r);
    }

    REQUIRE(lines.size() > 0);
    REQUIRE(lines.size() == records.size());
}