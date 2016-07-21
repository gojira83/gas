#ifndef GAS_ENGINE_GAS_HPP
#define GAS_ENGINE_GAS_HPP

#include <list>
#include <memory>

#include <logging/logger.hpp>

#include <gas/engine/config.hpp>
#include <gas/engine/cell.hpp>
#include <gas/engine/connection.hpp>


namespace gas {

    namespace engine {

        class Gas {
            unsigned _idpool = 0;
            unsigned _cluster_id_pool = 0;
            Cell* _first;
            Cell* _second;
            double* _inputs;
            double* _outputs;
            double *_first_dis_buffer;
            double *_dis_buffer;
            int _cycles;

            Cell* _createCell();
            Connection* _connect(Cell* start, Cell* end);
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
            std::shared_ptr<Config> config;

            Gas(std::shared_ptr<Config> c);

            void setInput(double* values);
            void calculate();
            void show(double* inputs, double* outputs);
            void approx(double* inputs, double* outputs);

            ///
            /// @return     The number of clusters found.
            ///
            unsigned clusteriese();

            virtual ~Gas();
        };

    } // engine

} /* namespace gas */

#endif /* GAS_ENGINE_GAS_HPP */
