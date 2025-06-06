#include <stdio.h>
#include <stdlib.h> // Pour system()
 
#ifdef _WIN32
#include <windows.h> // Pour Sleep()
#else
#include <unistd.h>  // Pour usleep() sur Unix/Linux
#endif

#include <fcntl.h>
#include <string.h>

#define NUM_LEDS 9  // Adapté à 9 LEDs

const char *led_paths[NUM_LEDS] = {
    "/sys/class/leds/fpga_led0/brightness",
    "/sys/class/leds/fpga_led1/brightness",
    "/sys/class/leds/fpga_led2/brightness",
    "/sys/class/leds/fpga_led3/brightness",
    "/sys/class/leds/fpga_led4/brightness",
    "/sys/class/leds/fpga_led5/brightness",
    "/sys/class/leds/fpga_led6/brightness",
    "/sys/class/leds/fpga_led7/brightness",
    "/sys/class/leds/fpga_led8/brightness"
};

// Allumer ou éteindre une LED
void set_led(int index, int state) {
    int fd = open(led_paths[index], O_WRONLY);
    if (fd < 0) {
        perror("Erreur ouverture LED");
        return;
    }

    const char *value = state ? "1" : "0";
    if (write(fd, value, strlen(value)) < 0) {
        perror("Erreur écriture LED");
    }

    close(fd);
}

int main() {
    int position = 0;

    while (1) {
        // Éteindre toutes les LEDs
        for (int i = 0; i < NUM_LEDS; i++) {
            set_led(i, 0);
        }

        // Allumer la LED courante
        set_led(position, 1);

        // Avancer à la LED suivante
        position = (position + 1) % NUM_LEDS;

        usleep(200000); // Pause de 200 ms
    }

    return 0;
}
