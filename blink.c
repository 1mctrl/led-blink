#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int kbd = open("/dev/input/event0", O_RDONLY);
    int led = open("/sys/class/leds/tpacpi::lid_logo_dot/brightness", O_WRONLY);

    struct input_event ev;

    while (read(kbd, &ev, sizeof(ev)) > 0)
    {
        if (ev.type == EV_KEY && ev.value == 1)
        {
            write(led, "255", 3);
            usleep(50000);
            write(led, "0", 1);
        }
    }

    close(kbd);
    close(led);
    return 0;
}
