/*
 * Gas.hpp
 *
 *  Created on: 10.03.2014
 *      Author: code.ninja
 */

#ifndef GAS_GAS_HPP_
#define GAS_GAS_HPP_

#include <list>

#include <logging/logger.hpp>

#include <gas/engine/config.hpp>
#include <gas/engine/cell.hpp>
#include <gas/engine/connection.hpp>


namespace gas {

    namespace engine {

        class Gas {
            int _idpool = 0;
            Cell* _first;
            Cell* _second;
            double* _inputs;
            double* _outputs;
            double *_first_dis_buffer;
            double *_dis_buffer;
            int _cycles;

            Cell* _createCell();
            Connection* _connect( Cell* start, Cell* end );
            /**
             * Find first and second nearest.
             */
            void __findnearest();
            void __movecells();
            void __correlation();
            /**
             * Remove old connections and cells without connections.
             */
            void __removeoldandunused();
            double __celltooutput( Cell* c );
            void __spawncell();
            void __errordecay();
            void __output();

        public:
            static logging::Logger log;

            std::list< Cell* > cells;
            std::list< Connection* > connections;
            std::string name;
            std::shared_ptr<Config> config;

            Gas(std::shared_ptr<Config> c);

            void setInput( double* values );
            void calculate();
            void show( double* inputs, double* outputs );

            virtual ~Gas();
        };

    } // engine

} /* namespace gas */

std::ostream& operator<<(std::ostream& os, const gas::engine::Gas& gg);

#endif /* GAS_GAS_HPP_ */
