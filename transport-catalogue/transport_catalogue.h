#pragma once

#include <algorithm>
#include <deque>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include "geo.h"
#include "domain.h"

namespace transport_catalogue {

class TransportCatalogue {
public:
    explicit TransportCatalogue() = default;

    void AddStop(const domain::Stop& stop); 

    void AddBus(const domain::Bus& bus); 

    domain::Stop* FindStop(std::string_view stop_name) const; 

    domain::Bus* FindBus(std::string_view bus_name) const ;  

    domain::BusStat GetRouteInfo(domain::Bus* bus) const; 

    std::set<std::string_view> GetBusesForStop(std::string_view stop_name) const;

    void AddStopsDistance(const domain::FromToDistance& stops_distance);

    uint64_t FindDistance(domain::Stop* start, domain::Stop* destination) const;

private:
    std::deque<domain::Bus> buses_;  
    std::deque<domain::Stop> stops_; 
    std::unordered_map<std::string_view, domain::Bus*> bus_indexes_; 
    std::unordered_map<std::string_view, domain::Stop*> stop_indexes_; 
    std::unordered_map<domain::Stop*, std::deque<domain::Bus*>> stop_to_buses_;
    std::unordered_map<std::pair<domain::Stop*, domain::Stop*>, uint64_t, domain::PairOfStopPtrHasher> stops_distances_; 
};

} // transport_catalogue