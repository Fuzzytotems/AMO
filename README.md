# AMO

# Must Read!

There is currently a major bug in the game where casting a spell in Play-In-Editor causes the game to crash to a Package-PlayInEditor() bug.  If you wish to test the game in PIE, you must do the following...
1.) Open BP_Spellbook, ArenaCharacter, SpellDataTable, SpellInfoStruct, and ALL spells found within the Spells folder
2.) Go into BP_Spellbook, go to the SpawnActor found within the FinishCastingFunc function, right click the node, and refresh it.  This step isn't always necessary, but sometimes the editor will crash if you try to cast a spell.

If you do not wish to go through this, you must launch the game in Standalone mode.

I apologize for the inconvenience, but it is currently unclear as to what is causing the crash.

# Controls

WASD are your movement controls.
B opens your spellbook.
I opens your inventory.
