#include <stdio.h>
#include <math.h>

// Globale Konstanten
const float g = 9.81;
const float R = 287.0;
const float n = 1.235;
const float Tn = 288.15;
const float dn = 1.225;

// Funktion für die Koordinatenunterscheidung
int caseDistinction(int lat, int lon) {
    int H = 0;
    if (lat == 48 && lon == 9) {
        H = 388;
    } else if (lat == 52 && lon == 13) {
        H = 37;
    } else if (lat == 48 && lon == 11) {
        H = 453;
    } else if (lat == 50 && lon == 8) {
        H = 110;
    } else {
        printf("Wrong coordinates entered!\n");
        return -1; // Fehlercode für ungültige Eingabe
    }
    return H;
}

// Berechnungsfunktion
void calculate(int height, int temp, int press, float values[4]) {
    float T = temp + 273.15;    // Temperatur in Kelvin
    float P = press * 100;      // Druck in Pascal

    float T0 = T + ((n - 1) / n) * (g / R) * height;
    values[0] = T0;

    float d0 = P / (R * T0);
    values[1] = d0;

    float d = d0 * pow((1 - ((n - 1) / n) * (g / (R * T0)) * height), (1 / (n - 1)));
    values[2] = d;

    float Hd = (pow((d / dn), (n - 1)) - 1) * (-n / (n - 1)) * ((R * Tn) / g);
    values[3] = Hd;
}

int main(void) {
    int lat, lon, temp, press;

    // Eingabeaufforderung
    printf("Please enter latitude, longitude, temperature, and pressure for the airport:\n");
    printf("Latitude: ");
    scanf("%d", &lat);
    printf("Longitude: ");
    scanf("%d", &lon);
    printf("Temperature (°C): ");
    scanf("%d", &temp);
    printf("Pressure (hPa): ");
    scanf("%d", &press);

    // Koordinaten überprüfen
    int height = caseDistinction(lat, lon);
    if (height == -1) {
        return 1; // Programm beenden bei ungültigen Koordinaten
    }

    // Berechnungen durchführen
    float values[4] = {0};
    calculate(height, temp, press, values);

    // Ergebnisse ausgeben
    printf("Results:\n");
    printf("T0 = %.3f K\n", values[0]);
    printf("rho0 = %.3f kg/m^3\n", values[1]);
    printf("rho = %.3f kg/m^3\n", values[2]);
    printf("Hd = %.3f m\n", values[3]);

    return 0;
}
