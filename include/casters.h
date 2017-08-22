
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
 * casters.h
 *
 *  Created on: 1 de ago de 2017
 *      Author: augalves
 */

/*
 * @file
 * 
 * @ingroup
 * 
 * @brief This file implements the bi-directional casts for hydra::tuple and hydra::pair specializing the
 * pybind11::detail::tuple_caster class.
 *
 * @todo 
 *
 */
#ifndef CASTERS_H_
#define CASTERS_H_

#include <pybind11/pybind11.h>
#include <hydra/Tuple.h>
#include <thrust/iterator/detail/tuple_of_iterator_references.h>
#include <thrust/device_ptr.h>

namespace pybind11 {

namespace detail {



// Base implementation for hydra::tuple
template <typename... Ts>
class tuple_caster<hydra::tuple, Ts...> {
    using type = hydra::tuple<Ts...>;
    static constexpr auto size = sizeof...(Ts);
    using indices = make_index_sequence<size>;
public:

    bool load(handle src, bool convert) {
        if (!isinstance<pybind11::sequence>(src))
            return false;
        const auto seq = reinterpret_borrow<sequence>(src);
        if (seq.size() != size)
            return false;
        return load_impl(seq, convert, indices{});
    }

    template <typename T>
    static handle cast(T&& src, return_value_policy policy, handle parent) {
        return cast_impl(std::forward<T&>(src), policy, parent, indices{});
    }

    static PYBIND11_DESCR name() {
        return type_descr(_("Tuple[") + concat(make_caster<Ts>::name()...) + _("]"));
    }

    template <typename T> using cast_op_type = type;

    operator type() & { return implicit_cast(indices{}); }
    operator type() && { return std::move(*this).implicit_cast(indices{}); }

protected:
    template <size_t... Is>
    type implicit_cast(index_sequence<Is...>) & { return type(cast_op<Ts>(hydra::get<Is>(subcasters))...); }
    template <size_t... Is>
    type implicit_cast(index_sequence<Is...>) && { return type(cast_op<Ts>(std::move(hydra::get<Is>(subcasters)))...); }

    static constexpr bool load_impl(const sequence &, bool, detail::index_sequence<>) { return true; }

    template <size_t... Is>
    bool load_impl(const sequence &seq, bool convert, index_sequence<Is...>) {
        for (bool r : {hydra::get<Is>(subcasters).load(seq[Is], convert)...})
            if (!r)
                return false;
        return true;
    }

    /* Implementation: Convert a C++ tuple into a Python tuple */
    template <typename T, size_t... Is>
    static handle cast_impl(T&& src, return_value_policy policy, handle parent, index_sequence<Is...>) {
        std::array<object, size> entries{{
        	reinterpret_steal<pybind11::object>(make_caster<Ts>::cast(hydra::get<Is>(std::forward<T&>(src)), policy, parent))...
        }};
        for (const auto &entry: entries)
            if (!entry)
                return handle();
        tuple result(size);
        int counter = 0;
        for (auto & entry: entries)
            PyTuple_SET_ITEM(result.ptr(), counter++, entry.release().ptr());
        return result.release();
    }

    hydra::tuple<make_caster<Ts>...> subcasters;
};


template <typename... Ts> class type_caster<hydra::tuple<Ts...>>
    : public tuple_caster<hydra::tuple, Ts...> {};

//===========================


// Base implementation for thrust::detail::tuple_of_iterator_references
template <typename... Ts>
class tuple_caster<thrust::detail::tuple_of_iterator_references, Ts...> {
    using type = thrust::detail::tuple_of_iterator_references<Ts...>;
    static constexpr auto size = sizeof...(Ts);
    using indices = make_index_sequence<size>;
public:

    bool load(handle src, bool convert) {
        if (!isinstance<pybind11::sequence>(src))
            return false;
        const auto seq = reinterpret_borrow<sequence>(src);
        if (seq.size() != size)
            return false;
        return load_impl(seq, convert, indices{});
    }

    template <typename T>
    static handle cast(T&& src, return_value_policy policy, handle parent) {
        return cast_impl(std::forward<T&>(src), policy, parent, indices{});
    }

    static PYBIND11_DESCR name() {
        return type_descr(_("Tuple[") + concat(make_caster<Ts>::name()...) + _("]"));
    }

    template <typename T> using cast_op_type = type;

    operator type() & { return implicit_cast(indices{}); }
    operator type() && { return std::move(*this).implicit_cast(indices{}); }

protected:
    template <size_t... Is>
    type implicit_cast(index_sequence<Is...>) & { return type(cast_op<Ts>(hydra::get<Is>(subcasters))...); }
    template <size_t... Is>
    type implicit_cast(index_sequence<Is...>) && { return type(cast_op<Ts>(std::move(hydra::get<Is>(subcasters)))...); }

    static constexpr bool load_impl(const sequence &, bool, detail::index_sequence<>) { return true; }

    template <size_t... Is>
    bool load_impl(const sequence &seq, bool convert, index_sequence<Is...>) {
        for (bool r : {hydra::get<Is>(subcasters).load(seq[Is], convert)...})
            if (!r)
                return false;
        return true;
    }

    /* Implementation: Convert a C++ tuple into a Python tuple */
    template <typename T, size_t... Is>
    static handle cast_impl(T&& src, return_value_policy policy, handle parent, index_sequence<Is...>) {
        std::array<object, size> entries{{
        	reinterpret_steal<pybind11::object>(make_caster<Ts>::cast(hydra::get<Is>(std::forward<T&>(src)), policy, parent))...
        }};
        for (const auto &entry: entries)
            if (!entry)
                return handle();
        tuple result(size);
        int counter = 0;
        for (auto & entry: entries)
            PyTuple_SET_ITEM(result.ptr(), counter++, entry.release().ptr());
        return result.release();
    }

    thrust::detail::tuple_of_iterator_references<make_caster<Ts>...> subcasters;
};


template <typename... Ts> class type_caster<thrust::detail::tuple_of_iterator_references<Ts...>>
    : public tuple_caster<thrust::detail::tuple_of_iterator_references, Ts...> {};


//===================================================
// Base implementation for hydra::pair
template <typename... Ts>
class tuple_caster<hydra::pair, Ts...> {
    using type = hydra::pair<Ts...>;
    static constexpr auto size = sizeof...(Ts);
    using indices = make_index_sequence<size>;
public:

    bool load(handle src, bool convert) {
        if (!isinstance<pybind11::sequence>(src))
            return false;
        const auto seq = reinterpret_borrow<sequence>(src);
        if (seq.size() != size)
            return false;
        return load_impl(seq, convert, indices{});
    }

    template <typename T>
    static handle cast(T &&src, return_value_policy policy, handle parent) {
        return cast_impl(std::forward<T>(src), policy, parent, indices{});
    }

    static PYBIND11_DESCR name() {
        return type_descr(_("Tuple[") + concat(make_caster<Ts>::name()...) + _("]"));
    }

    template <typename T> using cast_op_type = type;

    operator type() & { return implicit_cast(indices{}); }
    operator type() && { return std::move(*this).implicit_cast(indices{}); }

protected:
    template <size_t... Is>
    type implicit_cast(index_sequence<Is...>) & { return type(cast_op<Ts>(hydra::get<Is>(subcasters))...); }
    template <size_t... Is>
    type implicit_cast(index_sequence<Is...>) && { return type(cast_op<Ts>(std::move(hydra::get<Is>(subcasters)))...); }

    static constexpr bool load_impl(const sequence &, bool, detail::index_sequence<>) { return true; }

    template <size_t... Is>
    bool load_impl(const sequence &seq, bool convert, index_sequence<Is...>) {
        for (bool r : {hydra::get<Is>(subcasters).load(seq[Is], convert)...})
            if (!r)
                return false;
        return true;
    }

    /* Implementation: Convert a C++ tuple into a Python tuple */
    template <typename T, size_t... Is>
    static handle cast_impl(T &&src, return_value_policy policy, handle parent, index_sequence<Is...>) {
        std::array<object, size> entries{{
        	reinterpret_steal<pybind11::object>(make_caster<Ts>::cast(hydra::get<Is>(std::forward<T&>(src)), policy, parent))...
        }};
        for (const auto &entry: entries)
            if (!entry)
                return handle();
        tuple result(size);
        int counter = 0;
        for (auto & entry: entries)
            PyTuple_SET_ITEM(result.ptr(), counter++, entry.release().ptr());
        return result.release();
    }

    hydra::pair<make_caster<Ts>...> subcasters;
};



template <typename T1, typename T2> class type_caster<hydra::pair<T1, T2>>
    : public tuple_caster<hydra::pair, T1, T2> {};



}  // namespace detail

}  // namespace pybind11


#endif /* CASTERS_H_ */
