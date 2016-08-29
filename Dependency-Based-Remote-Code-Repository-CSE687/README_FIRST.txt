---------------------<README>---------------------
1) PART1 : Commandline arguments.
- To run this project provide command arguments as below:

start .\Debug\CppCli-WPF-App.exe "localhost:9086" "localhost:9095"
start .\Debug\Server.exe "localhost:9095"

In this for CppCli-WPF-App.exe first arguument will contain client address and second argument will contain server address.
For Server.exe the one and only argument should contain server address.
- Please note that the address follows PortAddress:PortNumber format.

2) PART2: Use Gui:

- GUI has main three tabs: Home,CheckIn and Extract. 

1)CheckIn:
 - Using this tab you will be able to checkIn files one or more than one simultaneously.
 - It is expected that a user will check in only .h and .cpp files.
 - User is allowed to check in muliple packages at a time but all the files should be in one folder from which it is being selected.
 - Please allow atleast 2 to 3 seconds before checking in again, doing multiple checkins before acknowledement from server could abort the application

 Check if Open and close are working properly:
  1) To do this first checkin a file with "open" radio button clicked.
  2) open the repository folder it will show the package name identical to filename.
  3) opening the package folder will show the latest uploaded folder with timedate.
  4)you can open and look at the xml for the checkInStatus Tag.
  5) Now checkin the file again with open or closed status as desired and the updated file will be overwritten in the version you just checked.
  6) this could be verified by repeating steps 2 and 3 again and it will prove that new version with ne time date is not created and previous version is
	 overwritten.
	 
  7) checking close property is simple ,just upload a file with close propert and then again upload file with close property, this should create two version datetimes.
 
 Selecting packages for dependency:
	-"Show repository Content" will display all the packages available in the Repository.
	- User can select multiple packages on which current package to be checked in depends and this will be recorderd in the .xml file at the server.
 
 CAUTION: "Show selected Items" and "Show set Dependency buttons" will show the selected items from both the select boxes, but user must click them again	
			before checking them in.

2)Extract:
	- Extract is simple, to see available packages in the repository press "Browse Repository".
	- Select package from which file to be downloaded.
	- Select extension for the file to be downloaded.
	- press "Extract Without Dependency".
	- A whole package consist of .h,.cpp and .xml.
	- and It could be downloaded by selecting proper packagename and extension.
	- This file will be downloaded to clientDownload directory.
  NOTE1: "Extract with dependency" is not implemented yet.
  NOTE2:To extract files on which current file depends on user is free to download .xml and look at dependency and is free to download all the packages it depends on.
  NOTE3: Extract will get the user the last checked in or the latest package, it is assumed that the latest package is what is relevent with the on going project.
 
3)Home:
  -This tab will display HttpMessages sent from the client, this is to prove that Http Message passing is used. Received messages are printed on console to 
   print them properly(no thread bad prints.)
   
   Two buttons on this tab are very important. 
   - When a user want to turn the application off, he/she must use following order:
	1)Press "Shutdown Server" first to turn off the server , this will stop sender thread of the server and it will close sucessfully.
	2)Press "Shutdown Client" to shut down client send thread.
	Warning: do not press any other button than Shutdown client after pressing shutdown server(1) as it wont be able to connect to server.
	3)After this user is safe to close all the opened windows.
   
Thank you for your patience and time.
Please feel free to contact for any issues.

Achal Velani
email: avelani@syr.edu
phone : 315 516 9163
---------------------<END>---------------------