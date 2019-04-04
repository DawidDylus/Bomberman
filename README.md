# Bomberman

Notes about map:
Bombs are not proportional and it let you go pass them. I will not change that because it can be done leater. Moreover possibity of passing bombs is intresting and might be quite fun. Have to check that leater.

Notes obout SpawnActorComponent:
I created it specialy for creating Actors in world.I wanted this to be a component because it's reusable and I will need similar functionality with pickups.

I am trying to put all my #include in .cpp files so it will not be loaded when I put reference to .h file

I had to change Character from BP to BP child of c++ class. I can use old BP function and add  new variables to it in c++. C++ class of character is imported from ThirdPersonView c++ project without some functions or components.