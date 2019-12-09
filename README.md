# Freefall_detector
SmP projekt

Projekt zakłada budowę detektora spadku swobodnego z użyciem płytki FRDM KL05.
Użyty zostanie wbudowany w płytkę akcelerometr MMA8451Q.
Komunikacja z nim zapewniona jest przez interfejs I2C.
Aby zwiększyć mobilność urządzenia zastosowane zostanie zasilanie bateryjne.
Będzie się to wiązało z użyciem trybów energooszczędnych procesora jak i peryferiów.
W chwili wykrycia zdarzenia spadku swobodnego zgłoszone zostanie przerwanie, które spowoduje zliczenie czasu spadku oraz przeliczenie go na odległość jaką przebędzie urządzenie.
Dane o kolejnych zdarzeniach będzie można odczytać z pliku tekstowego podłączając płytkę za pomocą USB do komputera.
