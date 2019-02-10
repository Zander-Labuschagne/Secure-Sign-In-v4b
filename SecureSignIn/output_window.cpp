#include "output_window.hpp"
#include "x11_clipboard.hpp"

#include <QFile>
#include <QFontDatabase>

OutputWindow::OutputWindow(QWidget *parent, char *cipher_password) : QDialog(parent)
{
	OutputWindow::cipher_password = cipher_password;
	initialize_components();

}

void OutputWindow::initialize_components()
{
	//Set up GUI controls
	QFile stylesheet_file(":/Resources/StyleSheets/gitkraken_cryogen.qss");
	QFontDatabase::addApplicationFont(":/Resources/fonts/Iosevka Nerd Font Complete.ttf");
	fnt_iosevka = QFont("Iosevka Nerd Font Complete", 14, 65);
	stylesheet_file.open(QFile::ReadOnly);
	QString stylesheet = QLatin1String(stylesheet_file.readAll());
	this->setStyleSheet(stylesheet);

	//LineEdit: Password box
	psw_password = new QLineEdit(this);
	psw_password->move(10, 30);
	psw_password->setStyleSheet(stylesheet);
	psw_password->setFixedSize(400, 25);
	psw_password->setEchoMode(QLineEdit::Password);
	psw_password->setClearButtonEnabled(false);
	psw_password->setReadOnly(true);
	preview_password = psw_password->addAction(QIcon(":/Resources/icons/eye/yosa/show.svg"), QLineEdit::TrailingPosition);
	connect(preview_password, &QAction::triggered, this, &OutputWindow::view_password);
	psw_password->setText(cipher_password);
	psw_password->setFont(fnt_iosevka);
	psw_password->show();

	//PushButton: OK button
	btn_ok = new QPushButton(this);
	btn_ok->setFixedSize(160, 25);
	btn_ok->move(250, 85);
	btn_ok->setText("OK");
	btn_ok->setStyleSheet(stylesheet);
	btn_ok->setFont(fnt_iosevka);
	btn_ok->show();
	connect(btn_ok, SIGNAL(clicked()), this, SLOT(ok()));

	//PushButton: Copy Password button
	btn_copy = new QPushButton(this);
	btn_copy->setFixedSize(230, 25);
	btn_copy->move(10, 85);
	btn_copy->setText("Copy Password");
	btn_copy->setStyleSheet(stylesheet);
	btn_copy->setFont(fnt_iosevka);
	btn_copy->show();
	connect(btn_copy, SIGNAL(clicked()), this, SLOT(copy_password()));
}

void OutputWindow::view_password()
{
	if (!password_visible) {
		psw_password->setEchoMode(QLineEdit::Normal);
		password_visible = true;
		psw_password->removeAction(preview_password);
		preview_password = psw_password->addAction(QIcon(":/Resources/icons/eye/yosa/hide.svg"), QLineEdit::TrailingPosition);
		connect(preview_password, &QAction::triggered, this, &OutputWindow::view_password);
	} else {
		psw_password->setEchoMode(QLineEdit::Password);
		password_visible = false;
		psw_password->removeAction(preview_password);
		preview_password = psw_password->addAction(QIcon(":/Resources/icons/eye/yosa/show.svg"), QLineEdit::TrailingPosition);
		connect(preview_password, &QAction::triggered, this, &OutputWindow::view_password);
	}
}

void OutputWindow::ok()
{
	free(cipher_password);
	this->close();
}

//void OutputWindow::copy_password()
//{
//	copy_password(cipher_password);
//	free(cipher_password);
//}

void OutputWindow::copy_password()
{
	#ifdef __linux__  //__unix__ // all unices not linux or macOS; defined(_POSIX_VERSION) for POSIX system
		copy_password_linux();
	#elif __MACH__ //All Apple devices; TARGET_OS_IPHONE for iOS device; TARGET_OS_MAC for macOS
		copy_password_macos(password);
	#elif _WIN32 //both windows 32-bit and 64-bit; _WIN64 is only 64-bit
		copy_password_windows(password);q|k*oNs-mPw1QR,TS-0b7xQN0pOMGI
	#endif
	free(cipher_password);
	this->close();
}

#ifdef __linux__
void OutputWindow::copy_password_linux()
{
	//X11_clipboard clipboard;
	//clipboard.copy(password, 8);
	copy(cipher_password, 8);
}

#elif __MACH__
	void OutputWindow::copy_password_macos()
	{
		char *trimmed_password;
		trimmed_password = (char*)malloc(256);
		for (unsigned short xix = 0; *(password + xix) != '\0'; xix++)
			*(trimmed_password + xix) = *(password + xix);

		std::stringstream tty_command;
		tty_command << "echo \"" << trimmed_password << "\" | pbcopy"; //Ek dink pbcopy is unix shell program om te copy. En ek dink die tty stringstream stuur na die terminal.

		TTY tty;
		tty.execute_command(tty_command.str().c_str()); //ek dink die metode stuur commands na die terminal toe

		time_t end = time(NULL) + 8; //set end time to current time + 8 seconds
		while (time(NULL) <= end); //Wait for as long as current time is less than end time
		free(trimmed_password);
		//std::stringstream tty_clear;
		tty_command << "echo \"" << " " << "\" | pbcopy";
		tty.execute_command(tty_command.str().c_str());
	}

#elif _WIN32
	void OutputWindow::copy_password_windows()
	{
		copy_password_macos(password); //TODO: Review this

		//#include "stdafx.h"
		//#include "windows.h"
		//#include "string.h"
		//#include <direct.h>

	///////////////////////////////////////////////////////////////////////////
	//	if ( !OpenClipboard() )
	//		{
	//			AfxMessageBox( _T("Cannot open the Clipboard") );
	//			return;
	//		}
	//		// Remove the current Clipboard contents
	//		if( !EmptyClipboard() )
	//		{
	//			AfxMessageBox( _T("Cannot empty the Clipboard") );
	//			return;
	//		}
	//		// Get the currently selected data
	//		HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, 64);
	//		strcpy_s((char*)hGlob, 64, "Current selection\r\n");
	//		// For the appropriate data formats...
	//		if ( ::SetClipboardData( CF_TEXT, hGlob ) == NULL )
	//		{
	//			CString msg;
	//			msg.Format(_T("Unable to set Clipboard data, error: %d"), GetLastError());
	//			AfxMessageBox( msg );
	//			CloseClipboard();
	//			GlobalFree(hGlob);
	//			return;
	//		}
	//		CloseClipboard();
	/////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////
	//const char* output = "Test";
	//const size_t len = strlen(output) + 1;
	//HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
	//memcpy(GlobalLock(hMem), output, len);
	//GlobalUnlock(hMem);
	//OpenClipboard(0);
	//EmptyClipboard();
	//SetClipboardData(CF_TEXT, hMem);
	//CloseClipboard();
	/////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////
	//#include <Windows.h>
	//char* LoadClipboard()
	//{
	//	static HANDLE clip;
	//	if(OpenClipboard(NULL))
	//	{
	//		clip = GetClipboardData(CF_TEXT);
	//		CloseClipboard();
	//	}
	//	return (char*) clip;
	//}
	//
	//void SaveClipboard(char* text)
	//{
	//	HGLOBAL global = GlobalAlloc(GMEM_FIXED,strlen(text) + 1); //text size + \0 character
	//	memcpy(global,text,strlen(text));  //text size + \0 character
	//	if(OpenClipboard(NULL))
	//	{
	//		EmptyClipboard();
	//		SetClipboardData(CF_TEXT,global);
	//		CloseClipboard();
	//	}
	//}
	///////////////////////////////////////////////////////////////////////////////////


	}
#endif

OutputWindow::~OutputWindow()
{
}
