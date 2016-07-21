#ifndef GAS_ENGINE_COMMON_HPP
#define GAS_ENGINE_COMMON_HPP

#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <exception>


namespace gas {

    namespace engine {

        class GasException: public std::exception {
        public:
            const char* message;

            explicit GasException(const char* msg);

            const char* what() const noexcept override;
        };

        // std::string get_random_name();

    } // engine


} // gas

#endif // GAS_ENGINE_COMMON_HPP
