# CS-300-Data-Structures-and-Algorithms
contains my CS-300 projects, including algorithm runtime and memory analysis, C++ course management software, and reflections on data structures and software development.

### 1. What was the problem you were solving in the projects for this course?

For both projects, the main purpose was to help ABC University develop a program that academic advisors could use to look up Computer Science courses and their prerequisites. The program needed to take the course information from a file, organize it, and allow the advisor to either print all the courses in alphanumeric order or search for a particular course. The problem was not necessarily figuring out how to display the information, but determining which data structure would make the most sense for storing and retrieving it.

In Project One, I had to compare a vector, hash table, and binary search tree and look at how each one performed. I examined their runtime and memory usage because even though all three structures could be used for the same purpose, they handled the information differently. I wanted to be methodical about the comparison rather than just selecting one because it seemed easier. A structure might be good at searching for a particular record but require additional work when trying to print everything in order.

Project Two was taking what I worked on in Project One and actually building the application in C++. This involved reading the CSV file, storing the information, and making sure the correct courses and prerequisites were displayed. There were some intricate parts to getting everything to work together, especially when dealing with the file and how the program processed the information.

Overall, I was trying to develop a program that accomplished what the university needed without making it more complicated than necessary. I had to be prudent about the design because getting the program to work was only part of the assignment. I also needed to understand why I was using that particular approach.

### 2. How did you approach the problem? Consider why data structures are important to understand.

When I started working on the projects, I first looked at what the program was required to do and then tried to figure out the best way to handle the information. I did not want to start writing everything and then have to go back and change a large portion of the code because the structure I chose was not working the way I expected. We had already worked with different structures in previous assignments, so I used those exercises to help me understand what would work for this particular program.

I looked at how a vector stores information and how the program would search through the records. From there, I compared it to a hash table, which uses a hash function to determine where information is stored. One thing I had to consider was how collisions would be handled because multiple records could end up being assigned to the same location. The binary search tree used a different approach by comparing course numbers to determine where the information belonged. Each structure had its advantages, but I also had to look at what additional work would be required to use it.

I used Big O notation to compare the time complexity and determine how the operations could change as more courses were added. This helped me distinguish between something that worked well with a small amount of information and something that would still be practical with a larger number of records. I also had to consider the difference between searching for one course and printing all of them in order.

What I took away from this was that selecting a data structure needs to be a deliberate decision. Just because one structure works does not mean it is the best option for every program. I have a better understanding of why it is necessary to look at the requirements first instead of trying to make the requirements fit whatever code I already know how to write.

### 3. How did you overcome any roadblocks you encountered while going through the activities or projects?

I had quite a few problems throughout this course, especially when we started getting into the linked list, hash table, and binary search tree assignments. There were times when I thought I had corrected one issue, only to find out that another function was not working correctly. Some of the problems were simple mistakes, while others required me to go back through the code and figure out what I was actually doing wrong.

One of the assignments that required more attention was the binary search tree. I had to understand how recursion worked when the program was inserting, searching, and removing records. If one of my conditional statements was wrong, it could affect how the program moved through the tree. I had to be meticulous about checking each part of the function because the program compiling did not necessarily mean everything was working correctly.

I also ran into problems during Project Two when I was trying to get the program to read the CSV file. The code was there, but Visual Studio was not locating the file the way I expected. I ended up going into the project properties and using the command-line arguments to provide the file path. Once I corrected that, the program was able to load the information. That was one of those problems where I was looking at the code when the issue was actually how the program was being launched.

The way I worked through these problems was by going back to the part that was failing, checking what the function was supposed to do, and testing it after making a correction. I tried not to change several things at the same time because then I would not know what actually fixed the problem. It was not always a quick process, and sometimes I had to go through the same section more than once.

I became more proficient at troubleshooting by taking a systematic approach instead of guessing. I still ran into errors, but I got better at figuring out where to start looking and what needed to be corrected.

### 4. How has your work on this project expanded your approach to designing software and developing programs?

Before this course, I was more focused on getting the code written and making sure the program did what the assignment asked. I still approach programming with that goal, but I now spend more time looking at how the program should be organized before I start putting everything together. One thing I noticed throughout these assignments was that a decision made early in the program could create additional problems later if I did not fully understand how everything was supposed to work.

Project One helped me with that because I had to look at algorithm efficiency instead of only concentrating on the output. I needed to compare how the structures worked, how much memory they required, and what would happen if the amount of course information increased. This made me pay more attention to the design before moving into the actual implementation.

During Project Two, I had to take that information and figure out how to put the application together. I needed separate functions for reading the file, handling the menu selections, displaying the courses, and searching for course information. Having a modular design made it easier to work through the program because I could focus on the section that was giving me problems instead of having everything tied together in one place.

I think my approach has become more pragmatic because I am looking at what the program actually needs rather than trying to add something just because I know how to do it. I also understand that a working program can still have problems with how it was designed. If I overlook something during the planning stage, I could end up spending more time correcting it later than I would have spent figuring it out in the beginning.

I am not going to say that I always get the design right the first time, because these projects showed me otherwise. However, I am paying more attention to the decisions I make before writing the code and how those decisions affect the rest of the application.

### 5. How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

One thing I have been working on throughout these assignments is making my code easier to follow, especially when I have to go back and make changes. Earlier in the course, I was mostly concerned with whether the program compiled and gave me the correct result. The more we worked with different functions, the more I realized that having working code does not mean it is going to be easy to understand or maintain later.

I started paying more attention to how I named my variables and functions, along with where comments were actually needed. I think descriptive identifiers are important because they help explain what a section of code is doing without having to write a paragraph above every line. At the same time, when the logic becomes more complicated, I would rather have a short comment explaining the purpose than come back to it later and have to figure everything out again.

I also learned to keep the different parts of the program manageable. For Project Two, having the file processing separated from the search and display functions made it easier to identify where a problem was occurring. If something needed to be changed, I could work on that particular section without having to rewrite the entire program. That is something I want to continue doing because maintainability becomes more important as a program gets larger.

Another thing I paid more attention to was input validation and error handling. When I was having problems accessing the CSV file, I saw how important it was to account for situations where the program could not find the information it needed. I cannot just assume that everything will always work correctly, especially when a program relies on files or information provided by the user.

I am more conscious now of how I organize my code and how someone else might look at it. I still have areas I need to improve, and I know that I am going to run into more problems as I continue programming. But I would rather write something that another person can follow and modify than have a program that works but is difficult to make sense of. The main thing I want to carry forward is making sure the code works, keeping it organized, and not making things more complicated than they need to be.
