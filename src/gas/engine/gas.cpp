/*
 * Gas.cpp
 *
 *  Created on: 10.03.2014
 *        Author: code.ninja
 */

#include <gas/engine/gas.hpp>

#include <cmath>
#include <gas/engine/common.hpp>
#include <limits>

namespace gas {

    namespace engine {

        logging::Logger Gas::log("gas.engine.gas");

        Gas::Gas(std::shared_ptr<Config> c) : config(c) {
            log.debug("create gas");

            _first_dis_buffer = new double[config->gas.inputs];
            _dis_buffer       = new double[config->gas.inputs];
            _inputs           = new double[config->gas.inputs];
            _outputs          = new double[config->gas.outputs];

            _connect(_createCell(), _createCell());
        }

        Gas::~Gas() {
            log.debug("destroy gas");

            delete _first_dis_buffer;
            delete _dis_buffer;
            delete _inputs;
            delete _outputs;

            for (auto cell : this->cells) {
                delete cell;
            }

            for (auto con : this->connections) {
                delete con;
            }
        }

        Cell *Gas::_createCell() {
            Cell *c = new Cell(++_idpool, config->gas.inputs, config->gas.outputs);
            cells.push_back(c);
            return c;
        }

        Connection *Gas::_connect(Cell *start, Cell *end) {
            Connection *c = new Connection(start, end);
            connections.push_back(c);
            return c;
        }

        void Gas::setInput(double *values) {
            for (int i = 0; i < config->gas.inputs; ++i) {
                _inputs[i] = values[i];
            }
        }

        void Gas::__findnearest() {
            _first                = nullptr;
            _second               = nullptr;
            double seconddistance = std::numeric_limits<double>::max();
            double firstdistance  = std::numeric_limits<double>::max();

            for (int i = 0; i < config->gas.inputs; ++i) {
                _first_dis_buffer[i] = std::numeric_limits<double>::max();
            }

            for (Cell *cell : cells) {
                double distance = 0;

                for (int i = 0; i < config->gas.inputs; ++i) {
                    _dis_buffer[i] = _inputs[i] - cell->inputs[i];
                    distance += _dis_buffer[i] * _dis_buffer[i];
                }

                if (distance <= firstdistance) {
                    _second        = _first;
                    seconddistance = firstdistance;
                    _first         = cell;
                    firstdistance  = distance;
                } else if (distance <= seconddistance) {
                    _second        = cell;
                    seconddistance = distance;
                }
            }

            _first->error += firstdistance;
        }

        void Gas::__movecells() {
            for (int i = 0; i < config->gas.inputs; ++i) {
                _first->inputs[i] += _first_dis_buffer[i] * config->gas.first_move_factor;
            }

            for (auto &entry : _first->neighbours) {
                entry.second->age += 1;

                Cell *cell = entry.first;
                for (int i = 0; i < config->gas.inputs; ++i) {
                    cell->inputs[i] += (_inputs[0] - cell->inputs[i]) * config->gas.neighbours_move_factor;
                }
            }
        }

        void Gas::__correlation() {
            Connection *corelation = _first->neighbours[_second];

            if (corelation != nullptr) {
                corelation->age = 0;
            } else {
                _connect(_first, _second);
            }
        }

        /**
         * Remove old connections and cells without connections.
         */
        void Gas::__removeoldandunused() {
            connections.remove_if([this](Connection *c) {
                if (c->age > config->gas.max_connection_age) {
                    c->start->neighbours.erase(c->end);
                    c->end->neighbours.erase(c->start);

                    if (c->start->neighbours.size() < 1) {
                        cells.remove(c->start);
                        delete c->start;
                    }

                    if (c->end->neighbours.size() < 1) {
                        cells.remove(c->end);
                        delete c->end;
                    }

                    return true;
                }

                return false;
            });
        }

        double Gas::__celltooutput(Cell *c) {
            double erg = 0;
            for (int i = 0; i < config->gas.inputs; ++i) {
                double d = _inputs[i] - c->inputs[i];
                erg += d * d;
            }

            erg = exp(erg) / -config->gas.sqr_phi;

            for (int i = 0; i < config->gas.outputs; ++i) {
                _outputs[i] += c->outputs[i] * erg;
            }

            return erg;
        }

        void Gas::__spawncell() {
            if (_cycles > config->gas.cycles_per_spawn) {
                _cycles                       = 0;
                std::list<Cell *>::iterator i = cells.begin();
                Cell *                      q = *i;
                Cell *                      f;

                while (i != cells.end()) {
                    ++i;
                    Cell *x = *i;
                    if (x->error > q->error) {
                        q = x;
                    }
                }

                auto entry = q->neighbours.begin();
                f          = entry->first;
                while (entry != q->neighbours.end()) {
                    ++entry;
                    Cell *x = entry->first;
                    if (x->error > f->error) {
                        f = x;
                    }
                }

                Cell *new_unite = _createCell();

                for (int j = 0; j < config->gas.inputs; ++j) {
                    new_unite->inputs[j]  = (q->inputs[j] + f->inputs[j]) * 0.5;
                    new_unite->outputs[j] = (q->outputs[j] + f->outputs[j]) * 0.5;
                }

                q->error *= config->gas.error_decrease;
                f->error *= config->gas.error_decrease;
                new_unite->error = q->error;

                Connection *c = q->neighbours[f];
                connections.remove(c);
                c->start->neighbours.erase(c->end);
                c->end->neighbours.erase(c->start);

                _connect(q, new_unite);
                _connect(f, new_unite);
            } else {
                _cycles++;
            }
        }

        void Gas::__errordecay() {
            for (auto c : cells) {
                c->error *= config->gas.error_decrease;
            }
        }

        void Gas::__output() {
            double hsum = 0;

            for (int i = 0; i < config->gas.outputs; ++i) {
                _outputs[i] = 0;
            }

            for (auto &c : _first->neighbours) {
                hsum += __celltooutput(c.first);
            }
            hsum += __celltooutput(_first);

            if (hsum != 0) {
                for (int i = 0; i < config->gas.outputs; ++i) {
                    _outputs[i] /= hsum;
                }
            } else {
                for (int i = 0; i < config->gas.outputs; ++i) {
                    _outputs[i] = 0;
                }
            }
        }

        void Gas::calculate() {
            log.debug("calculate");

            __findnearest();
            __movecells();
            __correlation();
            __removeoldandunused();
            __spawncell();
            __errordecay();
            __output();
        }

        void Gas::show(double *inputs, double *outputs) {
            log.debug("show");

            for (int i = 0; i < config->gas.inputs; ++i) {
                _inputs[i] = inputs[i];
            }

            __findnearest();
            __movecells();
            __correlation();
            __removeoldandunused();
            __spawncell();
            __errordecay();

            for (int i = 0; i < config->gas.outputs; ++i) {
                _first->outputs[i] = outputs[i];
            }

            __output();
        }

        void Gas::approx(double *inputs, double *outputs) {
            log.debug("approx");

            for (int i = 0; i < config->gas.inputs; ++i) {
                _inputs[i] = inputs[i];
            }

            __findnearest();
            __output();

            for (int i = 0; i < config->gas.outputs; ++i) {
                outputs[i] = _first->outputs[i];
            }
        }

        void __browse(Cell *previous) {
            for (auto entry : previous->neighbours) {

                if (entry.first->cluster_id == 0) {
                    entry.first->cluster_id = previous->cluster_id;
                    __browse(entry.first);
                }
            }
        }

        unsigned Gas::clusteriese() {
            _cluster_id_pool = 1;

            for (auto cell : cells) {
                cell->cluster_id = 0;
            }

            for (auto cell : cells) {
                if (cell->cluster_id == 0) {
                    cell->cluster_id = _cluster_id_pool++;
                    __browse(cell);
                }
            }

            return _cluster_id_pool - 1;
        }
    } // engine

} /* namespace gas */
