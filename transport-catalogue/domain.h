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
    double route_length = 0.;
    double curvature = 0.;
};

struct FromToDistance {
    std::string_view from;
    std::string_view to;
    uint64_t distance;
};

struct PairOfStopPtrHasher {
    size_t operator()(const std::pair<Stop*, Stop*>& p) const {
        auto h1 = ptr_hasher(p.first);
        auto h2 = ptr_hasher(p.second);
        return h1 + h2 * 43;
    }

private:
    std::hash<const void*> ptr_hasher;
};

} // transport_catalogue::domain