#include <gas/storage/yaml.hpp>

#include <fstream>
#include <yaml-cpp/yaml.h>
#include <gas/engine/gas.hpp>


namespace gas {

    namespace storage {

        namespace yaml {

            void store(const char* filename, engine::Gas* gas) {
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

                std::ofstream ofs( filename );
                ofs << out.c_str();
                ofs.close();
            }

        } // yaml

    } // storage

} // gas
