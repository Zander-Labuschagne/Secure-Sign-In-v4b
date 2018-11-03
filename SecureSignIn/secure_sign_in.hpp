#ifndef SECURE_SIGN_IN_HPP
#define SECURE_SIGN_IN_HPP

/*
 * Class containing encryption function(s) for the Secure Sign In application
 *
 * Author:
 *	Zander Labuschagne <zander.labuschagne@protonmail.ch>
 *
 * I am still learning C++ so if anything is unacceptable or a violation to some standards please inform me.
*/

class SecureSignIn
{
public:
	SecureSignIn();
	char *encrypt(const char *, const char *, unsigned short);
};

#endif // SECURE_SIGN_IN_HPP
