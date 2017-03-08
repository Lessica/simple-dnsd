This directory contains a dns server implementation (single query processing only).
For further information, please check RFC 1034 and RFC 1035.

How to use the program
----------------------
After compiling the application creates a binary file (dnsd). To force the resolver
to use this name server instead of the ones configured in the machine the file
/etc/resolv.conf should be modified. The example can be found inside the files 
directory (resolv.conf.dns). If the networking configuration is dhcp, is convenient
to modify the file /etc/dhcp.client otherwise from time to time the /etc/resolv.conf
is overwritten with the original values stored in the resolver. If the "supersede" 
line is modified -as shown in the sample you could find in files directory 
(dhcp.client.dns)- the resolver only uses the name server implemented here. 

It is possible to test the nameserver using a browser or simply a ping or a host
command. If no parameter is given, the log file is created inside /var/log/, but
the user can choose the name of the file with the option "-f file".

