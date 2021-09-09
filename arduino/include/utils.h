template <typename T>
void serialPrintLn(const T message) {
    Serial.println(message);
}

template <typename T, typename... Types>
void serialPrintLn(const T message, Types... otherMessages) {
    Serial.print(message);

    serialPrintLn(otherMessages...);
}

template <typename T>
bool arrayContains(const T* array, int size, T element) {
    for (int i = 0; i < size; i++) {
        if (element == array[i]) {
            return true;
        }
    }

    return false;
}