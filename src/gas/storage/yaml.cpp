#include <gas/storage/yaml.hpp>

#include <fstream>
#include <yaml-cpp/yaml.h>
#include <gas/engine/gas.hpp>
#include <gas/engine/config.hpp>


namespace gas {

    namespace storage {

        namespace yaml {


            void store(std::ostream& os, std::shared_ptr<engine::Config> config) {
                YAML::Emitter out;

                out << YAML::BeginMap;

                out << YAML::Key << "inputs" << YAML::Value << config->inputs;
                out << YAML::Key << "outputs" << YAML::Value << config->outputs;
                out << YAML::Key << "max_connection_age" << YAML::Value << config->max_connection_age;
                out << YAML::Key << "first_move_factor" << YAML::Value << config->first_move_factor;
                out << YAML::Key << "neighbours_move_factor" << YAML::Value << config->neighbours_move_factor;
                out << YAML::Key << "sqr_phi" << YAML::Value << config->sqr_phi;
                out << YAML::Key << "cycles_per_spawn" << YAML::Value << config->cycles_per_spawn;
                out << YAML::Key << "error_decrease" << YAML::Value << config->error_decrease;

                out << YAML::EndMap;

                os << out.c_str();
            }

            void load(std::istream& is, std::shared_ptr<engine::Config> config) {
                YAML::Node node = YAML::Load(is);

                config->inputs                 = node["inputs"].as<unsigned>();
                config->outputs                = node["outputs"].as<unsigned>();
                config->max_connection_age     = node["max_connection_age"].as<unsigned>();
                config->first_move_factor      = node["first_move_factor"].as<float>();
                config->neighbours_move_factor = node["neighbours_move_factor"].as<float>();
                config->sqr_phi                = node["sqr_phi"].as<float>();
                config->cycles_per_spawn       = node["cycles_per_spawn"].as<unsigned>();
                config->error_decrease         = node["error_decrease"].as<float>();
            }

            void load(std::istream& is, std::shared_ptr<engine::Gas> gas) {
                YAML::Node node = YAML::Load(is);
            }

            void store(std::ostream& os, std::shared_ptr<engine::Gas> gas) {
                YAML::Emitter out;

                out << YAML::Comment("gas cluster");

                out << YAML::BeginMap;

                // save config

                out << YAML::Key << "config";
                out << YAML::Value << YAML::BeginMap;

                out << YAML::Key << "inputs" << YAML::Value << gas->config->inputs;
                out << YAML::Key << "outputs" << YAML::Value << gas->config->outputs;
                out << YAML::Key << "max_connection_age" << YAML::Value << gas->config->max_connection_age;
                out << YAML::Key << "first_move_factor" << YAML::Value << gas->config->first_move_factor;
                out << YAML::Key << "neighbours_move_factor" << YAML::Value << gas->config->neighbours_move_factor;
                out << YAML::Key << "sqr_phi" << YAML::Value << gas->config->sqr_phi;
                out << YAML::Key << "cycles_per_spawn" << YAML::Value << gas->config->cycles_per_spawn;
                out << YAML::Key << "error_decrease" << YAML::Value << gas->config->error_decrease;

                out << YAML::EndMap;

                // save cells
                out << YAML::Key << "cells";
                out << YAML::BeginSeq;

                for(auto cell: gas->cells) {
                    out << YAML::BeginSeq;
                    out << cell->idx;

                    // inputs
                    out << YAML::BeginSeq;
                    for (int i = 0; i < gas->config->inputs; ++i)
                    {
                        out << cell->inputs[i];
                    }
                    out << YAML::EndSeq;

                    //outputs
                    out << YAML::BeginSeq;
                    for (int i = 0; i < gas->config->outputs; ++i)
                    {
                        out << cell->outputs[i];
                    }
                    out << YAML::EndSeq;

                    out << YAML::EndSeq;
                }

                out << YAML::EndSeq;

                // save connections
                out << YAML::Key << "outputs";
                out << YAML::Value << YAML::BeginSeq;

                for(auto con: gas->connections) {
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
