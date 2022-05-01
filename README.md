# DWM fork - dynamic window manager

[dwm](dwm.suckless.org) is an extremely fast, small, and dynamic window manager for X.


## Requirements

In order to build dwm you need the Xlib header files.


## Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

	make clean install


## Running dwm

Add the following line to your .xinitrc to start dwm using startx:

	exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

	DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

	while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
	do
		sleep 1
	done &
	exec dwm


## Configuration

The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.


## Applied Patches

- [Barpadding](https://dwm.suckless.org/patches/barpadding/dwm-barpadding-6.2.diff): This patch adds variables for verticle and horizontal space between the statusbar and the edge of the screen.
  [Dragmfact](https://dwm.suckless.org/patches/dragmfact/dwm-dragmfact-6.2.diff): This patch lets you resize the split in the tile layout (e.g. modify mfact) by holding the modkey and dragging the mouse.
  [Gapless](https://dwm.suckless.org/patches/gaplessgrid/dwm-gaplessgrid-6.1.diff): his patch is an altered gridmode layout for dwm, which arranges the windows in a grid.
  [Movestack](https://dwm.suckless.org/patches/movestack/dwm-movestack-20211115-a786211.diff): This plugin allows you to move clients around in the stack and swap them
  [Scratspads](https://dwm.suckless.org/patches/scratchpads/dwm-scratchpads-20200414-728d397b.diff): This patch enables multiple scratchpads.
  [Status2d](https://dwm.suckless.org/patches/status2d/dwm-status2d-6.3.diff): Status2d allows colors and rectangle drawing in your DWM status bar.
  [Spawn_cws](https://dwm.suckless.org/patches/spawn_cwd/dwm-6.0-spawn_cwd.diff): Spawns programs from currently focused client's working directory.
with the master.
- [Cfacts](https://dwm.suckless.org/patches/cfacts/dwm-cfacts-6.2-1.diff): This patch provides the ability to assign different weights to clients in their respective stack in tiled layout.
- [Statuspadding](https://dwm.suckless.org/patches/statuspadding/dwm-statuspadding-20150524-c8e9479.diff): This makes the amount of horizontal and vertical padding in the status bar into configurable options.
- [Center](https://dwm.suckless.org/patches/center/dwm-center-20160719-56a31dc.diff): Ability to center floating windows
  [Systray](https://dwm.suckless.org/patches/systray/dwm-systray-6.3.diff): A simple system tray implementation.
  [Underlinetags](https://dwm.suckless.org/patches/underlinetags/dwm-underlinetags-6.2.diff): Underlines selected tags.
  [Vanitygaps](https://dwm.suckless.org/patches/vanitygaps/dwm-cfacts-vanitygaps-6.2.diff): This patch differentiates between inner and outer gaps as well as
horizontal and vertical gaps.

## Added layouts
- [Bottomstack](https://dwm.suckless.org/patches/bottomstack/dwm-bottomstack-6.1.diff): bstack and bstackhoriz are two stack layouts for dwm.
- [centeredmaster](https://dwm.suckless.org/patches/centeredmaster/dwm-centeredmaster-6.1.diff): Centered master layout
  [Fibonacci](https://dwm.suckless.org/patches/fibonacci/dwm-fibonacci-6.2.diff): This patch adds two new layouts (spiral and dwindle) that arranges all windows in Fibonacci tiles.
- [Grid Layout](https://dwm.suckless.org/patches/gridmode/dwm-gridmode-20170909-ceac8c9.diff) in which the windows are arranged in a grid of equal sizes.
  [Horizontal](https://dwm.suckless.org/patches/horizgrid/dwm-horizgrid-6.1.diff): This patch is a variant of gaplessgrid.

