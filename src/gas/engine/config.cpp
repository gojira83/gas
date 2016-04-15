/**
 * Config.cpp
 *
 *  Created on: 10.03.2014
 *        Author: code.ninja
 */

#include <gas/engine/config.hpp>

#include <fstream>

#include <yaml-cpp/yaml.h>
#include <gas/engine/common.hpp>


namespace gas {

    namespace engine {

        logging::Logger Config::log("gas.engine.config");


        Config::Config() {
            log.debug("create configuration");
        }

        void Config::from_yaml(YAML::Node node) {

            if(node["inputs"]) {
                inputs = node["inputs"].as<unsigned>();
            }

            if(node["outputs"]) {
                outputs = node["outputs"].as<unsigned>();
            }

            if(node["max_connection_age"]) {
                max_connection_age = node["max_connection_age"].as<unsigned>();
            }

            if(node["first_move_factor"]) {
                first_move_factor = node["first_move_factor"].as<float>();
            }

            if(node["neighbours_move_factor"]) {
                neighbours_move_factor = node["neighbours_move_factor"].as<float>();
            }

            if(node["sqr_phi"]) {
                sqr_phi = node["sqr_phi"].as<float>();
            }

            if(node["cycles_per_spawn"]) {
                cycles_per_spawn = node["cycles_per_spawn"].as<unsigned>();
            }

            if(node["error_decrease"]) {
                error_decrease = node["error_decrease"].as<float>();
            }

            if(node["name"]) {
                name = node["name"].as<std::string>();
            }
            else {
                name = get_random_name();
            }
        }

        YAML::Node Config::to_yaml() {
            YAML::Node node;

            node["inputs"]                 = inputs;
            node["outputs"]                = outputs;
            node["max_connection_age"]     = max_connection_age;
            node["first_move_factor"]      = first_move_factor;
            node["neighbours_move_factor"] = neighbours_move_factor;
            node["sqr_phi"]                = sqr_phi;
            node["cycles_per_spawn"]       = cycles_per_spawn;
            node["error_decrease"]         = error_decrease;
            node["name"]                   = name;

            return node;
        }

        Config::~Config() {
            log.debug("destroy configuration ", name);
        }

    } // engine


} /* namespace gas */
