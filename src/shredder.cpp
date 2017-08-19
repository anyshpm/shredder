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
#include <wx/iconloc.h>
#include <wx/taskbar.h>

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
            // 每次都要 new 一个新的 wxMenu
            wxMenu *popupMenu = new wxMenu();
            popupMenu->Append(wxID_ABOUT, _("About"));
            popupMenu->AppendSeparator();
            popupMenu->Append(wxID_EXIT, _("Exit"));
            return popupMenu;
        };

    private:
        DECLARE_EVENT_TABLE();
};

class Shredder: public wxApp
{
    public:
        virtual bool OnInit ()
        {
            trayIcon = new ShredderTaskBarIcon();
            trayIcon->SetIcon(wxIcon("icon.bmp"));
            return true ;
        }
        ~Shredder()
        {
            if (trayIcon != NULL)
            {
                delete trayIcon;
            }
        }

    private:
        ShredderTaskBarIcon* trayIcon;
};

BEGIN_EVENT_TABLE(ShredderTaskBarIcon, wxTaskBarIcon)  
    EVT_MENU(wxID_ABOUT, ShredderTaskBarIcon::OnAbout)  
END_EVENT_TABLE() 
IMPLEMENT_APP(Shredder)
