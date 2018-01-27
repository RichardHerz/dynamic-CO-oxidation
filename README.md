Dynamic simulation of CO oxidation in a porous catalyst pellet built with LiveCode and C++ externals.

For a video showing the project running, see www.ReactorLab.net and click the tab "VIDEOS, SCREEN SHOTS & REPORTS" and see the video Catalyst Dynamics.

For a Windows standalone version, see www.ReactorLab.net and click the tab "DOWNLOAD" and see the dynamic Catalyst Pellet. 

This project was built circa 2008 using a version of Runtime Revolution - now renamed LiveCode - and Mac and Win compilers of that era. 

The Rev-LiveCode stacks should be saved only with stackFileVersion 2.7 in order to ensure compatibility with the externals. 

We have done limited testing of this open-source project:

* The simulation runs on a Mac (MacBook Pro 2011) running Mac OS 10.13.2 (High Sierra) using LiveCode Community 8.1.8.

* The simulation opens the stacks but **crashes** after the "start" button is pressed on a virtual machine running Windows 7 using LiveCode Community 8.1.8. We  suspect this is due to a memory leak in the external. A similar problem occurred on a Mac under LiveCode version 7 but then went away with version 8 with no change to project files. 

A simulation with simplified kinetics that has much of the same behavior of this system is the "Dynamic diffusion and reaction in a porous solid catalyst" Web Lab at www.ReactorLab.net and click the tab "WEB LABS." This system is also found in the "reaction-diffusion" GitHub Repository at this GitHub site. 


