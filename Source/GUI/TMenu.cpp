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
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/IO/Log.h>

#include "TMenu.h"

#include "../GlobalSettings.h"


namespace Urho3D
{

extern const char* UI_CATEGORY;


TMenu::TMenu(Context* context) : Menu(context)
{
    //GlobalSettings* gs = context_->GetSubsystem<GlobalSettings>();
    //this->SetStyle("Menu", gs->GetDefaultStyle());
    
    SetEnabled(true);
    focusMode_ = FM_FOCUSABLE;
    
    this->SetLayout(LM_VERTICAL, 1, IntRect(7, 3, 7, 3));
}

TMenu::~TMenu()
{

}

void TMenu::SetParameters(String name, String caption, bool isSubmenu, int minHeigth, int minWidth, int maxHeigth, int maxWidth)
{
    this->SetName(name);
    this->isSubmenu = isSubmenu;
    
    this->SetName(name);
    this->SetMaxHeight(maxHeigth);
    this->SetMaxWidth(maxWidth);
    
    // set text properties
    text = new Text(context_);
    this->AddChild(text);
    text->SetStyle("Text");
    //text->SetLayout(LM_VERTICAL, 1, IntRect(2, 3, 2, 3));
    text->SetAlignment(Urho3D::HA_LEFT, Urho3D::VA_CENTER);
    text->SetName("tx" + name);
    text->SetText(caption);
    
    // text can autoresize for the right text size
    if (minWidth < text->GetWidth())
    {
	minWidth = text->GetWidth();
    }
    if (minHeigth < text->GetMinHeight())
    {
	minHeigth = text->GetMinHeight();
    }
    
    this->SetMinSize(minWidth, minHeigth);
}

void TMenu::CreatePopup()
{
    popup_ = new Window(context_);
    popup_->SetStyle("Window");

    this->AddChild(popup_);
    this->SetPopup(popup_);

    if (isSubmenu)
	this->SetPopupOffset(this->GetWidth(), 0);
    else
	this->SetPopupOffset(0, this->GetHeight());
    
    popup_->SetLayout(LM_VERTICAL, 1, IntRect(2, 3, 2, 3));
    
    popup_->SetMinSize(this->GetMinWidth(), this->GetMinHeight());
}


TMenu* TMenu::AddMenuItem(String name, String caption)
{
    if (firstItem)
    {
	CreatePopup();
	firstItem = false;
    }
    
    TMenu* submenu = new TMenu(context_);
    popup_->AddChild(submenu); 
    submenu->SetStyle("Menu");
    submenu->SetParameters(name, caption, true);
    
    popupHeigth += submenu->GetHeight();
    popup_->SetMinHeight(popupHeigth);
    
    if (popup_->GetWidth() < submenu->GetWidth())
    {
	//popupWidth = submenu->GetWidth();
	popup_->SetMinWidth(submenu->GetWidth());
    }
    
    return submenu;
}

void TMenu::AddSeparator()
{
    if (firstItem)
    {
	CreatePopup();
	firstItem = false;
    }
    
    BorderImage* separator = new BorderImage(context_);
    popup_->AddChild(separator);
    separator->SetStyle("EditorDivider");
    
    popupHeigth += separator->GetHeight();
    popup_->SetMinHeight(popupHeigth);
}

void TMenu::RegisterObject(Context* context)
{
    context->RegisterFactory<TMenu>(UI_CATEGORY);
    
    COPY_BASE_ATTRIBUTES(Menu);
}

}