#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <QAction>
#include <QClipboard>
#include <QDialog>
#include <QGuiApplication>
#include <QLineEdit>
#include <QPushButton>

class OutputWindow : public QDialog
{
	Q_OBJECT
public:
	OutputWindow(QWidget *parent = 0, char *cipher_password = 0, QClipboard *clipboard = QGuiApplication::clipboard());
	void initialize_components();
	~OutputWindow();
private:
	char* cipher_password;
	bool password_visible;
	QClipboard *clipboard;
	QAction *preview_password;
	QFont fnt_iosevka;

	QLineEdit *psw_password;
	QPushButton *btn_copy;
	QPushButton *btn_ok;
private slots:
	void view_password();
	void ok();
	void copy_password();
};

#endif // OUTPUT_HPP
