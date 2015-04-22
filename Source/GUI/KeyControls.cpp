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
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/IO/Log.h>

#include "KeyControls.h"



KeyControls::KeyControls(Context* context) : 
    UIElement(context), 
    uiRoot_(GetSubsystem<UI>()->GetRoot())
{
}

KeyControls::~KeyControls()
{

}

void KeyControls::SetParameters(String caption, int keyForward, int keyBackward, int keyLeft, int keyRight)
{
    this->keyForward = keyForward;
    this->keyBackward = keyBackward;
    this->keyLeft = keyLeft;
    this->keyRight = keyRight;
    
    btForward = CreateButton(this, "btForward", GetLetter(keyForward), 40, 40);
    btForward->SetPosition(45, 0);
    btBackward = CreateButton(this, "btBackward", GetLetter(keyBackward), 40, 40);
    btBackward->SetPosition(45, 45);
    btLeft = CreateButton(this, "btLeft", GetLetter(keyLeft), 40, 40);
    btLeft->SetPosition(0, 45);
    btRight = CreateButton(this, "btRight", GetLetter(keyRight), 40, 40);
    btRight->SetPosition(90, 45);

    SubscribeToEvent(btForward, E_RELEASED, HANDLER(KeyControls, HandleButtonForwardClick));
    SubscribeToEvent(btBackward, E_RELEASED, HANDLER(KeyControls, HandleButtonBackwardClick));
    SubscribeToEvent(btLeft, E_RELEASED, HANDLER(KeyControls, HandleButtonLeftClick));
    SubscribeToEvent(btRight, E_RELEASED, HANDLER(KeyControls, HandleButtonRightClick));
    
    UpdateKeyBindings();
}
    
int* KeyControls::GetKeys()
{
    int ctrls[4];
    
    ctrls[0] = keyForward;
    ctrls[1] = keyBackward;
    ctrls[2] = keyLeft;
    ctrls[3] = keyRight;
    
    return ctrls;
}
    
void KeyControls::UpdateKeyBindings()
{    
    Text *txForward = (Text*) btForward->GetChild("text", false);
    txForward->SetText(GetLetter(keyForward));
    
    Text *txBackward = (Text*) btBackward->GetChild("text", false);
    txBackward->SetText(GetLetter(keyBackward));
    
    Text *txLeft = (Text*) btLeft->GetChild("text", false);
    txLeft->SetText(GetLetter(keyLeft));
    
    Text *txRight = (Text*) btRight->GetChild("text", false);
    txRight->SetText(GetLetter(keyRight));
    // TODO ovela jednoduchsie by to bolo keby som mal Button triedu ->
    // Treba updatnut text
}

String KeyControls::GetLetter(int key)
{
    switch (key) {
	case KEY_UP: 
	    return "Up";
	case KEY_DOWN: 
	    return "Down";
	case KEY_LEFT: 
	    return "Left";
	case KEY_RIGHT: 
	    return "Right";
	case KEY_0:
	    return "0";
	case KEY_1:
	    return "1";
	case KEY_2: 
	    return "2";
	case KEY_3:
	    return "3";
	case KEY_4:
	    return "4";
	case KEY_5: 
	    return "5";
	case KEY_6:
	    return "6";
	case KEY_7:
	    return "7";
	case KEY_8: 
	    return "8";
	case KEY_9:
	    return "9";
	case KEY_A:
	    return "A";
	case KEY_B:
	    return "B";
	case KEY_C:
	    return "C";
	case KEY_D:
	    return "D";
	case KEY_E:
	    return "E";
	case KEY_F:
	    return "F";
	case KEY_G:
	    return "G";
	case KEY_H:
	    return "H";
	case KEY_I:
	    return "I";
	case KEY_J:
	    return "J";
	case KEY_K:
	    return "K";
	case KEY_L:
	    return "L";
	case KEY_M:
	    return "M";
	case KEY_N:
	    return "N";
	case KEY_O:
	    return "O";
	case KEY_P:
	    return "P";
	case KEY_Q:
	    return "Q";
	case KEY_R:
	    return "R";
	case KEY_S:
	    return "S";
	case KEY_T:
	    return "T";
	case KEY_U:
	    return "U";
	case KEY_V:
	    return "V";
	case KEY_W:
	    return "W";
	case KEY_X:
	    return "X";
	case KEY_Y:
	    return "Y";
	case KEY_Z:
	    return "Z";
	case KEY_KP_0:
	    return "N 0";
	case KEY_KP_1:
	    return "N 1";
	case KEY_KP_2: 
	    return "N 2";
	case KEY_KP_3:
	    return "N 3";
	case KEY_KP_4:
	    return "N 4";
	case KEY_KP_5: 
	    return "N 5";
	case KEY_KP_6:
	    return "N 6";
	case KEY_KP_7:
	    return "N 7";
	case KEY_KP_8: 
	    return "N 8";
	case KEY_KP_9:
	    return "N 9";
	default:
	    return "";
    }
    
}

void KeyControls::HandleButtonForwardClick(StringHash eventType, VariantMap& eventData)
{
    editKey = FORWARD;
    CreateEditKeyWindow();    
}

void KeyControls::HandleButtonBackwardClick(StringHash eventType, VariantMap& eventData)
{
    editKey = BACKWARD;
    CreateEditKeyWindow();
}

void KeyControls::HandleButtonLeftClick(StringHash eventType, VariantMap& eventData)
{
    editKey = LEFT;
    CreateEditKeyWindow();
}

void KeyControls::HandleButtonRightClick(StringHash eventType, VariantMap& eventData)
{
    editKey = RIGHT;
    CreateEditKeyWindow();
}

void KeyControls::HandleKeyClicked(StringHash eventType, VariantMap& eventData)
{
    Input* input = GetSubsystem<Input>();
    int key = eventData.Values()[0].GetInt();  
    
    switch (editKey) {
	case FORWARD: {
	    keyForward = key;
	    break;
	}
	case BACKWARD: {
	    keyBackward = key;
	    break;
	}
	case LEFT: {
	    keyLeft = key;
	    break;
	}
	case RIGHT: {
	    keyRight = key;
	    break;
	}
    }
    
    DestroyKeyBindingWindow();
    UpdateKeyBindings();
}

Button* KeyControls::CreateButton(UIElement* parent, String name, String caption, int minWidth, int minHeigth, int maxWidth, int maxHeigth)
{
    Button* button = new Button(context_);
    button->SetName("bt" + name);
    button->SetMinSize(minWidth, minHeigth);
    button->SetStyleAuto();
    parent->AddChild(button);
    
    Text* text = new Text(context_);
    button->AddChild(text);
    text->SetStyle("Text");
    text->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_CENTER);
    text->SetName("text");
    text->SetText(caption);
    
    return button;
}

void KeyControls::CreateEditKeyWindow()
{
    String caption = "Key binding";
    String message = "Click the key you want to bind\nto this controll.";
    
    Window* w;
    w = new Window(context_);
    w->SetName("KeyBindingWindow");
    w->SetSize(400, 200);
    w->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_CENTER);
    w->SetModal(true);
    w->SetMovable(false);
    w->SetFixedHeightResizing(true);
    w->SetFixedWidthResizing(true);
    w->SetStyleAuto();
    uiRoot_->AddChild(w);
    
    Text* txMessage = new Text(context_);
    w->AddChild(txMessage);
    txMessage->SetStyle("Text");
    txMessage->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_TOP);
    txMessage->SetTextAlignment(Urho3D::HA_CENTER);
    txMessage->SetPosition(0, 40);
    txMessage->SetName("txBindingMessage");
    txMessage->SetText(message);
    txMessage->SetTextEffect(Urho3D::TE_STROKE);
    txMessage->SetColor(Color(0.9, 0.9, 0.9, 1));
    
    SubscribeToEvent(E_KEYDOWN, HANDLER(KeyControls, HandleKeyClicked));
}

void KeyControls::DestroyKeyBindingWindow()
{
    // BUG nvm preco ale niekedy nezmizne to okno >:(
    Window* w = (Window*) uiRoot_->GetChild("KeyBindingWindow", false);
    
    if (w != NULL) 
    {
	w->RemoveAllChildren();
	w->SetVisible(false); 
	w->Remove();
    }
    
    UnsubscribeFromEvent(E_KEYDOWN);
}


void KeyControls::RegisterObject(Context* context)
{
    context->RegisterFactory<KeyControls>();
    
    COPY_BASE_ATTRIBUTES(UIElement);
}
