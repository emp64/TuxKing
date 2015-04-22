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

#ifndef MAINMENU_H
#define MAINMENU_H

#include <Urho3D/Scene/LogicComponent.h>

#include "HUD.h"


class MainMenu : public HUD
{
    OBJECT(MainMenu);
    
public:
    MainMenu(Context* context);
    ~MainMenu();
    
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

private:
    /// Create and initialize a Window control.
    void InitMainMenuWindow();
    /// Create and add various common controls for demonstration purposes.
    void InitControls();
    
    void CreateMainMenu();
    void CreatePlayMenu();
    void CreateOptionsWindow();
    void CreateCreditsWindow();
    
    void CreatePreGameMenu();
    void CreateLevelMenu();
    void CreateIntroWindow();
    
    void CreateQuitWindow();
    
    void CreateInGameMenu();
    void HideInGameMenu();
    // Deletes all buttons (children) from wMainMenu
    void CleanMainMenu();
    // Deletes the Main menu window
    void DeleteMainMenu();
    // Deletes all the windows like Settings window, Credits window ...
    void DeleteWindows();
    
    void DeletePreGameMenu();
    /// Handle any UI control being clicked.
    void HandleControlClicked(StringHash eventType, VariantMap& eventData);
    /// Handle close button pressed and released.
    //void HandleQuitPressed(StringHash eventType, VariantMap& eventData);
    
    void HandlePlayClicked(StringHash eventType, VariantMap& eventData);
    void HandleOptionsClicked(StringHash eventType, VariantMap& eventData);
    void HandleMapEditorClicked(StringHash eventType, VariantMap& eventData);
    void HandleCreditsClicked(StringHash eventType, VariantMap& eventData);
    void HandleQuitClicked(StringHash eventType, VariantMap& eventData);
    
    void HandleLabyrinthClicked(StringHash eventType, VariantMap& eventData);
    void HandleDanceClicked(StringHash eventType, VariantMap& eventData);
    
    void HandlePlayMenuClicked(StringHash eventType, VariantMap& eventData);
    void HandleMainMenuClicked(StringHash eventType, VariantMap& eventData);
    void HandleLevelMenuClicked(StringHash eventType, VariantMap& eventData);

    void HandleOptionsApplyClicked(StringHash eventType, VariantMap& eventData);
    
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    
    void HandleExitClicked(StringHash eventType, VariantMap& eventData);
    void HandleCancelExitClicked(StringHash eventType, VariantMap& eventData);
    
    
    void HandleLevel01Clicked(StringHash eventType, VariantMap& eventData);
    
    
    /// The Window.
    //SharedPtr<Window> window_;
    WeakPtr<Window> wMainMenu;
    /// Pre game window with all the game settings and stuff
    WeakPtr<Window> wPreGame;
    /// Settings window
    WeakPtr<Window> wOptions;
    /// Credits window
    WeakPtr<Window> wCredits;
    
    /// Credits window
    WeakPtr<Window> wLevelMenu;
    /// The UI's root UIElement.
    SharedPtr<UIElement> uiRoot_;
    /// Remembered drag begin position.
    IntVector2 dragBeginPosition_;
};

#endif // MAINMENU_H
