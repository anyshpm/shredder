/*
 ============================================================================
 Name        : systrayicon.cpp
 Author      : anyshpm
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <wx/wx.h>
#include <wx/iconloc.h>
#include <wx/taskbar.h>
#include <wx/filefn.h>
#include <wx/filename.h>

class ShredderTaskBarIcon: public wxTaskBarIcon
{
    public:
        void OnAbout(wxCommandEvent& event)
        {
            wxMessageBox(_T("hello!"), wxT("About Tray!"), wxOK | wxICON_INFORMATION);
        }

    protected:
        virtual wxMenu *CreatePopupMenu()
        {
            wxMenu *popupMenu = new wxMenu();
            popupMenu->Append(wxID_ABOUT, _("About"));
            popupMenu->AppendSeparator();
            popupMenu->Append(wxID_EXIT, _("Exit"));
            return popupMenu;
        };

    private:
        ShredderTaskBarIcon();
};
//wxBEGIN_EVENT_TABLE(ShredderTaskBarIcon, wxTaskBarIcon)
//    EVT_MENU(wxID_ABOUT, ShredderTaskBarIcon::OnAbout)
//wxEND_EVENT_TABLE()
