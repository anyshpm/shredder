/*
 ============================================================================
 Name        : shredder.cpp
 Author      : anyshpm
 Version     :
 Copyright   :
 Description : Hello World in C++,
 ============================================================================
 */

#include <cstdio>
#include <wx/wx.h>
#include <wx/iconloc.h>
#include <wx/taskbar.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <list>

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
        DECLARE_EVENT_TABLE();
};

class Shredder: public wxApp
{
    public:
        static int EraseFileContent(wxString file)
        {
            FILE* f;
            long long i;

            f = fopen(file.c_str(), "a+");
            fseek(f, 0, SEEK_END);
            i = ftell(f);
            fclose(f);
            f = fopen(file.c_str(), "w+");
            while (i > 0)
            {
                fwrite("00000000", 8, 1, f);
                i -= 8;
            }
            fclose(f);

            return wxRemoveFile(file);
        }

        static int DeleteFile(wxString file)
        {
            if (wxDirExists(file) == true)
            {
                wxMessageBox(_T("确定要删除目录：") + file, _T("确认"), wxOK | wxICON_INFORMATION);
                std::list<wxString> fl;
                fl.push_back(file);
                while (fl.size() > 0)
                {
                    wxString fn;
                    wxString subfn;
                    fn = fl.back();
                    wxDir dir(fn);
                    bool hasSubFile = false;

                    if (dir.GetFirst(&subfn) == true)
                    {
                        do
                        {
                            wxString filename = dir.GetNameWithSep() + subfn;
                            if (wxDirExists(filename) == true)
                            {
                                fl.push_back(filename);
                                hasSubFile = true;
                            }
                            else if (wxFileExists(filename) == true)
                            {
                                Shredder::EraseFileContent(filename);
                            }
                        }
                        while (dir.GetNext(&subfn) == true);
                    }

                    if (hasSubFile == false)
                    {
                        fl.pop_back();
                        wxRmdir(fn);
                    }
                }
            }
            else if (wxFileExists(file) == true)
            {
                wxMessageBox(_T("确定要删除文件：") + file, _T("确认"), wxOK | wxICON_INFORMATION);
                if (Shredder::EraseFileContent(file) == true)
                {
                    wxMessageBox(_T("删除成功！"), _T("成功"), wxOK | wxICON_INFORMATION);
                }
                else
                {
                    wxMessageBox(_T("删除失败！"), _T("错误"), wxOK | wxICON_INFORMATION);
                }
            }
            else
            {
                wxMessageBox(_T("文件或目录不存在！"), _T("错误"), wxOK | wxICON_INFORMATION);
            }
        }

        virtual bool OnInit ()
        {
            trayIcon = new ShredderTaskBarIcon();
            trayIcon->SetIcon(wxIcon("icon.bmp"));

            if (argc > 1)
            {
                Shredder::DeleteFile(argv[1]);
            }
            else
            {
                wxMessageBox(_T("文件或目录不存在！"), _T("错误"), wxOK | wxICON_INFORMATION);
            }

            return false;
        }

        virtual int OnExit()
        {
            if (trayIcon != NULL)
            {
                delete trayIcon;
            }
        }

    private:
        ShredderTaskBarIcon* trayIcon;

        void debug(wxString s)
        {
            wxMessageBox(s, _T("DEBUG!"), wxOK | wxICON_INFORMATION);
        }
};

BEGIN_EVENT_TABLE(ShredderTaskBarIcon, wxTaskBarIcon)  
    EVT_MENU(wxID_ABOUT, ShredderTaskBarIcon::OnAbout)  
END_EVENT_TABLE() 
IMPLEMENT_APP(Shredder)
