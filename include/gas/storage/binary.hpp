#ifndef GAS_STORAGE_BINARY_HPP
#define GAS_STORAGE_BINARY_HPP

#include <ios>
#include <memory>


namespace gas {

    namespace engine {
        class Gas;
    } // engine

    namespace storage {

        namespace binary {

            void store(std::ostream& os, std::shared_ptr<engine::Gas> gas);

            void load(std::istream& is, std::shared_ptr<engine::Gas> gas);
        
        } // binary
    
    } // storage

} // gas

#endif // GAS_STORAGE_BINARY_HPP
