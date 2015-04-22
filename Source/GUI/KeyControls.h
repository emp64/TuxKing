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

#ifndef CONTROLS_H
#define CONTROLS_H

#include <Urho3D/Core/Context.h>
#include <Urho3D/UI/Window.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/UI/UIElement.h>


#include "../HUD/HUD.h"

enum EditedKey {FORWARD, BACKWARD, LEFT, RIGHT};

using namespace Urho3D;


class KeyControls : public UIElement
{
    OBJECT(KeyControls)
    
public:
    KeyControls(Context* context);
    ~KeyControls();
    
    void SetParameters(String caption, int keyForward, int keyBackward, int keyLeft, int keyRight);
    int* GetKeys();
    
    /// Register object factory and attributes.
    static void RegisterObject(Context* context);
    
    
protected:
    
    void HandleButtonForwardClick( StringHash eventType, VariantMap& eventData );
    void HandleButtonBackwardClick( StringHash eventType, VariantMap& eventData );
    void HandleButtonLeftClick( StringHash eventType, VariantMap& eventData );
    void HandleButtonRightClick( StringHash eventType, VariantMap& eventData );
    void HandleKeyClicked(StringHash eventType, VariantMap& eventData);
    
private:
    void UpdateKeyBindings();
    String GetLetter( int letter );
    Button* CreateButton(UIElement* parent, String name, String caption, int minWidth, int minHeigth, int maxWidth = 240000, int maxHeigth = 240000);
    void CreateEditKeyWindow();
    void DestroyKeyBindingWindow();

    SharedPtr<UIElement> uiRoot_;
    
    Button* btForward;
    Button* btBackward;
    Button* btLeft;
    Button* btRight;
    Button* btJump;
    
    int keyForward;
    int keyBackward; 
    int keyLeft; 
    int keyRight;
    
    EditedKey editKey;
};

#endif // CONTROLS_H
