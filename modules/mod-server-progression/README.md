# Server Progression Module

This module provides a global server phase system that allows administrators to control content unlocking over time.

## Configuration

The module loads its state from the `server_progression` table in the world database. Administrators can adjust the current phase via the in game command `.phase set <number>` and inspect it using `.phase get`.

## Installation

1. Apply the SQL found in `sql/server_progression.sql` to your world database.
2. Recompile the core with the module enabled (static by default).

After startup the server will load the current phase and store modifications automatically.
