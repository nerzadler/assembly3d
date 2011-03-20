/*
 * Copyright (c) 2011 Peter Vasil
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the project's author nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "PrimGen.h"
#include "primitives/Plane.h"
#include "primitives/Cube.h"
#include "primitives/Sphere.h"
#include "primitives/Torus.h"
#include <stdio.h>
#include <stdarg.h>

using namespace std;

PrimGen::PrimGen() : m_prim(0)
{
}

PrimGen::~PrimGen()
{
    SAFE_DELETE(m_prim)
}

void PrimGen::createMesh(Mesh* mesh, int primType, std::vector<float> values)
{
    switch(primType)
    {
    case PRIM_TYPE_PLANE:
        m_prim = new Plane(values[0]);
        break;
    case PRIM_TYPE_CUBE:
        m_prim = new Cube(values[0]);
        break;
    case PRIM_TYPE_SPHERE:
        m_prim = new Sphere(values[0], (int)values[1]);
        break;
    case PRIM_TYPE_TORUS:
        m_prim = new Torus(values[0], values[1],
                           (int)values[2], (int)values[3]);
        break;
    default:
        m_prim = 0;
    }
    m_prim->create(mesh);

}
