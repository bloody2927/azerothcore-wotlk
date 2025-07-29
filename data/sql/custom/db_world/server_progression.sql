-- Custom server progression table
CREATE TABLE IF NOT EXISTS `server_progression` (
  `id` TINYINT UNSIGNED NOT NULL DEFAULT 1 COMMENT 'singleton row id',
  `stage` TINYINT UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Current server progression stage',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

REPLACE INTO `server_progression` (`id`, `stage`) VALUES (1, 0);

