# Secure Sign In v4b

This is a C++ GUI(Qt) application I have created in an attempt to improve my online account security. The user provides a password with an accompanying key that is unique to the website(or account) requiring the password, the application then provides a lengthy and complicated password to be used instead. The _b_ in the version code states that this is the GUI(Graphical User Interface) version where _a_ would be the CLI(Command Line Interface). Find the CLI version at https://gitlab.com/Zander-Labuschagne/SecureSignIn-v4a or https://github.com/Zander-Labuschagne/SecureSignIn-v4a

## *This application is still being tested, there are a few known bugs*

### Benefits:
  - Remember one password for all sites, but all sites have different passwords.
  - Don't know the actual password which is entered in the password box on the website.
  - Provides a very strong, long and complex password.
  - No passwords are stored in file or database.
  - Easy to use.
  
This *(v4b)* is my first official C++ GUI(Qt) application, feel free to criticize or comment. I would appreciate criticism or comments on my coding style since I am not completely sure on the normal conventions, I have tried to stick with the Linux kernel coding style (https://github.com/torvalds/linux/blob/master/Documentation/process/coding-style.rst).
There are Android, iPhone, iPad and macOS applications available as well, however they are not always up to date and I have left some of them discontinued/incomplete. I work on these projects in my free time only so don't expect regular updates from me. This is only compatible on Linux and macOS systems. (There is Windows compatible code that is supposed to be the equivalent but I have not tested it yet and some are not fully implemented yet)

macOS(Swift) version: TBA

Sailfish OS version: *In progress*

iOS version: *TBA*

Android version: https://gitlab.com/Zander-Labuschagne/SecureSignIn-Mobile

The logo and name on the application comes from an iWorks template, it is not a registered company name or logo, I just added it to make it look impressive.

E-Mail: <zander.labuschagne@protonmail.ch>
Copyright (C) 2019 Zander Labuschagne. This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License version 3 as published by the Free Software Foundation.

## How to install:
### Linux:
TBC
### macOS:
TBC  
*(Feel free to create a Windows version, I will eventually do it myself when I get to it)*

## How to use application:
  1. Enter a password you will remember in the password box, preferably a strong and complicated password because this will influence the complexity of the resulting password.
  2. Enter a key, such as google, facebook or whatever.
  3. Click on Encrypt Password and the rest is self explanatory.
  4. Some websites have limitations on the length of the passwords, hence the compact password toggle switch.