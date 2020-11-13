# DIGIMUSER
DIGIMUSER is a digital vocal effect processor "stompbox" that applies a variety of real-time signal processing algorithms to alter the voice of a singer. DIGIMUSER takes a (1/4)" mono jack input from a dynamic microphone and outputs through another (1/4)" cable to an amplifier or to additional audio processing equipment. Since the effects applied by DIGIMUSER are performed digitally on a microcontroller, it can be reprogrammed to implement a wide collection of effecus such as filters, delays, distortions, and spatial effects. A standard bypass stomp button enables and disables the effect, a knob selects the type of applied effect, and a slider controls the intensity of the effect.
 
## Project Team Members
David Pierce Walker-Howell (EE), Luke kennard (COMPE), Danielle Stewart (COMPE), Suaod Alhajry (EE), Angel Martinez (COMPE)

## Contribute to this Project
Here are the guidelines to contribute to the project.

#### Branching
The development process for software or hardware must be done in a seperate branch from **main**. Once a software or hardware component is completed a pull request must be made before merging with **main**. The pull request must reviewed and approved before merging to main. 

Here is how to create a new branch off of main. Please use the following naming format for the branch **[Your_name]_[description_of_branch]**

```
Example

//Creates a new branch called "Pierce_I2S_software_development" off of the "main" branch
git checkout -b Pierce_I2S_software_development main
```

#### GIT workflow
Be sure to keep your branch (and the Repository) up-to-date on your local machine by performing pulls often (i.e. be sure to make a pull of the repo prior to making any new edits or commits). Also make sure to commit changes locally often and push those commits to the Github Repository often as well. Below is the typical workflow to follow

```
//Open a git bash or linux terminal and move to the DIGIMUSER project director

//You hop on your computer to begin working on the DIGIMUSER
//First, make sure to pull the repo

git pull

//Next, make sure you are in your development branch

git branch [THE_BRANCH_YOUR_ARE_DEVELOPING_IN]

//Work on coding and designing like on awesome engineer.

//Now you are at a good saving point, and would like to take a break for the day
//Commit your changes with a nice message about what you added/edited

git commit -m "Reworked the communication code for faster data transfer"

//You also want to save your code to the Github repo. So push those commits to the repo

git push origin [THE_BRANCH_YOU_ARE_DEVELOPING_IN]

```
