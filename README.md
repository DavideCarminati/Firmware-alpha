# Firmware alpha

## Processor-In-the-Loop (PIL)
*Processor-In-the-Loop* validation allows the developer to test the software directly on the target board. The board is connected with an external PC on which is running the physical model of the robot as well as a model of its actuators and sensors.
This firmware supports communication using the **UDP** protocol to talk with the external PC. The connection properties (e.g. IP, Port...) can be modified in the file *UDPComm.cpp*:
````c++
static const char*          mbedIP       = "192.168.1.55";      // This board IP seen from the network
static const char*          mbedMask     = "255.255.255.0";     // Mask
static const char*          mbedGateway  = "192.168.1.254";     // Gateway

static const char*          recvIP = "192.168.1.203";           // External PC IP */ "192.168.1.249";
static const char*          localIP = "0.0.0.0";                // Local IP on which the server of the board listens
````
The messaging protocol used is [Mavlink v2.0](https://mavlink.io/en/) since it is lightweight, open-source and widespread.
### PIL with Matlab/Simulink&reg;
It is possible to employ Simulink to create the robot model

## Code generation with Matlab/Simulink&reg;
For *Rapid Prototyping* purposes, code generation is a valid tool. The Firmware is compatible with C/C++ code automatically generated from Matlab/Simulink&reg;. Here it is shown which are the settings used in the **Configuration parameter pane**.