#include "secure_sign_in_window.hpp"
#include "secure_sign_in.hpp"
#include "workerthread.hpp"

#include <QAction>
//#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QThread>

/*
 * @author Zander Labuschagne
 * E-Mail: <zander.labuschagne@protonmail.ch>
 */

//TODO: Add more themes and experiment, Cryogen Theme, JetBrains, GitKraken, Atom etc

SecureSignInWindow::SecureSignInWindow(QWidget *parent) : QMainWindow(parent)
{
//	setWindowTitle(tr("Secure Sign In v4.0")); //Wat doen die tr()?

	plain_password = nullptr;
	key = nullptr;
	cipher_password = nullptr;
	password_visible = false;

	initialize_components();
}

void SecureSignInWindow::initialize_components()
{
	clipboard = QGuiApplication::clipboard();
	//Set up GUI controls
	QFontDatabase::addApplicationFont(":/Resources/fonts/Iosevka Nerd Font Complete.ttf");
	fnt_iosevka = QFont("Iosevka Nerd Font Complete", 14, 65);
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
	lbl_password->setFont(fnt_iosevka);
	lbl_password->show();

	//Label: password key label
	lbl_key = new QLabel(this);
	lbl_key->setFixedSize(40, 20);
	lbl_key->move(20, 145);
	lbl_key->setText("Key:");
	lbl_key->setFont(fnt_iosevka);
	lbl_key->show();

	//LineEdit: Password box
	psw_password = new QLineEdit(this);
	//psw_password.setParent(this);
	psw_password->setFixedSize(320, 25);
	psw_password->move(100, 105);
	psw_password->setEchoMode(QLineEdit::Password);
	psw_password->setClearButtonEnabled(true);
	preview_password = psw_password->addAction(QIcon(":/Resources/icons/eye/yosa/show.svg"), QLineEdit::TrailingPosition);
	connect(preview_password, &QAction::triggered, this, &SecureSignInWindow::view_password);
	psw_password->setStyleSheet(stylesheet);
	psw_password->setFont(fnt_iosevka);
	psw_password->show();

	//LineEdit: Key password box
	psw_key = new QLineEdit(this);
	psw_key->setFixedSize(320, 25);
	psw_key->move(100, 140);
	psw_key->setEchoMode(QLineEdit::Password);
	psw_key->setClearButtonEnabled(true);
	preview_key = psw_key->addAction(QIcon(":/Resources/icons/eye/yosa/show.svg"), QLineEdit::TrailingPosition);
	connect(preview_key, &QAction::triggered, this, &SecureSignInWindow::view_key);
	psw_key->setStyleSheet(stylesheet);
	psw_key->setFont(fnt_iosevka);
	psw_key->show();

	//PushButton: Encrypt password button
	btn_encrypt = new QPushButton(this);
	btn_encrypt->setFixedSize(400, 25);
	btn_encrypt->move(20, 205);
	btn_encrypt->setText("Encrypt Password");
	//TODO: Sit die icon in
	btn_encrypt->setStyleSheet(stylesheet);
	btn_encrypt->setFont(fnt_iosevka);
	btn_encrypt->show();
	connect(btn_encrypt, SIGNAL(clicked()), this, SLOT(encrypt_password()));
//	connect(btn_encrypt, SIGNAL(click()), output_window, SLOT(show()));
//	output_window = new OutputWindow(this); // Be sure to destroy your window somewhere
//	output_window->setFixedSize(300, 200);
//	output_window->setWindowTitle("Secure Sign In v4.0");



	//Label: Compact password switch label
	lbl_compact = new QLabel(this);
	lbl_compact->setFixedSize(120, 15);
	lbl_compact->move(265, 176);
	lbl_compact->setText("Compact Password: ");
	lbl_compact->setStyleSheet(stylesheet);
	lbl_compact->setFont(fnt_iosevka);
	lbl_compact->show();

	//HorizontalSlider: Compact password switch
	sld_compact = new QSlider(this);
	sld_compact->setOrientation(Qt::Horizontal);
	sld_compact->setFixedSize(30, 20);
	sld_compact->move(390, 175);
	sld_compact->setRange(0, 1);
	sld_compact->setSingleStep(1);
	sld_compact->setTickInterval(1);
	sld_compact->setValue(0);
	sld_compact->setTracking(false);
	sld_compact->setStyleSheet(stylesheet);
	sld_compact->show();
	connect(sld_compact, SIGNAL(sliderPressed()), this, SLOT(switch_compact_password()));

	//Logo displayed in label
	lbl_logo = new QLabel(this);
	lbl_logo->setPixmap(QPixmap::fromImage(QImage(":Resources/cryogen.png").scaledToHeight(85, Qt::SmoothTransformation)));
	lbl_logo->setFixedSize(320, 90);
	lbl_logo->move(100, 10);
	lbl_logo->show();
}



void SecureSignInWindow::view_password()
{
	if (!password_visible) {
		psw_password->setEchoMode(QLineEdit::Normal);
		password_visible = true;
		psw_password->removeAction(preview_password);
		preview_password = psw_password->addAction(QIcon(":/Resources/icons/eye/yosa/hide.svg"), QLineEdit::TrailingPosition);
		connect(preview_password, &QAction::triggered, this, &SecureSignInWindow::view_password);
	} else {
		psw_password->setEchoMode(QLineEdit::Password);
		password_visible = false;
		psw_password->removeAction(preview_password);
		preview_password = psw_password->addAction(QIcon(":/Resources/icons/eye/yosa/show.svg"), QLineEdit::TrailingPosition);
		connect(preview_password, &QAction::triggered, this, &SecureSignInWindow::view_password);
	}
}

void SecureSignInWindow::view_key()
{
	if (!key_visible) {
		psw_key->setEchoMode(QLineEdit::Normal);
		key_visible = true;
		psw_key->removeAction(preview_key);
		preview_key = psw_key->addAction(QIcon(":/Resources/icons/eye/yosa/hide.svg"), QLineEdit::TrailingPosition);
		connect(preview_key, &QAction::triggered, this, &SecureSignInWindow::view_key);
	} else {
		psw_key->setEchoMode(QLineEdit::Password);
		key_visible = false;
		psw_key->removeAction(preview_key);
		preview_key = psw_key->addAction(QIcon(":/Resources/icons/eye/yosa/show.svg"), QLineEdit::TrailingPosition);
		connect(preview_key, &QAction::triggered, this, &SecureSignInWindow::view_key);
	}
}

void SecureSignInWindow::switch_compact_password()
{
	if (sld_compact->value() == 0)
		sld_compact->setValue(1);
	else
		sld_compact->setValue(0);
}

void SecureSignInWindow::encrypt_password()
{
	SecureSignIn ssi;
	char *cipher_password;

	if (sld_compact->value() == 1)
		cipher_password =  ssi.encrypt(&(psw_password->text().toStdString().c_str()[0]), &(psw_key->text().toStdString().c_str()[0]), 12);
	else
		cipher_password =  ssi.encrypt(&(psw_password->text().toStdString().c_str()[0]), &(psw_key->text().toStdString().c_str()[0]), 32);

	output_window = new OutputWindow(this, cipher_password, clipboard);
	output_window->setFixedSize(420, 130);
	// Dalk moet die binne die ssiWindow se constructor wees soos in die voorbeeld...
	output_window->setWindowTitle("Secure Sign In v4.0");
	QIcon *cryogen_icon = new QIcon;
	cryogen_icon->addFile(":/Resources/icon.png", QSize(1024, 1024));
	output_window->setWindowIcon(*cryogen_icon);
	output_window->setModal(true);
//	output_window->show();
	output_window->exec();
	delete output_window;
    //wait 8sec on new thread
	WorkerThread *workerThread = new WorkerThread(this);
	connect(workerThread, &WorkerThread::resultReady, this, &SecureSignInWindow::clear);
	connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
	workerThread->start();
}

void SecureSignInWindow::clear()
{
	clipboard->clear();
	free(cipher_password);
}


SecureSignInWindow::~SecureSignInWindow()
{
	clear();
}
