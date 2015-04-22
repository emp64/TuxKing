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
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/UI/BorderImage.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/UI/LineEdit.h>
#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/UI/Menu.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/UIElement.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/UI/Window.h>


#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/DebugNew.h>

#include "../GlobalSettings.h"

#include "HUD.h"

// TODO prerobit na Object alebo Component
HUD::HUD(Context* context) :
    LogicComponent(context),
    uiRoot_(GetSubsystem<UI>()->GetRoot())
{
}

void HUD::Start()
{
    // Enable OS cursor
    GetSubsystem<Input>()->SetMouseVisible(true);
 
    // Load XML file containing default UI style sheet
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    XMLFile* style = cache->GetResource<XMLFile>("Urho resources/DefaultStyle.xml");

    // Set the loaded style as default style
    uiRoot_->SetDefaultStyle(style);
}

void HUD::InitControls()
{
    
}

void HUD::InitWindow()
{
    
}


void HUD::HandleClosePressed(StringHash eventType, VariantMap& eventData)
{
    //engine_->Exit();
}

void HUD::HandleControlClicked(StringHash eventType, VariantMap& eventData)
{
    
}

void HUD::RegisterObject (Context* context)
{
    context->RegisterFactory<HUD>();
}

Button* HUD::CreateButton(UIElement* parent, String name, String caption, int minWidth, int minHeigth, int maxWidth, int maxHeigth)
{
    Button* button = new Button(context_);
    button->SetName("bt" + name);
    //button->SetSize(width, heigth);
    button->SetMinSize(minWidth, minHeigth);
    //button->SetMaxSize(width, heigth);
    button->SetStyleAuto();
    parent->AddChild(button);
    
    Text* text = new Text(context_);
    button->AddChild(text);
    text->SetStyle("Text");
    text->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_CENTER);
    text->SetName("tx" + name);
    text->SetText(caption);
    
    return button;
}

CheckBox* HUD::CreateCheckbox(UIElement* parent, String name, String caption, int width, int heigth, int positionX, int positionY)
{
    CheckBox* cbox = CreateCheckbox(parent, name, caption);
    
    cbox->SetSize(width, heigth);
    cbox->SetPosition(positionX, positionY);
    
    return cbox;
}

CheckBox* HUD::CreateCheckbox(UIElement* parent, String name, String caption)
{
    CheckBox* cbox = new CheckBox(context_);
    cbox->SetName("cb" + name);
    cbox->SetHorizontalAlignment(Urho3D::HA_RIGHT);
    parent->AddChild(cbox);
    cbox->SetStyleAuto();
    
    Text* text = new Text(context_);
    cbox->AddChild(text);
    text->SetStyle("Text");
    text->SetColor(Color(0.9, 0.9, 0.9, 1));
    text->SetAlignment(Urho3D::HA_RIGHT, Urho3D::VA_CENTER);
    text->SetPosition(-30, 0);
    text->SetName("text");
    text->SetText(caption);
    
    return cbox;
}

Text* HUD::CreateCaption(String name, String text)
{
    Text* tx = new Text(context_);
    //Font* font = new Font("Fonts/Anonymous Pro.ttf");
    tx->SetName(name);
    tx->SetText(text);
    
    GlobalSettings* gs = context_->GetSubsystem<GlobalSettings>();
    tx->SetFont(gs->GetCaptionFont(), 18);
    
    return tx;
}






















