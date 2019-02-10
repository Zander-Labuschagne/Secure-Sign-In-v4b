#ifndef SECURESIGNIN_HPP
#define SECURESIGNIN_HPP

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>

#include "output_window.hpp"

/*
 * @author Zander Labuschagne
 * E-Mail: <zander.labuschagne@protonmail.ch>
 */

class SecureSignInWindow : public QMainWindow
{
	Q_OBJECT

public:
	SecureSignInWindow(QWidget *parent = 0);
	void initialize_components();
	~SecureSignInWindow();

private:
	QString *plain_password;
	QString *key;
	QString *cipher_password;
	bool password_visible;
	bool key_visible;
	QAction *preview_password;
	QAction *preview_key;

	//GUI Controls
	QLabel *lbl_password;
	QLabel *lbl_key;
	QLineEdit *psw_password;
	QLineEdit *psw_key; //Normal Text edit box with echoMode property set to password. //TODO: Add eye button to text box to preview password
	QLabel *lblCompact;
	QSlider *sld_compact; //Slider being used as a toggle button :) <- way easier than java
	QPushButton *btn_encrypt;
	QLabel *lbl_logo;
	OutputWindow *output_window;

private slots:
	void view_password();
	void view_key();
	void switch_compact_password();
	void encrypt_password();
};

#endif // SECURESIGNIN_HPP
