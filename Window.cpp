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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "Window.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Window::Window ()
    : sendingTextBox (0),
      sendingButton (0),
      followButton (0),
      portTextBox (0),
      messageTextBox (0)
{
    addAndMakeVisible (sendingTextBox = new TextEditor (T("send")));
    sendingTextBox->setMultiLine (true);
    sendingTextBox->setReturnKeyStartsNewLine (false);
    sendingTextBox->setReadOnly (false);
    sendingTextBox->setScrollbarsShown (true);
    sendingTextBox->setCaretVisible (true);
    sendingTextBox->setPopupMenuEnabled (true);
    sendingTextBox->setText (String::empty);

    addAndMakeVisible (sendingButton = new TextButton (T("sendButton")));
    sendingButton->setButtonText (T("Send"));
    sendingButton->addButtonListener (this);
    sendingButton->setVisible(false);    

    addAndMakeVisible (followButton = new TextButton (T("followButton")));
    followButton->setButtonText (T("Follow"));
    followButton->addButtonListener (this);
    followButton->setVisible(false);

    addAndMakeVisible (connectButton = new TextButton (T("connectButton")));
    connectButton->setButtonText (T("Connect"));
    connectButton->addButtonListener (this);

    addAndMakeVisible (portTextBox = new TextEditor (T("port")));
    portTextBox->setMultiLine (false);
    portTextBox->setReturnKeyStartsNewLine (false);
    portTextBox->setReadOnly (false);
    portTextBox->setScrollbarsShown (true);
    portTextBox->setCaretVisible (true);
    portTextBox->setPopupMenuEnabled (true);
    portTextBox->setText ("5000");
    
    addAndMakeVisible (ipTextBox = new TextEditor (T("ip")));
    ipTextBox->setMultiLine (false);
    ipTextBox->setReturnKeyStartsNewLine (false);
    ipTextBox->setReadOnly (false);
    ipTextBox->setScrollbarsShown (true);
    ipTextBox->setCaretVisible (true);
    ipTextBox->setPopupMenuEnabled (true);
    ipTextBox->setText ("127.0.0.1");

    addAndMakeVisible (messageTextBox = new TextEditor (T("messages")));
    messageTextBox->setMultiLine (true);
    messageTextBox->setReturnKeyStartsNewLine (false);
    messageTextBox->setReadOnly (true);
    messageTextBox->setScrollbarsShown (true);
    messageTextBox->setCaretVisible (true);
    messageTextBox->setPopupMenuEnabled (true);
    messageTextBox->setText (String::empty);

    addAndMakeVisible (statusTextBox = new TextEditor (T("status")));
    statusTextBox->setMultiLine (true);
    statusTextBox->setReturnKeyStartsNewLine (false);
    statusTextBox->setReadOnly (true);
    statusTextBox->setScrollbarsShown (true);
    statusTextBox->setCaretVisible (true);
    statusTextBox->setPopupMenuEnabled (true);
    statusTextBox->setText (String::empty);
    
    //[UserPreSize]
    //[/UserPreSize]

    setSize (800, 600);

    //[Constructor] You can add your own custom stuff here..

    connected = false;

    //[/Constructor]
}

void Window::addToBox(const char* text,TextEditor* box){
    String s = box->getText();
    s = text + s;
    box->setText(s);
}


/*
void Window::receivingFromServer(){
    String s = messageTextBox->getText();
    s = tweety.receive()+ String("\n") +s;
   
    messageTextBox->setText(s.toCString());
}*/

Window::~Window()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]
    deleteAndZero (sendingTextBox);
    deleteAndZero (sendingButton);
    deleteAndZero (followButton);
    deleteAndZero (portTextBox);
    deleteAndZero (messageTextBox);
    deleteAndZero (statusTextBox);
    deleteAndZero (ipTextBox);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Window::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Window::resized()
{
    connectButton->setBounds(320,30,150,24);
    ipTextBox->setBounds(500,70,150,24);
    portTextBox->setBounds (500, 10, 100, 24);

    sendingButton->setBounds (320, 140, 150, 24);
    followButton->setBounds (320, 180, 150, 24);
    sendingTextBox->setBounds (10, 130, 300, 100);
    statusTextBox->setBounds (10, 20, 300, 100);
    messageTextBox->setBounds (10, 300, 450, 400);  
}

void Window::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == sendingButton)
    {
        if(!sendingTextBox->isEmpty()){
            tweety.sending(sendingTextBox->getText().toCString());
            sendingTextBox->setText("");
        }
        else{
            addToBox("The sending Text is empty",statusTextBox);
        }
    }
    else if (buttonThatWasClicked == followButton)
    {
        if(!sendingTextBox->isEmpty()){
            string sender = "f ";
            sender.append(sendingTextBox->getText().toCString());
            runFunction(SEND,);
            sendingTextBox->setText("");
        }
        else{
            addToBox("The sending Text is empty",statusTextBox);
        }

    }
    else if (buttonThatWasClicked == connectButton)
    {
        bool success = runFunction(RUN,"");
        if(connected){
            tweety.closeClient();
            connectButton->setButtonText("Connect");
        }
        else{
            connectButton->setButtonText("Disconnect");
            success = runFunction(CONNECT,"");
        }
        if(success)connected = !connected;       
        
        sendingButton->setVisible(connected);
        followButton->setVisible(connected);
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

bool Window::runFunction(int function, const char* text){
    bool success;
    switch(function){
        case RUN:
            success = tweety.run();
            break;
        case CONNECT:
            int port = portTextBox->getText().getIntValue();
            success = tweety.connection(port, ipTextBox->getText().toCString());                
            if(success){
                addToBox("Connected with Server",statusTextBox);
                addToBox("Send a Tweetername to Login",statusTextBox);
                pthread_t pid;
                pthread_create(&pid ,NULL, &handleThread, this);                
            }
            break;
        case SEND:
            success = tweety.sending(text);
            if(success)addToBox("Message sended",statusTextBox);
            break;
        case RECEIVE:
            string received = tweety.receive(&success); 
            if(success) handleMessage(received);
            break;
    }
    if(!success){
        addToBox(tweety.getError(),statusTextBox);
    }
}

void Window::handleMessage(const char* text){
    String message = text;
    if(message.startsWithChar('m')){
        //message.substring(1);
         string t = message.substring(1,message.indexOfChar(';'));
         addToBox(t,messageTextBox); 
    }

}

void* Window::handleThread(void *arg){
    Window* thread = static_cast<Window*>(arg);
    pthread_detach(pthread_self());
    while(connected){
        thread->runFunction(RECEIVE,"");
    }
    return (NULL);
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Window" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="800" initialHeight="600">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TEXTEDITOR name="send" id="acaa27c826528d05" memberName="sendingTextBox" virtualName=""
              explicitFocusOrder="0" pos="40 376 496 144" initialText="" multiline="1"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTBUTTON name="sendButton" id="967b51d5f9704a3" memberName="sendingButton"
              virtualName="" explicitFocusOrder="0" pos="560 384 150 24" buttonText="Send"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="followButton" id="6b3ea09f59fc2546" memberName="followButton"
              virtualName="" explicitFocusOrder="0" pos="576 544 150 24" buttonText="Follow"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="follow" id="562629d74b92aff0" memberName="portTextBox"
              virtualName="" explicitFocusOrder="0" pos="320 544 224 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="messages" id="25e475ca74ee0bab" memberName="messageTextBox"
              virtualName="" explicitFocusOrder="0" pos="32 16 656 336" initialText=""
              multiline="1" retKeyStartsLine="0" readonly="1" scrollbars="1"
              caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
