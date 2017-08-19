/*
 ============================================================================
 Name        : shredder.cpp
 Author      : anyshpm
 Version     :
 Copyright   : 
 Description : Hello World in C++,
 ============================================================================
 */

#include <wx/wx.h>
#include <wx/progdlg.h>

class Simple: public wxFrame
{
    public:
        Simple(const wxString& title );
};

class MyApp : public wxApp
{
    public:
        virtual bool OnInit ();
};

Simple::Simple (const wxString& title ) :     wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize( 250, 150))
{
    Centre();
}

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit ()
{
    //Simple * simple = new Simple(wxT("Simple")) ;
    wxProgressDialog* dlg = new wxProgressDialog("title", "message");
    dlg->Show(true) ;
    return true ;
}

