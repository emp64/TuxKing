/*
 * Copyright (c) 2014 empirer <email>
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

#include <Urho3D/Urho3D.h>
#include <Urho3D/Input/Controls.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/UI/UIElement.h>
#include <Urho3D/UI/Window.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/CheckBox.h>
#include <Urho3D/UI/Text.h>


/// A simple 'HelloWorld' GUI created purely from code.
/// This sample demonstrates:
///     - Creation of controls and building a UI hierarchy
///     - Loading UI style from XML and applying it to controls
///     - Handling of global and per-control events
/// For more advanced users (beginners can skip this section):
///     - Dragging UIElements
///     - Displaying tooltips
///     - Accessing available Events data (eventData)

using namespace Urho3D;

class HUD : public LogicComponent
{
    OBJECT(HUD);

public:
    /// Construct.
    HUD(Context* context);

    /// Setup after engine initialization and before running the main loop.
    virtual void Start();
    
    /// Handle physics world update. Called by LogicComponent base class.
    //virtual void FixedUpdate(float timeStep);
    
    /// Register object factory and attributes.
    static void RegisterObject(Context* context);
    

protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    /*virtual String GetScreenJoystickPatchString() const { return
        "<patch>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">"
        "        <attribute name=\"Is Visible\" value=\"false\" />"
        "    </add>"
        "</patch>";
    }*/
    
    Button* CreateButton( UIElement* parent, String name, String caption, int minWidth, int minHeigth, int maxWidth = 240000, int maxHeigth = 240000);
    CheckBox* CreateCheckbox( UIElement* parent, String name, String caption );
    CheckBox* CreateCheckbox( UIElement* parent, String name, String caption, int width, int heigth, int positionX, int positionY );
    
    Text* CreateCaption( String name, String text );
    
    

private:
    /// Create and initialize a Window control.
    void InitWindow();
    /// Create and add various common controls for demonstration purposes.
    void InitControls();
    /// Handle any UI control being clicked.
    void HandleControlClicked(StringHash eventType, VariantMap& eventData);
    /// Handle close button pressed and released.
    void HandleClosePressed(StringHash eventType, VariantMap& eventData);
    

    /// The UI's root UIElement.
    SharedPtr<UIElement> uiRoot_;
    /// Remembered drag begin position.
    IntVector2 dragBeginPosition_;
};

