#include "python.hpp"

using namespace pyaboria;

#define VTK_PYTHON_CONVERSION(type)                                            \
  /* register the to-python converter */                                       \
  to_python_converter<vtkSmartPointer<type>,                                   \
                      vtkSmartPointer_to_python<type>>();                      \
  to_python_converter<type *, vtk_to_python<type *>>();                        \
  /* register the from-python converter */                                     \
  converter::registry::insert(&extract_vtk_wrapped_pointer, type_id<type>());

BOOST_PYTHON_MODULE(pyaboria) {

  VTK_PYTHON_CONVERSION(vtkUnstructuredGrid);

#define ADD_PROPERTY(name_string, name, D)                                     \
  .add_property(                                                               \
      name_string,                                                             \
      make_function(&get_non_const<name, ParticlesCellList_t<D>::value_type>,  \
                    return_value_policy<copy_non_const_reference>()),          \
      &set_data<name, ParticlesCellList_t<D>::value_type>)

#define ADD_PROPERTY_REF(name_string, name, D)                                 \
  .add_property(                                                               \
      name_string,                                                             \
      make_function(&get_non_const<name, ParticlesCellList_t<D>::reference>,   \
                    return_value_policy<copy_non_const_reference>()),          \
      &set_data<name, ParticlesCellList_t<D>::reference>)

#define ADD_PARTICLES(data_structure, D)                                       \
  class_<Particles##data_structure##_t<D>,                                     \
         std::shared_ptr<Particles##data_structure##_t<D>>>(                   \
      "Particles" #data_structure #D)                                          \
      .def(init<size_t>())                                                     \
      .def("__getitem__",                                                      \
           &getitem_particles<Particles##data_structure##_t<D>>)               \
      .def(                                                                    \
          "__setitem__",                                                       \
          &setitem_particles_from_reference<Particles##data_structure##_t<D>>) \
      .def("__setitem__",                                                      \
           &setitem_particles_from_value<Particles##data_structure##_t<D>>)    \
      .def("__len__", &Particles##data_structure##_t<D>::size)                 \
      .def("init_neighbour_search",                                            \
           &Particles##data_structure##_t<D>::init_neighbour_search)           \
      .def("get_grid", &Particles##data_structure##_t<D>::get_grid,            \
           return_value_policy<return_by_value>())                             \
      .def("append", &particles_push_back<Particles##data_structure##_t<D>>);

#define ADD_DIMENSION(D)                                                       \
  VectFromPythonList<double, D>();                                             \
  VectFromPythonList<bool, D>();                                               \
                                                                               \
  to_python_converter<Vector<double, D>, VectToPython<double, D>>();           \
                                                                               \
  ADD_PARTICLES(CellList, D)                                                   \
  ADD_PARTICLES(CellListOrdered, D)                                            \
  ADD_PARTICLES(Kdtree, D)                                                     \
  ADD_PARTICLES(NanoflannKdtree, D)                                            \
  ADD_PARTICLES(Octree, D)                                                     \
                                                                               \
  class_<ParticlesCellList_t<D>::reference>("ParticleRef" #D, no_init)         \
      ADD_PROPERTY_REF("id", id, D)                                            \
          ADD_PROPERTY_REF("position", position_d<D>, D)                       \
              ADD_PROPERTY_REF("alive", alive, D);                             \
  class_<ParticlesCellList_t<D>::value_type>("Particle" #D, init<>())          \
      ADD_PROPERTY("id", id, D) ADD_PROPERTY("position", position_d<D>, D)     \
          ADD_PROPERTY("alive", alive, D);

  ADD_DIMENSION(1)
  ADD_DIMENSION(2)
  ADD_DIMENSION(3)
  //.def("copy_from_vtk_grid",&ParticlesType<D>::copy_from_vtk_grid)      \

}
