Ben Gittelson
CS 2110
11/8/16

-How to play: To start the game from the title screen, press A. I mapped A to the actual A key in mednafen, but you may need to press Z or remap it in VBA-M. Pressing A will take you to the instructions screen. If you press the select key there, you'll return to the home screen. If you press L, you'll play the game as a Democrat; if you press R, you'll play as a Republican. Pressing any other key in this state will not do anything. 

When you get into the actual game, you'll have three lives/chances to get to the White House. You lose a life whenever you hit a member of the opposing party; doing so will also take your player back to the upper left hand corner (i.e. you'll lose any progress you've made thus far--this was a deliberate design choice). If you make it to the red, white, and blue line before you run out of lives, you'll win and will be taken to the winning screen. From there, you can press select to get back to the start screen and play again (you can also press select to return to the start screen at any other time). If you lose, you'll be taken to a similar lose screen (although the actual images on the lose and win screens will depend on the party you picked). 

-A quick tip: I've found that the most reliable way to win the game is to move diagonally down and to the right from the very beginning so that you can get straight into the White House, but you'll have to play around with it somewhat (it might take you a few tries before you can reliably beat it). 

-Some notes on my sources: I got the idea for my collision code from Mozilla (https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection), and much of my myLib.h code came from Professor Leahy's lecture code, although I modified it to fit my game. The images came from various clip art and news websites. 


