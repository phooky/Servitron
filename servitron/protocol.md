Servitron client-server protocol
================================

Server responsibilities:
* Track quadrature encoders
* Maintain information about position and velocity of all axes
* Execute positioning/velocity commands
* Maintain PID loops and current position
* Maintain brake

Types of interaction
--------------------

* Hello: client should connect to server and get a greeting message including server version
* Status: client can request status from the server and get current positions, speeds, and queue status.
* Non-blocking motion commands: clients should be able to place motions on a queue of sequentially interpreted commands

General command/response framework
----------------------------------

Most commands are fixed-length and determined by a simple struct. Commands begin with a one-byte command identifier.
Responses are also generally fixed-length and delivered as soon as possible. They begin with a one-byte response code.

All command-response transactions are sequential; a second command should not be sent before a reply is received unless the response has timed out. Responses delivered more than half a second after the command is sent are considered to have timed out.

Any command or response that is not fixed-length must end in a zero-terminated string.

Response codes
--------------
0x80 - OK
0x81 - generic error

Hello interaction
-----------------

The HELLO interaction is generally sent when a client connects. It is not required.

Command code: 0x01
Command payload:
    uint16_t clientVersion;
    char* clientString;

Response payload:
    uint16_t serverVersion;
    char* serverString;

Status interactions
-------------------

*Mechanical status*
Command code: 0x02
Command payload: None
Response payload:
    {
        int32_t position
        int32_t velocity
    }[6]

*Queue status*
Command code: 0x03
Command payload: None
Response payload:
    int16_t remainingMoves


