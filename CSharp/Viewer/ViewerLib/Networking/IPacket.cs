namespace ViewerLib.Networking
{
    /// <summary>
    /// Describes a packet sent from the car to the pits.
    /// </summary>
    public interface IPacket
    {
        /// <summary>
        /// The serialised data.
        /// </summary>
        string Data { get; set; }
    }
}