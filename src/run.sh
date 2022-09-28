#!/bin/sh
 broadwayd -p 80 :0&
 GDK_BACKEND=broadway BROADWAY_DISPAY=:0 ./gtk.app 