#ifndef _OGRE_CONSOLE_H_
#define _OGRE_CONSOLE_H_

#include "Console.h"
#include <OgreSingleton.h>
#include <iostream>

class OgreConsole : public Console, public Ogre::Singleton
{
public:
    OgreConsole(int commandHistory = 20, int textHistory = 50, bool echo = false,
        ConsoleFunction defaultFunction = NULL, int commandlineIndex = 0);
    ~OgreConsole();

    static OgreConsole* getSingletonPtr(void);
    static OgreConsole& getSingleton(void);

    void render();
};

#endif
