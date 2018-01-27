Dynamic simulation of CO oxidation in a porous catalyst pellet built with LiveCode and C++ externals.

For a video showing the project running, see www.ReactorLab.net and click the tab "VIDEOS, SCREEN SHOTS & REPORTS" and see the video Catalyst Dynamics.

For a Windows standalone version, see www.ReactorLab.net and click the tab "DOWNLOAD" and see the dynamic Catalyst Pellet. 

A simulation with simplified kinetics that has much of the same behavior of this system is the "Dynamic diffusion and reaction in a porous solid catalyst" Web Lab at www.ReactorLab.net and click the tab "WEB LABS." This system is also found in the "reaction-diffusion" GitHub Repository at this GitHub site. 

To run the simulation, open the stack file "Catalyst Pellet.rev" in LiveCode. The folder "files" must be located in the same folder as that stack file. With the Catalyst Pellet stack open, click the button "set and go." This sets the externals file (.dll or .bundle) for the stack "reactor pellet.rev" in the "files" folder and opens the reactor pellet stack. Then click the "start" button to start the simulation.

This project is currently being developed with the open-source, Community Edition of LiveCode. Get it at www.LiveCode.org. This project was originally built circa 2008 using a version of Runtime Revolution - now renamed LiveCode - and Mac and Win compilers of that era. 

We have done limited testing of this open-source project:

* The simulation runs on a Mac (MacBook Pro 2011) running Mac OS 10.13.2 (High Sierra) using LiveCode Community 8.1.8.

* The simulation opens the stacks but *crashes* after the "start" button is pressed on a virtual machine running Windows 7 using LiveCode Community 8.1.8. We  suspect this is due to a memory leak in the external. A similar problem occurred on a Mac under LiveCode version 7. 

We recommend that the Rev-LiveCode stacks should be saved only with stackFileVersion 2.7 in order to ensure compatibility with the externals. We have saved the stacks as stackFileVersion 8.1 on LC 8.1.8 on Mac OS 10.13.2 and the project works but the 2.7 stackFileVersion should probably maintained while the Windows version is debugged. 

