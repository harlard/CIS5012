#include "Console.h"

Console::Console(int commandHistory, int textHistory, bool echo, ConsoleFunction defaultFunction, int commandlineIndex)
{
    commandBufferSize = commandHistory;
    textBufferSize = textHistory;
    commandEcho = echo;
    defaultCommand = defaultFunction;
    lineIndex = commandlineIndex;
}

Console::~Console()
{}

void Console::print(const std::string & strTxt)
{
    // push it
    textBuffer.push_back(strTxt);

    // if we are out of bounds
    if(textBuffer.size() > textBufferSize)
    textBuffer.pop_front();
}

bool Console::parseCommandLine(std::string commandLine)
{
    std::ostringstream out;
    std::string::size_type index = 0;
    std::vector<std::string> arguments;
    std::list<ConsoleItem>::const_iterator iter;

    // add to text buffer
    if(commandEcho)
    {
        print(commandLine);
    }

    // add to commandline buffer
    commandBuffer.push_back(commandLine);
    if(commandBuffer.size() > commandBufferSize) commandBuffer.erase(commandBuffer.begin());

    // tokenize
    while(index != std::string::npos)
    {
        // push word
        std::string::size_type nextSpace = commandLine.find(' ', index);
        arguments.push_back(commandLine.substr(index, nextSpace));

        // increment index
        if(nextSpace != std::string::npos) index = nextSpace + 1;
        else break;
    }

    // execute
    for(iter = itemList.begin(); iter != itemList.end(); ++iter)
    {
        if(iter->name == arguments[0])
        {
            switch(iter->type)
            {
            case CTYPE_UCHAR:
                if(arguments.size() > 2)
                {
                    return true;
                }
                else if(arguments.size() == 1)
                {
                    out.str("");
                    out << (*iter).name << " = " << *((unsigned char *)(*iter).variablePointer);
                    print(out.str());
                    return true;
                }
                else if(arguments.size() == 2)
                {
                    *((unsigned char *)(*iter).variablePointer) = (unsigned char) atoi(arguments[1].c_str());
                    return true;
                }
                break;

            case CTYPE_CHAR:
                if(arguments.size() > 2)
                {
                    return true;
                }
                else if(arguments.size() == 1)
                {
                    out.str("");
                    out << (*iter).name << " = " << *((char *)(*iter).variablePointer);
                    print(out.str());
                    return true;
                }
                else if(arguments.size() == 2)
                {
                    *((char *)(*iter).variablePointer) = (char) atoi(arguments[1].c_str());
                    return true;
                }
                break;

            case CTYPE_UINT:
                if(arguments.size() > 2)
                {
                    return true;
                }
                else if(arguments.size() == 1)
                {
                    out.str("");
                    out << (*iter).name << " = " << *((unsigned int *)(*iter).variablePointer);
                    print(out.str());
                    return true;
                }
                if(arguments.size() == 2)
                {
                    *((unsigned int *)(*iter).variablePointer) = (unsigned int) atoi(arguments[1].c_str());
                    return true;
                }
                break;

            case CTYPE_INT:
                if(arguments.size() > 2)
                {
                    return true;
                }
                else if(arguments.size() == 1)
                {
                    out.str("");
                    out << (*iter).name << " = " << *((int *)(*iter).variablePointer);
                    print(out.str());
                    return true;
                }
                if(arguments.size() == 2)
                {
                    *((int *)(*iter).variablePointer) = (int) atoi(arguments[1].c_str());
                    return true;
                }
                break;

            case CTYPE_FLOAT:
                if(arguments.size() > 2)
                {
                    return true;
                }
                else if(arguments.size() == 1)
                {
                    out.str("");
                    out << (*iter).name << " = " << *((float *)(*iter).variablePointer);
                    print(out.str());
                    return true;
                }
                if(arguments.size() == 2)
                {
                    *((float *)(*iter).variablePointer) = (float)atof(arguments[1].c_str());
                    return true;
                }
                break;

            case CTYPE_STRING:
                if(arguments.size() == 1)
                {
                    out.str("");
                    out << (*iter).name << " = " << *(std::string *)(*iter).variablePointer;
                    print(out.str());
                    return false;
                }
                else if(arguments.size() > 1)
                {
                    // reset variable
                    *((std::string *)(*iter).variablePointer) = "";

                    // add new string
                    for(int i = 1; i < arguments.size(); ++i)
                    {
                        *((std::string *)(*iter).variablePointer) += arguments[i];
                    }
                    return true;
                }
                break;

            case CTYPE_FUNCTION:
                (*iter).function(arguments);
                return true;
                break;

            default:
                defaultCommand(arguments);
                return false;
                break;
            }
        }
    }

    // Couldn't match the command
    defaultCommand(arguments);
    return false;
}

void Console::sendMessage(std::string command)
{
    // If you are using multiple threads this is where you
    // should grab the semaphore to prevent data corruption.
    commandQueue.push_back(command);
    // Release the semaphore here.
}

void Console::addItem(const std::string & strName, void *pointer, ConsoleItemType type)
{
    ConsoleItem it;

    // fill item properties
    it.name = strName;
    it.type = type;

    // address
    if(type != CTYPE_FUNCTION)
    {
        it.variablePointer = pointer;
    }
    else
    {
        it.function = (ConsoleFunction) pointer;
    }

    // add item
    itemList.push_back(it);
}

void Console::deleteItem(const std::string & strName)
{
    ItemList::iterator iter;

    // find item
    for (iter = itemList.begin(); iter != itemList.end(); ++iter)
    {
        if (iter->name == strName)
        {
            itemList.erase(iter);
            break;
        }
    }
}

void Console::parseCommandQueue()
{
    std::list<std::string>::iterator it;

    for(it = commandQueue.begin(); it != commandQueue.end(); ++it)
    {
        parseCommandLine(*it);
    }
    commandQueue.clear();
}

void Console::setOutputBufferSize(int size)
{
    textBufferSize = size;

    // remove any extra line
    if(textBuffer.size() > textBufferSize)
    {
        std::list<std::string>::iterator it;
        int diff = textBuffer.size() - textBufferSize;
        for(int i = 0; i < diff; i++)
        {
            textBuffer.erase(textBuffer.begin());
        }
    }
}

void Console::setCommandBufferSize(int size)
{
    commandBufferSize = size;

    // remove any extra line
    if(commandBuffer.size() > commandBufferSize)
    {
        std::vector<std::string>::iterator it;
        it = commandBuffer.end() - commandBufferSize;
        commandBuffer.erase(commandBuffer.begin(), it);
    }
}

std::string Console::getPrevCommand(int i)
{
    // increment line index
    lineIndex += i;

    // error correct line index
    if(lineIndex < 0)
    {
        lineIndex = 0;
    }
    else if(lineIndex >= textBuffer.size())
    {
        lineIndex = textBuffer.size() - 1;
    }

    // set command line
    if(!commandBuffer.empty()) return commandBuffer[lineIndex];
    else return "";
}
