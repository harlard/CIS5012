#ifndef _CONSOLE_H_
#define _CONSOLE_H_

// Disable signed/unsigned mismatch warning
#pragma warning(disable : 4018)
// Disable conversion from 'size_t' to 'int', possible loss of data warning
#pragma warning(disable : 4267)

#include <vector>
#include <list>
#include <sstream>
#include <assert.h>

enum ConsoleItemType
{
    CTYPE_UCHAR,
    CTYPE_CHAR,
    CTYPE_UINT,
    CTYPE_INT,
    CTYPE_FLOAT,
    CTYPE_STRING,
    CTYPE_FUNCTION
};

typedef void (*ConsoleFunction)(const std::vector<std::string> &);

typedef struct {
    std::string name;
    ConsoleItemType type;
    union
    {
        ConsoleFunction function;
        void *variablePointer;
    };
} ConsoleItem;

typedef std::list<ConsoleItem> ItemList;

class Console
{
public:
    Console(int commandHistory, int textHistory, bool echo, ConsoleFunction defaultFunction, int lineIndex);
    virtual ~Console();

    void addItem(const std::string &strName, void *pointer, ConsoleItemType type);
    void deleteItem(const std::string &strName);
    void print(const std::string &strText);
    void setCommandBufferSize(int size);
    int getCommandBufferSize() { return commandBufferSize; }
    void clearCommandBuffer() { commandBuffer.clear(); }
    void setOutputBufferSize(int size);
    int getOutputBufferSize() { return textBufferSize; }
    void clearOutputBuffer() { textBuffer.clear(); }
    std::string getPrevCommand(int index);
    void setDefaultCommand(ConsoleFunction def) { defaultCommand = def; }
    void parseCommandQueue();
    void sendMessage(std::string command);
    void sendImmediateMessage(std::string command) { parseCommandLine(command); }

    virtual void render() = 0;

protected:
    std::list<std::string> textBuffer;
    std::vector<std::string> commandBuffer;

private:
    bool parseCommandLine(std::string commandLine);

    bool commandEcho;
    int lineIndex;
    int commandBufferSize;
    int textBufferSize;
    ConsoleFunction defaultCommand;
    ItemList itemList;
    std::list<std::string> commandQueue;
};
#endif
