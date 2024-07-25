#pragma once

#include <string>
#include <vector>

// these have to come last
#include <cor.h>
#include <corprof.h>
#undef __valid

namespace appmap {
    struct parameter_info {
        std::string type;
        std::string name;
    };

    struct code_location {
        std::string file_name;
        int line_number;
    };

    struct method_info {
        std::string defined_class;
        std::string method_id;
        code_location location;
        bool is_static;
        std::string return_type;
        std::vector<parameter_info> parameters{};
    };

    inline std::vector<method_info> method_infos;
}
