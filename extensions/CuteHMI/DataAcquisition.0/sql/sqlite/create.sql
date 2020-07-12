CREATE TABLE [%1.tag]
(
        id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
        name VARCHAR(255) NOT NULL UNIQUE
);

CREATE INDEX [%1.index_tag_name] ON [%1.tag] (name);

CREATE TABLE [%1.recency_bool]
(
        tag_id INTEGER REFERENCES [%1.tag](id) PRIMARY KEY,
        value BOOL NOT NULL,
        time INTEGER NOT NULL
);

CREATE TABLE [%1.recency_int]
(
        tag_id INTEGER REFERENCES [%1.tag](id) PRIMARY KEY,
        value INTEGER NOT NULL,
        time INTEGER NOT NULL
);

CREATE TABLE [%1.recency_real]
(
        tag_id INTEGER REFERENCES [%1.tag](id) PRIMARY KEY,
        value double precision NOT NULL,
        time INTEGER NOT NULL
);

CREATE TABLE [%1.event_bool]
(
        id serial PRIMARY KEY,
        tag_id INTEGER REFERENCES [%1.tag](id),
        value BOOL NOT NULL,
        time INTEGER NOT NULL
);

CREATE INDEX [%1.index_event_bool_time] ON [%1.event_bool] (time);

CREATE TABLE [%1.event_int]
(
        id serial PRIMARY KEY,
        tag_id INTEGER REFERENCES [%1.tag](id),
        value INTEGER NOT NULL,
        time INTEGER NOT NULL
);

CREATE INDEX [%1.index_event_int_time] ON [%1.event_int] (time);

CREATE TABLE [%1.event_real]
(
        id serial PRIMARY KEY,
        tag_id INTEGER REFERENCES [%1.tag](id),
        value double precision NOT NULL,
        time INTEGER NOT NULL
);

CREATE INDEX [%1.index_event_real_time] ON [%1.event_real] (time);

CREATE TABLE [%1.history_bool]
(
        id serial PRIMARY KEY,
        tag_id INTEGER REFERENCES [%1.tag](id),
        open BOOL NOT NULL,
        close BOOL NOT NULL,
        min BOOL NOT NULL,
        max BOOL NOT NULL,
        open_time INTEGER NOT NULL,
        close_time INTEGER NOT NULL,
        count INTEGER NOT NULL
);

CREATE INDEX [%1.index_history_bool_close_time] ON [%1.history_bool] (close_time);

CREATE TABLE [%1.history_int]
(
        id serial PRIMARY KEY,
        tag_id INTEGER REFERENCES [%1.tag](id),
        open INTEGER NOT NULL,
        close INTEGER NOT NULL,
        min INTEGER NOT NULL,
        max INTEGER NOT NULL,
        open_time INTEGER NOT NULL,
        close_time INTEGER NOT NULL,
        count INTEGER NOT NULL
);

CREATE INDEX [%1.index_history_int_close_time] ON [%1.history_int] (close_time);

CREATE TABLE [%1.history_real]
(
        id serial PRIMARY KEY,
        tag_id INTEGER REFERENCES [%1.tag](id),
        open double precision NOT NULL,
        close double precision NOT NULL,
        min double precision NOT NULL,
        max double precision NOT NULL,
        open_time INTEGER NOT NULL,
        close_time INTEGER NOT NULL,
        count INTEGER NOT NULL
);

CREATE INDEX [%1.index_history_real_close_time] ON [%1.history_real] (close_time);
