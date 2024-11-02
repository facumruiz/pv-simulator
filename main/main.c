#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LED_PIN 2 // Cambia esto según el pin del LED en tu placa

void simulate_panel_task(void *pvParameter) {
    // Inicializa el generador de números aleatorios
    srand(time(NULL));

    // Imprimir la cabecera de la tabla
    printf("%-12s %-8s %-10s %-12s %-10s %-10s %-12s %-14s %-10s %-14s\n",
           "Date", "Time", "Energy", "Efficiency", "Power", "Average", "Normalised", "Temperature", "Voltage", "Energy Used");

    while (1) {
        // Obtener la fecha y hora actual
        time_t now;
        struct tm timeinfo;
        time(&now);
        localtime_r(&now, &timeinfo);

        // Simular datos del sistema fotovoltaico
        float energy = (rand() % 10000) / 100.0; // Energía en kWh
        float efficiency = (rand() % 1000) / 10.0; // Eficiencia en %
        float power = (rand() % 5000) / 100.0; // Potencia en kW
        float average = (rand() % 5000) / 100.0; // Promedio
        float normalised = (rand() % 5000) / 100.0; // Normalizado
        float temperature = (rand() % 4000 + 2000) / 100.0; // Temperatura en °C
        float voltage = (rand() % 4000 + 1000) / 100.0; // Voltaje en V
        float energy_used = (rand() % 5000) / 100.0; // Energía usada en kWh

        // Mostrar los datos simulados en formato de columnas
        printf("%02d-%02d-%04d %-8s %-10.2f %-12.2f %-10.2f %-10.2f %-12.2f %-14.2f %-10.2f %-14.2f\n",
               timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900,
               " ", // Espacio para alinear la hora
               energy, efficiency, power, average, normalised, temperature, voltage, energy_used);

        // Enciende el LED
        gpio_set_level(LED_PIN, 1);

        // Simula el tiempo que tarda en enviar un dato (1 segundo)
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        // Apaga el LED
        gpio_set_level(LED_PIN, 0);

        // Espera 1 segundo antes de generar otros valores
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main() {
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    // Crea una tarea para simular el sistema fotovoltaico
    xTaskCreate(&simulate_panel_task, "simulate_panel_task", 2048, NULL, 5, NULL);
}
