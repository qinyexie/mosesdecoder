#include <pybind11/pybind11.h>
#include "moses/ExportInterface.h"

namespace py = pybind11;

PYBIND11_PLUGIN(translate) {
    py::module m("translate", "python moses");

    py::class_<SimpleTranslationInterface>(m, "SimpleTranslationInterface")
        .def(py::init<const std::string &>())
        .def("translate", &SimpleTranslationInterface::translate);

    return m.ptr();
}
