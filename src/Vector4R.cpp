#include <pybind11/pybind11.h>
#include "Vector4R.h"
#include "Vector3R.h"
#include "hydra/Types.h"
#include "hydra/Events.h"
#include "hydra/detail/Config.h"
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <sstream>

namespace py = pybind11;

namespace hydra {

  struct PyVector3R {

      inline PyVector3R() {
          impl = new Vector3R();
      }

      inline PyVector3R(GReal_t px, GReal_t py, GReal_t pz) {
          impl = new Vector3R(px, py, pz);
      }

      inline PyVector3R(const PyVector3R& other) {
          impl = new Vector3R(*(other.impl));
      }

      inline PyVector3R& operator*=(GReal_t c) {
          (*impl) *= c;
          return *this;
      }

      inline PyVector3R& operator/=(GReal_t c) {
          (*impl) /= c;
          return *this;
      }

      inline PyVector3R& operator+=(const PyVector3R& other) {
          (*impl) += *(other.impl);
          return *this;
      }

      inline PyVector3R& operator-=(const PyVector3R& other) {
          (*impl) -= *(other.impl);
          return *this;
      }

      inline GReal_t get(GInt_t i) const {
          return impl->get(i);
      }

      inline void set(GInt_t i, GReal_t d) {
          impl->set(i, d);
      }

      inline void set(GReal_t px, GReal_t py, GReal_t pz) {
          impl->set(px, py, pz);
      }

      inline void applyRotateEuler(GReal_t alpha, GReal_t beta, GReal_t gamma) {
          impl->applyRotateEuler(alpha, beta, gamma);
      }

      inline GReal_t dot(const PyVector3R& other) const {
          return impl->dot(*(other.impl));
      }

      inline GReal_t d3mag() const {
          return impl->d3mag();
      }

      inline PyVector3R operator*(GReal_t c) const {
          Vector3R temp = (*(impl)) * c;
          return PyVector3R(temp.get(0), temp.get(1), temp.get(2));
      }

      inline friend PyVector3R operator*(GReal_t c, const PyVector3R &other) {
          Vector3R temp = (*(other.impl)) * c;
          return PyVector3R(temp.get(0), temp.get(1), temp.get(2));
      }

      inline friend GReal_t operator*(const PyVector3R& other1, const PyVector3R& other2) {
          return (*(other1.impl)) * (*(other2.impl));
      }

      inline friend PyVector3R operator/(const PyVector3R& other, GReal_t c) {
          Vector3R temp = (*(other.impl)) / c;
          return PyVector3R(temp.get(0), temp.get(1), temp.get(2));
      }

      inline friend PyVector3R operator+(const PyVector3R& other1, const PyVector3R& other2) {
          Vector3R temp = (*(other1.impl)) + (*(other2.impl));
          return PyVector3R(temp.get(0), temp.get(1), temp.get(2));
      }

      inline friend PyVector3R operator-(const PyVector3R& other1, const PyVector3R& other2) {
          Vector3R temp = (*(other1.impl) - (*(other2.impl)));
          return PyVector3R(temp.get(0), temp.get(1), temp.get(2));
      }

      // Helper function to check if everything is working fine or not.
      inline std::string print() {
          std::stringstream ss;
          ss << *impl;
          return ss.str();
      }

      inline ~PyVector3R() {
          delete impl;
          std::cout << "Destroyed Vector3R" << std::endl;
      }

      Vector3R* impl;
  };

  struct PyVector4R {

        inline PyVector4R() {
            impl = new Vector4R();
        }

        inline PyVector4R(GReal_t e, GReal_t px, GReal_t py, GReal_t pz) {
            impl = new Vector4R(e, px, py, pz);
        }

        inline PyVector4R(const PyVector4R& other) {
            impl = new Vector4R(*(other.impl));
        }

        inline void set(GInt_t i, GReal_t d) {
            impl->set(i, d);
        }

        inline void set(GReal_t e, GReal_t px, GReal_t py, GReal_t pz) {
            impl->set(e, px, py, pz);
        }

        inline PyVector4R& operator*=(GReal_t c) {
            (*impl) *= c;
            return *this;
        }

        inline PyVector4R& operator/=(GReal_t c) {
            (*impl) /= c;
            return *this;
        }

        inline PyVector4R& operator=(const PyVector4R& other) {
            (*impl) = *(other.impl);
            return *this;
        }

        inline PyVector4R& operator+=(const PyVector4R& other) {
            (*impl) += *(other.impl);
            return *this;
        }

        inline PyVector4R& operator-=(const PyVector4R& other) {
            (*impl) -= *(other.impl);
            return *this;
        }

        inline GReal_t get(GInt_t i) const {
            return impl->get(i);
        }

        inline GReal_t cont(const PyVector4R& other) const {
            return impl->cont(*(other.impl));
        }

        inline GReal_t mass2() const {
            return impl->mass2();
        }

        inline GReal_t mass() const {
            return impl->mass();
        }

        inline void applyRotateEuler(GReal_t alpha, GReal_t beta, GReal_t gamma) {
            impl->applyRotateEuler(alpha, beta, gamma);
        }

        inline void applyBoostTo(const PyVector4R& other, bool inverse = false) {
            impl->applyBoostTo(*(other.impl), inverse);
        }

        inline void applyBoostTo(const PyVector3R& other, bool inverse = false) {
            impl->applyBoostTo(*(other.impl), inverse);
        }

        inline void applyBoostTo(const GReal_t bx, const GReal_t by, const GReal_t bz, bool inverse = false) {
            impl->applyBoostTo(bx, by, bz, inverse);
        }

        inline PyVector4R cross(const PyVector4R& other) {
            Vector4R temp = impl->cross(*(other.impl));
            return PyVector4R(temp.get(0), temp.get(1), temp.get(2), temp.get(3));
        }

        inline GReal_t dot(const PyVector4R& other) const {
            return impl->dot(*(other.impl));
        }

        inline GReal_t d3mag() const {
            return impl->d3mag();
        }


        inline GReal_t scalartripler3(const PyVector4R& other1, const PyVector4R& other2, const PyVector4R& other3) const {
            return impl->scalartripler3(*(other1.impl), *(other2.impl), *(other3.impl));
        }

        inline GReal_t dotr3(const PyVector4R& other1, const PyVector4R& other2) const {
            return impl->dotr3(*(other1.impl), *(other2.impl));
        }

        inline GReal_t mag2r3(const PyVector4R& other) const {
            return impl->mag2r3(*(other.impl));
        }

        inline GReal_t magr3(const PyVector4R& other) const {
            return impl->magr3(*(other.impl));
        }

        inline PyVector4R operator*(GReal_t c) const {
            Vector4R temp = (*(impl)) * c;
            return PyVector4R(temp.get(0), temp.get(1), temp.get(2), temp.get(3));
        }

        inline friend PyVector4R operator*(GReal_t c, const PyVector4R &other) {
            Vector4R temp = (*(other.impl)) * c;
            return PyVector4R(temp.get(0), temp.get(1), temp.get(2), temp.get(3));
        }

        inline friend GReal_t operator*(const PyVector4R& other1, const PyVector4R& other2) {
            return (*(other1.impl)) * (*(other2.impl));
        }

        inline friend PyVector4R operator/(const PyVector4R& other, GReal_t c) {
            Vector4R temp = (*(other.impl)) / c;
            return PyVector4R(temp.get(0), temp.get(1), temp.get(2), temp.get(3));
        }

        inline friend PyVector4R operator+(const PyVector4R& other1, const PyVector4R& other2) {
            Vector4R temp = (*(other1.impl)) + (*(other2.impl));
            return PyVector4R(temp.get(0), temp.get(1), temp.get(2), temp.get(3));
        }

        inline friend PyVector4R operator-(const PyVector4R& other1, const PyVector4R& other2) {
            Vector4R temp = (*(other1.impl) - (*(other2.impl)));
            return PyVector4R(temp.get(0), temp.get(1), temp.get(2), temp.get(3));
        }

        // Helper function to check if everything is working fine or not.
        inline std::string print() {
            std::stringstream ss;
            ss << *impl;
            return ss.str();
        }

        inline ~PyVector4R() {
            delete impl;
            std::cout << "Destroyed Vector4R" << std::endl;
        }

        Vector4R* impl;

    };

}


PYBIND11_MODULE(Vector4R, m) {
  py::class_< hydra::PyVector3R >(m, "Vector3R")
    .def(py::init<>())
    .def(py::init<hydra::GReal_t, hydra::GReal_t, hydra::GReal_t>())
    .def(py::init<hydra::PyVector3R>())
    .def("__imul__", &hydra::PyVector3R::operator*=)
    .def("__itruediv__", &hydra::PyVector3R::operator/=)
    .def("__iadd__", &hydra::PyVector3R::operator+=)
    .def("__isub__", &hydra::PyVector3R::operator-=)
    .def("set", (void (hydra::PyVector3R::*)(hydra::GInt_t, hydra::GReal_t)) &hydra::PyVector3R::set)
    .def("set", (void (hydra::PyVector3R::*)(hydra::GReal_t, hydra::GReal_t, hydra::GReal_t)) &hydra::PyVector3R::set)
    .def("applyRotateEuler", &hydra::PyVector3R::applyRotateEuler)
    .def("get", &hydra::PyVector3R::get)
    .def("dot", &hydra::PyVector3R::dot)
    .def("d3mag", &hydra::PyVector3R::d3mag)
    .def("__repr__", [](hydra::PyVector3R& e) { return e.print(); })
    .def(hydra::GReal_t() * py::self)
    .def(py::self * hydra::GReal_t())
    .def(py::self * hydra::PyVector3R())
    .def(py::self / hydra::GReal_t())
    .def(py::self + hydra::PyVector3R())
    .def(py::self - hydra::PyVector3R())
    .def("__eq__", [](const hydra::PyVector3R& one, const hydra::PyVector3R& two){
        for (auto i = 0; i < 3; ++i)
            if ((*(one.impl)).get(i) != ((*(two.impl)).get(i)))
                return false;
        return true;
    }, py::is_operator())
    .def("__ne__", [](const hydra::PyVector3R& one, const hydra::PyVector3R& two){
        for (auto i = 0; i < 3; ++i)
            if ((*(one.impl)).get(i) != ((*(two.impl)).get(i)))
                return true;
        return false;
    }, py::is_operator())
    .def("__getitem__", [](hydra::PyVector3R& obj, hydra::GInt_t idx){
        return (*(obj.impl)).get(idx);
    }, py::is_operator())
    .def("__setitem__", [](hydra::PyVector3R& obj, hydra::GInt_t idx, hydra::GReal_t value){
        return (*(obj.impl)).set(idx, value);
    }, py::is_operator())
  ;

  py::class_< hydra::PyVector4R >(m, "Vector4R")
    .def(py::init<>())
    .def(py::init<hydra::GReal_t, hydra::GReal_t, hydra::GReal_t, hydra::GReal_t>())
    .def(py::init<hydra::PyVector4R>())
    .def("set", (void (hydra::PyVector4R::*)(hydra::GInt_t, hydra::GReal_t)) &hydra::PyVector4R::set)
    .def("set", (void (hydra::PyVector4R::*)(hydra::GReal_t, hydra::GReal_t, hydra::GReal_t, hydra::GReal_t)) &hydra::PyVector4R::set)
    .def("__imul__", &hydra::PyVector4R::operator*=)
    .def("__itruediv__", &hydra::PyVector4R::operator/=)
    .def("assign", &hydra::PyVector4R::operator=)
    .def("__iadd__", &hydra::PyVector4R::operator+=)
    .def("__isub__", &hydra::PyVector4R::operator-=)
    .def("get", &hydra::PyVector4R::get)
    .def("cont", &hydra::PyVector4R::cont)
    .def("mass2", &hydra::PyVector4R::mass2)
    .def("mass", &hydra::PyVector4R::mass)
    .def("applyRotateEuler", &hydra::PyVector4R::applyRotateEuler)
//    .def("applyBoostTo", &hydra::PyVector4R::applyBoostTo, "other"_a, "inverse"_a=false) // Not Working
    .def("applyBoostTo", (void (hydra::PyVector4R::*)(const hydra::PyVector4R&, bool)) &hydra::PyVector4R::applyBoostTo, py::arg("other"), py::arg("inverse")=false)
    .def("applyBoostTo", (void (hydra::PyVector4R::*)(const hydra::PyVector3R&, bool)) &hydra::PyVector4R::applyBoostTo, py::arg("other"), py::arg("inverse")=false)
    .def("applyBoostTo", (void (hydra::PyVector4R::*)(const hydra::GReal_t, const hydra::GReal_t, const hydra::GReal_t, bool inverse)) &hydra::PyVector4R::applyBoostTo, py::arg("bx"), py::arg("by"), py::arg("bz"), py::arg("inverse")=false)
    .def("cross", &hydra::PyVector4R::cross)
    .def("dot", &hydra::PyVector4R::dot)
    .def("d3mag", &hydra::PyVector4R::d3mag)
//    .def("scalartripler3", &hydra::PyVector4R::scalartripler3)
    .def("dotr3", &hydra::PyVector4R::dotr3)
    .def("mag2r3", &hydra::PyVector4R::mag2r3)
    .def("magr3", &hydra::PyVector4R::magr3)
    .def("__repr__", [](hydra::PyVector4R& e) { return e.print(); })
    .def(hydra::GReal_t() * py::self)
    .def(py::self * hydra::GReal_t())
    .def(py::self * hydra::PyVector4R())
    .def(py::self / hydra::GReal_t())
    .def(py::self + hydra::PyVector4R())
    .def(py::self - hydra::PyVector4R())
    .def("__eq__", [](const hydra::PyVector4R& one, const hydra::PyVector4R& two){
        for (auto i = 0; i < 4; ++i)
            if ((*(one.impl)).get(i) != ((*(two.impl)).get(i)))
                return false;
        return true;
    }, py::is_operator())
    .def("__ne__", [](const hydra::PyVector4R& one, const hydra::PyVector4R& two){
        for (auto i = 0; i < 4; ++i)
            if ((*(one.impl)).get(i) != ((*(two.impl)).get(i)))
                return true;
        return false;
    }, py::is_operator())
    .def("__getitem__", [](hydra::PyVector4R& obj, hydra::GInt_t idx){
        return (*(obj.impl)).get(idx);
    }, py::is_operator())
    .def("__setitem__", [](hydra::PyVector4R& obj, hydra::GInt_t idx, hydra::GReal_t value){
        return (*(obj.impl)).set(idx, value);
    }, py::is_operator())
    ;
}


/*
#ifndef VECTOR4R_H_
#define VECTOR4R_H_

#include <math.h>
#include <iostream>

// #include <hydra/detail/Config.h>
#include <hydra/Types.h>
// #include <hydra/Vector3R.h>

using std::ostream;

namespace hydra {
  class Vector4R {
    // Private Inline
    inline friend Vector4R operator*(GReal_t d, const Vector4R& v2);
    inline friend Vector4R operator*(const Vector4R& v2, GReal_t d);
    inline friend Vector4R operator/(const Vector4R& v2, GReal_t d);
    inline friend GReal_t operator*(const Vector4R& v1, const Vector4R& v2);
    inline friend Vector4R operator+(const Vector4R& v1, const Vector4R& v2);
    inline friend Vector4R operator-(const Vector4R& v1, const Vector4R& v2);

  public:
    inline Vector4R(); // done
    inline Vector4R(GReal_t e, GReal_t px, GReal_t py, GReal_t pz); // done
    inline Vector4R(const Vector4R& other); // done
    inline void set(GInt_t i, GReal_t d); // done
    inline void set(GReal_t e, GReal_t px, GReal_t py, GReal_t pz); // done
    inline Vector4R& operator*=(GReal_t c); // done
    inline Vector4R& operator/=(GReal_t c); // done
    inline Vector4R& operator=(const Vector4R& v2); // done
    inline Vector4R& operator+=(const Vector4R& v2); // done
    inline Vector4R& operator-=(const Vector4R& v2); // done
    inline GReal_t get(GInt_t i) const; // done
    inline GReal_t cont(const Vector4R& v4) const; // done
    inline friend std::ostream& operator<<(std::ostream& s, const Vector4R& v); // done
    inline GReal_t mass2() const; // done
    inline GReal_t mass() const; // done
    inline void applyRotateEuler(GReal_t alpha, GReal_t beta, GReal_t gamma); // done
    inline void applyBoostTo(const Vector4R& p4, bool inverse = false); // done
    inline void applyBoostTo(const Vector3R& boost, bool inverse = false); // done
    inline void applyBoostTo(const GReal_t bx, const GReal_t by, const GReal_t bz, bool inverse = false); // done
    inline Vector4R cross(const Vector4R& v2); // done
    inline GReal_t dot(const Vector4R& v2) const; // done
    inline GReal_t d3mag() const; // done
    inline GReal_t scalartripler3(const Vector4R& p1, const Vector4R& p2, const Vector4R& p3) const; // done
    inline GReal_t dotr3(const Vector4R& p1, const Vector4R& p2) const; // done
    inline GReal_t mag2r3(const Vector4R& p1) const; // done
    inline GReal_t magr3(const Vector4R& p1) const; // done

  private:

    GReal_t v[4];
    inline GReal_t Square(GReal_t x) const {
      return x * x;
    }

  };

  Vector4R rotateEuler(const Vector4R& rs, GReal_t alpha, GReal_t beta, GReal_t gamma);
  Vector4R boostTo(const Vector4R& rs, const Vector4R& p4, bool inverse = false);
  Vector4R boostTo(const Vector4R& rs, const Vector3R& boost, bool inverse = false);

  inline Vector4R operator*(GReal_t c, const Vector4R& v2) {
    return Vector4R(v2) *= c;
  }

  inline Vector4R operator*(const Vector4R& v2, GReal_t c) {
    return Vector4R(v2) *= c;
  }

  inline Vector4R operator/(const Vector4R& v2, GReal_t c) {
    return Vector4R(v2) /= c;
  }

  inline GReal_t operator*(const Vector4R& v1, const Vector4R& v2) {
    return v1.v[0] * v2.v[0] - v1.v[1] * v2.v[1] - v1.v[2] * v2.v[2] - v1.v[3] * v2.v[3];
  }

  inline Vector4R operator-(const Vector4R& v1, const Vector4R& v2) {
    return Vector4R(v1) -= v2;
  }

  inline Vector4R operator+(const Vector4R& v1, const Vector4R& v2) {
    return Vector4R(v1) += v2;
  }

  inline Vector4R rotateEuler(const Vector4R& rs, GReal_t alpha, GReal_t beta, GReal_t gamma) {
    Vector4R tmp(rs);
    tmp.applyRotateEuler(alpha, beta, gamma);
    return tmp;
  }


  inline Vector4R boostTo(const Vector4R& rs, const Vector4R& p4, bool inverse) {
    Vector4R tmp(rs);
    tmp.applyBoostTo(p4, inverse);
    return tmp;
  }


  inline Vector4R boostTo(const Vector4R& rs, const Vector3R& boost, bool inverse) {
    Vector4R tmp(rs);
    tmp.applyBoostTo(boost, inverse);
    return tmp;
  }

  inline ostream& operator<<(ostream& s, const Vector4R& v) {
    s << "(" << v.v[0] << "," << v.v[1] << "," << v.v[2] << "," << v.v[3] << ")";
    return s;
  }

}

#include "Vector4R.inl"
#endif // VECTOR4R_H_
 */
