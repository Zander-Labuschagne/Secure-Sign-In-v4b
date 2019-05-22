#include "secure_sign_in_window.hpp"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{//TODO: Sit dalk 'n if in om die terminal app te include
	QApplication application(argc, argv);
//	application.setStyle(QStyleFactory::create("gtk"));
	SecureSignInWindow ssiWindow;
	//ssiWindow.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint); //Die werk nie?
	ssiWindow.setFixedSize(440, 240);
	// Dalk moet die binne die ssiWindow se constructor wees soos in die voorbeeld...
	ssiWindow.setWindowTitle("Secure Sign In v4.0");
	QIcon *cryogen_icon = new QIcon;
	cryogen_icon->addFile(":/Resources/icon.png", QSize(1024, 1024));
	ssiWindow.setWindowIcon(*cryogen_icon);
	ssiWindow.show();

	return application.exec();
}
