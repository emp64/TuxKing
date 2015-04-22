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

#include <Urho3D/Urho3D.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/UI/UI.h>

#include "ColorPicker.h"


namespace Urho3D
{

extern const char* UI_CATEGORY;

ColorPicker::ColorPicker(Context *context) : 
    Button(context)
{
    SetPlayerColor(Color::BLUE);
}

ColorPicker::~ColorPicker()
{

}

void ColorPicker::SetParameters(UIElement *parent, String name, Color clr, int minWidth, int minHeigth, int maxWidth, int maxHeigth)
{
    parent->AddChild(this);
    
    this->SetName(name);
    
    this->SetMinSize(minWidth, minHeigth);
    this->SetMaxSize(maxWidth, maxHeigth);
    
    window = new Window(context_);
    parent->AddChild(window);
    window->SetStyleAuto();
    window->SetPosition(30, 30);
    window->SetSize(100, 100);
    window->SetVisible(false);
    window->SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    
    Button *btBlack = new Button(context_);
    btBlack->SetName("btBlack"); 
    btBlack->SetStyle("ColorPicker");
    btBlack->SetMinSize(80, 30);
    btBlack->SetColor(Color::BLACK);
    
    Button *btBlue = new Button(context_);
    btBlue->SetName("btBlue"); 
    btBlue->SetMinSize(80, 30);
    btBlue->SetStyle("ColorPicker");
    btBlue->SetColor(Color::BLUE);
    
    Button *btGreen = new Button(context_);
    btGreen->SetName("btGreen"); 
    btGreen->SetMinSize(80, 30);
    btGreen->SetStyle("ColorPicker");
    btGreen->SetColor(Color::GREEN);
    
    Button *btMagenta = new Button(context_);
    btMagenta->SetName("btMagenta"); 
    btMagenta->SetStyle("ColorPicker");
    btMagenta->SetMinSize(80, 30);
    btMagenta->SetColor(Color::MAGENTA);
    
    Button *btRed = new Button(context_);
    btRed->SetName("btRed"); 
    btRed->SetStyle("ColorPicker");
    btRed->SetMinSize(80, 30);
    btRed->SetColor(Color::RED);
    
    Button *btYellow = new Button(context_);
    btYellow->SetName("btYellow"); 
    btYellow->SetStyle("ColorPicker");
    btYellow->SetMinSize(80, 30);
    btYellow->SetColor(Color::YELLOW);
    
    
    window->AddChild(btBlack);
    window->AddChild(btBlue);
    window->AddChild(btGreen);
    window->AddChild(btMagenta);
    window->AddChild(btRed);
    window->AddChild(btYellow);
    
    
    this->SetPlayerColor(clr);
    
    
    SubscribeToEvent(this, E_RELEASED, HANDLER(ColorPicker, HandleClicked));
    
    SubscribeToEvent(btBlue, E_RELEASED, HANDLER(ColorPicker, HandleBlueClicked));
    SubscribeToEvent(btBlack, E_RELEASED, HANDLER(ColorPicker, HandleBlackClicked));
    SubscribeToEvent(btGreen, E_RELEASED, HANDLER(ColorPicker, HandleGreenClicked));
    SubscribeToEvent(btMagenta, E_RELEASED, HANDLER(ColorPicker, HandleMagentaClicked));
    SubscribeToEvent(btRed, E_RELEASED, HANDLER(ColorPicker, HandleRedClicked));
    SubscribeToEvent(btYellow, E_RELEASED, HANDLER(ColorPicker, HandleYellowClicked));
}

void ColorPicker::SetStyle(String stylename)
{
    Button::SetStyle(stylename);
    window->SetStyle("Window");
}

void ColorPicker::SetPlayerColor(Color clr)
{
    if (clr == Color::BLACK || clr == Color::BLUE || clr == Color::GREEN || clr == Color::RED || clr == Color::MAGENTA || clr == Color::YELLOW)
    {
	currentColor = clr;
    this->SetColor(clr);
    }
    else 
    {
	clr = Color::BLUE;
    }
}


void ColorPicker::HandleClicked(StringHash eventType, VariantMap& eventData)
{
    window->SetAlignment(this->GetHorizontalAlignment(), this->GetVerticalAlignment());
    if (window->IsVisible()) 
    {
	window->SetVisible(false);
    }
    else 
    {
	IntVector2 pos = this->GetPosition();
	
	//window->SetPosition(100, 100);
	window->SetPosition(pos.x_, pos.y_ + this->GetHeight());
	window->SetVisible(true);
    }
}

void ColorPicker::HandleBlackClicked(StringHash eventType, VariantMap& eventData)
{
    SetPlayerColor(Color::BLACK);
    window->SetVisible(false);
}

void ColorPicker::HandleBlueClicked(StringHash eventType, VariantMap& eventData)
{
    SetPlayerColor(Color::BLUE);
    window->SetVisible(false);
}

void ColorPicker::HandleGreenClicked(StringHash eventType, VariantMap& eventData)
{
    SetPlayerColor(Color::GREEN);
    window->SetVisible(false);
}

void ColorPicker::HandleMagentaClicked(StringHash eventType, VariantMap& eventData)
{
    SetPlayerColor(Color::MAGENTA);
    window->SetVisible(false);
}

void ColorPicker::HandleRedClicked(StringHash eventType, VariantMap& eventData)
{
    SetPlayerColor(Color::RED);
    window->SetVisible(false);
}

void ColorPicker::HandleYellowClicked(StringHash eventType, VariantMap& eventData)
{
    SetPlayerColor(Color::YELLOW);
    window->SetVisible(false);
}

void ColorPicker::RegisterObject(Context* context)
{
    context->RegisterFactory<ColorPicker>(UI_CATEGORY);
    
    COPY_BASE_ATTRIBUTES(Button);
}
}