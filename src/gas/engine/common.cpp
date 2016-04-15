#include <gas/engine/common.hpp>

namespace gas {

    namespace engine {

        GasException::GasException(const char* msg): message(msg) {}

        const char* GasException::what() const noexcept {
            return message;
        }

        // std::string get_random_name() {
        //     std::ifstream names("/etc/names.csv");

        //     if(names) {
        //         srand(time(nullptr));

        //         names.seekg(0, names.end);
        //         int size = names.tellg();
        //         int random_line = rand() % (size - 1);

        //         names.seekg(random_line, names.beg);

        //         char buffer[50];

        //         names.getline(buffer, 50);
        //         names.getline(buffer, 50);

        //         return buffer;
        //     }
        //     else {
        //         throw GasException("could not find /etc/names.csv");
        //     }
        // }

    } // engine


} // gas
