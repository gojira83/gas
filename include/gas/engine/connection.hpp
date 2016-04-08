/*
 * Connection.hpp
 *
 *  Created on: 10.03.2014
 *        Author: code.ninja
 */

#ifndef GAS_CONNECTION_HPP_
#define GAS_CONNECTION_HPP_

#include "cell.hpp"


namespace gas {

    namespace engine {

        class Connection {
         public:
                Cell* start;
                Cell* end;
                int age = 0;

                Connection(Cell* s, Cell* e);
                virtual ~Connection();
        };

    } // engine


} /* namespace gas */


#endif /* GAS_CONNECTION_HPP_ */
