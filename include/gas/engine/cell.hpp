/*
 * Cell.hpp
 *
 *  Created on: 10.03.2014
 *        Author: code.ninja
 */

#ifndef GAS_CELL_HPP_
#define GAS_CELL_HPP_

#include <map>


namespace gas {

    namespace engine {

       class Connection;

       class Cell {
        public:

            unsigned idx;
            unsigned cluster_id;
            double *inputs;
            double *outputs;
            double error = 0;
            std::map< Cell*, Connection* > neighbours;

            Cell(unsigned Idx, unsigned Ins, unsigned Outs);
            
            virtual ~Cell();
       };

    } // engine


} /* namespace gas */


#endif /* GAS_CELL_HPP_ */
