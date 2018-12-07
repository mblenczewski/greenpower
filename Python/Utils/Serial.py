from serial import *

# possible encodings for data
ENCODINGS = {
    "ascii" : 0,
    "utf-8" : 1
}


class SerialConnection:
    """ A class encompassing a serial connection. """
    def __init__(self):
        self.name = ""


class SerialWriter:
    """ A class for writing to a serial connection. """
    def __init__(self, serial_connection):
        self.name = ""

    @staticmethod
    def write(serial_stream, string_data):
        pass


class SerialReader:
    """ A class for reading from a serial connection. """
    def __init__(self, serial_connection):
        self.name = ""

    @staticmethod
    def read(serial_stream) -> str:
        return "unimplemented read function in serial reader"


class Serial:
    """ A class for communicating via a serial connection. """
    def __init__(self, encoding = "utf-8"):
        self.encoding = ENCODINGS[encoding.lower()]

    def write(self, string_data):
        SerialWriter.write(string_data)

    def read(self) -> str:
        return SerialReader.read()
