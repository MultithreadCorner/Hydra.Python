
/*----------------------------------------------------------------------------
 *
 *   Copyright (C) 2017 Antonio Augusto Alves Junior
 *
 *
 *   This file is part of the Hydra.Python Analysis Framework.
 *
 *   Hydra.Python is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Hydra.Python is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Hydra.Python.  If not, see <http://www.gnu.org/licenses/>.
 *
 *---------------------------------------------------------------------------*/

/*
 * bind_container.h
 *
 *  Created on: 28 de jul de 2017
 *      Author: augalves
 */

/*
 * @file
 * 
 * @ingroup custom_binders
 * 
 * @brief this file implements the hydra_vector bindings. It is largely based
 * in the pybind11/stl_bind.h header, with the necessary  adaptations
 * to make it transparent to thrust and hydra.
 *
 * @todo 
 *
 */
#ifndef BIND_CONTAINER_H_
#define BIND_CONTAINER_H_


#include "pybind11/detail/common.h"
#include "pybind11/operators.h"

#include <thrust/find.h>
#include <thrust/count.h>

#include <algorithm>
#include <sstream>
#include <type_traits>


namespace hydra_python {

namespace detail {


/* SFINAE helper class used by 'is_comparable */
template <typename T>  struct container_traits {
    template <typename T2> static std::true_type test_comparable(decltype(std::declval<const T2 &>() == std::declval<const T2 &>())*);
    template <typename T2> static std::false_type test_comparable(...);
    template <typename T2> static std::true_type test_value(typename T2::value_type *);
    template <typename T2> static std::false_type test_value(...);
    template <typename T2> static std::true_type test_pair(typename T2::first_type *, typename T2::second_type *);
    template <typename T2> static std::false_type test_pair(...);

    static constexpr const bool is_comparable = std::is_same<std::true_type, decltype(test_comparable<T>(nullptr))>::value;
    static constexpr const bool is_pair = std::is_same<std::true_type, decltype(test_pair<T>(nullptr, nullptr))>::value;
    static constexpr const bool is_vector = std::is_same<std::true_type, decltype(test_value<T>(nullptr))>::value;
    static constexpr const bool is_element = !is_pair && !is_vector;
};

/* Default: is_comparable -> std::false_type */
template <typename T, typename SFINAE = void>
struct is_comparable : std::false_type { };

/* For non-map data structures, check whether operator== can be instantiated */
template <typename T>
struct is_comparable<
    T, pybind11::detail::enable_if_t<container_traits<T>::is_element &&
                   container_traits<T>::is_comparable>>
    : std::true_type { };

/* For a vector/map data structure, recursively check the value type (which is std::pair for maps) */
template <typename T>
struct is_comparable<T, pybind11::detail::enable_if_t<container_traits<T>::is_vector>> {
    static constexpr const bool value =
        is_comparable<typename T::value_type>::value;
};

/* For pairs, recursively check the two data types */
template <typename T>
struct is_comparable<T, pybind11::detail::enable_if_t<container_traits<T>::is_pair>> {
    static constexpr const bool value =
        is_comparable<typename T::first_type>::value &&
        is_comparable<typename T::second_type>::value;
};

/* Fallback functions */
template <typename, typename, typename... Args> void vector_if_copy_constructible(const Args &...) { }
template <typename, typename, typename... Args> void vector_if_equal_operator(const Args &...) { }
template <typename, typename, typename... Args> void vector_if_insertion_operator(const Args &...) { }
template <typename, typename, typename... Args> void vector_modifiers(const Args &...) { }

/*

void vector_if_copy_constructible(pybind11::detail::enable_if_t<
    std::is_copy_constructible<Vector>::value &&
    std::is_copy_constructible<typename Vector::value_type>::value, Class_> &cl) {

    cl.def(pybind11::init<const Vector &>(), "Copy constructor");
}
*/
template<typename Vector, typename Class_>
void vector_if_copy_constructible(pybind11::detail::enable_if_t<pybind11::detail::is_copy_constructible<Vector>::value, Class_> &cl) {
     cl.def(pybind11::init<const Vector &>(), "Copy constructor");
 }

template<typename Vector, typename Class_>
void vector_if_equal_operator(pybind11::detail::enable_if_t<is_comparable<Vector>::value, Class_> &cl) {
    using T = typename Vector::value_type;

    cl.def(pybind11::detail::self == pybind11::detail::self);
    cl.def(pybind11::detail::self != pybind11::detail::self);

    cl.def("count",
        [](const Vector &v, const T &x) {
            return thrust::count(v.begin(), v.end(), x);
        },
		pybind11::arg("x"),
        "Return the number of times ``x`` appears in the list"
    );

    cl.def("remove", [](Vector &v, const T &x) {
            auto p = thrust::find(v.begin(), v.end(), x);
            if (p != v.end())
                v.erase(p);
            else
                throw pybind11::value_error();
        },
        pybind11::arg("x"),
        "Remove the first item from the list whose value is x. "
        "It is an error if there is no such item."
    );

    cl.def("__contains__",
        [](const Vector &v, const T &x) {
            return thrust::find(v.begin(), v.end(), x) != v.end();
        },
        pybind11::arg("x"),
        "Return true the container contains ``x``"
    );
}

// Vector modifiers -- requires a copyable vector_type:
// (Technically, some of these (pop and __delitem__) don't actually require copyability, but it seems
// silly to allow deletion but not insertion, so include them here too.)
template <typename Vector, typename Class_>
void vector_modifiers(pybind11::detail::enable_if_t<pybind11::detail::is_copy_constructible<typename Vector::value_type>::value, Class_> &cl) {
    using T = typename Vector::value_type;
    using SizeType = typename Vector::size_type;
    using DiffType = typename Vector::difference_type;

    cl.def("append",
           [](Vector &v, const T &value) { v.push_back(value); },
           pybind11::arg("x"),
           "Add an item to the end of the list");

    cl.def("__init__", [](Vector &v, pybind11::iterable it) {
        new (&v) Vector();
        try {
            v.reserve(pybind11::len(it));
            for (pybind11::handle h : it)
               v.push_back(h.cast<T>());
        } catch (...) {
            v.~Vector();
            throw;
        }
    });

    cl.def("extend",
       [](Vector &v, const Vector &src) {
           v.insert(v.end(), src.begin(), src.end());
       },
	   pybind11::arg("L"),
       "Extend the list by appending all the items in the given list"
    );

    cl.def("insert",
        [](Vector &v, SizeType i, const T &x) {
            if (i > v.size())
                throw pybind11::index_error();
            v.insert(v.begin() + (DiffType) i, x);
        },
		pybind11::arg("i") , pybind11::arg("x"),
        "Insert an item at a given position."
    );

    cl.def("pop",
        [](Vector &v) {
            if (v.empty())
                throw pybind11::index_error();
            T t = v.back();
            v.pop_back();
            return t;
        },
        "Remove and return the last item"
    );

    cl.def("pop",
        [](Vector &v, SizeType i) {
            if (i >= v.size())
                throw pybind11::index_error();
            T t = v[i];
            v.erase(v.begin() + (DiffType) i);
            return t;
        },
		pybind11::arg("i"),
        "Remove and return the item at index ``i``"
    );

    cl.def("__setitem__",
        [](Vector &v, SizeType i, const T &t) {
            if (i >= v.size())
                throw pybind11::index_error();
            v[i] = t;
        }
    );

    /// Slicing protocol
    cl.def("__getitem__",
        [](const Vector &v, pybind11::slice slice) -> Vector * {
            size_t start, stop, step, slicelength;

            if (!slice.compute(v.size(), &start, &stop, &step, &slicelength))
                throw pybind11::error_already_set();

            Vector *seq = new Vector();
            seq->reserve((size_t) slicelength);

            for (size_t i=0; i<slicelength; ++i) {
                seq->push_back(v[start]);
                start += step;
            }
            return seq;
        },
		pybind11::arg("s"),
        "Retrieve list elements using a slice object"
    );

    cl.def("__setitem__",
        [](Vector &v, pybind11::slice slice,  const Vector &value) {
            size_t start, stop, step, slicelength;
            if (!slice.compute(v.size(), &start, &stop, &step, &slicelength))
                throw pybind11::error_already_set();

            if (slicelength != value.size())
                throw std::runtime_error("Left and right hand size of slice assignment have different sizes!");

            for (size_t i=0; i<slicelength; ++i) {
                v[start] = value[i];
                start += step;
            }
        },
        "Assign list elements using a slice object"
    );

    cl.def("__delitem__",
        [](Vector &v, SizeType i) {
            if (i >= v.size())
                throw pybind11::index_error();
            v.erase(v.begin() + DiffType(i));
        },
        "Delete the list elements at index ``i``"
    );

    cl.def("__delitem__",
        [](Vector &v, pybind11::slice slice) {
            size_t start, stop, step, slicelength;

            if (!slice.compute(v.size(), &start, &stop, &step, &slicelength))
                throw pybind11::error_already_set();

            if (step == 1 && false) {
                v.erase(v.begin() + (DiffType) start, v.begin() + DiffType(start + slicelength));
            } else {
                for (size_t i = 0; i < slicelength; ++i) {
                    v.erase(v.begin() + DiffType(start));
                    start += step - 1;
                }
            }
        },
        "Delete list elements using a slice object"
    );

}

// If the type has an operator[] that doesn't return a reference (most notably std::vector<bool>),
// we have to access by copying; otherwise we return by reference.
template <typename Vector> using vector_needs_copy = pybind11::detail::negation<
    std::is_same<decltype(std::declval<Vector>()[typename Vector::size_type()]), typename Vector::value_type &>>;

// The usual case: access and iterate by reference
template <typename Vector, typename Class_>
void vector_accessor(pybind11::detail::enable_if_t<!vector_needs_copy<Vector>::value, Class_> &cl) {
    using T = typename Vector::value_type;
    using SizeType = typename Vector::size_type;
    using ItType   = typename Vector::iterator;

    cl.def("__getitem__",
        [](Vector &v, SizeType i) -> T & {
            if (i >= v.size())
                throw pybind11::index_error();
            return v[i];
        },
		pybind11::return_value_policy::reference_internal // ref + keepalive
    );

    cl.def("__iter__",
           [](Vector &v) {
               return pybind11::make_iterator<
            		   pybind11::return_value_policy::reference_internal, ItType, ItType, T&>(
                   v.begin(), v.end());
           },
		   pybind11::keep_alive<0, 1>() /* Essential: keep list alive while iterator exists */
    );
}

// The case for special objects, like std::vector<bool>, that have to be returned-by-copy:
template <typename Vector, typename Class_>
void vector_accessor(pybind11::detail::enable_if_t<vector_needs_copy<Vector>::value, Class_> &cl) {
    using T = typename Vector::value_type;
    using SizeType = typename Vector::size_type;
    using ItType   = typename Vector::iterator;
    cl.def("__getitem__",
        [](const Vector &v, SizeType i) -> T {
            if (i >= v.size())
                throw pybind11::index_error();
            return v[i];
        }
    );

    cl.def("__iter__",
           [](Vector &v) {
               return pybind11::make_iterator<
            		   pybind11::return_value_policy::copy, ItType, ItType, T>(
                   v.begin(), v.end());
           },
		   pybind11::keep_alive<0, 1>() /* Essential: keep list alive while iterator exists */
    );
}

template <typename Vector, typename Class_> auto vector_if_insertion_operator(Class_ &cl, std::string const &name)
    -> decltype(std::declval<std::ostream&>() << std::declval<typename Vector::value_type>(), void()) {
    using size_type = typename Vector::size_type;

    cl.def("__repr__",
           [name](Vector &v) {
            std::ostringstream s;
            s << name << '[';
            for (size_type i=0; i < v.size(); ++i) {
                s << v[i];
                if (i != v.size() - 1)
                    s << ", ";
            }
            s << ']';
            return s.str();
        },
        "Return the canonical string representation of this list."
    );
}

// Provide the buffer interface for vectors if we have data() and we have a format for it
// GCC seems to have "void std::vector<bool>::data()" - doing SFINAE on the existence of data() is insufficient, we need to check it returns an appropriate pointer
template <typename Vector, typename = void>
struct vector_has_data_and_format : std::false_type {};
template <typename Vector>
struct vector_has_data_and_format<Vector, pybind11::detail::enable_if_t<std::is_same<decltype(pybind11::format_descriptor<typename Vector::value_type>::format(), std::declval<Vector>().data()), typename Vector::value_type*>::value>> : std::true_type {};

// Add the buffer interface to a vector
template <typename Vector, typename Class_, typename... Args>
pybind11::detail::enable_if_t<pybind11::detail::any_of<std::is_same<Args, pybind11::buffer_protocol>...>::value>
vector_buffer(Class_& cl) {
    using T = typename Vector::value_type;

    static_assert(vector_has_data_and_format<Vector>::value, "There is not an appropriate format descriptor for this vector");

    // numpy.h declares this for arbitrary types, but it may raise an exception and crash hard at runtime if PYBIND11_NUMPY_DTYPE hasn't been called, so check here
    pybind11::format_descriptor<T>::format();

    cl.def_buffer([](Vector& v) -> pybind11::buffer_info {
        return pybind11::buffer_info(v.data(), static_cast<ssize_t>(sizeof(T)), pybind11::format_descriptor<T>::format(), 1, {v.size()}, {sizeof(T)});
    });

    cl.def("__init__", [](Vector& vec, pybind11::buffer buf) {
        auto info = buf.request();
        if (info.ndim != 1 || info.strides[0] % static_cast<ssize_t>(sizeof(T)))
            throw pybind11::type_error("Only valid 1D buffers can be copied to a vector");
        if (!pybind11::detail::compare_buffer_info<T>::compare(info) || (ssize_t) sizeof(T) != info.itemsize)
            throw type_error("Format mismatch (Python: " + info.format + " C++: " + pybind11::format_descriptor<T>::format() + ")");
        new (&vec) Vector();
        vec.reserve((size_t) info.shape[0]);
        T *p = static_cast<T*>(info.ptr);
        ssize_t step = info.strides[0] / static_cast<ssize_t>(sizeof(T));
        T *end = p + info.shape[0] * step;
        for (; p != end; p += step)
            vec.push_back(*p);
    });

    return;
}

template <typename Vector, typename Class_, typename... Args>
pybind11::detail::enable_if_t<!pybind11::detail::any_of<std::is_same<Args, pybind11::buffer_protocol>...>::value> vector_buffer(Class_&) {}

}  // namespace detail



//
// std::vector
//
template <typename Vector, typename holder_type = std::unique_ptr<Vector>, typename... Args>
pybind11::class_<Vector, holder_type> bind_vector(pybind11::module &m, std::string const &name, Args&&... args) {
    using Class_ = pybind11::class_<Vector, holder_type>;

    Class_ cl(m, name.c_str(), std::forward<Args>(args)...);

    // Declare the buffer interface if a buffer_protocol() is passed in
    detail::vector_buffer<Vector, Class_, Args...>(cl);


    cl.def(pybind11::init<>());

    cl.def(pybind11::init<size_t>());

    // Register copy constructor (if possible)
    detail::vector_if_copy_constructible<Vector, Class_>(cl);

    // Register comparison-related operators and functions (if possible)
    detail::vector_if_equal_operator<Vector, Class_>(cl);

    // Register stream insertion operator (if possible)
    detail::vector_if_insertion_operator<Vector, Class_>(cl, name);

    // Modifiers require copyable vector value type
    detail::vector_modifiers<Vector, Class_>(cl);

    // Accessor and iterator; return by value if copyable, otherwise we return by ref + keep-alive
    detail::vector_accessor<Vector, Class_>(cl);

    cl.def("get_range", [](Vector& v){return std::make_pair(v.begin(),v.end());},"get_range function"

    );

    cl.def("__bool__",
        [](const Vector &v) -> bool {
            return !v.empty();
        },
        "Check whether the list is nonempty"
    );

  cl.def("__len__", &Vector::size);

    return cl;
}


}



#endif /* BIND_CONTAINER_H_ */
