CREATE TABLE IF NOT EXISTS `server_progression` (
  `name` VARCHAR(64) NOT NULL,
  `value` INT UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Server progression flags';

REPLACE INTO `server_progression` (`name`, `value`) VALUES ('content_phase', 1);
