﻿//-----------------------------------------------------------------------------
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

#include "c-interface/c-interface.h"

namespace Scene
{

   ConsoleMethodGroupBeginWithDocs(PhysicsBaseComponent, BaseComponent)

   ConsoleMethod(PhysicsBaseComponent, setLinearVelocity, ConsoleVoid, 3, 3, (""))
   {
      Point3F velocity;
      Con::setData(TypePoint3F, velocity, 0, 1, &argv[2]);

      object->setLinearVelocity(velocity);
   }

   ConsoleMethodGroupEndWithDocs(PhysicsBaseComponent)

   extern "C" {
      DLL_PUBLIC PhysicsBaseComponent* PhysicsBaseComponentCreateInstance()
      {
         return new PhysicsBaseComponent();
      }

      DLL_PUBLIC void PhysicsBaseComponentSetLinearVelocity(PhysicsBaseComponent* component, CInterface::Point3FParam velocity)
      {
         component->setLinearVelocity(velocity);
      }
   }
}