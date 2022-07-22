//
// Created by consta
//
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <iterator>
#include <list>
#include <string>
#include "parse.h"

TEST_CASE("nginx log parsed", "[parsing the log]") {
    std::list<std::string> lines = load_file("../resources/access.log");
    std::list<log_record> records = std::list<log_record>();
    for (std::string line: lines) {
        log_record r = parse_line(line);
        records.push_back(r);
    }

    REQUIRE(lines.size() > 0);
    REQUIRE(lines.size() == records.size());
}
