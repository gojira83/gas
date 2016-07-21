#ifndef GAS_ENGINE_CELL_HPP
#define GAS_ENGINE_CELL_HPP

#include <map>

namespace gas {

    namespace engine {

        class Connection;

        class Cell {
          public:
            unsigned idx;
            unsigned cluster_id;
            double * inputs;
            double * outputs;
            double   error = 0;
            std::map<Cell *, Connection *> neighbours;

            Cell(unsigned Idx, unsigned Ins, unsigned Outs);

            virtual ~Cell();
        };

    } // engine

} /* namespace gas */

#endif /* GAS_ENGINE_CELL_HPP */
