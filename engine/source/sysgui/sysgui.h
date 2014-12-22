//-----------------------------------------------------------------------------
// Copyright (c) 2014 Andrew Mac
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

#ifndef _SYSGUI_H_
#define _SYSGUI_H_

#ifndef _EVENT_H_
#include "platform/event.h"
#endif

namespace SysGUI
{
   struct Element
   {
      struct Text
      {
         char val[256];
      };

      enum Type
      {
         BeginScrollArea,
         EndScrollArea,
         Label,
         CheckBox,
         Slider,
         TextInput,
         Separator,
         List,
         Button,
         COUNT
      };

      Element()
      {
         _hidden = false;
         _align_right = false;
         _align_bottom = false;
      }

      bool           _hidden;
      U32            _id;
      Type           _type;
      U32            _x;
      U32            _y;
      U32            _width;
      U32            _height;
      S32            _min;
      S32            _max;

      bool           _align_right;
      bool           _align_bottom;

      Text           _value_label;
      Text           _value_text;
      S32            _value_int;
      bool           _value_bool;
      Vector<Text>   _value_list;
      S32            _selected_list_item;
      Text           _value_script;

   };

   extern Vector<Element>  elementList;
   extern S32              elementMaxID;

   extern Point2F mousePosition;
   extern bool    mouseButtonOne;
   extern bool    mouseButtonTwo;
   extern S32     mouseScroll;

   extern Vector<char>  keyboardQueue;
   extern U64           _keyboardLastInput;

   // 
   void init();
   void destroy();
   void setEnabled(bool val);
   void render();

   S32 addElement(Element elem);
   S32 getNewID();
   Element* getElementById(S32 id);

   // Controls
   S32 beginScrollArea(const char* title, U32 x, U32 y, U32 width, U32 height);
   S32 endScrollArea();
   S32 label(const char* label);
   S32 list();
   S32 checkBox(const char* label, bool value);
   S32 slider(const char* label, S32 value, S32 min, S32 max);
   S32 textInput(const char* label, const char* text);
   S32 button(const char* label, const char* script);
   S32 separator();

   bool processInputEvent(const InputEvent *event);
   bool updateMousePosition(Point2F pt);

   void  addListValue(S32 id, const char* val);
   const char* getListValue(S32 id, S32 index);

   void  setElementHidden(S32 id, bool val);
   char* getLabelValue(S32 id);
   void  setLabelValue(S32 id, const char* val);
   char* getTextValue(S32 id);
   void  setTextValue(S32 id, const char* val);
   S32   getIntValue(S32 id);
   void  setIntValue(S32 id, S32 val);
   bool  getBoolValue(S32 id);
   void  setBoolValue(S32 id, bool val);

   void  alignLeft(S32 id);
   void  alignRight(S32 id);
   void  alignTop(S32 id);
   void  alignBottom(S32 id);
}

#endif // _SYSGUI_H_