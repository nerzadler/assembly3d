/*
 * Copyright (c) 2011 Peter Vasil, Micheal Nischt
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

#include "Mesh.h"
#include "ProgramSimple.h"

Mesh::Mesh(ProgramSimple* p) : prog(p)
{
}

Mesh::~Mesh() 
{
    glDeleteBuffers(nAttributes, buffers);
    delete buffers;
    delete nTriangles;
    delete attrSizes;
    delete attrTypeSizes;
    delete attrTypes;
    attrNames.clear();
    groupNames.clear();
}

GLvoid Mesh::draw() 
{
    bindBuffers();
    glDrawElements(GL_TRIANGLES, 3*nTotalTriangles, indexType, (GLvoid*) 0);
    disableBuffers();
}

GLvoid Mesh::draw(GLuint index) 
{
    bindBuffers();
    GLsizei count = nTriangles[index+1] - nTriangles[index];
    glDrawElements(GL_TRIANGLES, 3*count, indexType, (GLvoid*) (nTriangles[index]*3*indexSize));
    disableBuffers();
}

void Mesh::bindBuffers()//GLuint position,GLuint normal, GLuint texcoord)
{
    for(int i = 0; i < nAttributes; ++i)
    {
        GLint attrLoc = -1;
        if(attrNames[i].compare("POSITION") == 0)
        {
            attrLoc = prog->position();
        }
        else if(attrNames[i].compare("NORMAL") == 0)
        {
            attrLoc = prog->normal();
        }
        else if(attrNames[i].compare("TEXCOORD") == 0)
        {
            attrLoc = prog->texCoord();
        }
        glBindBuffer(GL_ARRAY_BUFFER, buffers[i]);
        glVertexAttribPointer(attrLoc, attrSizes[i], attrTypes[i], GL_FALSE, 0, (GLvoid*) 0);
        glEnableVertexAttribArray(attrLoc);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[nAttributes]);
}

void Mesh::disableBuffers()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    for(int i = 0; i < nAttributes; ++i)
    {
        GLint attrLoc = -1;
        if(attrNames[i].compare("POSITION") == 0)
        {
            attrLoc = prog->position();
        }
        else if(attrNames[i].compare("NORMAL") == 0)
        {
            attrLoc = prog->normal();
        }
        else if(attrNames[i].compare("TEXCOORD") == 0)
        {
            attrLoc = prog->texCoord();
        }
        
        glDisableVertexAttribArray(attrLoc);
    }
}

