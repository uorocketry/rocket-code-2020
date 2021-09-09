template <typename T>
void serialPrintLn(const T message) {
    Serial.println(message);
}

template <typename T, typename... Types>
void serialPrintLn(const T message, Types... otherMessages) {
    Serial.print(message);

    serialPrintLn(otherMessages...);
}