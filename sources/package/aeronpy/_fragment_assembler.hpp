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

#pragma once

#include <Aeron.h>
#include <FragmentAssembler.h>
#include <pybind11/pybind11.h>

#include <memory>
#include <string>
#include <vector>

namespace py = pybind11;

/**
 * @brief Represents an interop proxy for an Aeron fragment_assembler.
 */
class fragment_assembler final
{
public:
    /**
     * @brief Creates a new instance of proxy wrapping given aeron fragment_assembler.
     * @param aeron_fragment_assembler Aeron fragment_assembler to wrap.
     */
    fragment_assembler(py::function& handler);

    //py::function& handler();


private:

    aeron::FragmentAssembler aeron_fragment_assembler_;

};
