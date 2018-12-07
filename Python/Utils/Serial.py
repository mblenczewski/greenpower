from Python.Utils.Packet import Packet, PacketBuilder
from serial import *


class SerialHandler:
    """
    A class for communicating via a serial connection.
    Uses even parity and UTF-8 as the string encoding.
    """
    def __init__(self, baud_rate=9600, port="COM1"):
        self.serial_stream = Serial()
        self.configure(port, baud_rate)

    def configure(self, serial_port: str, baud_rate: int):
        """ Configures the serial stream with the given parameters. """
        self.serial_stream.port = serial_port
        self.serial_stream.baudrate = baud_rate
        self.serial_stream.parity = PARITY_EVEN
        self.serial_stream.rtscts = 1

    def write(self, packet: Packet):
        """ Writes the given packet to the serial stream in a binary format. """
        serialised_packet: bytes = str.encode(PacketBuilder.serialise_packet(packet))
        self.serial_stream.write(serialised_packet)

    def read(self) -> Packet:
        """ Receives a packet from the serial stream, deserialises it and returns it. """
        serialised_packet: str = self.serial_stream.read_until(PacketBuilder.terminator).decode()
        return PacketBuilder.deserialise_packet(serialised_packet)

    def __enter__(self):
        """ Allows for entering a context with this class. """
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        """
        Allows for exiting a context with this class.
        Also prints exception stats to the stdout if one is the cause of the context exit.
        """
        self.serial_stream.close()
        if exc_type is not None:
            print("Exception during context. Type: {}, Value: {}, Trace-back: {}".format(exc_type, exc_val, exc_tb))
