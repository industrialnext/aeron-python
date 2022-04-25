/*
 * Copyright 2018 Fairtide Pte. Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "_fragment_assembler.hpp"

#include <fmt/format.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/functional.h>

using namespace std;
using namespace std::chrono;
using namespace aeron;
using namespace fmt;
namespace py = pybind11;


fragment_assembler::fragment_assembler(py::function& handler)
    : aeron_fragment_assembler_(
            [handler](auto& buffer, auto offset, auto length, auto& header)
            {
                py::gil_scoped_acquire gil_guard;

                printf("Got here\n");

                auto data_info = py::buffer_info(
                        buffer.buffer() + offset,
                        sizeof(uint8_t),
                        py::format_descriptor<uint8_t>::format(),
                        length);

                handler(py::memoryview(data_info));
                //if (is_complete_poll_handler(handler)) // expected performance hit
                //    handler(py::memoryview(data_info), header);
                //else
                //    handler(py::memoryview(data_info));
            })
{}

fragment_handler_t fragment_assembler::handler() {
    return aeron_fragment_assembler_.handler();
}

PYBIND11_MODULE(_fragment_assembler, m)
{
    static constexpr auto default_fragment_limit = 10;

    py::class_<fragment_assembler>(m, "FragmentAssembler")
            .def(py::init<py::function &>(),
                    py::call_guard<py::gil_scoped_release>())
            .def("handler", &fragment_assembler::handler);
            //.def("poll", &fragment_assembler::poll,
            //        py::arg("handler"),
            //        py::arg("fragment_limit") = default_fragment_limit,
            //        py::call_guard<py::gil_scoped_release>())
            //.def("__bool__", &fragment_assembler::__bool__)
            //.def("__str__", &fragment_assembler::__str__);

}




