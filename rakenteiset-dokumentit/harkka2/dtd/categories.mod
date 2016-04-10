<!-- Each level should have at least vegetables, nonVegetables and enemies. The powerUps are optional-->
<!ELEMENT gameObjects (vegetables, nonVegetables, enemies, powerUps?)> 
<!ELEMENT vegetables (vegetable+)>
<!ELEMENT nonVegetables (nonVegetable+)>
<!ELEMENT enemies (enemy+)>
<!ELEMENT powerUps (powerUp*)>

<!-- Each enemy must have a health point value and a level value describing its strength. -->
<!ELEMENT enemy (#PCDATA) >
<!ATTLIST enemy health CDATA #REQUIRED >
<!ATTLIST enemy level CDATA #REQUIRED >

<!-- Each vegetable must at least specify how many points it yields. It can also have a description.-->
<!ELEMENT vegetable (#PCDATA) >
<!ATTLIST vegetable points CDATA #REQUIRED >
<!ATTLIST vegetable description CDATA #IMPLIED >

<!-- NonVegetables have to specify the amount of damage they deal and they can have a description too.-->
<!ELEMENT nonVegetable (#PCDATA) >
<!ATTLIST nonVegetable damage CDATA #REQUIRED >
<!ATTLIST nonVegetable description CDATA #IMPLIED >

<!-- PowerUps must specify which property of Mr Green Genes they affect eg. speed and how long they last.-->
<!ELEMENT powerUp (#PCDATA)>
<!ATTLIST powerUp effect (speed|jumpHeight|damage) #REQUIRED>
<!ATTLIST powerUp duration CDATA #REQUIRED>


