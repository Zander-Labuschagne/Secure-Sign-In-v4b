#include "securesignin.hpp"

#include <QAction>
#include <QDebug>
#include <QFile>

/*
 * @author Zander Labuschagne
 * E-Mail: <zander.labuschagne@protonmail.ch>
 */

//TODO: Add more themes and experiment, Cryogen Theme, JetBrains, GitKraken, Atom etc

SecureSignIn::SecureSignIn(QWidget *parent) : QMainWindow(parent)
{
//	setWindowTitle(tr("Secure Sign In v4.0")); //Wat doen die tr()?

	plain_password = nullptr;
	key = nullptr;
	cipher_password = nullptr;
	password_visible = false;

	initialize_components();
}

void SecureSignIn::initialize_components()
{
	//Set up GUI controls
	QFile stylesheet_file(":/Resources/StyleSheets/gitkraken_cryogen.qss");
	stylesheet_file.open(QFile::ReadOnly);
	QString stylesheet = QLatin1String(stylesheet_file.readAll());
	//MainWindow:
	this->setStyleSheet(stylesheet);

	//Label: password label
	lbl_password = new QLabel(this);
	lbl_password->setFixedSize(60, 15);
	lbl_password->move(20, 110);
	lbl_password->setText("Password:");
	lbl_password->setStyleSheet(stylesheet);
	lbl_password->show();

	//Label: password key label
	lbl_key = new QLabel(this);
	lbl_key->setFixedSize(40, 20);
	lbl_key->move(20, 145);
	lbl_key->setText("Key:");
	lbl_key->show();

	//LineEdit: Password box
	psw_password = new QLineEdit(this);
	//psw_password.setParent(this);
	psw_password->setFixedSize(320, 25);
	psw_password->move(100, 105);
	psw_password->setEchoMode(QLineEdit::Password);
	psw_password->setClearButtonEnabled(true);
	preview_password = psw_password->addAction(QIcon(":/Resources/icons/eye/yosa/show.svg"), QLineEdit::TrailingPosition);
	connect(preview_password, &QAction::triggered, this, &SecureSignIn::view_password);
	psw_password->setStyleSheet(stylesheet);
	psw_password->show();

	//LineEdit: Key password box
	psw_key = new QLineEdit(this);
	psw_key->setFixedSize(320, 25);
	psw_key->move(100, 140);
	psw_key->setEchoMode(QLineEdit::Password);
	psw_key->setClearButtonEnabled(true);
	preview_key = psw_key->addAction(QIcon(":/Resources/icons/eye/yosa/show.svg"), QLineEdit::TrailingPosition);
	connect(preview_key, &QAction::triggered, this, &SecureSignIn::view_key);
	psw_password->setStyleSheet(stylesheet);
	psw_key->show();

	//PushButton: Encrypt password button
	btn_encrypt = new QPushButton(this);
	btn_encrypt->setFixedSize(400, 25);
	btn_encrypt->move(20, 205);
	btn_encrypt->setText("Encrypt Password");
	//TODO: Sit die icon in
	btn_encrypt->setStyleSheet(stylesheet);
	btn_encrypt->show();
}



void SecureSignIn::view_password()
{
	if (!password_visible) {
		psw_password->setEchoMode(QLineEdit::Normal);
		password_visible = true;
		psw_password->removeAction(preview_password);
		preview_password = psw_password->addAction(QIcon(":/Resources/icons/eye/yosa/hide.svg"), QLineEdit::TrailingPosition);
		connect(preview_password, &QAction::triggered, this, &SecureSignIn::view_password);
	} else {
		psw_password->setEchoMode(QLineEdit::Password);
		password_visible = false;
		psw_password->removeAction(preview_password);
		preview_password = psw_password->addAction(QIcon(":/Resources/icons/eye/yosa/show.svg"), QLineEdit::TrailingPosition);
		connect(preview_password, &QAction::triggered, this, &SecureSignIn::view_password);
	}
}

void SecureSignIn::view_key()
{
	if (!key_visible) {
		psw_key->setEchoMode(QLineEdit::Normal);
		key_visible = true;
		psw_key->removeAction(preview_key);
		preview_key = psw_key->addAction(QIcon(":/Resources/icons/eye/yosa/hide.svg"), QLineEdit::TrailingPosition);
		connect(preview_key, &QAction::triggered, this, &SecureSignIn::view_key);
	} else {
		psw_key->setEchoMode(QLineEdit::Password);
		key_visible = false;
		psw_key->removeAction(preview_key);
		preview_key = psw_key->addAction(QIcon(":/Resources/icons/eye/yosa/show.svg"), QLineEdit::TrailingPosition);
		connect(preview_key, &QAction::triggered, this, &SecureSignIn::view_key);
	}
}

SecureSignIn::~SecureSignIn()
{
}
