#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILED_OPEN 1
#define EXIT_FAILED_WRITE 2
#define EXIT_WRONG_PARAM 3

int get_path(char *path);

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
int main(int argc, char **argv)
{
    FILE *led;
    int written = 0;
    unsigned char state = '0';
    char ledpath[60] = {0};
    //const char *ledpath="/sys/class/leds/input6::capslock/brightness";

    get_path(ledpath);

    led = fopen(ledpath, "r+");
    if (led == NULL)
        return -EXIT_FAILED_OPEN;

    /* If no param is given toggle LED */
    if (argc == 1) {
        fread(&state, 1 , 1, led);
        state = (state == '0' ? '1' : '0');
    } else if (argc >= 2) {
        if (*argv[1] == '1')
            state = '1';
    } else {
        return -EXIT_WRONG_PARAM;
    }

    written = fwrite(&state, 1, 1, led);
    if (written != 1)
        return -EXIT_FAILED_WRITE;

    fclose(led);
    return EXIT_SUCCESS;
}

/**
 * Get correct path to LED
 * On my system (Dell XPS15  9560), the input number happened to change
 * from time to time.
 */
int get_path(char *path)
{
    static char ledpath[60] = "/sys/class/leds/";
    int ledlen = 0;
    DIR *d = opendir(ledpath);
    struct dirent *dir;

    if (d == NULL)
        return -1;

    ledlen = strlen(ledpath);

    while ((dir = readdir(d)) != NULL) {
        if (dir->d_type != DT_DIR) {
            if (strstr(dir->d_name, "capslock") != NULL) {
                int len = strlen(dir->d_name);
                strncat(&ledpath[ledlen], dir->d_name, len);
                strncat(&ledpath[ledlen + len], "/brightness", 12);
            }
        }
    }
    closedir(d);

    ledlen = strlen(ledpath);
    memcpy(path, ledpath, ledlen);

    return ledlen;
}
