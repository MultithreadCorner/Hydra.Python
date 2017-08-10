//
// Created by deep on 8/8/17.
//

#ifndef PYITERATOR_H_
#define PYITERATOR_H_

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace hydra_python {
    namespace detail {
        template<typename Iterator, typename Sentinel, bool KeyIterator, py::return_value_policy Policy>
        struct iterator_state {
            Iterator it;
            Sentinel end;
            bool first_or_done;
        };
    }


    /// Makes a python iterator from a first and past-the-end C++ InputIterator.
    template<py::return_value_policy Policy = py::return_value_policy::reference_internal,
            typename Iterator,
            typename Sentinel,
            typename ValueType = decltype(*std::declval<Iterator>()),
            typename... Extra>
    py::iterator make_iterator(Iterator first, Sentinel last, Extra &&... extra) {
        typedef detail::iterator_state<Iterator, Sentinel, false, Policy> state;

        if (!py::detail::get_type_info(typeid(state), false)) {
            py::class_<state>(py::handle(), "iterator", pybind11::module_local())
                    .def("__iter__", [](state &s) -> state & { return s; })
                    .def("__next__", [](state &s) -> ValueType {
                        if (!s.first_or_done)
                            ++s.it;
                        else
                            s.first_or_done = false;
                        if (s.it == s.end) {
                            s.first_or_done = true;
                            throw py::stop_iteration();
                        }
                        return *s.it;
                    }, std::forward<Extra>(extra)..., Policy);
        }


        return py::cast(state{first, last, true});
    }
}
#endif //PYITERATOR_H_
