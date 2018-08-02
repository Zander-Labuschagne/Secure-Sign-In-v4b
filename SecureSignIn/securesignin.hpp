#ifndef SECURESIGNIN_HPP
#define SECURESIGNIN_HPP

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>

/*
 * @author Zander Labuschagne
 * E-Mail: <zander.labuschagne@protonmail.ch>
 */

class SecureSignIn : public QMainWindow
{
	Q_OBJECT

public:
	SecureSignIn(QWidget *parent = 0);
	void initialize_components();
	~SecureSignIn();

private:
	QString *plain_password;
	QString *key;
	QString *cipher_password;
	bool password_visible;
	bool key_visible;
	bool compact;
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

private slots:
	void view_password();
	void view_key();
	void switch_compact_password();
};

#endif // SECURESIGNIN_HPP