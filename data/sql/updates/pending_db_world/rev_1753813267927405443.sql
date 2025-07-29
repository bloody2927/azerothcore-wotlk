-- DB update pending -> remove invalid event references
-- Remove creatures in game_event_creature not present in creature table
DELETE FROM `game_event_creature`
WHERE `guid` NOT IN (SELECT `guid` FROM `creature`);

-- Remove gameobjects in game_event_gameobject not present in gameobject table
DELETE FROM `game_event_gameobject`
WHERE `guid` NOT IN (SELECT `guid` FROM `gameobject`);
