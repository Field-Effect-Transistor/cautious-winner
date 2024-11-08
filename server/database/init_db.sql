-- init_db.sql

CREATE TABLE IF NOT EXISTS Users (
    user_id INTEGER PRIMARY KEY AUTOINCREMENT,
    email TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL,
    lPlate TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS Auth (
    user_id INTEGER PRIMARY KEY,
    lastAuth INTEGER,
    created_at INTEGER,
    FOREIGN KEY (user_id) REFERENCES Users(user_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS Parking (
    park_id INTEGER PRIMARY KEY AUTOINCREMENT,
    type INTEGER,
    start_date INTEGER NOT NULL,
    end_date INTEGER,
    slot_id INTEGER,
    user_id INTEGER,
    lPlate TEXT,
    FOREIGN KEY (user_id) REFERENCES Users(user_id) ON DELETE CASCADE
);
