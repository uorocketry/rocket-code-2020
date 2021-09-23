#include <Arduino.h>

template <typename T>
void serialPrintLn(const T message)
{
    Serial.println(message);
}

template <typename T, typename... Types>
void serialPrintLn(const T message, Types... otherMessages)
{
    Serial.print(message);

    serialPrintLn(otherMessages...);
}

template <typename... Types>
void serialInfo(Types... messages)
{
    serialPrintLn("INFO: ", messages...);
}

template <typename... Types>
void serialWarning(Types... messages)
{
    serialPrintLn("WARN: ", messages...);
}

template <typename... Types>
void serialError(Types... messages)
{
    serialPrintLn("Error: ", messages...);
}

template <typename T>
bool arrayContains(const T *array, int size, T element)
{
    for (int i = 0; i < size; i++)
    {
        if (element == array[i])
        {
            return true;
        }
    }

    return false;
}