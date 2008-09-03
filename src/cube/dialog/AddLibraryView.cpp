//////////////////////////////////////////////////////////////////////////////
//
// License Agreement:
//
// The following are Copyright � 2007, mC2 Team
//
// Sources and Binaries of: mC2, win32cpp
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright 
//      notice, this list of conditions and the following disclaimer in the 
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the author nor the names of other contributors may 
//      be used to endorse or promote products derived from this software 
//      without specific prior written permission. 
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE. 
//
//////////////////////////////////////////////////////////////////////////////

#include "pch.hpp"
#include <cube/dialog/AddLibraryView.hpp>
#include <core/LibraryFactory.h>
#include <win32cpp/Label.hpp>
#include <win32cpp/Button.hpp>
#include <win32cpp/LinearLayout.hpp>
#include <win32cpp/BarLayout.hpp>
#include <win32cpp/EditView.hpp>

//////////////////////////////////////////////////////////////////////////////

using namespace musik::cube::dialog;
using namespace win32cpp;

//////////////////////////////////////////////////////////////////////////////

AddLibraryView::AddLibraryView(int type)
: Frame(NULL,FramePadding(6))
, type(type)
{
}

void AddLibraryView::OnCreated()
{
    FontRef boldFont(Font::Create());
    boldFont->SetBold(true);

    // Top Row layout
    LinearLayout* topRowLayout = new LinearLayout(LinearRowLayout);
    topRowLayout->SetDefaultChildFill(false);
    topRowLayout->SetDefaultChildAlignment(win32cpp::ChildAlignMiddle);

    // First rows column layout
    LinearLayout* firstColumnLayout = new LinearLayout(LinearColumnLayout);
    firstColumnLayout->SetDefaultChildFill(false);
    firstColumnLayout->SetDefaultChildAlignment(win32cpp::ChildAlignCenter);

    Label* title    = firstColumnLayout->AddChild(new Label(_T("Add Library")));
    title->SetFont(boldFont);
    topRowLayout->AddChild(firstColumnLayout);


    // Second rows column layout
    LinearLayout* secondColumnLayout = new LinearLayout(LinearColumnLayout);
    secondColumnLayout->SetDefaultChildAlignment(win32cpp::ChildAlignTop);

    win32cpp::Label* nameLabel      = secondColumnLayout->AddChild(new Label(_T("Library name:") ));
    this->name                      = secondColumnLayout->AddChild(new EditView(160,20 ));
    topRowLayout->AddChild(secondColumnLayout);


    // Third rows column layout
    if(this->type==musik::core::LibraryFactory::Remote){
        LinearLayout* remoteHostColumnLayout = new LinearLayout(LinearColumnLayout);
//        remoteHostColumnLayout->SetDefaultChildAlignment(win32cpp::ChildAlignTop);
        remoteHostColumnLayout->AddChild(new Label(_T("Remote host:") ));
        this->remoteHost = remoteHostColumnLayout->AddChild(new EditView(160,20 ));
        topRowLayout->AddChild(remoteHostColumnLayout);

        LinearLayout* remotePortColumnLayout = new LinearLayout(LinearColumnLayout);
//        remotePortColumnLayout->SetDefaultChildAlignment(win32cpp::ChildAlignTop);
        remotePortColumnLayout->AddChild(new Label(_T("Remote port:") ));
        this->remotePort = remotePortColumnLayout->AddChild(new EditView(100,20 ));
        this->remotePort->SetCaption(uistring(_T("10543")));
        topRowLayout->AddChild(remotePortColumnLayout);
    }

    // Last rows column layout
    LinearLayout* bottomButtonLayout = new LinearLayout(LinearColumnLayout);
    bottomButtonLayout->SetDefaultChildFill(false);
    this->cancelButton  = bottomButtonLayout->AddChild(new Button(_T("Cancel")));
    this->okButton      = bottomButtonLayout->AddChild(new Button(_T("OK")));
    this->cancelButton->Resize(60,20);
    this->okButton->Resize(60,20);
    topRowLayout->AddChild(bottomButtonLayout);
    topRowLayout->SetChildAlignment(bottomButtonLayout,ChildAlignRight);



    this->AddChild(topRowLayout);

}