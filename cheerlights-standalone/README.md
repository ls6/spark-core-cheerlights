This is a standalone spark client for cheerlights. It reconnects every minute and updates the color of the on-board LED accordingly.

In addition you can change the LED color via a serial connection. I've used the standard Arduino serial terminal at 57600 and it worked nicely.
Sending 0 will restore the default LED behaviour, numbers `1`-`9`, `a` and `b` just change the color.

Have fun :)
