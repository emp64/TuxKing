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

#ifndef STATE_H
#define STATE_H

#include "Urho3D/Engine/Application.h"
#include "Urho3D/Urho3D.h"
#include "Urho3D/Engine/Engine.h"
#include "Urho3D/Scene/Scene.h"
#include "Urho3D/Core/Object.h"
#include "Urho3D/Scene/LogicComponent.h"


using namespace Urho3D;

class State : public LogicComponent
{
    OBJECT(State);
    
public:
    State(Context *context);
    ~State();
    bool operator== ( const State& other ) const;
    
    /// Register object factory and attributes.
    static void RegisterObject(Context* context);
    
    int loadResources();
    
    
protected:
    void OnWindowResize();
    void Start();
    /// Scene.
    SharedPtr<Scene> scene_;
    /// Camera scene node.
    SharedPtr<Node> cameraNode_;
    /// Camera yaw angle.
    float yaw_;
    /// Camera pitch angle.
    float pitch_;
    
private:
    
    
    
    
};

#endif // STATE_H
