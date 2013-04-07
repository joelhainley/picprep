picprep :

Well here you have it, a command-line image processing utility that doesn't do anything fancy or
terribly complex but what it does do it does with a minimum of fuss and with very consistent results.
This is pretty much feature complete for me, however I might make some small modifications and might
port it to Mac OS-X at some point. IF there is anything that you'd like to see added to this application
send me an e-mail at jhainley at myndkryme dot com and we'll see what we can work out for you.

------------------------------------------------------------------------------------------------

Special Thanks :
- Amy Stephenson for making the iced tea that powers my various endeavors
- Ken Schultz, did a bunch of testing for me when I was having some memory leak issues.
- James "Jimmy" Owens, tried to process some files with the version 0.8.0 version of this product and
found out just how horrid my command-line interface skills were. He gave me a list of things I screwed
up on so thanks dude.
- The IDM Solutions team for their wonderful UltraEdit product, i used this exclusively while creating
the website and the documentation.
- The DocBook team for their contribution to the field of software documentation, i use this toolset for
all of my product documentation so if you have a need, check it out.
- And finally to Brodie, my dog..for keeping my feet warm ( by sleeping on them ) while I put this utility
together.
------------------------------------------------------------------------------------------------

Usage notes :

The best way to use picprep is to install it to some directory and then update your path to include 
that directory. I know that there are some people out there using windows that aren't comfortable with
the command line, but there are times when it is the best way to do things. Embrace it, you'll be glad
you did. ;-)

------------------------------------------------------------------------------------------------
todo for version 1.3.0 :
- linux support? : this should be really easy since it works on osx, i'm not really sure if i'll
do this but it's certainly worth considering at some point ;-)

todo for version 1.2.0 :
- ability to rotate images

------------------------------------------------------------------------------------------------
version 1.1.0 : ( 10.11.2004 )

Comments :
----------
picprep now runs on Mac Osx. There are a few subtle things in this implementation that may change
over time, mostly having to do with how the parameters are passed into the application. I ran into
a problem while building this release that I didn't expect to run into..

Just so we're on the same page, osx has a unix shell for its commandline interface. Now in the unix
world when you pass *.png parameters to an application, the unix shell expands this to be a list of
of the files that match the shell, so instead of getting a parameter called "*.png" you might get
[ pic1,png, pic2.png pic3.png ] as three seperate arguments to the application. This is NOT what I
expected when I jumped into adding support. For now, you simply must wrap your parameters with ' or "
characters to get it to work as you expected. I chose to require all parameters to be wrapped in '/" parameters
this made things easier to remember, although it does require a bit more typing.

All in all, as my first real porting effort i'm quite happy, both apps compile from the same sources
with a few #ifdef's to sort out system specific things, so as new features/fixes are made to one
they will also appear in the other..very cool!! Especially since this is one of the biggest reasons
that I bought the mac in the first place..to learn porting techniques...and now i use it a lot more
than i thought i would

------------------------------------------------------------------------------------------------

version 1.0.1 : ( 09.26.2004 )

Comments :
----------
I added the aspectRatio turn off feature to the application quite a while ago when I was bored one
evening but it was something that wasn't part of the original specification for the application so
i didn't mention it. However, while looking over a few of the "commercial/shareware" products that
are out there that do the same sorta thing, they listed it as a FEATURE. I never really thought of
it as a feature, but I thought I might as well document it.

I've begun porting the application to OS-X, i don't anticipate a long delay in getting the OS-X release
out into the public's hands, however, the intent here is to build both applications from a single
source tree so chance are pretty good that there will be a "no new features added" release in the near
future for the win32 version of the application that will coincide with the OS-X release. I will most
likely be bumping up the Version to a 1.1.x so that the individual version can start out with the same
version numbers.

------------------------------------------------------------------------------------------------

version 1.0.0 : ( 09.19.2004 )

comments :
----------
I was sitting at the bar last night and realized that while the log file feature for picprep
was something that sounded good in theory, I had not had a need for it yet, and if i just made
the processing output messages a bit nicer then I could just redirect the processing output to
a file and use that as a log file if I ever needed it. This was the last thing holding up a
ver 1.0 release of this utility so this morning I updated the documentation and cleaned up the
log messages and viola!..it's ready for public consumption on a massive scale.

I have some todos listed above for version 1.1.0 however I must admit that these are not a high
priority for me.

------------------------------------------------------------------------------------------------

version 0.9.0 : ( 09.18.2004 )

comments :
----------
Big thanks to James Owens and Ken Schultz for their help in diagnosing some problems with
the memory leaks in the 0.8 release. I think that things are all working relatively well
although some of the messages it spits out are a little retarded. I want to get this out
into everyone's hands while i clean up things for the version 1.0 release.

------------------------------------------------------------------------------------------------

version 0.8 :

comments :
----------
Buggy release, but it'll give you an idea of what i've been working on.

------------------------------------------------------------------------------------------------