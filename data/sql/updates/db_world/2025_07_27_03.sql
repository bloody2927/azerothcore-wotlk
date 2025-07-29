-- DB update 2025_07_27_02 -> 2025_07_27_03

DROP TABLE IF EXISTS `server_progression`;
CREATE TABLE `server_progression` (
    `expansion` TINYINT UNSIGNED NOT NULL DEFAULT '3' COMMENT 'game expansion level',
    `phase` TINYINT UNSIGNED NOT NULL DEFAULT '0' COMMENT 'content progression stage',
    PRIMARY KEY (`expansion`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Server progression state';

INSERT INTO `server_progression` (`expansion`, `phase`) VALUES (3, 0);
