#include <gas/storage/binary.hpp>

#include <map>

#include <gas/engine/cell.hpp>
#include <gas/engine/connection.hpp>
#include <gas/engine/gas.hpp>

namespace gas {

    namespace storage {

        namespace binary {

            void store(std::ostream &os, std::shared_ptr<engine::Gas> gas) {
                unsigned cellcount = gas->cells.size();
                os.write((char *)&cellcount, sizeof(unsigned));

                for (auto cell : gas->cells) {
                    os.write((char *)&cell->idx, sizeof(cell->idx));
                    os.write((char *)&cell->cluster_id, sizeof(cell->cluster_id));

                    for (int i = 0; i < gas->config->gas.inputs; ++i) {
                        os.write((char *)&cell->inputs[i], sizeof(float));
                    }

                    for (int i = 0; i < gas->config->gas.outputs; ++i) {
                        os.write((char *)&cell->outputs[i], sizeof(float));
                    }
                }

                unsigned concount = gas->connections.size();
                os.write((char *)&concount, sizeof(unsigned));

                for (auto con : gas->connections) {
                    os.write((char *)&con->start->idx, sizeof(con->start->idx));
                    os.write((char *)&con->end->idx, sizeof(con->end->idx));
                    os.write((char *)&con->age, sizeof(con->age));
                }
            }

            void load(std::istream &is, std::shared_ptr<engine::Gas> gas) {
                unsigned cellcount;
                std::map<unsigned, engine::Cell *> celllookup;
                is.read((char *)&cellcount, sizeof(unsigned));

                for (unsigned i = 0; i < cellcount; ++i) {
                    engine::Cell *cell = new engine::Cell(0, gas->config->gas.inputs, gas->config->gas.outputs);

                    is.read((char *)&cell->idx, sizeof(cell->idx));
                    is.read((char *)&cell->cluster_id, sizeof(cell->cluster_id));

                    for (int i = 0; i < gas->config->gas.inputs; ++i) {
                        is.read((char *)&cell->inputs[i], sizeof(float));
                    }

                    for (int i = 0; i < gas->config->gas.outputs; ++i) {
                        is.read((char *)&cell->outputs[i], sizeof(float));
                    }

                    gas->cells.push_back(cell);
                    celllookup[cell->idx] = cell;
                }

                unsigned concount;
                is.read((char *)&concount, sizeof(unsigned));

                for (unsigned i = 0; i < concount; ++i) {
                    unsigned sid, eid, age;

                    is.read((char *)&sid, sizeof(unsigned));
                    is.read((char *)&eid, sizeof(unsigned));
                    is.read((char *)&age, sizeof(unsigned));

                    auto con = new engine::Connection(celllookup[sid], celllookup[eid]);
                    con->age = age;

                    gas->connections.push_back(con);
                }
            }

        } // binary

    } // storage

} // gas
