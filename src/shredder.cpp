/*
 ============================================================================
 Name        : shredder.cpp
 Author      : anyshpm
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <cstdio>
#include <list>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "shredder.h"
#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "icon.xpm"

class ShredderFrame: public wxFrame
{
	public:
		ShredderFrame(const wxString& title, const wxPoint& pos, const wxSize& size):
			wxFrame(NULL, wxID_ANY, title, pos, size)
		{
			wxIcon icon((char*)DOTA2_ICON);
			SetIcon(icon);
		}

		~ShredderFrame(){}
};

class Shredder: public wxApp
{
    public:
        virtual bool OnInit ()
        {
            if (argc > 1)
            {
            	wxMessageBox(_T("确定要删除么？"), _T("确定"), wxOK | wxICON_INFORMATION);
            	std::string path(argv[1].mb_str());
                if (DeletePath(path) == 0)
                {
                	wxMessageBox(_T("删除成功！"), _T("成功"), wxOK | wxICON_INFORMATION);
                }
            }
            else
            {
                wxMessageBox(_T("文件或目录不存在！"), _T("错误"), wxOK | wxICON_INFORMATION);
            }

            return false;
        }
};

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
wxIMPLEMENT_APP(Shredder);
