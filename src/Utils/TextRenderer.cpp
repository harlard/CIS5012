#include "TextRenderer.h"

template<> TextRenderer* Ogre::Singleton<TextRenderer>::ms_Singleton = 0;

TextRenderer::TextRenderer()
{
    _overlayMgr = Ogre::OverlayManager::getSingletonPtr();

    _overlay = _overlayMgr->create("overlay1");
    _panel = static_cast<Ogre::OverlayContainer*>(_overlayMgr->createOverlayElement("Panel", "container1"));
    _panel->setDimensions(1, 1);
    _panel->setPosition(0, 0);

    _overlay->add2D(_panel);

    _overlay->show();
}

void TextRenderer::addTextBox(const std::string& ID,
                const std::string& text,
                Ogre::Real x, Ogre::Real y,
                Ogre::Real width, Ogre::Real height,
                const Ogre::ColourValue& color)
{
    Ogre::OverlayElement* textBox = _overlayMgr->createOverlayElement("TextArea", ID);
    textBox->setDimensions(width, height);
    textBox->setMetricsMode(Ogre::GMM_PIXELS);
    textBox->setPosition(x, y);
    textBox->setWidth(width);
    textBox->setHeight(height);
    textBox->setParameter("font_name", "MyFont");
    textBox->setParameter("char_height", "0.3");
    textBox->setColour(color);

    textBox->setCaption(text);

    _panel->addChild(textBox);
}

void TextRenderer::removeTextBox(const std::string& ID)
{
    _panel->removeChild(ID);
    _overlayMgr->destroyOverlayElement(ID);
}

void TextRenderer::setText(const std::string& ID, const std::string& Text)
{
    Ogre::OverlayElement* textBox = _overlayMgr->getOverlayElement(ID);
    textBox->setCaption(Text);
}

const std::string& TextRenderer::getText(const std::string& ID)
{
    Ogre::OverlayElement* textBox = _overlayMgr->getOverlayElement(ID);
    return textBox->getCaption();
}
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
