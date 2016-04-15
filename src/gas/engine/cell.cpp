/*
 * Cell.cpp
 *
 *  Created on: 10.03.2014
 *      Author: code.ninja
 */

#include <gas/engine/cell.hpp>

#include <boost/random/lagged_fibonacci.hpp>


namespace gas {

   namespace engine {

      Cell::Cell(unsigned Idx, unsigned Ins, unsigned Outs) {
         idx = Idx;
         inputs = new double[Ins];
         outputs = new double[Outs];
            // lagged_fibonacci607

         boost::random::lagged_fibonacci607 fibrand;

         for(unsigned i = 0; i < Ins; i++){
            inputs[i] = fibrand();
         }
      }

      Cell::~Cell() {
         delete inputs;
         delete outputs;
      }

   } // engine


} /* namespace gas */

