#ifndef GAS_ENGINE_CONNECTION_HPP
#define GAS_ENGINE_CONNECTION_HPP

#include "cell.hpp"

namespace gas {

    namespace engine {

        class Connection {
          public:
            Cell *start;
            Cell *end;
            int   age = 0;

            Connection(Cell *s, Cell *e);
            virtual ~Connection();
        };
    }
}

#endif /* GAS_ENGINE_CONNECTION_HPP */
