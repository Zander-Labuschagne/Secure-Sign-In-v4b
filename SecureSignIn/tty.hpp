#ifndef TTY_HPP
#define TTY_HPP

/*
 * class containing functions to allow interaction with tty session on UNIX systems
 *
 * Author:
 *	Zander Labuschagne <zander.labuschagne@protonmail.ch>
 *
 * This should only be compatible with UNIX-like systems, if not please inform me.
 * I am still learning C++ so if anything is unacceptable or a violation to some standards please inform me.
*/

#include <sstream>

#if defined (__MACH__) || defined(__linux__)
	#include <termios.h>
	#include <unistd.h>
#elif _WIN32
	#include <windows.h>
#endif


class TTY
{
public:
	TTY();
	std::string execute_command(const char *tty);
	void set_echo(bool enabled);
	void set_buffer(bool enabled);

private:
	struct termios tty;
	void set_echo_unix(bool enabled);
	void set_echo_windows(bool enabled);
	void set_buffer_unix(bool enabled);
	void set_buffer_windows(bool enabled);
};

#endif // TTY_HPP
