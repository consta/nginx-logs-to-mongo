//
// Created by consta
//

#include "parse.h"
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>

log_record parse_line(std::string line) {
    log_record r;
    std::regex rgx_overall (REGEX_OVERALL);
    std::regex rgx_http_path (REGEX_HTTP_PATH);

    std::smatch m_overall;
    std::smatch m_http_path;
    if(std::regex_search(line, m_overall, rgx_overall)) {
        r.remote_addr = std::string(m_overall[1].str());
        r.remote_user = std::string(m_overall[2].str());
        r.time_local = std::string(m_overall[3].str());

        std::string path_string = std::string(m_overall[4].str());
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

        r.http_referer = std::string(m_overall[7].str());
        r.http_user_agent = std::string(m_overall[8].str());
    }
    else {
        std::cerr << "Failed to parse record [" << line << "]" << std::endl;
    }
    return r;
}

std::list<std::string> load_file(std::string filename) {
    std::list<std::string> result =std::list<std::string>();

    std::ifstream infile(filename);
    if (infile.is_open()) {
        for (std::string line; std::getline(infile, line);) {
            result.push_back(line);
        }
        infile.close();
    }
    else {
        std::cerr << "Failed to open the file " << filename << std::endl;
    }

    return result;
}
