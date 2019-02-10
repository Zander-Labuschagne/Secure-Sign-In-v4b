#include "output_window.hpp"
//#include "x11_clipboard.hpp"
//#include "tty.hpp"

#include <QFile>
#include <QFontDatabase>

OutputWindow::OutputWindow(QWidget *parent, char *cipher_password, QClipboard *clipboard) : QDialog(parent)
{
	OutputWindow::cipher_password = cipher_password;
	OutputWindow::clipboard = clipboard;
	initialize_components();
}

void OutputWindow::initialize_components()
{
	clipboard = QGuiApplication::clipboard();
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
	free(clipboard);
	this->close();
}

void OutputWindow::copy_password()
{
	clipboard->setText(cipher_password);
	this->close();
}

OutputWindow::~OutputWindow()
{
}
