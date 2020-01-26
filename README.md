# Freefall_detector


Projekt na przedmiot Systemy Mikroprocesorowe.

Prowadzący laboratoria: mgr inż. Sebastian Koryciak


Całość została napisana w języku C w stylu "bare metal" w środowisku Keil uVision w zgodności z płytką FRDM-KL05Z.


Projekt wykorzystuje umieszczony na płytce akcelerometr MMA8451Q. Mikroprocesor komunikuje się z nim za pomocą interfejsu I2C.
Akcelerometr ma skonfigurowane przerwanie w momencie wystąpienia warunków spadku swobodnego, które sygnalizowane jest na jednym z pinów. W momencie zmiany stanu na owym wyjściu zgłaszane jest przerwanie od portu mikrokontrolera. Procedura przerwania uruchamia licznik TPM, który uruchamia swoje przerwanie co jedną milisekundę. Gdy warunki spadku swobodnego mijają, zostaje wykonana kolejny raz procedura przerwania od portu, która tym razem zatrzymuje licznik TPM i odczytuje ile razy wystąpiło przerwanie licznika. Wartość ta w milisekundach jest przeliczana na odległość w centymetrach jaką pokonała płytka. Następnie liczba ta jest wysyłana przez UART.


Mikrokontroler działa w trybie Very Low Power Run (VLPR), czyli większość jego peryferiów jest aktywna, lecz częstotliwości zegarów są zmniejszone w celu obniżenia zużycia energii. Oprócz tego w celu optymalizacji zużycia energii, jedyna funkcja w głównej pętli programu to __wfi() wait for interrupt.

[![Alt text](https://img.youtube.com/vi/wpuqIMKy0Io/0.jpg)](https://youtu.be/wpuqIMKy0Io)
