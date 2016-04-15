#include <gas/storage/binary.hpp>

#include <map>

#include <gas/engine/gas.hpp>
#include <gas/engine/cell.hpp>
#include <gas/engine/connection.hpp>

namespace gas {

    namespace storage {

        namespace binary {

            void store(std::ostream& os, std::shared_ptr<engine::Gas> gas) {
                os.write((char*)&gas->config->inputs, sizeof(gas->config->inputs));
                os.write((char*)&gas->config->outputs, sizeof(gas->config->outputs));
                os.write((char*)&gas->config->max_connection_age, sizeof(gas->config->max_connection_age));
                os.write((char*)&gas->config->first_move_factor, sizeof(gas->config->first_move_factor));
                os.write((char*)&gas->config->neighbours_move_factor, sizeof(gas->config->neighbours_move_factor));
                os.write((char*)&gas->config->sqr_phi, sizeof(gas->config->sqr_phi));
                os.write((char*)&gas->config->cycles_per_spawn, sizeof(gas->config->cycles_per_spawn));
                os.write((char*)&gas->config->error_decrease, sizeof(gas->config->error_decrease));

                unsigned cellcount = gas->cells.size();
                os.write((char*)&cellcount, sizeof(unsigned));

                for(auto cell : gas->cells) {
                    os.write((char*)&cell->idx, sizeof(cell->idx));
                    os.write((char*)&cell->cluster_id, sizeof(cell->cluster_id));

                    for (int i = 0; i < gas->config->inputs; ++i) {
                        os.write((char*)&cell->inputs[i], sizeof(float));
                    }

                    for (int i = 0; i < gas->config->outputs; ++i) {
                        os.write((char*)&cell->outputs[i], sizeof(float));
                    }
                }

                unsigned concount = gas->connections.size();
                os.write((char*)&concount, sizeof(unsigned));

                for(auto con : gas->connections) {
                    os.write((char*)&con->start->idx, sizeof(con->start->idx));
                    os.write((char*)&con->end->idx, sizeof(con->end->idx));
                    os.write((char*)&con->age, sizeof(con->age));
                }
            }

            void load(std::istream& is, std::shared_ptr<engine::Gas> gas) {
                is.read((char*)&gas->config->inputs, sizeof(gas->config->inputs));
                is.read((char*)&gas->config->outputs, sizeof(gas->config->outputs));
                is.read((char*)&gas->config->max_connection_age, sizeof(gas->config->max_connection_age));
                is.read((char*)&gas->config->first_move_factor, sizeof(gas->config->first_move_factor));
                is.read((char*)&gas->config->neighbours_move_factor, sizeof(gas->config->neighbours_move_factor));
                is.read((char*)&gas->config->sqr_phi, sizeof(gas->config->sqr_phi));
                is.read((char*)&gas->config->cycles_per_spawn, sizeof(gas->config->cycles_per_spawn));
                is.read((char*)&gas->config->error_decrease, sizeof(gas->config->error_decrease));

                unsigned cellcount;
                std::map<unsigned, engine::Cell*> celllookup;
                is.read((char*)&cellcount, sizeof(unsigned));

                for(unsigned i = 0; i < cellcount; ++i) {
                    Cell* cell = new engine::Cell(0, gas->config->inputs, gas->config->outputs);

                    is.read((char*)&cell->idx, sizeof(cell->idx));
                    is.read((char*)&cell->cluster_id, sizeof(cell->cluster_id));

                    for (int i = 0; i < gas->config->inputs; ++i) {
                        is.read((char*)&cell->inputs[i], sizeof(float));
                    }

                    for (int i = 0; i < gas->config->outputs; ++i) {
                        is.read((char*)&cell->outputs[i], sizeof(float));
                    }

                    gas->cells.push_back(cell);
                    celllookup[cell->idx] = cell;
                }

                unsigned concount;
                is.read((char*)&concount, sizeof(unsigned));

                for(unsigned i = 0; i < concount; ++i) {
                    unsigned sid, eid, age;

                    is.read((char*)&sid, sizeof(unsigned));
                    is.read((char*)&eid, sizeof(unsigned));
                    is.read((char*)&age, sizeof(unsigned));

                    auto con = new engine::Connection(celllookup[sid], celllookup[eid]);
                    con->age = age;

                    gas->connections.push_back(con);
                }
            }
        
        } // binary
    
    } // storage

} // gas