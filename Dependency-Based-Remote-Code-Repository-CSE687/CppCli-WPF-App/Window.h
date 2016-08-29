#ifndef WINDOW_H
#define WINDOW_H
//////////////////////////////////////////////////////////////////////////
// Window.h - C++\CLI implementation of WPF Application                 //
// Ver: 2.0																//
// Application: Project #4 Dependency-Based Remote Code Repository      //
// Language:    C++, Visual Studio 2015									//
// Platform:    Dell Inspiron 5548, Core-i5, Windows 10					//
// Author:      Achal Velani, SUID:292190387							//
// Reference:   Jim Fawcett, CST 4-187, Syracuse University				//
//              (315) 443-3948, jfawcett@twcny.rr.com					//
//////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package demonstrates how to build a C++\CLI WPF application.  It 
*  provides one class, WPFCppCliDemo, derived from System::Windows::Window
*  that is compiled with the /clr option to run in the Common Language
*  Runtime, and another class MockChannel written in native C++ and compiled
*  as a DLL with no Common Language Runtime support.
*
*  The window class hosts, in its window, a tab control with three views, two
*  of which are provided with functionality that you may need for Project #4.
*  It loads the DLL holding MockChannel.  MockChannel hosts a send queue, a
*  receive queue, and a C++11 thread that reads from the send queue and writes
*  the deQ'd message to the receive queue.
*
*  The Client can post a message to the MockChannel's send queue.  It hosts
*  a receive thread that reads the receive queue and dispatches any message
*  read to a ListBox in the Client's FileList tab.  So this Demo simulates
*  operations you will need to execute for Project #4.
*
*  Required Files:
*  ---------------
*  Window.h, Window.cpp, MochChannel.h, MochChannel.cpp,
*  resources.h
* 
*  Public Interface:
*  ----------------
*  WPFCppCliDemo(array<System::String^>^ args) - This is a constructor which takes arguments to sent client and server addresses and ports.
*
*  Build Command:
*  --------------
*  devenv Project4.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
*  ver 2.0 : 15 Apr 2015
*  - completed message passing demo with moch channel
*  - added FileBrowserDialog to show files in a selected directory
*  ver 1.0 : 13 Apr 2015
*  - incomplete demo with GUI but not connected to mock channel
*/
/*
* Create C++/CLI Console Application
* Right-click project > Properties > Common Language Runtime Support > /clr
* Right-click project > Add > References
*   add references to :
*     System
*     System.Windows.Presentation
*     WindowsBase
*     PresentatioCore
*     PresentationFramework
*/
using namespace System;
using namespace System::Text;
using namespace System::Windows;
using namespace System::Windows::Input;
using namespace System::Windows::Markup;
using namespace System::Windows::Media;                   // TextBlock formatting
using namespace System::Windows::Controls;                // TabControl
using namespace System::Windows::Controls::Primitives;    // StatusBar
using namespace System::Threading;
using namespace System::Threading::Tasks;
using namespace System::Windows::Threading;
using namespace System::ComponentModel;

#include "../MockChannel/MockChannel.h"
#include <iostream>
#include "../HttpMessage/HttpMessage.h"
namespace CppCliWindows
{
	ref class WPFCppCliDemo : Window
	{
		// MockChannel references

		//ISendr* pSendr_;
		//IRecvr* pRecvr_;
		IMockChannel* pChann_;
		// Controls for Window
		DockPanel^ hDockPanel = gcnew DockPanel();      // support docking statusbar at bottom
		Grid^ hGrid = gcnew Grid();
		TabControl^ hTabControl = gcnew TabControl();
		TabItem^ hSendMessageTab = gcnew TabItem();
		TabItem^ hCheckinTab = gcnew TabItem();
		TabItem^ hExtractTab = gcnew TabItem();
		StatusBar^ hStatusBar = gcnew StatusBar();
		StatusBarItem^ hStatusBarItem = gcnew StatusBarItem();
		TextBlock^ hStatus = gcnew TextBlock();
		// Controls for SendMessage View
		Grid^ hSendMessageGrid = gcnew Grid();
		Button^ hShutDownServer = gcnew Button();  //hSendButton
		Button^ hClearButton = gcnew Button();
		Label^ hLabel1 = gcnew Label();
		TextBlock^ hTextBlock1 = gcnew TextBlock();
		ScrollViewer^ hScrollViewer1 = gcnew ScrollViewer();
		StackPanel^ hStackPanel1 = gcnew StackPanel();
		String^ msgText
			= "Command:ShowMessage\n"   // command
			+ "Sendr:localhost@8080\n"  // send address
			+ "Recvr:localhost@8090\n"  // receive address
			+ "Content-length:44\n"     // body length attribute
			+ "\n"                      // end header
			+ "Hello World\nCSE687 - Object Oriented Design";  // message body

		  // Controls for FileListView View
		Grid^ hCheckinGrid = gcnew Grid();
		Forms::FolderBrowserDialog^ hFolderBrowserDialog = gcnew Forms::FolderBrowserDialog();
		Forms::FolderBrowserDialog^ hFolderBrowserDialog1 = gcnew Forms::FolderBrowserDialog();
		ListBox^ hListBox = gcnew ListBox();
		ListBox^ hListBox1 = gcnew ListBox();
		Button^ hFolderBrowseButton = gcnew Button();
		Button^ hShowItemsButton = gcnew Button();
		Button^ hFolderBrowseButton1 = gcnew Button();
		Button^ hShowItemsButton1 = gcnew Button();
		Button^ hCheckinButton = gcnew Button();
		RadioButton^ hRadioOpen = gcnew RadioButton();
		RadioButton^ hRadioClose = gcnew RadioButton();
		Label^ hLabelOpen = gcnew Label();
		Label^ hLabelClose = gcnew Label();
		StackPanel^ hStackPanel2 = gcnew StackPanel();
		StackPanel^ hStackPanel3 = gcnew StackPanel();
		Grid^ hGrid2 = gcnew Grid();

		//Extarct view
		//Forms::FolderBrowserDialog^ hFolderBrowserDialog3 = gcnew Forms::FolderBrowserDialog();
		Grid^ hExtractGrid = gcnew Grid();
		ListBox^ hListBox3 = gcnew ListBox();
		ListBox^ hListBox4 = gcnew ListBox();
		Label^ hLabelhcpp = gcnew Label();
		Button^ hRepoBrowseButton = gcnew Button();
		Button^ hWDepButton = gcnew Button();
		Button^ hWODepButton = gcnew Button();
		StackPanel^ hStackPanel4 = gcnew StackPanel();
		StackPanel^ hStackPanel5 = gcnew StackPanel();

		// receive thread
		Thread^ recvThread;

	public:
		WPFCppCliDemo(array<System::String^>^ args);
		~WPFCppCliDemo();



	private:
		void setUpStatusBar(); // This sets up status bar
		void setUpTabControl(); // This sets up tab control.		
		void setUpHomeView(); // This sets Up home view
		void setUpCheckinView(); // This sets up checkIn view
		void setUpExtractView(); // This sets up exractView

		void shutDownServerMessage(Object^ obj, RoutedEventArgs^ args); // This will form shutdown server
		void addText(String^ msg);// This will add text to the textBlock.
		void getMessage();// This will get messages from the channel and redirect it to specified functions
		void shutDownClientSend(Object^ sender, RoutedEventArgs^ args);// This will shut down the client sender

		void getItemsFromList(Object^ sender, RoutedEventArgs^ args);//This will get items from the list.
		void getDependencyFromList(Object^ sender, RoutedEventArgs^ args);// This will get dependency list.
		void browseForFolder(Object^ sender, RoutedEventArgs^ args);//This will browse the folder.
		void browseForFolderInRepo(Object^ sender, RoutedEventArgs^ args);// This will help in browsing all the files from the repo
		void radioOpen(Object^ sender, RoutedEventArgs^ args);// This will display status of open radio button on the status bar.
		void radioClose(Object^ sender, RoutedEventArgs^ args);// This will display status of close radio button on the status bar.
		void checkin(Object^ sender, RoutedEventArgs^ args);//This will handel all the things when check in button is clicked

		void browseRepo(Object^ sender, RoutedEventArgs^ args);//This will create the message for repository check, on clicking the browse button for the repo
		void extractWDep(Object^ sender, RoutedEventArgs^ args);//This will do button properties for the extract with dependencies
		void extractWODep(Object^ sender, RoutedEventArgs^ args);// This will create a message to extract without dependency when certain set of conditions are met

		void OnLoaded(Object^ sender, RoutedEventArgs^ args);// This will display message on console when window is loaded.
		void Unloading(Object^ sender, System::ComponentModel::CancelEventArgs^ args);// This will display a message on window when the GUI is closed.

		array<String^>^ WPFCppCliDemo::getPackageNames(HttpMessage& msg);//This will extract package names from the incoming messages.
		void updateListBox1(array<String^>^ args);// This will update the list box 
		void WPFCppCliDemo::updateStatusBox(String^ msg);// Update status message in application. 
		std::string statusCheck();// This function will help in reading the status of the radio buttons.
		void setUpExtractButtons();// THis will set up the extract buttons.
		void setUpStackPanel4();//This will set up the stack panel 4.
		void setUpStackPanel2();//This will set up stack panel 2.
		void setUpCheckInHelper(); // This will set up check in helper tab
		void setUpCheckInHelperButtons();//This will set up check in butoons.
		void setUpCheckInHelperStackPanel3(); //This will help in setting up stack panel 3.

		// Following functions are functions for displaying various requirements of the project.
		void testExec();
		void req1_2();
		void req3();
		void checkInPackage_5();
		void openCloseProperty_6();
		void extraction_7();
		void messagePassing_8();
		void httpMessage_9();
		void streamBytes_10();
		void automatedtestSuit();
		
		std::string toStdString(String^ pStr);//This converts manged string to standard string.
		String^ toSystemString(std::string& str);// This will convert std::string to String^
		void setTextBlockProperties();//this sets text block properties.
		void setButtonsProperties();// This sets up butoon properties
		std::string httpStyleMessage(HttpMessage msg);// This function will convert httpStyle message object to string
		std::vector<std::string> getAttributes(HttpMessage msg, std::string temp);//This function will split thre messahe by its attributes.
		std::map<std::string, std::string> getMap(HttpMessage msg, std::vector<std::string> attributes);//This function returns map of all the attributes in the HttpMessage
		String^ printHelper(std::map<std::string, std::string> map);//This function will help in printing the httpStyle message on the GUI
		bool parseCommandLineArguments(array<System::String^>^ args);// This function will parse the command line arguments and will set client and server ports

		String^ clientArgument; //This will store incomin client address
		String^ serverArgument; // This will store incoming server address
		array<String^>^ client; // This store client address and port 
		array<String^>^ server;// This store server address and port 

		String^ serverAddress; //This stores the server address.
		String^ serverPort; // This sstores server port
		String^ clientAddress; // This stores client address
		String^ clientPort; //This stores client port
	};
}


#endif
