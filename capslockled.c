#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define EXIT_SUCCESS (0)
#define EXIT_FAILURE (1)

/**
 * Function to set LED on CapsLock Button
 *
 * For people using their CapsLock key as Escape in Vim,
 * this can be used as an indicator for modes [NORMAL], [INSERT].
 * This program must be owned by `root` and have SUID bit set.
 *
 * $ sudo chown root capslockled
 * $ sudo chmod u+s capslockled
 *
 * \arg argv 1 -> turn LED on
 * \arg argv 0 -> turn LED off (basically any other argument turns LED off)
 *
 * \return 0 on success
 * \return 1 on failure
 */
int main (int argc, char **argv)
{
    FILE *led;
    int written = 0;
    unsigned char state = '0';
    const char *ledpath="/sys/class/leds/input6::capslock/brightness";

    led = fopen(ledpath, "w");

    if (led == NULL)
        return EXIT_FAILURE;

    if (argc >= 2) {
        if (*argv[1] == '1')
            state = '1';

        written = fwrite(&state, 1, 1, led);

        if (written != 1)
            return EXIT_FAILURE;
    }

    fclose(led);
    return EXIT_SUCCESS;
}
