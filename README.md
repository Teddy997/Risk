# COMP345_risk 
<strong>CHECKLIST FOR PD1 (NOV 11 OR NOV 12)</strong>
<table>
<tr>
<td>User-driven creation of map elements, such as country, continent, and connectivity between countries.</td><td></td>
</tr>
<tr>
<td>Saving a map to a file exactly as edited.</td><td></td>
</tr>
<tr>
<td>Loading a map from an existing file, then editing the map</td><td></td>
</tr>
<tr>
<td>Verification of map correctness before saving (at least 3 types of incorrect maps)</td><td></td>
</tr>
<tr>
<td>Implementation of a game driver implementing the game phases.</td><td><strong>X</strong></td>
</tr>
<tr>
<td>Game starts by user selection of a user-saved map file, then loads the map as a connected graph.</td><td></td>
</tr>
<tr>
<td>User chooses the number of players, all countries are randomly assigned to players.</td><td><strong>X</strong></td>
</tr>
<tr>
<td>Calculation of correct number of reinforcement armies.</td><td><strong>X</strong></td>
</tr>
<tr>
<td>User-driven placement of reinforcement armies on the map.</td><td><strong>X</strong></td>
</tr>
<tr>
<td>Implementation of a valid fortification move according to the Risk rules. </td><td><strong>X</strong></td>
</tr>
</table>

Demo Sequence:</br>
1. Run program</br>
2. Display options: load map, edit map</br>

Load Map:</br>
1. Play default</br>
2. Display others</br>

Display Others:</br>
1. Show list of maps</br>
2. User chooses map to load</br>

Edit map:</br>
1. Choose a new map or choose a map to edit</br>

New edit map:</br>
1. Type name of map</br>
2. Load default map</br>
3. Ask for new country name</br>
4. Create country with name</br>
5. Ask for continent that it's contained in OR create new continent</br>
6. Ask for adjacencies</br>
7. Check for proper map: (1. continent has at least one country. 2. country has at least 1 adjacency. 3. country belongs to one and only one continent)</br>

Edit existing map:</br>
1. List map files</br>
2. Choose map</br>
3. Proceed to new edit map sequence</br>

Play</br>
1. Ask number of players (2-4) XXX </br>
2. Assign countries randomly to players XXX </br>
3. Put 1 army in each country automagically. Then randomly assign rest. Display message: "for demo purposes we have assigned all armies randomly" XXX </br>
4. Start main game sequence XXX </br>

Main game sequence:</br>
1. Player plays first XXX </br>
2. Reinforcement phase (calculates number of countries/3 and then you can distribute it to your countries) XXX </br>
3. Skip battle phase cause lame XXX </br>
4. Fortification phase - only once (player can choose a country they own and move armies to another country they own through a path of adjacent countries they own)</br>
5. Repeat XXX </br>
