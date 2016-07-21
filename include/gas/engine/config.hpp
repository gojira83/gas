#ifndef GAS_ENGINE_CONFIG_HPP
#define GAS_ENGINE_CONFIG_HPP

#include <string>

namespace gas {

    namespace engine {

        struct Config {
            struct {
                unsigned inputs                 = 2;
                unsigned outputs                = 1;
                unsigned max_connection_age     = 50;
                float    first_move_factor      = 0.1;
                float    neighbours_move_factor = 0.1;
                float    sqr_phi                = 0.25;
                unsigned cycles_per_spawn       = 10;
                float    error_decrease         = 0.8;
            } gas;

            struct {
                std::string format;
                std::string path;
            } storage;

            Config() {}

            virtual ~Config() {}
        };
    }
}

#endif /* GAS_ENGINE_CONFIG_HPP */
