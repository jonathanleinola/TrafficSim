# Review form for project

**Name of project to be reviewed:**
* Traffic Simulator 2019 - Group 2

**Names of reviewers:**
* Jonathan Leinola - 477329
* Niko Uski - 51961T
* Artur Gynter - 569499
* Hien Cao - 716718


## 1. Overall design and functionality (0-6p)

  * 1.1: The implementation corresponds to the selected topic and scope. The extent of project is large enough to accommodate work for everyone (2p)
    + In the plan, it mentions that they would fulfill all basic features required by the course and continue to add additional features later. The work is enough for everyone. 
    + They took an analytical approach to implement this project as they mentioned in the meeting.

  * 1.2: The software structure is appropriate, clear and well documented. e.g. class structure is justified, inheritance used where appropriate, information hiding is implemented as appropriate. (2p)
    + It is good to have a diagram to illustrate the software structure. However, the diagram is not explained in detail. It is recommended to update the software structure during the development process.
    + Their class structure is similar to ours. Should work well for them.

  * 1.3: Use of external libraries is justified and well documented. (2p)
    + They plan to use Qt for the GUI and OpenStreetMap for the map data.

## 2. Working practices (0-6p)

  * 2.1: Git is used appropriately (e.g., commits are logical and frequent enough, commit logs are descriptive). (2 p)
    + At the time of the review, there are 25 commits in the project repositories. Part of commits is in English, and the rest is in Finnish. It is better to unify in one language. 
    + Most of the commits are descriptive enough.

  * 2.2: Work is distributed and organized well. Everyone contributes to the project and has a relevant role that matches his/her skills. The distribution of roles is described well enough. (2p)
    + The works are distributed equally. The plan explains the task division quite clear and reasonable. 

  * 2.3: Quality assurance is appropriate. Implementation is tested comprehensively and those testing principles are well documented. 
  (2p)
    + Project is in early stage and testing will probably come later. Not much to add here

## 3. Implementation aspects (0-8p)

  * 3.1: Building the software is easy and well documented. CMake or such tool is highly recommended. (2p)
    + We couldn't find documentation on how to build and run this project.
    + They don't use Cmake or another similar tool.

  * 3.2: Memory management is robust, well-organized and coherent. E.g., smart pointers are used where appropriate or RO3/5 is followed. The memory management practices should be documented. (2p)
    + Dynamic allocations with "new"-keyword
    + There is no documentation on which class will have ownership of these allocated object and we couldn't find any delete calls. 
    + There are memory leaks at this point.

  * 3.3: C++ standard library is used where appropriate. For example, containers are used instead of own solutions where it makes sense. (2p)
    + Yes, they utilize std::vector for example
    + According to a team member, he does not agree with storing Coordinates as std::pair<int, int>, struct might be a better approach (more descriptive and scalable).

  * 3.4: Implementation works robustly also in exceptional situations. E.g., functions can survive invalid inputs and exception handling is used where appropriate. (2p)
    + When loading a city from a file, it is not done inside of the try block.
    + Current implementation is relying on that the file is found and file is in a correct format.

## 4. Project extensiveness (0-10p)

  * Project contains features beyond the minimal requirements: Most of the projects list additional features that can be implemented for more points. Teams can also suggest their own custom features, though they have to be in the scope of the project and approved by the course assistant who is overseeing the project. (0-10p)
    + It cannot be commented on this at the moment (mid-term of the project).