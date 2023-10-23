#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iterator>
#include <iostream>

#include "geo.h"
#include "transport_catalogue.h"

namespace transport_catalogue::input_reader {

struct CommandDescription {
    explicit operator bool() const {
        return !command.empty();
    }

    bool operator!() const {
        return !operator bool();
    }

    std::string command;      
    std::string id;          
    std::string description;  
};

class InputReader {
public:
    void ParseLine(std::string_view line);

    void ApplyCommands(TransportCatalogue& catalogue) const;

private:
    std::vector<CommandDescription> commands_;
};

} // transport_catalogue::input_reader