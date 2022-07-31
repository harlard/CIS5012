#include "OgreConsole.h"

OgreConsole::OgreConsole(int commandHistory, int textHistory, bool echo,
        ConsoleFunction defaultFunction, int commandlineIndex)
        :Console(commandHistory, textHistory, echo, defaultFunction, commandlineIndex)
{
}

OgreConsole::~OgreConsole()
{
}

template<> OgreConsole* Ogre::Singleton<OgreConsole>::ms_Singleton = 0;

OgreConsole* OgreConsole::getSingletonPtr(void)
{
    return ms_Singleton;
}

OgreConsole& OgreConsole::getSingleton(void)
{
    assert(ms_Singleton);
    return (*ms_Singleton);
}

void OgreConsole::render()
{
    for(std::list<std::string>::const_iterator iter = textBuffer.begin(); iter != textBuffer.end(); ++iter)
    {
        std::cout << *iter << "\n";
    }
}
