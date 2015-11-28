# COMP345_risk 
<strong>CURRENT KNOWN BUGS / FEATURES WE NEED</strong>
<table>
<tr><td>Need to be able to delete maps</td><td></td></tr>
<tr><td>Need to have a check for the number of AI players if the map is too small (can't have 3 AI with a map of two countries)</td><td></td></tr>
<tr><td>DEFAULT MAP is the default map we can load. Need to prevent anyone from attempting to edit it</td><td></td></tr>
</table>

<strong>CHECKLIST FOR FINAL PROJECT (DEC 3 OR DEC 4)</strong>
<table>
<tr>
<td>User-driven creation of map elements, such as country, continent, and connectivity between countries.</td><td><strong>X</strong></td>
</tr>
<tr>
<td>Saving a map to a file exactly as edited.</td><td><strong>X</strong></td>
</tr>
<tr>
<td>Loading a map from an existing file, then editing the map</td><td><strong>X</strong></td>
</tr>
<tr>
<td>Use of the Adapter pattern to save/load from two different map file formats (based on assign3)</td><td></td>
</tr>
<tr>
<td>Verification of map correctness before saving (at least 3 types of incorrect maps)</td><td><strong>X</strong></td>
</tr>
<tr>
<td>Implementation of a round-robin loop for players' turns/phases, identification of a winner and end of game, defeated player is removed from round-robin loop</td><td></td>
</tr>
<tr>
<td>Save/Load a game in progress using a Builder pattern (based on assign3)</td><td><strong>X</strong></td>
</tr>
<tr>
<td>Player Observer that displays relevant information about a player (based on assign2)</td><td></td>
</tr>
<tr>
<td>Map Observer that displays relevant information about the map (based on assign2)</td><td></td>
</tr>
<tr>
<td>Game statistics Observer/Decorator that displays user-selected game statistics (based on assign3)</td><td></td>
</tr>
<tr>
<td>Game log Observer/Decorator that displays logging of user-selected players/phased (based on assign3)</td><td></td>
</tr>
<tr>
<td>Game log and game statistics Observers are initially set to show user-selected parts (based on assign3) using the Observer and Decorator patterns</td><td></td>
</tr>
<tr>
<td>User selection of a previously user-saved map, then load the map</td><td><strong>X</strong></td>
</tr>
<tr>
<td>User chooses the number of players, all countries are randomly assigned to players.</td><td><strong>X</strong></td>
</tr>
<tr>
<td>Types of players are initially assigned and implemented using a Strategy pattern (based on assign2). Types of players can be changed at any time during play.</td><td></td>
</tr>
<tr>
<td>Calculation of correct number of reinforcement armies and placement of armies on the map.</td><td><strong>X</strong></td>
</tr>
<tr>
<td>Correct implementation of cards and their additional reinforcements.</td><td><strong>X</strong></td>
</tr>
<tr>
<td>Correct identification of valid attacking/attacked country.</td><td><strong>X</strong></td>
</tr>
<tr>
<td>Correct implementation of an attack using the Risk battle model</td><td><strong>X</strong></td>
</tr>
<tr>
<td>Correct implementation of the post-battle movement after a victory.</td><td><strong>X</strong></td>
</tr>
<tr>
<td>A victory gives a card, eliminating a player transfers all the defeated player's cards.</td><td><strong>X</strong></td>
</tr>
<tr>
<td>Implementation of a valid fortification move according to the Risk rules. </td><td><strong>X</strong></td>
</tr>
</table>
