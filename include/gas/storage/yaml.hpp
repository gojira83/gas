#ifndef GAS_STORAGE_YAML_HPP
#define GAS_STORAGE_YAML_HPP


namespace gas {

    namespace engine {
        class Gas;
    } // engine

    namespace storage {

        namespace yaml {

            void store(const char* filename, engine::Gas* gas);

        } // yaml


    } // storage

} // gas


#endif // GAS_STORAGE_YAML_HPP
