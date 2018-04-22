#ifndef PYABORIA_H_
#define PYABORIA_H_

#include "Aboria.h"
#include <boost/python.hpp>

namespace pyaboria {

using namespace Aboria;
using namespace boost::python;

template <unsigned int D>
using ParticlesCellList_t = Particles<std::tuple<>, D, std::vector, CellList>;
template <unsigned int D>
using ParticlesCellListOrdered_t =
    Particles<std::tuple<>, D, std::vector, CellListOrdered>;
template <unsigned int D>
using ParticlesKdtree_t = Particles<std::tuple<>, D, std::vector, Kdtree>;
template <unsigned int D>
using ParticlesNanoflannKdtree_t =
    Particles<std::tuple<>, D, std::vector, Kdtree>;
template <unsigned int D>
using ParticlesOctree_t = Particles<std::tuple<>, D, std::vector, HyperOctree>;

} // namespace pyaboria

#endif
