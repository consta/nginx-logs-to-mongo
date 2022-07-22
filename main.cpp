#include "parse.h"
#include <iostream>

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::document::value;

void usage() {
    std::cout << "Usage: nginx_logs_to_mongo" << " nginx_log_file [mongodb_uri]" << std::endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        usage();
        return -1;
    }

    std::list<std::string> lines = load_file(argv[1]);
    if (!lines.empty()) {
        mongocxx::instance instance{}; // This should be done only once.
        mongocxx::uri uri("mongodb://localhost:27017");
        mongocxx::client client(uri);
        mongocxx::database db = client["my_database"];
        mongocxx::collection coll = db["nginx_logs"];

        for (std::string line: lines) {
            log_record r = parse_line(line);
            auto builder = document{};
            value doc_value = builder
                    << "remote_addr" << r.remote_addr
                    << "server_name" << r.server_name
                    << "remote_user" << r.remote_user
                    << "time_local" << r.time_local
                    << "method" << r.method
                    << "path" << r.path
                    << "http_version" << r.http_version
                    << "status" << r.status
                    << "body_bytes_sent" << r.body_bytes_sent
                    << "http_referer" << r.http_referer
                    << "http_user_agent" << r.http_user_agent
                    << bsoncxx::builder::stream::finalize;
            bsoncxx::stdx::optional<mongocxx::result::insert_one> result = coll.insert_one(doc_value.view());
        }
        std::cout << "Processed " << lines.size() << " lines" << std::endl;
    }
    return 0;
}

