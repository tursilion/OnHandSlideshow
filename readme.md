20020924

OnHandPC SlideShow
------------------

This is a simple program I wrote to perform a SlideShow with the OnHandPC.
I wanted an easy way to scan though a folder of images without waiting
for directory listings or futzing about with menus.

This program is intended to be extremely simple - and as such does not
offer real-time configuration (I didn't want to waste flash space with
a configuration file for only 2 items!) Therefore, a Win32 program is
included. This program takes three parameters:

Delay: The delay, per picture, in seconds (1-99) (default is 5)
Path: The path, on the OnHandPC, to your images 
      (default is \ACCESSOR\GRAPHICS\). Must be an absolute path!
FileName: The name of the .EXF that you want to write 
      (default is SLIDSHOW)

This Win32 program does NOT require the original .EXF file, it
will create a new one!

If you can run the Windows program, then you may skip to the USAGE
section below.

If you can not run Windows programs, you can use the SLIDSHOW.EXF
in the archive, with the defaults above. If you wish to change it,
you may try using a hex editor. The configuration is clearly 
labelled in readable text for this purpose, near the end of the
EXF file, as shown here (note that offsets may change):

```
00001510  FE 2D 2D 2D 53 54 41 52 54 20 44 41 54 41 2D 2D  .---START DATA--
00001520  00 44 65 6C 61 79 3A 20 28 30 30 35 29 20 73 00  .Delay: (005) s.
00001530  00 50 61 74 68 20 74 6F 20 70 69 63 73 3A 00 00  .Path to pics:..
00001540  00 5C 41 43 43 45 53 53 4F 52 5C 47 52 41 50 48  .\ACCESSOR\GRAPH
00001550  49 43 53 5C 00 00 00 00 00 00 00 00 00 00 00 00  ICS\............
00001560  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
00001570  00 00 00 2D 2D 2D 2D 45 4E 44 20 44 41 54 41 2D  ...----END DATA-
00001580  2D 2D 00                                         --.
```
The delay must be three digits and must fit inside the () set.
The path must start 16 bytes after the start of the word 'Path' as shown,
and may be up to 50 characters long. It must end with a backslash and it
must be followed by a '0' byte. It should start with a backslash.

USAGE
-----
Once copied onto the OnHand, the program may simply be executed. It will
pause two seconds for station identification ( ;) ), and then start up.

The Slideshow recognizes three file types:

MMP - The original Matsucom monochrome image. Although up to 320x240 may
be loaded, only the top left corner (102x64) is visible.
GMP - 8 level grayscale image achieved by flickering the display. GMPs
are nice, but they take 9 times the space of a 102x64 MMP.
ZMP - 4 level grayscale image achieved by timed flickering. Actually,
this is still in the concept stage for me, and no software yet creates them,
but I added support anyway. These files take only twice the space of a 
102x64 MMP file.

The following controls are active during the slideshow:
-Joystick LEFT - previous image. A list of the last 20-30 images is kept,
and may be cycled through by tapping LEFT.
-Joystick RIGHT - next image.
-Joystick UP - hold image. The current image remains on the display. When
UP is released, the normal countdown timer begins before the next image is
displayed.
FILER/MENU - exit the slideshow. The slideshow also exits after the last
image has been displayed.
EL - turns on the backlight for 20 seconds

TROUBLESHOOTING
---------------
Limited troubleshooting is available, but there are a few basic steps:

If the 'Programmed by Tursi' logo does not appear, then no '*.?MP'
images were found at the path you specified. Check that you have the
path entered correctly, that it begins and ends with a '\' (not '/'),
and that it's the complete path to the actual pictures.

If the logo appears, but no pictures do, it's possible that the images
are corrupted. Download them with PC Filer and test them in the image
conversion tool. I haven't run into viewing problems yet, but my
testbed is pretty small.

If grayscale images appear to 'break up' or 'dissolve' when loading the
next image -- actually that's normal, as the flicker is stopped during
that process.

If 'banding' or other artifacts occur during grayscale images - well,
let me know how bad it is. There are two ways to do it, that I could
see. One is to use the 64hz timer, the other is to just go full-tilt.
On my watch, using the timer generates little black lines all over
the image, but going full-tilt works fine (except for some slight
scrolling bands). So I chose to release the latter version. If
it's just not acceptable, we can make that configurable too.

If the slideshow just exits back to the Filer - that's because it
ran out of pictures to load. It exits instead of looping because
I don't want it to be able to run down the batteries if accidentally
launched. It's quick enough to restart, isn't it? :)

LICENSE
-------
This program is provided freely 'AS-IS' provided that no money is
made from it's distribution or use, directly or indirectly, and that
no modifications are made, except as described in this document for
configuration. Please do not *distribute* patches that modify the
behaviour of this program, or patched versions of the program. 
(I don't mind if you make them for your own use, though.)
