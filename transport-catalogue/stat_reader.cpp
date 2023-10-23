#include "stat_reader.h"

namespace transport_catalogue::stat_reader {

void ParseAndPrintStat(const TransportCatalogue& transport_catalogue, std::string_view request, std::ostream& output) {
    if (request.substr(0, 4) == "Bus ") {
        std::string_view bus_name = request.substr(4);

        domain::Bus* bus = transport_catalogue.FindBus(bus_name);
        
        if (bus) {
            domain::BusStat route_info = transport_catalogue.GetRouteInfo(bus);

            output << "Bus " << bus->name << ": " << route_info.stop_count << " stops on route, "
                   << route_info.unique_stop_count << " unique stops, "
                   << std::setprecision(6) <<route_info.route_length << " route length" << std::endl;
        } else {
            output << "Bus " << bus_name << ": not found" << std::endl;
        }
    } else if (request.substr(0, 5) == "Stop ") {
        std::string_view stop_name = request.substr(5);

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
    } else {
        output << "Invalid request format" << std::endl;
    }
}

} // transport_catalogue::stat_reader