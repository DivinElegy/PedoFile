Simple application to read keypress events.

Setting Up
==========
-Set up libhid (more about that below)
-Set KEYBOARD_DEVICE in logger.h to the relevant /dev/input node.
-Needs to be run as root.
-Start policyserve.sh as root before starting PedoFile (thanks Adobe ლ(ಠ益ಠლ)).

libhid
======
libhid is needed to talk to the pac drive. I got it from here http://alioth.debian.org/frs/?group_id=30451

There is an a small problem that stops the build, the fix is here http://matthewcmcmillan.blogspot.com.au/2013_03_01_archive.html

`make install` puts libhid in /usr/local/lib. Make a symlink to the so: `ln -s /usr/local/lib/libhid.so.0 /usr/lib/libhid.so.0`
