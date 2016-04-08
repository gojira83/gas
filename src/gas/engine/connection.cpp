/*
 * Connection.cpp
 *
 *  Created on: 10.03.2014
 *      Author: code.ninja
 */

#include "connection.hpp"

namespace gas {

    namespace engine {

       Connection::Connection( Cell* s, Cell* e )
             : start( s ), end( e ) {
          start->neighbours[ end ] = this;
          end->neighbours[ start ] = this;
       }

       Connection::~Connection() {
       }

    } // engine


} /* namespace gas */

