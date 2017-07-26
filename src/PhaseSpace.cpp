#include "PhaseSpace.h"
#include "hydra/Types.h"
#include "hydra/Events.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

namespace py = pybind11;

PYBIND11_MODULE(PhaseSpace, m) {
  py::class_< hydra::PhaseSpace<3> >(m, "PhaseSpace")
    .def(py::init<hydra::GReal_t, std::vector<hydra::GReal_t> >())
    .def("Generate", &hydra::PhaseSpace<3>::Generate<hydra::Events<3, hydra::device>::iterator>)
    ;
}
