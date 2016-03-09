# Inet sockets

1. [ROT1 server](rot1_server.c)
1. [send lines client](send_lines_client.c)
1. [send file client](send_file_client.c)
1. [receive file client](receive_file_client.c)

## Usage

Inet sockets, can be used across different computers for networking.

Get two computers in a LAN.

Run the server on one computer with:

    ./server.out

Get the IP of the server computer with `ifconfig`.

Then on the other computer, run:

    ./client.out 192.168.0.1

Or use some existing client like:

    netcat localhost 12345

and then type your messages.

Also try `netcat -4` and `netcat -6` to exercise different IP versions.

## Message length

The `read` calls on both client and server run inside while loops.

Like when reading from files, the OS may split up messages arbitrarily to make things faster, e.g. one packet may arrive much earlier than the other.

So the protocol must specify a convention of where messages stop. Common methods include:

- a header with a length indicator (e.g. HTTP `Content-Length`)
- an unique string that terminates messages. Here we use `\n`.
- the server closes connection: HTTP allows that <http://stackoverflow.com/a/25586633/895245>. Limited of course since the next message requires a reconnect.

TODO: I think if we were using UDP, the size of messages would be known always from the protocol.

## SO_REUSEADDR

If we don't use this on the server `bind`, then:

- bind here on the server,
- connect once with a client
- kill server
- try to restart server
- bind fails, because the connection still exists on TIME-WAIT

This allows the bind to happen even it TIME-WAIT is going on.

See also:

- <http://stackoverflow.com/questions/24194961/how-do-i-use-setsockoptso-reuseaddr>
- <http://serverfault.com/questions/329845/how-to-forcibly-close-a-socket-in-time-wait>
- <http://stackoverflow.com/questions/10619952/how-to-completely-destroy-a-socket-connection-in-c>
