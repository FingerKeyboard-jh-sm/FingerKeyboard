#!/usr/bin/python2.7
#
# PiTooth allows the Raspberry Pi to act as a Bluetooth keyboard, and relays
# keypresses from a USB keyboard to a Bluetooth client. Written by Liam Fraser
# for a Linux User & Developer tutorial.
#

import pdb
import os # Used to call external commands
import sys # Used to exit the script
import bluetooth
from bluetooth import *
import dbus # Used to set up the SDP record
import time # Used for pausing the process

class Bluetooth:
    HOST = 0 # BT Mac address
    PORT = 1 # Bluetooth Port Number

    # Define the ports we'll use
    P_CTRL = 17
    P_INTR = 19

    def __init__(self):
        # Set the device class to a keyboard and set the name
        os.system("hciconfig hci0 class 0x002540")
        os.system("hciconfig hci0 name Raspberry")
        # Make device discoverable
        os.system("hciconfig hci0 piscan")

        # Define our two server sockets for communication
        self.scontrol = BluetoothSocket(L2CAP)
        self.sinterrupt = BluetoothSocket(L2CAP)

        # Bind these sockets to a port
        self.scontrol.bind(("", Bluetooth.P_CTRL))
        self.sinterrupt.bind(("", Bluetooth.P_INTR))
        
        # Set up dbus for advertising the service record
        self.bus = dbus.SystemBus()
        try:
            self.manager = dbus.Interface(self.bus.get_object("org.bluez", "/"),
                                                              "org.bluez.Manager")
            adapter_path = self.manager.DefaultAdapter()
            self.service = dbus.Interface(self.bus.get_object("org.bluez", adapter_path),
                                                              "org.bluez.Service")
        except:
            sys.exit("Could not configure bluetooth. Is bluetoothd started?")

        # Read the service record from file
        try:
            fh = open(sys.path[0] + "/sdp_record.xml", "r")
        except:
            sys.exit("Could not open the sdp record. Exiting...")            
        self.service_record = fh.read()
        fh.close()

    def listen(self):
        # Advertise our service record
        self.service_handle = self.service.AddRecord(self.service_record)
        print "Service record added"

        # Start listening on the server sockets
        self.scontrol.listen(1) # Limit of 1 connection
        self.sinterrupt.listen(1)
        print "Waiting for a connection"
        self.ccontrol, self.cinfo = self.scontrol.accept()
        print "Got a connection on the control channel from " + self.cinfo[Bluetooth.HOST]
        self.cinterrupt, self.cinfo = self.sinterrupt.accept()
        print "Got a connection on the interrupt channel from " + self.cinfo[Bluetooth.HOST]

    def send_input(self,str):
       
	

		
        
	if(str=='a\n'):
		
	        self.cinterrupt.send('\xa1\x01\x00\x00\x04\x00\x00\x00\x00\x00')
		self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
	elif(str=='b\n'):
		self.cinterrupt.send('\xa1\x01\x00\x00\x05\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='c\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x06\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='d\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x07\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='e\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x08\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='f\n'):                                        
                self.cinterrupt.send('\xa1\x01\x00\x00\x09\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='g\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x0a\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='h\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x0b\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='i\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x0c\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='j\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x0d\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='k\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x0e\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='l\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x0f\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='m\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x10\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='n\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x11\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='o\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x12\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='p\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x13\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='q\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x14\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='r\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x15\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='s\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x16\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='t\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x17\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='u\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x18\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='v\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x19\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='w\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x1a\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='x\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x1b\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='y\n'):                                         
                self.cinterrupt.send('\xa1\x01\x00\x00\x1c\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='z\n'):                                         
                self.cinterrupt.send('\xa1\x01\x02\x00\x1d\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
	elif(str=='~\n'): #backspace
                self.cinterrupt.send('\xa1\x01\x00\x00\x2c\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='!\n'): #space
                self.cinterrupt.send('\xa1\x01\x00\x00\x2a\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
        elif(str=='@\n'): #hanguel
                self.cinterrupt.send('\xa1\x01\x00\x00\x44\x00\x00\x00\x00\x00')
                self.cinterrupt.send('\xa1\x01\x00\x00\x00\x00\x00\x00\x00\x00')
       

		 
		
		
			

if __name__ == "__main__":
    # We can only run as root
    if not os.geteuid() == 0:
        sys.exit("Only root can run this script")

#    pdb.set_trace()

    
    bt = Bluetooth()
    bt.listen()

    



    while True:

	 str = sys.stdin.readline()
	 print ("recieve" + str)
         bt.send_input(str)
