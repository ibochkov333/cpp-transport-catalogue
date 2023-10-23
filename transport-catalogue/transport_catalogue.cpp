#include "transport_catalogue.h"

namespace transport_catalogue {

void TransportCatalogue::AddStop(domain::Stop stop) {
    stops_.emplace_back(stop);
    stop_indexes_[stops_.back().name] = &stops_.back();
    stop_to_buses_[&stops_.back()];
}

void TransportCatalogue::AddBus(domain::Bus bus) {
    buses_.emplace_back(bus);

    const auto& stops = buses_.back().route;
    for (const auto& stop_ptr : stops) {
        stop_to_buses_.at(stop_ptr).push_back(&buses_.back());
    }

    bus_indexes_[buses_.back().name] = &buses_.back();
}

domain::Stop* TransportCatalogue::FindStop(std::string_view stop_name) const {
    if (stop_indexes_.count(stop_name)) {
        return stop_indexes_.at(stop_name);
    }
    return nullptr;
}

domain::Bus* TransportCatalogue::FindBus(std::string_view bus_name) const {
    if (bus_indexes_.count(bus_name)) {
        return bus_indexes_.at(bus_name);
    }
    return nullptr;
}

domain::BusStat TransportCatalogue::GetRouteInfo(domain::Bus* bus) const {
    domain::BusStat route_info;
    route_info.stop_count = bus->is_circle ? bus->route.size() : 2 * bus->route.size() - 1;

    {
        std::unordered_set<std::string_view> unique_stops;
        for (const auto& stop_ptr : bus->route) {
            unique_stops.insert(std::string_view(stop_ptr->name));
        }
        route_info.unique_stop_count = unique_stops.size();
    }

    route_info.route_length = 0.;

    const auto& bus_route = bus->route;
    const size_t size = bus_route.size();

    for (size_t i = 1; i < size; ++i) {
        double distance = ComputeDistance(bus_route[i - 1]->coordinates, bus_route[i]->coordinates);
        route_info.route_length += distance;
    }

    if (!bus->is_circle) {
        double distance = ComputeDistance(bus_route[size - 1]->coordinates, bus_route[0]->coordinates);
        route_info.route_length += distance;
    }
    
    return route_info;
}

std::set<std::string_view> TransportCatalogue::GetBusesForStop(std::string_view stop_name) const {
    std::set<std::string_view> result;
    domain::Stop* current_stop = FindStop(stop_name);

    if (current_stop) {
        for (const auto& bus : stop_to_buses_.at(current_stop)) {
            result.insert(bus->name);
        }
    }

    return result;
}

} // transport_catalogue