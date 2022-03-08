# hack-n-paper

Bogazici University

Computer Engineering Department

Fall 2020

CMPE 250

Project 2

Altay Acar

***

A discrete event simulation project that simulates a virtual hackathon organized by the famous Dunder Mifflin from The Office TV-Series.

Rules:
- Hack-N-Paper simulates with fictional hackers to find how many desks would be enough. The hackers arrive at different times to the event and they regularly commit code snippets. They also visit hoodie and sticker desks, which are placed sequentially: To grab the stickers and hoodies, one first visits the sticker desk and waits in the sticker queue until the desk is available. When the waiting is finally over, the hacker is served with the sticker and immediately enters the hoodie queue.
- There might be multiple sticker and hoodie desks, depending on the simulation configuration. In this case, every desk is operated by an attendant who serves the gifts (stickers and hoodies) and the service takes some time. Every desk has a different service time.
- There are exactly two queues in the event: one for stickers and one for hoodies. So, the sticker desks share a common queue, and so do the hoodie desks.
- The sticker queue works in first-come-first-served fashion. If two hackers arrive at the same time, the one with the lower ID is served first. When the hacker is served, they enter the hoodie queue, immediately. Hackers with less than 3 commits are not allowed to enter the queue and call such attempts “invalid”.
- The commits with line changes over 20 are only counted towards queue entrance. In other words, the commits with less than 20 changed lines are simply irrelevant to deserve the right to enter the sticker queue.
- In the hoodie queue, the more the commits, the earlier the service. If any two hackers have an equal number of commits, the one that arrived earlier is served before. If they arrived at the same time as well, the one with the lower ID is served first.
- Both for the sticker and hoodie desks, hackers visit the first available desk for service (the available desk with the smallest ID) when they leave the queue.
- Each hacker is allowed to take at most 3 stickers and hoodies. Hence, whenever a hacker attempts to enter the queue 4th time, this is also called an “invalid attempt”.
- The commits are made only while waiting in a sticker queue or during the period out of the queues.
- One can enter the hoodie queue only through a sticker desk, no direct entrance is possible.
- Hackers are associated with increasing IDs as they arrive in HackNPaper. The first comer is assigned with ID 1, the next one is assigned with 2, etc.

Testing:
- Code will be run with the below command to the CLI:
  > g++ *.cpp *.h -std=c++11 -o project2
  > ./project2 inputFile outputFile

Input:
- The first line contains an integer N that denotes the total number of hackers and N floats that denote the arrival time of each hacker in terms of seconds passed from the beginning of HackNPaper.
- The second line contains an integer C which is the total number of code commits, including the ones shorter than 20 lines.
- Each of the next C lines contains two integers and one float: the ID of the hacker that commits the code, the number of line changes in the commit, and the second T in which the commit is made.
- Each of the next C lines contains two integers and one float: the ID of the hacker that commits the code, the number of line changes in the commit, and the second T in which the commit is made.
- Each of the the next Q lines contains one integer and one float which are the ID of the hacker and the second he/she attempts to enter the sticker queue, respectively.
- The next line comprises an integer Ds that denotes the number of sticker desks and a list of floats of size Ds. The ith element of the list denotes the service time of the ith sticker desk.
- The next line starts with an integer Dh and is followed by a list of floats of size Dh. Similar to previous line, the ith element of the list denotes the service time of the ith hoodie desk.

Output:
- 13 statistics are printed to the output file. In case you cannot report any of the following 13 statistics, print -2 for each of them in order to adhere the output format.
  1. Maximum length of the sticker queue.
  2. Maximum length of the hoodie queue.
  3. Average number of gifts grabbed per hacker.
  4. Average waiting time in the sticker queue.
  5. Average waiting time in the hoodie queue.
  6. Average number of code commits per hacker.
  7. Average change length of the commits, including the ones shorter than 20 lines.
  8. Average turnaround time (Turnaround time: Total time passed from the sticker queue entrance until leaving the hoodie desk.) To compute, sum all turnaround times and divide it by the number of turnarounds, which is also equal to the number of total gifts given away.
  9. Total number of invalid attempts to enter sticker queue.
  10. Total number of invalid attempts to get more than 3 gifts.
  11. ID of the hacker who spent the most time in the queues and the waiting time of that hacker in seconds. If more than one hacker spent the same amount of time, choose the one with the smallest ID.
  12. ID of the hacker who spent the least time in the queues and the waiting time of that hacker in seconds, among the ones who grabbed three stickers and hoodies. If more than one hacker spent the same amount of time, choose the one with the smallest ID. If there is no hacker that grabbed three stickers and hoodies, print -1 for both.
  13. Total seconds passed during the hackathon.
