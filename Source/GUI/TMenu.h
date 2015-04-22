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

#include <Urho3D/UI/Menu.h>
#include <Urho3D/UI/Window.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/UI/Text.h>

namespace Urho3D
{
    
class URHO3D_API TMenu : public Menu
{
    OBJECT(TMenu);
    
public:
    TMenu(Context* context);
    ~TMenu();
    
    void SetParameters( Urho3D::String name, Urho3D::String caption, bool isSubmenu = false, int minHeigth = 20, int minWidth = 20, int maxHeigth = 2147483647, int maxWidth = 2147483647);
    
    TMenu* AddMenuItem(String name, String caption);
    void AddSeparator();
    
    static void RegisterObject( Context* context );
    
protected:   
    void CreatePopup();
    
    Text* text;
    
    bool firstItem = true;
    bool isSubmenu;
    
    int popupHeigth = 0;
    int popupWidth = 0;
};

}
