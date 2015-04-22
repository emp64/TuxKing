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

#include <Urho3D/Urho3D.h>
#include "Urho3D/Engine/Application.h"
#include "Urho3D/Graphics/Camera.h"
#include "Urho3D/Engine/Console.h"
#include "Urho3D/UI/Cursor.h"
#include "Urho3D/Engine/DebugHud.h"
#include "Urho3D/Engine/Engine.h"
#include "Urho3D/IO/FileSystem.h"
#include "Urho3D/Graphics/Graphics.h"
#include "Urho3D/Input/Input.h"
#include "Urho3D/Input/InputEvents.h"
#include "Urho3D/Graphics/Renderer.h"
#include "Urho3D/Resource/ResourceCache.h"
#include "Urho3D/Scene/Scene.h"
#include "Urho3D/Scene/SceneEvents.h"
#include "Urho3D/UI/Sprite.h"
#include "Urho3D/Graphics/Texture2D.h"
#include "Urho3D/Core/Timer.h"
#include "Urho3D/UI/UI.h"
#include "Urho3D/Resource/XMLFile.h"
#include "Urho3D/Graphics/Zone.h"

#include "Urho3D/Graphics/AnimatedModel.h"
#include "Urho3D/Graphics/AnimationController.h"
#include "Urho3D/Core/Context.h"
#include "Urho3D/Physics/CollisionShape.h"
#include "Urho3D/Input/Controls.h"
#include "Urho3D/Core/CoreEvents.h"
#include "Urho3D/Engine/Engine.h"
#include "Urho3D/IO/FileSystem.h"
#include "Urho3D/UI/Font.h"
#include "Urho3D/Input/Input.h"
#include "Urho3D/Graphics/Light.h"
#include "Urho3D/Graphics/Material.h"
#include "Urho3D/Graphics/Model.h"
#include "Urho3D/Graphics/Octree.h"
#include "Urho3D/Physics/PhysicsWorld.h"
#include "Urho3D/Core/ProcessUtils.h"
#include "Urho3D/Graphics/Renderer.h"
#include "Urho3D/Physics/RigidBody.h"
#include "Urho3D/Resource/ResourceCache.h"
#include "Urho3D/Scene/Scene.h"
#include "Urho3D/Graphics/StaticModel.h"
#include "Urho3D/UI/Text.h"
#include "Urho3D/UI/UI.h"
#include "Urho3D/Graphics/Zone.h"


#include "Urho3D/UI/Font.h"
#include "Urho3D/UI/Text.h"

#include "Urho3D/DebugNew.h"

#include "../HUD/MainMenu.h"
#include "MainMenuState.h"


#include "../Game/PlayerController.h"


MainMenuState::MainMenuState(Context *context) : State(context)
    
{
    //scene = new Scene;
    //MainMenu::RegisterObject(context);
    MainMenu::RegisterObject(context);
    //Player::RegisterObject(context);
    
    CreateScene();
    
    CreateMainMenu();
}

MainMenuState::~MainMenuState()
{
    mainMenu_->~MainMenu();
}

bool MainMenuState::operator== ( const MainMenuState& other ) const
{

}

void MainMenuState::RegisterObject ( Context* context )
{
    context->RegisterFactory<MainMenuState>();
}


int MainMenuState::loadResources()
{
    return 0;
}

void MainMenuState::Start()
{
    //CreateScene();
    
    //CreateMainMenu();
}


void MainMenuState::CreateScene()
{
    scene_ = new Scene(context_);
    
    // Create scene subsystem components
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<PhysicsWorld>();
    
    // Create camera and define viewport. We will be doing load / save, so it's convenient to create the camera outside the scene,
    // so that it won't be destroyed and recreated, and we don't have to redefine the viewport on load
    cameraNode_ = new Node(context_);
    Camera* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(300.0f);
    GetSubsystem<Renderer>()->SetViewport(0, new Viewport(context_, scene_, camera));
    
    // Create static scene content. First create a zone for ambient lightning and fog control
    Node* zoneNode = scene_->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));
    zone->SetFogStart(0.0f);
    zone->SetFogEnd(30.0f);
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));

    // Create a directional light with cascaded shadow mapping
    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.3f, -0.5f, 0.425f));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetSpecularIntensity(0.5f);
}

void MainMenuState::CreateMainMenu()
{
    Node* objectNode = scene_->CreateChild("hh");
    objectNode->SetPosition(Vector3(0.0f, 1.0f, 0.0f));
    
    //hud_ = objectNode->CreateComponent<HUD>();
    mainMenu_ = objectNode->CreateComponent<MainMenu>();
    
    
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    // Construct new Text object, set string to display and font to use
    /*Text* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText(
        "Use WASD keys and mouse/touch to move\n"
        "Space to jump, F to toggle 1st/3rd person\n"
        "F5 to save scene, F7 to load"
    );
    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
    // The text has multiple rows. Center them in relation to each other
    instructionText->SetTextAlignment(HA_CENTER);

    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight() / 4);*/
}

Scene* MainMenuState::GetScenePointer()
{
    return scene_;
}

