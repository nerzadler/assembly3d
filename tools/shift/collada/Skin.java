/*
 * Copyright (c) 2011 Michael Nischt
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
package org.interaction3d.assembly.tools.shift.collada;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import org.interaction3d.assembly.tools.shift.util.Assembly;


final class Skin
{
  private float[] bindMatrix;

  private String[] jointNames;
  private float[] jointBinding;

  float[] vertexWeights;

  private int[] vertexCounts;
  private int[] vertexJointIndices;
  private int[] vertexWeightIndices;

  void foo()
  {
    int joints = jointNames.length;

    int[][] vertices = new int[joints][];
    float[][] weights = new float[joints][];


    int[] counts = new int[joints];

    int index = 0;
    for(int v=0; v<vertexCounts.length; v++)
    {
      for(int i=0; i<vertexCounts[v]; i++)
      {
        int j = vertexJointIndices[index++];
        counts[j]++;
      }
    }

    for(int j=0; j<joints; j++)
    {
      int count = counts[j];
      vertices[j] = new int[count];
      weights[j] = new float[count];
    }

    index=0;
    for(int v=0; v<vertexCounts.length; v++)
    {
      for(int i=0; i<vertexCounts[v]; i++)
      {
        int j = vertexJointIndices[index];
        float w = vertexWeights[vertexWeightIndices[index]];
        index++;
        int ndx = --counts[j];
        vertices[j][ndx] = v;
        weights[j][ndx] = w;
      }
    }
  }


  void convert(String name, Assembly assembly)
  {
    StringBuilder xml = new StringBuilder();

    ByteBuffer buffer = ByteBuffer.allocateDirect(0).order(ByteOrder.LITTLE_ENDIAN);

    //assembly.assemble(name, xml, buffer);
  }

}