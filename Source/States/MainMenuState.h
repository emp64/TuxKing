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

#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "Urho3D/Scene/LogicComponent.h"
#include "Urho3D/Scene/Scene.h"
#include "Urho3D/Core/Context.h"

#include "State.h"
#include "../HUD/HUD.h"
#include "../HUD/MainMenu.h"

using namespace Urho3D;

class MainMenuState : public State
{
    OBJECT(MainMenuState);
    
public:
    MainMenuState(Context *context);
    ~MainMenuState();
    bool operator== ( const MainMenuState& other ) const;
    
    /// Register object factory and attributes.
    static void RegisterObject(Context* context);
    
    int loadResources();
    
    void CreateScene();
    
    void CreateMainMenu();
    
    Scene *GetScenePointer();
    
    void Start();
    
protected:
    /// Scene.
    SharedPtr<Scene> scene_;
    //Scene* scene_;
    /// Camera scene node.
    SharedPtr<Node> cameraNode_;
    
private:
    
    
    WeakPtr<MainMenu> mainMenu_;
    //WeakPtr<HUD> hud_;
    
};

#endif // MAINMENUSTATE_H
