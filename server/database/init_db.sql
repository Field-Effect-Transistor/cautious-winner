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

CREATE TABLE IF NOT EXISTS Slots (
    slot_id INTEGER PRIMARY KEY AUTOINCREMENT,
    status TEXT NOT NULL DEFAULT 'FREE'
);

CREATE TABLE IF NOT EXISTS Parking (d
    park_id INTEGER PRIMARY KEY AUTOINCREMENT,
    type INTEGER,
    start_date INTEGER NOT NULL,
    end_date INTEGER,
    slot_id INTEGER,
    user_id INTEGER,
    lPlate TEXT,
    FOREIGN KEY (slot_id) REFERENCES Slots(slot_id) ON DELETE SET NULL,
    FOREIGN KEY (user_id) REFERENCES Users(user_id) ON DELETE CASCADE
);
