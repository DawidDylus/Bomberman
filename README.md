# Bomberman

If i would work on project more:

1. In Pickup classes add functions that will change character variables(BombRange, BombsQuantity, RunSpeed). Those functions should trigger when there is  colision with any character(change only specific Character using cast).
2. Add condition to explosion function in bomb class, so that when the traceRay collide with ABomb class it will trigger Explosion Function of that specific Bomb object. Bombs would generate Block hits.
3. Adds new UI in game add textblock for displaying variable RoundTime which i would specify in gamemode blueprint(or c++). variable would be updated in function. 
4. Add UI that will be called when all characters in level would have leaves variable set to 0 or lower/UI could also be called when round time ends.
To froze the game i would use SetGlobalTimeDilation();
5. To Show draw when the last players die in the same blomb blast i would create variable in characters and bombs that would register explosion id. Bombs would generate explosionID when the time that they were set to trigger at, became 0(and the bombs explode). That id will be passet to bombs that are trigger by that explosion. In this way all chained explosion would have the same ID. When Players die ID would be checked and if it is the same and condition to end the game would be true then the DRAW would be shown. To check for DRAW by end of time round we have to check if there is at least 2 players alive(exist in level or lives variable is >= 1), when the time ends.
6. Multiplayer: Add UI that will handle connection to sesion by lan network. Using CretePlayer function to spawn new player and controler. Set his location baset on how many  players there are in level. Make sure that replication is set, and references to objects are unique.
7. AI: Create AI controler that will be spawn by using CreatePlayer function. We can swap new players with AI or could add another one. AI should change position if there is bomb in one of the four direction on map (maybe change range that ai run away as game progres). Put bomb if there is player on line. Check if there is pickup in vicinity and go to that location if it is. IF there is no player nerby put bomb on the same lane that normalboxes are. 
