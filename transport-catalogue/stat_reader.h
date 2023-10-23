#pragma once

#include <iostream>
#include <iomanip> 
#include <sstream> 
#include <set>
#include <iosfwd>
#include <string_view>
#include <ios>

#include "transport_catalogue.h"

namespace transport_catalogue::stat_reader {

void ParseAndPrintStat(const TransportCatalogue& tansport_catalogue, std::string_view request, std::ostream& output);

void PrintBusStat(const TransportCatalogue& tansport_catalogue, std::string_view bus_name, std::ostream& output);

void PrintStopStat(const TransportCatalogue& tansport_catalogue, std::string_view stop_name, std::ostream& output);

} // transport_catalogue::stat_reader