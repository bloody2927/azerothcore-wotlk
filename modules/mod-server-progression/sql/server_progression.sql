CREATE TABLE IF NOT EXISTS `server_progression` (
  `phase` TINYINT UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `server_progression` (`phase`) VALUES (0);

CREATE TABLE IF NOT EXISTS `server_progression_quest` (
  `quest` MEDIUMINT UNSIGNED NOT NULL,
  `required_phase` TINYINT UNSIGNED NOT NULL,
  PRIMARY KEY (`quest`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
