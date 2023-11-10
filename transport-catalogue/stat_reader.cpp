#include "stat_reader.h"

namespace transport_catalogue::stat_reader {

void ParseAndPrintStat(const TransportCatalogue& transport_catalogue, std::string_view request, std::ostream& output) {
    if (request.substr(0, 4) == "Bus ") {
        std::string_view bus_name = request.substr(4);
        PrintBusStat(transport_catalogue, bus_name, output);
    } else if (request.substr(0, 5) == "Stop ") {
        std::string_view stop_name = request.substr(5);
        PrintStopStat(transport_catalogue, stop_name, output);      
    } else {
        output << "Invalid request format" << std::endl;
    }
}

void PrintBusStat(const TransportCatalogue& transport_catalogue, std::string_view bus_name, std::ostream& output) {
    domain::Bus* bus = transport_catalogue.FindBus(bus_name);
        
    if (bus) {
        domain::BusStat route_info = transport_catalogue.GetRouteInfo(bus);

        output << "Bus " << bus->name << ": " << route_info.stop_count << " stops on route, "
                << route_info.unique_stop_count << " unique stops, "
                << std::setprecision(6) <<route_info.route_length << " route length, "
                << route_info.curvature << "curvature " << std::endl;
    } else {
        output << "Bus " << bus_name << ": not found" << std::endl;
    }
}

void PrintStopStat(const TransportCatalogue& transport_catalogue, std::string_view stop_name, std::ostream& output) {
    if (transport_catalogue.FindStop(stop_name) == nullptr) {
        output << "Stop " << stop_name << ": not found" << std::endl;
    } else {
        std::set<std::string_view> buses_names = transport_catalogue.GetBusesForStop(stop_name);

        if (buses_names.size() == 0) {
            output << "Stop " << stop_name << ": no buses" << std::endl;
        } else {
            output << "Stop " << stop_name << ": buses ";
            for (const auto& name : buses_names) {
                output << name << " ";
            }
            output << std::endl;
        }
    }  
}

} // transport_catalogue::stat_reader