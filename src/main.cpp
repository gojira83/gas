#include <gas/engine/gas.hpp>
#include <gas/engine/config.hpp>
#include <gas/storage/binary.hpp>
#include <gas/storage/yaml.hpp>
#include <logging/logging.hpp>

#include <tclap/CmdLine.h>

#include <fstream>


int main(int argc, char const *argv[]) {
    auto log = logging::get("gas");

    try {
        auto config = std::shared_ptr<gas::engine::Config>(new gas::engine::Config());
        std::shared_ptr<gas::engine::Gas> gas;
        TCLAP::CmdLine cmd("growing neuronal gas", ' ', "0.1");

        TCLAP::ValueArg<std::string> configArg("c", "config", "The gas configuration to use", true, "gas.config.yml", "string", cmd);
        TCLAP::ValueArg<std::string> gasdbArg("g", "gasfile", "The gas network file", true, "gas.db", "string", cmd);

        // cmd.add( configArg );

        cmd.parse( argc, argv );

        std::string configfile = configArg.getValue();
        std::string gasdbfile = gasdbArg.getValue();

        log->info("use config: ", configfile);
        log->info("use gas db: ", gasdbfile);

        std::ifstream ifs(configfile.c_str());

        if(ifs) {
            gas::storage::yaml::load(ifs, config);

            gas = std::shared_ptr<gas::engine::Gas>(new gas::engine::Gas(config));

            std::ofstream ofs(gasdbfile, std::ofstream::binary | std::ofstream::trunc);

            if(ofs) {
                gas::storage::binary::store(ofs, gas);
            }
            else {
                log->error("could not write to: ", gasdbfile);
            }
        }
        else {
            log->error("could not open: ", configfile);
        }

    }
    catch (TCLAP::ArgException &e) { 
        log->error( e.error(), " for arg ", e.argId() ); 
    }
    catch(std::exception &e) {
        log->error( e.what() );
    }

    return 0;
}
