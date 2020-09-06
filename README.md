# Programmer-GBM-POM (MAC OS-X)
Program to initialise the Gleis Besetz Meldung (GBM)

This program allows the initialisation (by reading and modifying CV variables) of the [occupancy detection (feedback) / Gleis Besetz Meldung decoder](https://github.com/aikopras/OPENDECODER22GBM). This decoder sends feedback messages via the RS-Bus and can, for initialisation purposes but also to switch relays, listen to DCC commands. Given that it uses RS-Bus messages for feedback, the decoders will primarily be interesting in environments with LENZ Master stations (like the LZV 100) connected via the LAN/USB interface (23151).<BR>
The program is written for MAC OSX; the executable can be [dowloaded directly](/Program/Programmer%20GBM-POM.app.zip) or can be compiled from scratch using Xcode.<BR>
 
## Main screen ## 
After startup the program shows its main screen. After entering the current RS-Bus address of the decoder all CV values are being downloaded from the decoder. Screenshots for the other tabs can be seen [here](/Screenshots/).
![Main](/Screenshots/Main.png)


## How does the program work? ##
To initialise and modify the decoder's Configuration Variables (CVs) the program sends Programming on the Main (PoM) messages. Since the XPressNet specification  supports PoM messages only for train decoders (but not for accessory / feedback decoders), the "trick" the GBM decoder uses is to listen to the loco address equal to the <I>RS-Bus address + 6000</I>.<BR>
The requested CV values are send back via the RS-Bus.

The program communicates with the LENZ Master station via the LAN/USB interface (23151). If different master stations are used for DCC commands and RS-Bus feedback messages, two LAN/USB interfaces may be used. The IP address(es) of the LAN interfaces can be entered via the program preferences.
![Main](/Screenshots/Preferences.png)
