#include <gas/engine/gas.hpp>
#include <logging/logging.hpp>

#include <tclap/CmdLine.h>


int main(int argc, char const *argv[]) {
    auto log = logging::get("gas");

    try {
        TCLAP::CmdLine cmd("growing neuronal gas", ' ', "0.1");

        TCLAP::ValueArg<std::string> configArg("c", "config", "The gas configuration to use", true, "gas.config.yml", "string");

        cmd.add( configArg );

        cmd.parse( argc, argv );

        log->info("use config: ", configArg.getValue());
    }
    catch (TCLAP::ArgException &e) { 
        log->error( e.error(), " for arg ", e.argId() ); 
    }

    return 0;
}
