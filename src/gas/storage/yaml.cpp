#include <gas/storage/yaml.hpp>

#include <fstream>
#include <gas/engine/config.hpp>
#include <gas/engine/gas.hpp>
#include <yaml-cpp/yaml.h>

namespace gas {

    namespace storage {

        namespace yaml {

            void store(std::ostream &os, std::shared_ptr<engine::Config> config) {
                YAML::Emitter out;

                out << YAML::BeginMap;

                out << YAML::Key << "storage" << YAML::Value << YAML::BeginMap;
                out << YAML::Key << "format" << YAML::Value << config->storage.format;
                out << YAML::Key << "path" << YAML::Value << config->storage.path;
                out << YAML::EndMap;

                out << YAML::Key << "gas" << YAML::Value << YAML::BeginMap;

                out << YAML::Key << "inputs" << YAML::Value << config->gas.inputs;
                out << YAML::Key << "outputs" << YAML::Value << config->gas.outputs;
                out << YAML::Key << "max_connection_age" << YAML::Value << config->gas.max_connection_age;
                out << YAML::Key << "first_move_factor" << YAML::Value << config->gas.first_move_factor;
                out << YAML::Key << "neighbours_move_factor" << YAML::Value << config->gas.neighbours_move_factor;
                out << YAML::Key << "sqr_phi" << YAML::Value << config->gas.sqr_phi;
                out << YAML::Key << "cycles_per_spawn" << YAML::Value << config->gas.cycles_per_spawn;
                out << YAML::Key << "error_decrease" << YAML::Value << config->gas.error_decrease;

                out << YAML::EndMap << YAML::EndMap;

                os << out.c_str();
            }

            void load(std::istream &is, std::shared_ptr<engine::Config> config) {
                YAML::Node node    = YAML::Load(is);
                auto       gas     = node["gas"];
                auto       storage = node["storage"];

                config->storage.format = storage["format"].as<std::string>();
                config->storage.path   = storage["path"].as<std::string>();

                config->gas.inputs                 = gas["inputs"].as<unsigned>();
                config->gas.outputs                = gas["outputs"].as<unsigned>();
                config->gas.max_connection_age     = gas["max_connection_age"].as<unsigned>();
                config->gas.first_move_factor      = gas["first_move_factor"].as<float>();
                config->gas.neighbours_move_factor = gas["neighbours_move_factor"].as<float>();
                config->gas.sqr_phi                = gas["sqr_phi"].as<float>();
                config->gas.cycles_per_spawn       = gas["cycles_per_spawn"].as<unsigned>();
                config->gas.error_decrease         = gas["error_decrease"].as<float>();
            }

            void load(std::istream &is, std::shared_ptr<engine::Gas> gas) { YAML::Node node = YAML::Load(is); }

            void store(std::ostream &os, std::shared_ptr<engine::Gas> gas) {
                YAML::Emitter out;

                out << YAML::Comment("gas cluster");

                out << YAML::BeginMap;

                // save cells
                out << YAML::Key << "cells";
                out << YAML::BeginSeq;

                for (auto cell : gas->cells) {
                    out << YAML::BeginSeq;
                    out << cell->idx;

                    // inputs
                    out << YAML::BeginSeq;
                    for (int i = 0; i < gas->config->gas.inputs; ++i) {
                        out << cell->inputs[i];
                    }
                    out << YAML::EndSeq;

                    // outputs
                    out << YAML::BeginSeq;
                    for (int i = 0; i < gas->config->gas.outputs; ++i) {
                        out << cell->outputs[i];
                    }
                    out << YAML::EndSeq;

                    out << YAML::EndSeq;
                }

                out << YAML::EndSeq;

                // save connections
                out << YAML::Key << "outputs";
                out << YAML::Value << YAML::BeginSeq;

                for (auto con : gas->connections) {
                    out << YAML::BeginSeq;
                    out << con->start->idx;
                    out << con->end->idx;
                    out << YAML::EndSeq;
                }

                out << YAML::EndSeq;
                out << YAML::EndMap;

                os << out.c_str();
            }

        } // yaml

    } // storage

} // gas
