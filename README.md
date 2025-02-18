# Parkour Ball

Parkour Ball is a short 3rd person puzzle platforming demo where you can activate platforms with dodgeballs.

## Programming
This is just a super short test project made using C++ in Unreal Engine 5.3. I made a custom 3rd person Character and created a rough throwing animation. 
The thrown projectile will spawn attached to a socket on the character model's hand. At the end of the animation the ball is released and velocity is applied.
All moving platforms use the same Movement Component to control their location and rotation. From an initial Puzzle Platform class, I created a timed variant that can toggle the movement/rotation on or off after a short delay.
These platforms can be used in combination with the Platform Button class to have their movement/rotation triggered on and off when hit by a Throwable Projectile.
I created a super short level to showcase each element created and their different use cases. I also created a simple Goal component to give the level a definitive end.
