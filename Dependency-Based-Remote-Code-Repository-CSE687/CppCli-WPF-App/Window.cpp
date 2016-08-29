//////////////////////////////////////////////////////////////////////////
// Window.cpp - C++\CLI implementation of WPF Application               //
// Ver: 2.0																//
// Application: Project #4 Dependency-Based Remote Code Repository      //
// Language:    C++, Visual Studio 2015									//
// Platform:    Dell Inspiron 5548, Core-i5, Windows 10					//
// Author:      Achal Velani, SUID:292190387							//
// Reference:   Jim Fawcett, CST 4-187, Syracuse University				//
//              (315) 443-3948, jfawcett@twcny.rr.com					//
//////////////////////////////////////////////////////////////////////////


#include "Window.h"
using namespace CppCliWindows;

//This funcrion will be used to display required information on the command prompt.
void CppCliWindows::WPFCppCliDemo::testExec()
{
	std::cout << "\n------------BEGGINNING OF AUTOMATED TEST EXECUTIVE------------\n";
	req1_2();
	req3();
	checkInPackage_5();
	openCloseProperty_6();
	extraction_7();
	messagePassing_8();
	httpMessage_9();
	streamBytes_10();
	automatedtestSuit();
}

void CppCliWindows::WPFCppCliDemo::req1_2()
{
	std::cout << "\n****************************************************************************************************************************\n";
	std::cout << "REQUIREMENT 1 & 2:\n";
	std::cout << "****************************************************************************************************************************\n\n";
	std::cout << "I have used Visual Studio 2015 and its C++ Windows Console Projects\n";
	std::cout << "I have used C++ standard library's streams for all I/O and new and delete for all heap-based memory management\n\n\n";
}
void CppCliWindows::WPFCppCliDemo::req3()
{
	std::cout << "****************************************************************************************************************************\n";
	std::cout << "REQUIREMENT 3:\n";
	std::cout << "****************************************************************************************************************************\n\n";
	std::cout << " Please Use the GUI to check the file in the repository. XML will be created on the server side with required data.\n\n\n";

}

void CppCliWindows::WPFCppCliDemo::checkInPackage_5()
{
	std::cout << "****************************************************************************************************************************\n";
	std::cout << "REQUIREMENT 5:\n";
	std::cout << "****************************************************************************************************************************\n\n";
	std::cout << "Each time same file whose package is already there is checked in the version will be created according to time date stamp.\n\n";
}

void CppCliWindows::WPFCppCliDemo::openCloseProperty_6()
{
	std::cout << "****************************************************************************************************************************\n";
	std::cout << "REQUIREMENT 6:\n";
	std::cout << "****************************************************************************************************************************\n\n";
	std::cout << " The metadata in the package has checkInStatus tag which will contain boolean property open or close.\n";
	std::cout << " Working of this could be tested by uploading a file with open property and then again uploading a file with same name and \n different contain so the file in the repo would be overwritten in the previously created version.\n ";
	std::cout << "Formore information check the readMe! \n\n\n";
}

void CppCliWindows::WPFCppCliDemo::extraction_7()
{
	std::cout << "****************************************************************************************************************************\n";
	std::cout << "REQUIREMENT 7:\n";
	std::cout << "****************************************************************************************************************************\n\n";
	std::cout << "Package extraction is implemented in a way that the user will be able to extract files one by one form the latest package.\n";
	std::cout << "For this he will have to choose a package name and select the file type and then click extract button.\n";
	std::cout << "The chosen file will be downloaded to \"ClientDownload\" folder. \n\n\n";
}

void CppCliWindows::WPFCppCliDemo::messagePassing_8()
{
	std::cout << "****************************************************************************************************************************\n";
	std::cout << "REQUIREMENT 8:\n";
	std::cout << "****************************************************************************************************************************\n\n";
	std::cout << "Here we are doing message-passing between client and the server and hence the client is able to use functionalities of the \n repository.\n\n\n";
}
void CppCliWindows::WPFCppCliDemo::httpMessage_9()
{
	std::cout << "****************************************************************************************************************************\n";
	std::cout << "REQUIREMENT 9:\n";
	std::cout << "****************************************************************************************************************************\n\n";
	std::cout << "I have used Httpstyle messages to create request and responces which is displayed when message send/ receive is done \n under the home tab and response on the command prompt.\n\n\n";
}

void CppCliWindows::WPFCppCliDemo::streamBytes_10()
{
	std::cout << "****************************************************************************************************************************\n";
	std::cout << "REQUIREMENT 10:\n";
	std::cout << "****************************************************************************************************************************\n\n";
	std::cout << "I have implemented file checkIn and extract which uses byte streaming to transfer the files.\n\n\n";
}

void CppCliWindows::WPFCppCliDemo::automatedtestSuit()
{
	std::cout << "****************************************************************************************************************************\n";
	std::cout << "REQUIREMENT 11:\n";
	std::cout << "****************************************************************************************************************************\n\n";
	std::cout << "This along with the GUI is the automated test suit which will suffice the requirement 11.\n\n\n";
}


// This is a constructor which will set up everything for the GUI.
WPFCppCliDemo::WPFCppCliDemo(array<System::String^>^ args){
  if (!parseCommandLineArguments(args))
	return;
  // set up channel
  testExec();
  ObjectFactory* pObjFact = new ObjectFactory;
  pChann_ = pObjFact->createMockChannel(toStdString(clientAddress), stoi(toStdString(clientPort)));
  pChann_->start();
  delete pObjFact;
  // client's receive thread
  recvThread = gcnew Thread(gcnew ThreadStart(this, &WPFCppCliDemo::getMessage));
  recvThread->Start();
  // set event handlers
  this->Loaded += 
    gcnew System::Windows::RoutedEventHandler(this, &WPFCppCliDemo::OnLoaded);
  this->Closing += 
    gcnew CancelEventHandler(this, &WPFCppCliDemo::Unloading);
  hShutDownServer->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::shutDownServerMessage);
  hClearButton->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::shutDownClientSend);
  hFolderBrowseButton->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::browseForFolder);
  hFolderBrowseButton1->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::browseForFolderInRepo);
  hShowItemsButton->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::getItemsFromList);
  hShowItemsButton1->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::getDependencyFromList);
  hRadioOpen->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::radioOpen);
  hRadioClose->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::radioClose);
  hCheckinButton->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::checkin);
  hRepoBrowseButton->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::browseRepo);
  hWDepButton->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::extractWDep);
  hWODepButton->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::extractWODep);
  // set Window properties
  this->Title = "Project #4 Dependency-Based Remote Code Repository";
  this->Width = 800;
  this->Height = 600;
  // attach dock panel to Window
  this->Content = hDockPanel;
  hDockPanel->Children->Add(hStatusBar);
  hDockPanel->SetDock(hStatusBar, Dock::Bottom);
  hDockPanel->Children->Add(hGrid);
  hDockPanel->SetDock(hGrid, Dock::Left);
  // setup Window controls and views
  setUpTabControl();
  setUpStatusBar();
  setUpHomeView();
  setUpCheckinView();
  setUpExtractView();
}

// This is a distructor gor the WPF client.
WPFCppCliDemo::~WPFCppCliDemo(){
  delete pChann_;
}

// This sets up status bar.
void WPFCppCliDemo::setUpStatusBar(){
  hStatusBar->Items->Add(hStatusBarItem);
  hStatus->Text = "very important messages will appear here";
  hStatusBarItem->Content = hStatus;
  hStatusBar->Padding = Thickness(10, 2, 10, 2);
}

//This sets up tab control
void WPFCppCliDemo::setUpTabControl(){
  hGrid->Children->Add(hTabControl);
  hSendMessageTab->Header = "Home";
  hCheckinTab->Header = "Checkin";
  hExtractTab->Header = "Extract";
  hTabControl->Items->Add(hSendMessageTab);
  hTabControl->Items->Add(hCheckinTab);
  hTabControl->Items->Add(hExtractTab);
}

//this sets text block properties.
void WPFCppCliDemo::setTextBlockProperties(){
  RowDefinition^ hRow1Def = gcnew RowDefinition();
  hSendMessageGrid->RowDefinitions->Add(hRow1Def);
  Border^ hBorder1 = gcnew Border();
  hBorder1->BorderThickness = Thickness(1);
  hBorder1->BorderBrush = Brushes::Black;
  hBorder1->Child = hTextBlock1;
  hTextBlock1->Padding = Thickness(15);
  hTextBlock1->Text = "";
  hTextBlock1->FontFamily = gcnew Windows::Media::FontFamily("Tahoma");
  hTextBlock1->FontWeight = FontWeights::Bold;
  hTextBlock1->FontSize = 16;
  hScrollViewer1->VerticalScrollBarVisibility = ScrollBarVisibility::Auto;
  hScrollViewer1->Content = hBorder1;
  hSendMessageGrid->SetRow(hScrollViewer1, 1);
  hSendMessageGrid->Children->Add(hScrollViewer1);
}

// This sets up butoon properties
void WPFCppCliDemo::setButtonsProperties(){
  RowDefinition^ hRow2Def = gcnew RowDefinition();
  hRow2Def->Height = GridLength(75);
  hSendMessageGrid->RowDefinitions->Add(hRow2Def);
  hShutDownServer->Content = "Shutdown Server";
  Border^ hBorder2 = gcnew Border();
  hBorder2->Width = 150;
  hBorder2->Height = 60;
  hBorder2->BorderThickness = Thickness(2);
  hBorder2->BorderBrush = Brushes::Black;
  hClearButton->Content = "Shutdown Client";
  hBorder2->Child = hShutDownServer;
  Border^ hBorder3 = gcnew Border();
  hBorder3->Width = 150;
  hBorder3->Height = 60;
  hBorder3->BorderThickness = Thickness(2);
  hBorder3->BorderBrush = Brushes::Black;
  hBorder3->Child = hClearButton;
  hStackPanel1->Children->Add(hBorder2);
  TextBlock^ hSpacer = gcnew TextBlock();
  hSpacer->Width = 10;
  hStackPanel1->Children->Add(hSpacer);
  hStackPanel1->Children->Add(hBorder3);
  hStackPanel1->Orientation = Orientation::Horizontal;
  hStackPanel1->HorizontalAlignment = System::Windows::HorizontalAlignment::Center;
  hSendMessageGrid->SetRow(hStackPanel1, 2);
  hSendMessageGrid->Children->Add(hStackPanel1);
}

// This sets up send message view
void WPFCppCliDemo::setUpHomeView(){
  Console::Write("\n  setting up sendMessage view");
  hSendMessageGrid->Margin = Thickness(20);
  hSendMessageTab->Content = hSendMessageGrid;
  hLabel1->Content = "HttpMessages are displayed here: ";
  hLabel1->FontSize = 20;
  hLabel1->Height = 60;
  hLabel1->Width = 350;
  RowDefinition^ rw = gcnew RowDefinition();
  hSendMessageGrid->RowDefinitions->Add(rw);
  hSendMessageGrid->SetRow(hLabel1,0);
  hSendMessageGrid->Children->Add(hLabel1);
  setTextBlockProperties();
  setButtonsProperties();
}

//This converts manged string to standard string.
std::string WPFCppCliDemo::toStdString(String^ pStr){
  std::string dst;
  for (int i = 0; i < pStr->Length; ++i)
    dst += (char)pStr[i];
  return dst;
}


//This is the button event for shutting down the server.
void WPFCppCliDemo::shutDownServerMessage(Object^ obj, RoutedEventArgs^ args){
  //STOP / SHUTDOWN SERVER
  HttpMessage shutdownServer;
  shutdownServer.command = SHUTDOWN_SERVER;
  shutdownServer.senderPort = stoi(toStdString(clientPort));
  shutdownServer.sourceAddress = toStdString(clientAddress);
  shutdownServer.destAdd = toStdString(serverAddress);
  shutdownServer.destPort =stoi(toStdString(serverPort));
  std::string pr = httpStyleMessage(shutdownServer);
  std::vector<std::string> a = getAttributes(shutdownServer,pr);
  std::map<std::string, std::string>mp = getMap(shutdownServer, a);
  String ^ print = printHelper(mp);
  hTextBlock1->Text += "\n SHUTDOWN SERVER MESSAGE:\n";
  hTextBlock1->Text += print;
  pChann_->postMessage(shutdownServer);
  Console::Write("\n  Server is shut down!");
  hStatus->Text = "SERVER SHUTDOWN!";
}

// This will convert std::string to String^
String^ WPFCppCliDemo::toSystemString(std::string& str){
  StringBuilder^ pStr = gcnew StringBuilder();
  for (size_t i = 0; i < str.size(); ++i)
    pStr->Append((Char)str[i]);
  return pStr->ToString();
}

// This will add text to the textBlock.
void WPFCppCliDemo::addText(String^ msg){
  hTextBlock1->Text += msg + "\n\n";
}

// This function will convert httpStyle message object to string
std::string CppCliWindows::WPFCppCliDemo::httpStyleMessage(HttpMessage msg){
	std::string stringHttp;
	stringHttp = msg.createHeaderMessage(msg);
	return stringHttp;
}

//This function will split thre messahe by its attributes.
std::vector<std::string> CppCliWindows::WPFCppCliDemo::getAttributes(HttpMessage msg, std::string temp){
	return msg.split(temp, ETX);
}

//This function returns map of all the attributes in the HttpMessage
std::map<std::string, std::string> CppCliWindows::WPFCppCliDemo::getMap(HttpMessage msg, std::vector<std::string> attributes)
{
	return msg.createMap(attributes);
}

//This function will help in printing the httpStyle message on the GUI
String ^ CppCliWindows::WPFCppCliDemo::printHelper(std::map<std::string, std::string> map){
	String^ print;
	for (auto keyvaluePair : map) {
		std::string printString;
		printString.append("     " + keyvaluePair.first + " : " + keyvaluePair.second);
		printString.append("\n");
		print += toSystemString(printString);
	}
	return print;
}

// This will get messages from the channel and redirect it to specified functions
void WPFCppCliDemo::getMessage(){
  // recvThread runs this function
  while (true){
	  HttpMessage msg = pChann_->getMessage();
	  String^ sMsg = toSystemString(msg.createHeaderMessage(msg));
	  if (msg.command == GETPACKAGES_RESPONSE && msg.body.size() > 0){
		  std::cout << "\n\n PACKAGE RESPONSE MESSAGE: \n";
		  std::cout << "\n-------------------------------\n";
		  std::cout << toStdString(printHelper(getMap(msg, getAttributes(msg, httpStyleMessage(msg)))));
		  std::cout << "\n-------------------------------\n";
		  array<String^>^ args = getPackageNames(msg);
		  array<Object^>^ parms = gcnew array<Object^> { args };
		  Action<array<String^>^>^ act = gcnew Action<array<String^>^>(this, &WPFCppCliDemo::updateListBox1);
		  Dispatcher->Invoke(act, parms);
	  }
	  else if (msg.command == DOWNLOAD_ACK){
		  std::cout << "\n\n DOWNLOAD ACKNOWLEDGE\n";
		  std::cout << "\n-------------------------------\n";
		  std::cout << toStdString(printHelper(getMap(msg, getAttributes(msg, httpStyleMessage(msg)))));
		  std::cout << "\n-------------------------------\n";
		  std::cout << "\n--- FILE DOWNLOADED: ";
		  std::cout << msg.fileName << std::endl;
		  sMsg = "Download was sucessful!";
		  Action<String^>^ act = gcnew Action<String^>(this, &WPFCppCliDemo::updateStatusBox);
		  Dispatcher->Invoke(act, sMsg);
	  }
	  else if (msg.command == UPLOAD_ACK){
		  std::cout<<"\n\n UPLOAD ACKNOWLEDGE\n";
		  std::cout << "\n-------------------------------\n";
		  std::cout<<toStdString(printHelper(getMap(msg, getAttributes(msg, httpStyleMessage(msg)))));
		  std::cout << "\n-------------------------------\n";
		  std::cout << "\n--- FILE UPLOADED: ";
		  std::cout << msg.fileName << std::endl;
		  sMsg = "Upload was sucessful!";
		  Action<String^>^ act = gcnew Action<String^>(this, &WPFCppCliDemo::updateStatusBox);
		  Dispatcher->Invoke(act, sMsg);
	  }
  }
}
// Update status message in application. 
void WPFCppCliDemo::updateStatusBox(String^ msg){
	hStatus->Text = msg;
}

// This will update the list box 
void WPFCppCliDemo::updateListBox1(array<String^>^ args){
	for each(String^ arg in args){
		hListBox1->Items->Add(arg);
		hListBox3->Items->Add(arg);
	}
	hStatus->Text = "File list updated.";
}

//This will extract package names from the incoming messages.
array<String^>^ CppCliWindows::WPFCppCliDemo::getPackageNames(HttpMessage & msg){
	String^ sMsg = toSystemString(msg.body);
	std::vector<std::string> packageList = msg.extractPackageName_Responce(toStdString(sMsg));
	array<String^>^ args = gcnew array<String^>(packageList.size());
	for (size_t i = 0; i < packageList.size(); i++){
		args[i] =  toSystemString(packageList[i]);
	}
	return args;
}

// This will shut down the client sender 
void WPFCppCliDemo::shutDownClientSend(Object^ sender, RoutedEventArgs^ args){
	HttpMessage shutDownClient;
	shutDownClient.command = "end of send queue";
	shutDownClient.destAdd = toStdString(serverAddress);
	shutDownClient.destPort = stoi(toStdString(serverPort));
	hTextBlock1->Text += "\n SHUTDOWN CLIENT SEND\n";
	hTextBlock1->Text += printHelper(getMap(shutDownClient, getAttributes(shutDownClient, httpStyleMessage(shutDownClient))));
	pChann_->postMessage(shutDownClient);
	Console::Write("\n  Clent Shut Down");
	hStatus->Text = "Client is safe to shutdown!";
}

//This will set up stack panel 2.
void CppCliWindows::WPFCppCliDemo::setUpStackPanel2(){
	TextBlock^ hSpacer1 = gcnew TextBlock();
	hSpacer1->Width = 10;
	TextBlock^ hSpacer2 = gcnew TextBlock();
	hSpacer2->Width = 10;
	TextBlock^ hSpacer3 = gcnew TextBlock();
	hSpacer3->Width = 10;
	TextBlock^ hSpacer4 = gcnew TextBlock();
	hSpacer4->Width = 10;
	hStackPanel2->Children->Add(hRadioOpen);
	hStackPanel2->Children->Add(hSpacer1);
	hStackPanel2->Children->Add(hLabelOpen);
	hStackPanel2->Children->Add(hSpacer2);
	hStackPanel2->Children->Add(hSpacer3);
	hStackPanel2->Children->Add(hRadioClose);
	hStackPanel2->Children->Add(hSpacer4);
	hStackPanel2->Children->Add(hLabelClose);
	hStackPanel2->Orientation = Orientation::Horizontal;
	hStackPanel2->HorizontalAlignment = System::Windows::HorizontalAlignment::Left;
	hCheckinGrid->SetRow(hStackPanel2, 3);
	hCheckinGrid->SetColumn(hStackPanel2, 0);
	hCheckinGrid->Children->Add(hStackPanel2);
}

// This will set up check in helper tab
void CppCliWindows::WPFCppCliDemo::setUpCheckInHelper(){
	Console::Write("\n  setting up FileList view");
	hCheckinGrid->Margin = Thickness(20);
	hCheckinTab->Content = hCheckinGrid;
	ColumnDefinition^ hRow1Def = gcnew ColumnDefinition();
	hCheckinGrid->ColumnDefinitions->Add(hRow1Def);
	Border^ hBorder1 = gcnew Border();
	hBorder1->BorderThickness = Thickness(1);
	hBorder1->BorderBrush = Brushes::Black;
	hListBox->SelectionMode = SelectionMode::Multiple;
	hBorder1->Child = hListBox;
	hCheckinGrid->SetRow(hBorder1, 1);
	hCheckinGrid->SetColumn(hBorder1, 0);
	hCheckinGrid->Children->Add(hBorder1);
	ColumnDefinition^ hRow11Def = gcnew ColumnDefinition();
	hCheckinGrid->ColumnDefinitions->Add(hRow11Def);
	Border^ hBorder11 = gcnew Border();
	hBorder11->BorderThickness = Thickness(1);
	hBorder11->BorderBrush = Brushes::Black;
	hListBox1->SelectionMode = SelectionMode::Multiple;
	hBorder11->Child = hListBox1;
	hCheckinGrid->SetRow(hBorder11, 1);
	hCheckinGrid->SetColumn(hBorder11, 1);
	hCheckinGrid->Children->Add(hBorder11);
	RowDefinition^ hRow2Def = gcnew RowDefinition();
	RowDefinition^ hRow2Def2 = gcnew RowDefinition();
	hCheckinGrid->RowDefinitions->Add(hRow2Def);
	hFolderBrowseButton->Content = "Select Package for checkin";
	hFolderBrowseButton->Height = 30;
	hFolderBrowseButton->Width = 150;
	hFolderBrowseButton->BorderThickness = Thickness(2);
	hFolderBrowseButton->BorderBrush = Brushes::Black;
	hCheckinGrid->SetRow(hFolderBrowseButton, 0);
	hCheckinGrid->SetColumn(hFolderBrowseButton, 0);
	hCheckinGrid->Children->Add(hFolderBrowseButton);
	hCheckinGrid->RowDefinitions->Add(hRow2Def2);
}

//This will set up check in butoons.
void CppCliWindows::WPFCppCliDemo::setUpCheckInHelperButtons(){
	hShowItemsButton->Content = "Show Selected Items";
	hShowItemsButton->Height = 30;
	hShowItemsButton->Width = 120;
	hShowItemsButton->BorderThickness = Thickness(2);
	hShowItemsButton->BorderBrush = Brushes::Black;
	hCheckinGrid->SetRow(hShowItemsButton, 2);
	hCheckinGrid->SetColumn(hShowItemsButton1, 0);
	hCheckinGrid->Children->Add(hShowItemsButton);
	hFolderBrowseButton1->Content = "Show Repository Content";
	hFolderBrowseButton1->Height = 30;
	hFolderBrowseButton1->Width = 150;
	hFolderBrowseButton1->BorderThickness = Thickness(2);
	hFolderBrowseButton1->BorderBrush = Brushes::Black;
	hCheckinGrid->SetRow(hFolderBrowseButton1, 0);
	hCheckinGrid->SetColumn(hFolderBrowseButton1, 1);
	hCheckinGrid->Children->Add(hFolderBrowseButton1);
}

//This will help in setting up stack panel 3.
void CppCliWindows::WPFCppCliDemo::setUpCheckInHelperStackPanel3(){
	hStackPanel3->Children->Add(hCheckinButton);
	hStackPanel2->Orientation = Orientation::Horizontal;
	hStackPanel2->HorizontalAlignment = System::Windows::HorizontalAlignment::Right;
	hCheckinGrid->SetRow(hStackPanel3, 3);
	hCheckinGrid->SetColumn(hStackPanel3, 1);
	hCheckinGrid->Children->Add(hStackPanel3);
	hFolderBrowserDialog->ShowNewFolderButton = false;
	hFolderBrowserDialog->SelectedPath = System::IO::Directory::GetCurrentDirectory();
	hFolderBrowserDialog1->ShowNewFolderButton = false;
	hFolderBrowserDialog1->SelectedPath = System::IO::Directory::GetCurrentDirectory();
}

//This will set up check in view.
void WPFCppCliDemo::setUpCheckinView(){
  setUpCheckInHelper();
  // Show selected items button.
  setUpCheckInHelperButtons();
  // Show selected items button.
  hShowItemsButton1->Content = "Show set Dependency";
  hShowItemsButton1->Height = 30;
  hShowItemsButton1->Width = 135;
  hShowItemsButton1->BorderThickness = Thickness(2);
  hShowItemsButton1->BorderBrush = Brushes::Black;
  hCheckinGrid->SetRow(hShowItemsButton1, 2);
  hCheckinGrid->SetColumn(hShowItemsButton1, 1);
  hCheckinGrid->Children->Add(hShowItemsButton1);
  // Radio button for open
  RowDefinition^ hRow4Def = gcnew RowDefinition();
  RowDefinition^ hRow4Def2 = gcnew RowDefinition();
  hRow4Def2->Height = GridLength(39);
  hCheckinGrid->RowDefinitions->Add(hRow4Def);
  hCheckinGrid->RowDefinitions->Add(hRow4Def2);
  hRadioOpen->Height = 50;
  hRadioOpen->Width = 30;
  hRadioOpen->BorderThickness = Thickness(2);
  hRadioOpen->BorderBrush = Brushes::Black;
  // Radio button for close
  hRadioClose->Height = 50;
  hRadioClose->Width = 30;
  hRadioClose->BorderThickness = Thickness(2);
  hRadioClose->BorderBrush = Brushes::Black;
  //Labels for radio open and close
  hLabelOpen->Content =  "Open";
  hLabelOpen->Height = 60;
  hLabelOpen->Width =100;
  hLabelClose->Content = "Close";
  hLabelClose->Height = 60;
  hLabelClose->Width = 100;
  //Checkin button
  hCheckinButton->Content = "Checkin";
  hCheckinButton->Height = 40;
  hCheckinButton->Width = 135;
  hCheckinButton->BorderThickness = Thickness(2);
  hCheckinButton->BorderBrush = Brushes::Black;
  //Stack panel for radio buttons
  setUpStackPanel2();
  //Stack panel 3 for chekin button
  setUpCheckInHelperStackPanel3();
}

//This will get items from the list.
void WPFCppCliDemo::getItemsFromList(Object^ sender, RoutedEventArgs^ args){
	int index = 0;
	int count = 0;
	count = hListBox->SelectedItems->Count;
	hStatus->Text = "Show Selected Items";
	array<System::String^>^ items = gcnew array<String^>(count);
	if (count > 0) {
		for each (String^ item in hListBox->SelectedItems){
			items[index++] = item;
		}
	}
	hListBox->Items->Clear();
	if (count > 0) {
		for each (String^ item in items){
			hListBox->Items->Add(item);
		}
	}
	else{ 
		hStatus->Text = "Select atleast one Item"; 
	}
}

// This will get dependency list.
void WPFCppCliDemo::getDependencyFromList(Object^ sender, RoutedEventArgs^ args)
{
	int index = 0;
	int count = 0;
	count = hListBox1->SelectedItems->Count;
	hStatus->Text = "Show Dependency";
	array<System::String^>^ items = gcnew array<String^>(count);
	if (count > 0) {
		for each (String^ item in hListBox1->SelectedItems){
			items[index++] = item;
		}
	}

	hListBox1->Items->Clear();
	if (count > 0) {
		for each (String^ item in items){
			hListBox1->Items->Add(item);
		}
	}
	else{ 
		hStatus->Text = "Select at least one Dependency"; 
	}
}

//This will browse the folder.
void WPFCppCliDemo::browseForFolder(Object^ sender, RoutedEventArgs^ args){
  std::cout << "\n  Browsing for folder";
  hStatus->Text = "Browsing for folder";
  hListBox->Items->Clear();
  System::Windows::Forms::DialogResult result;
  result = hFolderBrowserDialog->ShowDialog();
  if (result == System::Windows::Forms::DialogResult::OK){
    String^ path = hFolderBrowserDialog->SelectedPath;
    std::cout << "\n  opening folder \"" << toStdString(path) << "\"";
    array<String^>^ files = System::IO::Directory::GetFiles(path, L"*.*");
    for (int i = 0; i < files->Length; ++i)
      hListBox->Items->Add(files[i]);
    array<String^>^ dirs = System::IO::Directory::GetDirectories(path);
    for (int i = 0; i < dirs->Length; ++i)
      hListBox->Items->Add(L"<> " + dirs[i]);
  }
}

// This will help in browsing all the files from the repo
void WPFCppCliDemo::browseForFolderInRepo(Object^ sender, RoutedEventArgs^ args){
	std::cout << "\n  Browsing for folder In Repository";
	hStatus->Text = "Browsing for folder In Repository";
	hListBox1->Items->Clear();
	HttpMessage pr;
	pr.command = REPOSITORYCHECK;
	pr.senderPort = stoi(toStdString(clientPort));
	pr.sourceAddress = toStdString(clientAddress);
	pr.destAdd = toStdString(serverAddress);
	pr.destPort = stoi(toStdString(serverPort));
	hTextBlock1->Text += "\n REPOSITORY PACKAGE REQUEST\n";
	hTextBlock1->Text += printHelper(getMap(pr, getAttributes(pr, httpStyleMessage(pr))));
	pChann_->postMessage(pr);
}

// This will display status of open radio button on the status bar.
void WPFCppCliDemo::radioOpen(Object^ sender, RoutedEventArgs^ args){
	std::cout << "\nOpen radio button clicked";
	hStatus->Text = "Open Radio Button clicked";

}

// This will display status of close radio button on the status bar.
void WPFCppCliDemo::radioClose(Object^ sender, RoutedEventArgs^ args){
	std::cout << "\nClose radio button clicked";
	hStatus->Text = "Close Radio Button Clicked";
}

// This function will help in reading the status of the radio buttons.
std::string WPFCppCliDemo::statusCheck(){
	std::string status;
	if (hRadioClose->IsChecked)
		status = CLOSED;
	else
		status = OPEN;
	return status;
}

//This will handel all the things when check in button is clicked
void WPFCppCliDemo::checkin(Object^ sender, RoutedEventArgs^ args){
	int pindex = 0;			int pcount = 0;
	int dindex = 0;			int dcount = 0;
	pcount = hListBox->SelectedItems->Count;
	array<System::String^>^ packageitems = gcnew array<String^>(pcount);
	if (pcount > 0) {
		for each (String^ item in hListBox->SelectedItems){
			std::cout << std::endl << toStdString(item);
			packageitems[pindex++] = item;
			
		}
	}
	dcount = hListBox1->SelectedItems->Count;
	array<System::String^>^ depeitems = gcnew array<String^>(dcount);
	if (dcount > 0) {
		for each (String^ item in hListBox1->SelectedItems){
			depeitems[dindex++] = item;
		}
	}
	std::cout << "\nCheckin button clicked";
	if ((hRadioClose->IsChecked || hRadioOpen->IsChecked) && pcount > 0){
		hStatus->Text = "Checkin Button Clicked";
		for (int j = 0; j < pcount; j++){
			HttpMessage chk;
			chk.command = CHECK_IN;
			chk.fileName = toStdString(packageitems[j]);
			chk.destAdd = toStdString(serverAddress);
			chk.destPort = stoi(toStdString(serverPort));
			chk.senderPort = stoi(toStdString(clientPort));
			chk.sourceAddress = toStdString(clientAddress);
			chk.status = statusCheck();
			if (dcount > 0){
				for (int k = 0; k < dcount; k++){
					chk.dependancies.push_back(toStdString(depeitems[k]));
				}
			}
			hTextBlock1->Text += "\n CHECK IN REQUEST\n";
			hTextBlock1->Text += printHelper(getMap(chk, getAttributes(chk, httpStyleMessage(chk))));
			pChann_->postMessage(chk);
		}
	}
	else if(!hRadioClose->IsChecked && !hRadioOpen->IsChecked)
		hStatus->Text = "Please select the status: Open / Close";
	else
		hStatus->Text = "Select atleast one item to Checkin";
}

// THis will set up the extract buttons.
void WPFCppCliDemo::setUpExtractButtons(){
	RowDefinition^ hRowDef44 = gcnew RowDefinition();
	hExtractGrid->RowDefinitions->Add(hRowDef44);
	hWODepButton->Content = "Extract Without Dependency";
	hWODepButton->Height = 30;
	hWODepButton->Width = 170;
	hWODepButton->BorderThickness = Thickness(2);
	hWODepButton->BorderBrush = Brushes::Black;

	hWDepButton->Content = "Extract With Dependency";
	hWDepButton->Height = 30;
	hWDepButton->Width = 170;
	hWDepButton->BorderThickness = Thickness(2);
	hWDepButton->BorderBrush = Brushes::Black;
}

//This will set up the stack panel 4.
void CppCliWindows::WPFCppCliDemo::setUpStackPanel4(){
	hStackPanel4->Children->Add(hWODepButton);
	TextBlock^ hSpacer = gcnew TextBlock();
	hSpacer->Width = 10;
	hStackPanel4->Children->Add(hSpacer);
	hStackPanel4->Children->Add(hWDepButton);
	hStackPanel4->Orientation = Orientation::Horizontal;
	hStackPanel4->HorizontalAlignment = System::Windows::HorizontalAlignment::Center;
	hExtractGrid->SetRow(hStackPanel4, 3);
	hExtractGrid->Children->Add(hStackPanel4);
}

// This will set up the extract view.
void WPFCppCliDemo::setUpExtractView(){
  Console::Write("\n  setting up Extract view");
  hExtractGrid->Margin = Thickness(20);
  hExtractTab->Content = hExtractGrid;
  RowDefinition^ hRowDef4 = gcnew RowDefinition();
  hExtractGrid->RowDefinitions->Add(hRowDef4);
  hRepoBrowseButton->Content = "Browse Repository";
  hRepoBrowseButton->Height = 30;
  hRepoBrowseButton->Width = 150;
  hRepoBrowseButton->BorderThickness = Thickness(2);
  hRepoBrowseButton->BorderBrush = Brushes::Black;
  hExtractGrid->SetRow(hRepoBrowseButton, 0);
  hExtractGrid->Children->Add(hRepoBrowseButton);
  RowDefinition^ hRowDef = gcnew RowDefinition();
  hExtractGrid->RowDefinitions->Add(hRowDef);
  Border^ hBorder1 = gcnew Border();
  hBorder1->BorderThickness = Thickness(1);
  hBorder1->BorderBrush = Brushes::Black;
  hListBox3->SelectionMode = SelectionMode::Single;
  hBorder1->Child = hListBox3;
  hExtractGrid->SetRow(hBorder1, 1);
  hExtractGrid->Children->Add(hBorder1);
  // Extarct with and without dependency button.
  setUpExtractButtons();
  //Stack panel 4
  setUpStackPanel4();
  //list box 4 for .h and .cpp selection
  RowDefinition^ hRowDef444 = gcnew RowDefinition();
  hExtractGrid->RowDefinitions->Add(hRowDef444);
  hLabelhcpp->Height = 50;
  hLabelhcpp->Width = 150;
  hLabelhcpp->Content = "Select .h or .cpp or .xml: ";
  TextBlock^ hSpacer1 = gcnew TextBlock();
  hSpacer1->Width = 10;
  hListBox4->SelectionMode = SelectionMode::Single;
  hListBox4->Items->Add(".h");
  hListBox4->Items->Add(".cpp");
  hListBox4->Items->Add(".xml");
  hListBox4->Height = 75;
  hListBox4->Width = 100;
  //Stack panel 5
  hStackPanel5->Children->Add(hLabelhcpp);
  hStackPanel5->Children->Add(hSpacer1);
  hStackPanel5->Children->Add(hListBox4);
  hStackPanel5->Orientation = Orientation::Horizontal;
  hStackPanel5->HorizontalAlignment = System::Windows::HorizontalAlignment::Center;
  hExtractGrid->SetRow(hStackPanel5, 2);
  hExtractGrid->Children->Add(hStackPanel5);
}

//This will create the message for repository check, on clicking the browse button for the repo
void WPFCppCliDemo::browseRepo(Object^ sender, RoutedEventArgs^ args){
	std::cout << "\n  Browsing Repository";
	hStatus->Text = "Browsing Repository";
	hListBox3->Items->Clear();
	HttpMessage pr;
	pr.command = REPOSITORYCHECK;
	pr.senderPort = stoi(toStdString(clientPort));
	pr.sourceAddress = toStdString(clientAddress);
	//
	pr.destAdd = toStdString(serverAddress);
	pr.destPort = stoi(toStdString(serverPort));
	hTextBlock1->Text += "\n REPOSITORY PACKAGE REQUEST\n";
	hTextBlock1->Text += printHelper(getMap(pr, getAttributes(pr, httpStyleMessage(pr))));
	pChann_->postMessage(pr);
}

//This will do button properties for the extract with dependencies
void WPFCppCliDemo::extractWDep(Object^ sender, RoutedEventArgs^ args) {
	std::cout << "\n--- Extract With Dependency clicked";
	std::cout << "\n--- But this functionalities is not yet implemented!";
	int count = 0;
	count = hListBox3->SelectedItems->Count;
	if(count > 0)
		hStatus->Text = "This functionality is not implemented yet!";
	else
		hStatus->Text = "This functionality is not implemented yet!";
}

// This will create a message to extract without dependency when certain set of conditions are met
void WPFCppCliDemo::extractWODep(Object^ sender, RoutedEventArgs^ args) {
	std::cout << "\n Extract Without Dependency clicked";
	int count = 0;
	std::string extension;
	count = hListBox3->SelectedItems->Count;
	int count1 = 0;
	count1 = hListBox4->SelectedItems->Count;
	if (count > 0 && count1>0){
		extension = toStdString(hListBox4->SelectedItem->ToString());
		std::string selectedPackage = toStdString(hListBox3->SelectedItem->ToString());
		std::string fileName = selectedPackage.append(extension);
		hStatus->Text = "Extract Without Dependency";
		HttpMessage dl;
		dl.command = EXTRACT_WO_DEP;
		dl.senderPort = stoi(toStdString(clientPort));
		dl.sourceAddress = toStdString(clientAddress);
		dl.destAdd = toStdString(serverAddress);
		dl.destPort = stoi(toStdString(serverPort));
		dl.fileName = fileName;
		hTextBlock1->Text += "\n EXTRACT WITHOUT DEPENDECY\n";
		hTextBlock1->Text += printHelper(getMap(dl, getAttributes(dl, httpStyleMessage(dl))));
		pChann_->postMessage(dl);
	}
	else
		hStatus->Text = "Select atleast one item from both list boxes!`";
}

// This will display message on console when window is loaded.
void WPFCppCliDemo::OnLoaded(Object^ sender, RoutedEventArgs^ args){
  Console::Write("\n  Window loaded");
}

// This will display a message on window when the GUI is closed.
void WPFCppCliDemo::Unloading(Object^ sender, System::ComponentModel::CancelEventArgs^ args){
  Console::Write("\n  Window closing");
}

// This function will parse the command line arguments and will set client and server ports
bool CppCliWindows::WPFCppCliDemo::parseCommandLineArguments(array<System::String^>^ args)
{
	if(args->Length== 2)
	{
		clientArgument = args[0];
		client= clientArgument->Split(':');
		serverArgument = args[1];
		server = serverArgument->Split(':');
		if(client->Length == 2){ 
			clientAddress = client[0];
			clientPort = client[1];
		}
		if (server->Length == 2){
			serverAddress = server[0];
			serverPort = server[1];
		}
		if (clientAddress == "" || clientPort == "" || serverAddress == "" || serverPort == ""){
			std::cout << "\nOne of the address or port is not set\n";
			return false;
		}
		return true;
	}
	else{
		std::cout << "\nNo Command line Argument OR";
		std::cout << "\nWrong format of arguments please check and try again!";
		return false;
	}
}

[STAThread]
//int _stdcall WinMain()
int main(array<System::String^>^ args)
{
  Console::WriteLine(L"\n Starting WPFCppCliDemo");
  Application^ app = gcnew Application();
  app->Run(gcnew WPFCppCliDemo(args));
  Console::WriteLine(L"\n\n");
}