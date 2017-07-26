#include <pybind11/pybind11.h>
#include "Events.h"
#include "hydra/Types.h"
#include <iostream>
#include <memory>


namespace py = pybind11;

namespace hydra {
    template<size_t N, unsigned int BACKEND>
    struct PyEvents {

        PyEvents() {
            std::cout << "Pybind default" << std::endl;
            impl = new Events<N, BACKEND>();
        }

        PyEvents(GLong_t nevents) {
            std::cout << "Pybind nevents: " << nevents << std::endl;
            impl = new Events<N, BACKEND>(nevents);
        }

        template <unsigned int BACKEND2>
        PyEvents(PyEvents<N, BACKEND2> const& other) {
            std::cout << "Called pybind" << std::endl;
            impl = new Events<N, BACKEND>(*(other.impl));
        }

        template<unsigned int BACKEND2>
        Events<N,BACKEND>& operator=(PyEvents<N,BACKEND2> const& other) {
            std::cout << "Inside" << std::endl;
            Events<N,BACKEND> *e;
            *e = *(other.impl);
            return *e;
        };

        GReal_t GetMaxWeight() const {
            return impl->GetMaxWeight();
        }

        void SetMaxWeight(GReal_t maxWeight) {
            impl->SetMaxWeight(maxWeight);
        }

        GLong_t GetNEvents() const {
            return impl->GetNEvents();
        }

        void SetNEvents(GLong_t nEvents) {
            impl->SetNEvents(nEvents);
        }

        auto FlagsBegin() const{
            return impl->FlagsBegin();
        }

        auto FlagsEnd() const{
            return impl->FlagsEnd();
        }

        auto begin(){
            return impl->begin();
        }

        auto  end(){
            return impl->end();
        }

        auto getBackend(){
            return BACKEND;
        }

        Events<N, BACKEND> *impl;
    };
}

PYBIND11_MODULE(Events, m) {
    py::class_< hydra::PyEvents<3, hydra::device> >(m, "Events")
        .def(py::init<>())
        .def(py::init< hydra::GLong_t > ())
        .def(py::init< hydra::PyEvents<3, 0> >())
        .def(py::init< hydra::PyEvents<3, hydra::device> >())
        .def("assign", &hydra::PyEvents<3, hydra::device>::operator=<0>)
        .def("GetMaxWeight", &hydra::PyEvents<3, hydra::device>::GetMaxWeight)
        .def("SetMaxWeight", &hydra::Events<3, hydra::device>::SetMaxWeight)
        .def("GetNEvents", &hydra::PyEvents<3, hydra::device>::GetNEvents)
        .def("SetNEvents", &hydra::PyEvents<3, hydra::device>::SetNEvents)
        .def("FlagsBegin", &hydra::PyEvents<3, hydra::device>::FlagsBegin)
        .def("FlagsEnd", &hydra::PyEvents<3, hydra::device>::FlagsEnd)
        .def("begin", &hydra::PyEvents<3, hydra::device>::begin)
        .def("end", &hydra::PyEvents<3, hydra::device>::end)
        .def("_getBackEnd", &hydra::PyEvents<3, hydra::device>::getBackend)
    ;

    py::class_< hydra::PyEvents<3, 0> >(m, "Events0")
        .def(py::init<>())
        .def(py::init< hydra::GLong_t > ())
        .def(py::init< hydra::PyEvents<3, hydra::device> >())
        .def(py::init< hydra::PyEvents<3, 0> >())
        .def("assign", &hydra::PyEvents<3, 0>::operator=<hydra::device>)
        .def("GetMaxWeight", &hydra::PyEvents<3, 0>::GetMaxWeight)
        .def("SetMaxWeight", &hydra::Events<3, 0>::SetMaxWeight)
        .def("GetNEvents", &hydra::PyEvents<3, 0>::GetNEvents)
        .def("SetNEvents", &hydra::PyEvents<3, 0>::SetNEvents)
        .def("FlagsBegin", &hydra::PyEvents<3, 0>::FlagsBegin)
        .def("FlagsEnd", &hydra::PyEvents<3, 0>::FlagsEnd)
        .def("begin", &hydra::PyEvents<3, 0>::begin)
        .def("end", &hydra::PyEvents<3, 0>::end)
        .def("_getBackEnd", &hydra::PyEvents<3, 0>::getBackend)
    ;
}

//        .def("__iter__", [](hydra::PyEvents<3, hydra::device> &event) {
//                return py::make_iterator((event.impl)->begin(), (event.impl)->end());
//            }, py::keep_alive<0, 1>())