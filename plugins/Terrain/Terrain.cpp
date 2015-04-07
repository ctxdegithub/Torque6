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

#include "Terrain.h"
#include <plugins/plugins_shared.h>

#include <sim/simObject.h>
#include <3d/rendering/common.h>
#include <graphics/utilities.h>
#include <bx/fpumath.h>

#include "TerrainCell.h"

// Link to Editor Plugin
#include "TerrainEditor.h"

using namespace Plugins;

bool terrainEnabled = false;
bgfx::TextureHandle terrainTextures[1] = {BGFX_INVALID_HANDLE};
bgfx::FrameBufferHandle terrainTextureBuffer = BGFX_INVALID_HANDLE;
bgfx::ProgramHandle terrainMegaShader = BGFX_INVALID_HANDLE;

// Called when the plugin is loaded.
void create()
{
   // Register Console Functions
   Link.Con.addCommand("Terrain", "loadEmptyTerrain", loadEmptyTerrain, "", 5, 5);
   Link.Con.addCommand("Terrain", "loadHeightMap", loadHeightMap, "", 4, 4);
   Link.Con.addCommand("Terrain", "loadTexture", loadTexture, "", 5, 5);
   Link.Con.addCommand("Terrain", "enable", enableTerrain, "", 1, 1);
   Link.Con.addCommand("Terrain", "disable", disableTerrain, "", 1, 1);
   Link.Con.addCommand("Terrain", "stitchEdges", stitchEdges, "", 1, 1);

   // Load Shader
   Graphics::ShaderAsset* terrainMegaShaderAsset = Plugins::Link.Graphics.getShaderAsset("Terrain:megaShader");
   if ( terrainMegaShaderAsset )
      terrainMegaShader = terrainMegaShaderAsset->getProgram();

   const U32 samplerFlags = 0
      | BGFX_TEXTURE_RT
      | BGFX_TEXTURE_MIN_POINT
      | BGFX_TEXTURE_MAG_POINT
      | BGFX_TEXTURE_MIP_POINT
      | BGFX_TEXTURE_U_CLAMP
      | BGFX_TEXTURE_V_CLAMP;

   // G-Buffer
   terrainTextures[0] = Link.bgfx.createTexture2D(2048, 2048, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT, NULL);
   terrainTextureBuffer = Link.bgfx.createFrameBuffer(1, terrainTextures, false);
   Link.requestPluginAPI("Editor", loadEditorAPI);
}

void render()
{
   F32 proj[16];
   bx::mtxOrtho(proj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f);
   Link.bgfx.setViewFrameBuffer(Graphics::ViewTable::TerrainTexture, terrainTextureBuffer);
   Link.bgfx.setViewTransform(Graphics::ViewTable::TerrainTexture, NULL, proj, BGFX_VIEW_STEREO, NULL);
   Link.bgfx.setViewRect(Graphics::ViewTable::TerrainTexture, 0, 0, 2048, 2048);

   // YELLOW for debugging.
   Link.bgfx.setViewClear(Graphics::ViewTable::TerrainTexture, BGFX_CLEAR_COLOR, 0xffff00ff, 1.0, 0); 
   Link.bgfx.submit(Graphics::ViewTable::TerrainTexture, 0);

   Link.bgfx.setProgram(terrainMegaShader);
   Link.bgfx.setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE, 0);
   Link.Graphics.fullScreenQuad(2048, 2048);
   Link.bgfx.submit(Graphics::ViewTable::TerrainTexture, 0);

   for(U32 n = 0; n < terrainGrid.size(); ++n)
   {
      terrainGrid[n].updateTexture();
   }
}

void destroy()
{
   //
   Link.bgfx.destroyFrameBuffer(terrainTextureBuffer);
}

// Console Functions
void enableTerrain(SimObject *obj, S32 argc, const char *argv[])
{
   terrainEnabled = true;
}

void disableTerrain(SimObject *obj, S32 argc, const char *argv[])
{
   terrainEnabled = false;
}

void loadEmptyTerrain(SimObject *obj, S32 argc, const char *argv[])
{
   S32 gridX = dAtoi(argv[1]);
   S32 gridY = dAtoi(argv[2]);
   S32 width = dAtoi(argv[3]);
   S32 height = dAtoi(argv[4]);
   for(U32 n = 0; n < terrainGrid.size(); ++n)
   {
      if ( terrainGrid[n].gridX != gridX || terrainGrid[n].gridY != gridY )
         continue;

      terrainGrid[n].loadEmptyTerrain(width, height);
      return;
   }

   // Create new cell
   TerrainCell cell(&terrainTextures[0], gridX, gridY);
   terrainGrid.push_back(cell);
   terrainGrid.back().loadEmptyTerrain(width, height);
}

void loadHeightMap(SimObject *obj, S32 argc, const char *argv[])
{
   S32 gridX = dAtoi(argv[1]);
   S32 gridY = dAtoi(argv[2]);
   for(U32 n = 0; n < terrainGrid.size(); ++n)
   {
      if ( terrainGrid[n].gridX != gridX || terrainGrid[n].gridY != gridY )
         continue;

      terrainGrid[n].loadHeightMap(argv[3]);
      return;
   }

   // Create new cell
   TerrainCell cell(&terrainTextures[0], gridX, gridY);
   terrainGrid.push_back(cell);
   terrainGrid.back().loadHeightMap(argv[3]);
}

void loadTexture(SimObject *obj, S32 argc, const char *argv[])
{
   S32 gridX = dAtoi(argv[1]);
   S32 gridY = dAtoi(argv[2]);
   for(U32 n = 0; n < terrainGrid.size(); ++n)
   {
      if ( terrainGrid[n].gridX != gridX || terrainGrid[n].gridY != gridY )
         continue;

      terrainGrid[n].loadTexture(dAtoi(argv[3]), argv[4]);
      return;
   }

   // Create new cell
   TerrainCell cell(&terrainTextures[0], gridX, gridY);
   terrainGrid.push_back(cell);
   terrainGrid.back().loadTexture(dAtoi(argv[3]), argv[4]);
}

