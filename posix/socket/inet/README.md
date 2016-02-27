# Inet sockets

Inet sockets, can be used across different computers for networking.

Get two computers in a LAN.

Run the server on one computer with:

    ./server.out

Get the IP of the server computer with `ifconfig`.

Then on the other computer, run:

    ./client.out 192.168.0.1

## Message length

The `read` calls on both client and server run inside while loops.

Like when reading from files, the OS may split up messages arbitrarily to make things faster, e.g. one packet may arrive much earlier than the other.

So it is necessary to have a convention of where messages stop, which is either:

- a header with a length indicator
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
