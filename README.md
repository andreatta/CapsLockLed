# CapsLockLed
A little program to control the CapsLock LED on my laptop (DELL XPS 15 9560) keyboard.

I like to have CapsLock mapped to Escape, since I use Escape way more than I ever use CapsLock.
This is especially useful in vim to exit from `INSERT` mode.

What I don't like is useless technical stuff.
What I like is giving useless technical stuff new purpose.

So I thought, the integrated CapsLock LED on my keyboard would make a good visual indicator for `INSERT` mode.

## This program must be owned by `root` and have `SUID` bit set.

```bash
$ sudo chown root capslockled
$ sudo chmod u+s capslockled
```

The program can be called with
`./capslockled 1` to turn LED on. Basically any other argument turns the LED off, but it would of course make sense to call it with `./capslockled 0`

On success the program returns `0` on failure `1`.

## Building this program

It has a simple Makefile to compile the program, set permissions and copy it to a specific folder.

Only build program, you have to change ownership and set SUID bit yourself.

```bash
make
```

Or just let the Makefile handle it.
Default is to copy the compiled program to ~/bin. This is the folder where I keep my own compiled programs. You will have to adapt it to your likings.

```bash
make install
```


