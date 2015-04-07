//-----------------------------------------------------------------------------
// Copyright (c) 2015 Andrew Mac
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef _TERRAINBUILDER_H_
#define _TERRAINBUILDER_H_

#ifndef _PLUGINS_SHARED_H
#include <plugins/plugins_shared.h>
#endif

#ifndef _SIM_OBJECT_H_
#include <sim/simObject.h>
#endif

struct PosUVColorVertex
{
   F32 m_x;
	F32 m_y;
	F32 m_z;
	F32 m_u;
	F32 m_v;
	U32 m_abgr;
};

class TerrainCell
{
protected:
   Vector<PosUVColorVertex> mVerts;
   Vector<uint16_t> mIndices;

   bgfx::TextureHandle*             mTexture;
   bgfx::TextureHandle              mTextures[3];
   Vector<Rendering::TextureData>   mTextureData;
   Vector<Rendering::UniformData>   mUniformData;
   bgfx::ProgramHandle              mShader;
   Rendering::RenderData*           mRenderData;
   bgfx::DynamicVertexBufferHandle  mDynamicVB;
   bgfx::DynamicIndexBufferHandle   mDynamicIB;
   bgfx::VertexBufferHandle         mVB;
   bgfx::IndexBufferHandle          mIB;

public:
   S32   gridX;
   S32   gridY;
   F32*  heightMap;
   U32   width;
   U32   height;
   F32   maxTerrainHeight;
   Rendering::UniformData* u_focusPoint;

   TerrainCell(bgfx::TextureHandle* _texture, S32 _gridX, S32 _gridY);
   ~TerrainCell();

   Point3F getWorldSpacePos(U32 x, U32 y);
   void loadTexture(U32 layer, const char* path);
   void loadHeightMap(const char* path);
   void loadEmptyTerrain(S32 _width, S32 _height);
   void refresh();
   void rebuild();
   void updateTexture();
   void refreshVertexBuffer();
   void refreshIndexBuffer();
};

extern Vector<TerrainCell> terrainGrid;
void stitchEdges(SimObject *obj, S32 argc, const char *argv[]);

#endif