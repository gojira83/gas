#ifndef GAS_STORAGE_YAML_HPP
#define GAS_STORAGE_YAML_HPP

#include <memory>
#include <ios>

namespace gas {

    namespace engine {
        class Gas;
        class Config;
    } // engine

    namespace storage {

        namespace yaml {

            void store(std::ostream& os, std::shared_ptr<engine::Config> gas);

            void load(std::istream& is, std::shared_ptr<engine::Config> gas);

            void store(std::ostream& os, std::shared_ptr<engine::Gas> gas);

            void load(std::istream& is, std::shared_ptr<engine::Gas> gas);

        } // yaml


    } // storage

} // gas


#endif // GAS_STORAGE_YAML_HPP
