CREATE TABLE Hero (
  hero_id INTEGER PRIMARY KEY AUTOINCREMENT,
  navn CHAR(25),
  xp INT,
  level INT,
  styrke INT,
  hp INT,
  baseHP INT,
  gold INT
);

CREATE TABLE Weapon (
  weapon_id INTEGER PRIMARY KEY AUTOINCREMENT,
  navn CHAR(25),
  skade INT,
  styrkeModifier INT,
  holdbarhed INT,
  hero_id INT,
  FOREIGN KEY (hero_id) REFERENCES Hero(hero_id)
);

CREATE TABLE KillLog (
  log_id INTEGER PRIMARY KEY AUTOINCREMENT,
  hero_id INT,
  weapon_id INT,
  enemy_name CHAR(25),
  FOREIGN KEY (hero_id) REFERENCES Hero(hero_id),
  FOREIGN KEY (weapon_id) REFERENCES Weapon(weapon_id)
);
