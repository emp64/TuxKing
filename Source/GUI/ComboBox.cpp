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
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/EngineEvents.h>
#include <Urho3D/Graphics/GraphicsEvents.h>
#include <Urho3D/UI/UIEvents.h>

#include "ComboBox.h"

namespace Urho3D
{

extern const char* UI_CATEGORY;


ComboBox::ComboBox(Context* context) : DropDownList(context)
{
    this->SetEnabled(true);
    this->SetResizePopup(true);
    //this->SetLayout(LM_VERTICAL, 1, IntRect(7, 3, 7, 3));
    
    SubscribeToEvent(this, E_ITEMSELECTED, HANDLER(ComboBox, HandleSelectedChanged));
}


ComboBox::~ComboBox()
{
    
}


void ComboBox::SetParameters(String name, String text, int minHeigth, int minWidth, int maxHeigth, int maxWidth)
{
    this->SetName(name);
    this->SetMinHeight(minHeigth);
    this->SetMinWidth(minWidth);
    this->SetMaxHeight(maxHeigth);
    this->SetMaxWidth(maxWidth);
}

void ComboBox::SetStyle(String stylename)
{
    DropDownList::SetStyle(stylename);
    this->popup_->SetStyle("ComboBoxWindow");

}


void ComboBox::SetItemsVector(Vector<String> items)
{
    //this->RemoveAllItems();
           
    for (int i = 0; i < items.Size(); i++)
    {
	String name = items[i];
	Text* text = new Text(context_);
        text->SetStyle("Text");
	//text->SetColor(Color(0.9, 0.9, 0.9, 1));
        text->SetText(name);
	
	this->AddItem(text);
	
	// change Combo size according to the biggest text
	if (text->GetMinHeight() > this->GetMinHeight())
	    this->SetMinHeight(text->GetMinHeight() + 6);
	if (text->GetMinWidth() > this->GetMinWidth())
	    this->SetMinWidth(text->GetMinWidth() + 14);
	
	text->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_CENTER);
    }
    
    this->SetSelection(0);
}


void ComboBox::RegisterObject(Context* context)
{
    context->RegisterFactory<ComboBox>(UI_CATEGORY);
    
    COPY_BASE_ATTRIBUTES(DropDownList);
}

// TODO nejako nefunguje
void ComboBox::HandleSelectedChanged(StringHash eventType, VariantMap& eventData)
{
}


}
