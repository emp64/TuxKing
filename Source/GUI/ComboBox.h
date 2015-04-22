/*
 * Copyright (c) 2015 empirer <empirer64@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#pragma once

#include <Urho3D/UI/DropDownList.h>
#include <Urho3D/Core/Context.h>

namespace Urho3D
{

class URHO3D_API ComboBox : public DropDownList
{
    OBJECT(ComboBox);
    
public:
    ComboBox(Context* context);
    ~ComboBox();
    
    void SetParameters( Urho3D::String name, Urho3D::String text = "", int minHeigth = 20, int minWidth = 20, int maxHeigth = 2147483647, int maxWidth = 2147483647 );
    
    void SetItemsVector(Vector<String> items);
    void SetStyle(String stylename);
    
    static void RegisterObject(Context* context);
    
protected:
    void HandleSelectedChanged( Urho3D::StringHash eventType, Urho3D::VariantMap& eventData );
};

}

