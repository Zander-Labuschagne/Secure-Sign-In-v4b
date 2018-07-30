#include "securesignin.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);
	SecureSignIn ssiWindow;
	//ssiWindow.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint); //Die werk nie?
	ssiWindow.setFixedSize(442, 272);
	// Dalk moet die binne die ssiWindow se constructor wees soos in die voorbeeld...
	ssiWindow.setWindowTitle("Secure Sign In v4.0");
	ssiWindow.setWindowIcon(QIcon(":/Resources/icon.png"));
	ssiWindow.show();

	return application.exec();
}
