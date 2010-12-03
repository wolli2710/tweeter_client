/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  30 Nov 2010 10:23:57am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_WINDOW_WINDOW_CE8A25C5__
#define __JUCER_HEADER_WINDOW_WINDOW_CE8A25C5__

//[Headers]     -- You can add your own extra header files here --
#include "client.h"
#include "juce.h"
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Window  : public Component,
                public ButtonListener
{
public:
    //==============================================================================
    Window ();
    ~Window();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    static void* handleThread(void *arg);
    void receivingFromServer();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    client tweety;
    bool connected;  
    //[/UserVariables]

    //==============================================================================
    TextButton* sendingButton;
    TextButton* followButton;
    TextButton* connectButton;
    TextEditor* sendingTextBox;
    TextEditor* portTextBox;
    TextEditor* messageTextBox;
    TextEditor* ipTextBox;
    TextEditor* statusTextBox;
    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    Window (const Window&);
    const Window& operator= (const Window&);
};


#endif   // __JUCER_HEADER_WINDOW_WINDOW_CE8A25C5__
