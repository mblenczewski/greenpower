using System;
using System.IO;
using System.Linq;
using System.Reflection;

namespace ViewerLib.Utils
{
    public static class CsvFileHandler
    {
        public static T Deserialise<T>(string serialisedItem) where T : new()
        {
            T deserialisedItem = new T();
            return deserialisedItem;
        }

        public static string Serialise<T>(T item)
        {
            string serialisedItem = "";

            Type itemType = typeof(T);
            PropertyInfo[] properties = itemType.GetProperties();

            for (int i = 0; i < properties.Length; i++)
            {
                serialisedItem += i == properties.Length - 1
                    ? properties[i].GetValue(item).ToString().TrimEnd('\r') + "\n"
                    : properties[i].GetValue(item).ToString().TrimEnd('\r') + ", ";
            }

            return serialisedItem;
        }

        public static T Read<T>(string filepath) where T : new()
        {
            return Deserialise<T>(File.ReadAllText(filepath));
        }

        public static void Write<T>(T[] items, string filepath)
        {
            string serialisedArray = "";

            Type itemType = typeof(T);
            PropertyInfo[] properties = itemType.GetProperties();

            for (int i = 0; i < properties.Length; i++)
            {
                serialisedArray += i == properties.Length - 1
                    ? properties[i].Name.TrimEnd('\r') + "\n"
                    : properties[i].Name.TrimEnd('\r') + ", ";
            }

            serialisedArray = items.Aggregate(
                serialisedArray,
                (current, t) => current + Serialise(t));

            File.WriteAllText(filepath, serialisedArray);
        }
    }
}