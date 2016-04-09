** Backgrounds appear on mame on a scale of 1/3 the size of the tiles.
To make the backgrounds have a size coherent with the sprites in the 
spritesheets, they have been amplified x3 using the "Nearest Neighbour"
enlargement option in PS, since pixels don't get blurry that way !!!


** All sprites are separated from each other in the spritesheets
with a 20 px gap, just to make things easier when we start having 
a lot of sprites!!!

- Screen resolution: 768x671 px // Starts at 20 px to the right and 
				    20 px to the top on the spritesheet
- Saloon house size: 336x432 px  

** The rest of the sprites are composed by tiles, which makes calculating
the resolution easier !!! Knowing that each tile is 48x48 px, we can 
guess the size of every spriten by guessing by how many tiles it is 
composed. f.e.; if a sprite is composed by tiles such like:

 []	// Then this example sprite resolution is going to be 48x96px !! 
 []						                (96=48*2)

**** We still need to take out all the sprites of destruction for 
this stage. And it's a lot of work! 


