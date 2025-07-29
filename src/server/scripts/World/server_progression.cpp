#include "WorldScript.h"
#include "DatabaseEnv.h"
#include "Log.h"

class ServerProgressionInitializer : public WorldScript
{
public:
    ServerProgressionInitializer() : WorldScript("ServerProgressionInitializer", { WORLDHOOK_ON_STARTUP }) { }

    void OnStartup() override
    {
        WorldDatabase.DirectExecute(R"(
            CREATE TABLE IF NOT EXISTS `server_progression` (
                `name` VARCHAR(64) NOT NULL,
                `value` INT UNSIGNED NOT NULL DEFAULT 0,
                PRIMARY KEY (`name`)
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci
        )");

        WorldDatabase.DirectExecute("REPLACE INTO `server_progression` (`name`, `value`) VALUES ('content_phase', 1)");
        LOG_INFO("server.loading", "Server progression table initialized");
    }
};

void AddSC_server_progression()
{
    new ServerProgressionInitializer();
}
