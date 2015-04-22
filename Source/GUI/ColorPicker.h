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

#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Window.h>


namespace Urho3D
{

class URHO3D_API ColorPicker : public Button
{
    OBJECT(ColorPicker)
    
public:
    ColorPicker(Context *context);
    ~ColorPicker();
    
    void SetParameters(UIElement* parent, String name, Color clr, int minWidth, int minHeigth, int maxWidth = 999999, int maxHeigth = 999999 );
    
    void SetStyle(String stylename);
    
    // sets the current color
    void SetPlayerColor(Color clr);
    
    static void RegisterObject(Context *context);
    
protected:
    void HandleClicked(StringHash eventType, VariantMap& eventData);
    
    void HandleBlackClicked(StringHash eventType, VariantMap& eventData);
    void HandleBlueClicked(StringHash eventType, VariantMap& eventData);
    void HandleGreenClicked(StringHash eventType, VariantMap& eventData);
    void HandleMagentaClicked(StringHash eventType, VariantMap& eventData);
    void HandleRedClicked(StringHash eventType, VariantMap& eventData);
    void HandleYellowClicked(StringHash eventType, VariantMap& eventData);
    
    SharedPtr<Window> window;
    Color currentColor;
};

}

#endif // COLORPICKER_H
