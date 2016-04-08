/*
 * Config.hpp
 *
 *  Created on: 10.03.2014
 *      Author: code.ninja
 */

#ifndef GAS_CONFIG_HPP_
#define GAS_CONFIG_HPP_

#include <yaml-cpp/yaml.h>
#include <logging/logger.hpp>


namespace gas {

   namespace engine {

      class Config {
         public:
            static logging::Logger log;

            std::string name;
            unsigned inputs = 2;
            unsigned outputs = 1;
            unsigned max_connection_age = 50;
            float first_move_factor = 0.1;
            float neighbours_move_factor = 0.1;
            float sqr_phi = 0.25;
            unsigned cycles_per_spawn = 10;
            float error_decrease = 0.8;

            Config();

            void from_yaml(YAML::Node node);

            YAML::Node to_yaml();

            virtual ~Config();
      };

   } // engine


} /* namespace gas */


#endif /* GAS_CONFIG_HPP_ */
