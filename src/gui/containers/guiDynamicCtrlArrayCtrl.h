//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
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

#ifndef _GUIDYNAMICCTRLARRAYCTRL_H_
#define _GUIDYNAMICCTRLARRAYCTRL_H_

#ifndef _GUICONTROL_H_
#include "gui/guiControl.h"
#endif

#include "graphics/dgl.h"
#include "console/console.h"
#include "console/consoleTypes.h"

class GuiDynamicCtrlArrayControl : public GuiControl
{
private:
   typedef GuiControl Parent;

   S32 mCols;
   S32 mRowSize;
   S32 mColSize;
   S32 mRowSpacing;
   S32 mColSpacing;
   bool mResizing;

public:
   GuiDynamicCtrlArrayControl();
   virtual ~GuiDynamicCtrlArrayControl();

   void updateChildControls();
   void resize(const Point2I &newPosition, const Point2I &newExtent);

   void addObject(SimObject *obj);

   void childResized(GuiControl *child);

   void inspectPostApply();

   S32 getCols() { return mCols; }
   void setCols(S32 cols) { mCols = cols; }
   S32 getColSize() { return mColSize; }
   void setColSize(S32 ColSize) { mColSize = ColSize; }
   S32 getRowSize() { return mRowSize; }
   void setRowSize(S32 size) { mRowSize = size; }
   S32 getRowSpacing() { return mRowSpacing; }
   void setRowSpacing(S32 spacing) { mRowSpacing = spacing; }
   S32 getColSpacing() { return mColSpacing; }
   void setColSpacing(S32 spacing) { mColSpacing = spacing; }

   static void initPersistFields();
   DECLARE_CONOBJECT(GuiDynamicCtrlArrayControl);
};

#endif // _GUIDYNAMICCTRLARRAYCTRL_H_