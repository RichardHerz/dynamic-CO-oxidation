Dynamic simulation of CO oxidation in a porous catalyst pellet built with LiveCode and C++ externals.

For a video showing the project running, see www.ReactorLab.net and click the tab "VIDEOS, SCREEN SHOTS & REPORTS" and see the video Catalyst Dynamics.

On Windows OS, currently, the simulation stacks will open but will *crash* if you click the "start" button. See testing below. 

For a Windows standalone version that does run correctly, see www.ReactorLab.net and click the tab "DOWNLOAD" and see the dynamic Catalyst Pellet. Updates to the "reactor pellet.rev" stack in this distribution, when saved with legacy stackFileVersion 2.4 only, are able to run with this standalone.

A simulation with simplified kinetics that has much of the same behavior of this system is the "Dynamic diffusion and reaction in a porous solid catalyst" Web Lab at www.ReactorLab.net and click the tab "WEB LABS." This system is also found in the "reaction-diffusion" GitHub Repository at this GitHub site. 

To run the simulation, open the stack file "Catalyst Pellet.rev" in LiveCode. The folder "files" must be located in the same folder as that stack file. With the Catalyst Pellet stack open, click the button "set and go." This sets the externals file (.dll or .bundle) for the stack "reactor pellet.rev" in the "files" folder and opens the reactor pellet stack. Then click the "start" button in the reactor pellet stack to start the simulation. When running, the simulation calls functions in the compiled externals file.

This project is currently being developed with the open-source, Community Edition of LiveCode, version 8. Get it at www.LiveCode.org. This project was originally built circa 2008 using Mac and Win compilers of that era and version 2.4 of Runtime Revolution, where Runtime Revolution was later renamed LiveCode. 

We have done limited testing of this open-source project:

* The simulation runs on a Mac (MacBook Pro 2011) running Mac OS 10.13.2 (High Sierra) using LiveCode Community 8.1.8.

* The simulation opens the stacks but *crashes* after the "start" button is pressed on a virtual machine running Windows 7 and an HP laptop running Windows 10, both using LiveCode Community 8.1.8. We  suspect this is due to a memory leak in the external. A similar problem occurred on a Mac under LiveCode versions 5-7 but has been fixed in version 8.1, at least. See note above about the standalone version at ReactorLab.

