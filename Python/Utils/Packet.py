from typing import Dict, Any
from datetime import datetime

PACKET_ATTRIBUTE_SEPARATOR = ":"
""" The character used to delimit a serialised attribute name from its value. """

PACKET_ATTRIBUTE_DELIMITER = "|"
""" The character used to delimit serialised properties in the packet. """

PACKET_END = "{EOP}"
""" The character sequence used to signal the end of a data packet. """


def str_convert(val: str) -> str:
    """ Converts the given value to a string type. """
    return str(val)


def int_convert(val: str) -> int:
    """ Converts the given value to an int type. """
    return int(val)


def float_convert(val: str) -> float:
    """ Converts the given value to a float type. """
    return float(val)


TYPES = {
    str: str_convert,
    int: int_convert,
    float: float_convert
}


class Packet:
    """
    A base class encapsulating a basic data packet.
    Should be overwritten for custom packets.
    If inherited, the __str__ and __dir__ methods should be
    overridden to provide adequate serialisation and
    deserialisation.
    """

    date: str
    """ The date that this packet was sent on. """

    packet_id: int
    """ The id of the packet. """

    def __init__(self, date: datetime = datetime.now, packet_id: int = 0):
        self.date = "01.01.0001"
        self.packet_id = packet_id

    def __dir__(self) -> Dict[str, type]:
        """ Overrides the default __dir__ method, to provide a list of all attributes and their values. """
        attr_dict: Dict[str, type] = {}
        for attr in self.__dict__:
            attr_dict[attr] = type(self.__getattribute__(attr))

        return attr_dict

    def __str__(self) -> str:
        """ Overrides the default __str__ method, for serialising the packet to a string. """
        serialised_packet: str = ""
        attribute_list = self.__dir__()
        for attr in attribute_list:
            serialised_packet += attr + ":" + str(self.__getattribute__(attr)) + PACKET_ATTRIBUTE_DELIMITER
        return serialised_packet + PACKET_END


class PacketBuilder:
    """
    A static factory class for serialising and deserialising data packets.
    """

    @staticmethod
    def serialise_packet(packet: Packet) -> str:
        """ Serialises and returns the string representation of the given data packet. """
        return str(packet)

    @staticmethod
    def deserialise_packet(packet: str) -> Packet:
        """ Deserialises and returns a packet from the given string. """
        if packet.find(PACKET_END) != -1:
            data_packet: Packet = Packet()  # final packet to return
            packet_attributes = data_packet.__dir__()  # gets all the packet attributes
            delimited_data: str = packet.strip(PACKET_END)  # strips the packet terminator from the packet

            for serialised_attribute in delimited_data.split(PACKET_ATTRIBUTE_DELIMITER):  # splits packet to attributes
                if serialised_attribute is "":  # skips empty attributes
                    continue

                attribute_name: str = serialised_attribute.split(PACKET_ATTRIBUTE_SEPARATOR)[0]  # gets attribute names
                attribute_type: type = packet_attributes[attribute_name]  # gets the type of the attribute
                attribute_value = serialised_attribute.split(PACKET_ATTRIBUTE_SEPARATOR)[1]  # gets attr values

                data_packet.__setattr__(attribute_name, TYPES[attribute_type](attribute_value))

            return data_packet
        else:
            raise ValueError("Malformed packet given, lacking end delimiter. Packet given: '{}'".format(packet))
