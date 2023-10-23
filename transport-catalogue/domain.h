#pragma once

#include <deque>
#include <string>

#include "geo.h"

namespace transport_catalogue::domain {

struct Stop {
    std::string name;
    geo::Coordinates coordinates;
};

struct Bus {
    std::string name;
    bool is_circle;
    std::deque<Stop*> route;
};

struct BusStat {
    uint64_t stop_count = 0;
    uint64_t unique_stop_count = 0;
    double route_length = 0;
};

} // transport_catalogue::domain