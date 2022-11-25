CREATE SCHEMA %1;

CREATE TABLE %1.tag
(
        id serial PRIMARY KEY,
        name varchar(255) NOT NULL UNIQUE
);

CREATE INDEX index_tag_name ON %1.tag USING hash (name);

CREATE TABLE %1.recency_bool
(
        tag_id integer REFERENCES %1.tag(id) PRIMARY KEY,
        value bool NOT NULL,
        time timestamptz NOT NULL
);

CREATE TABLE %1.recency_int
(
        tag_id integer REFERENCES %1.tag(id) PRIMARY KEY,
        value integer NOT NULL,
        time timestamptz NOT NULL
);

CREATE TABLE %1.recency_real
(
        tag_id integer REFERENCES %1.tag(id) PRIMARY KEY,
        value double precision NOT NULL,
        time timestamptz NOT NULL
);

CREATE TABLE %1.event_bool
(
        id serial PRIMARY KEY,
        tag_id integer REFERENCES %1.tag(id),
        value bool NOT NULL,
        time timestamptz NOT NULL
);

CREATE INDEX index_event_bool_time ON %1.event_bool (time);

CREATE TABLE %1.event_int
(
        id serial PRIMARY KEY,
        tag_id integer REFERENCES %1.tag(id),
        value integer NOT NULL,
        time timestamptz NOT NULL
);

CREATE INDEX index_event_int_time ON %1.event_int (time);

CREATE TABLE %1.event_real
(
        id serial PRIMARY KEY,
        tag_id integer REFERENCES %1.tag(id),
        value double precision NOT NULL,
        time timestamptz NOT NULL
);

CREATE INDEX index_event_real_time ON %1.event_real (time);

CREATE TABLE %1.history_bool
(
        id serial PRIMARY KEY,
        tag_id integer REFERENCES %1.tag(id),
        open bool NOT NULL,
        close bool NOT NULL,
        min bool NOT NULL,
        max bool NOT NULL,
        open_time timestamptz NOT NULL,
        close_time timestamptz NOT NULL,
        count integer NOT NULL
);

CREATE INDEX index_history_bool_close_time ON %1.history_bool (close_time);

CREATE TABLE %1.history_int
(
        id serial PRIMARY KEY,
        tag_id integer REFERENCES %1.tag(id),
        open integer NOT NULL,
        close integer NOT NULL,
        min integer NOT NULL,
        max integer NOT NULL,
        open_time timestamptz NOT NULL,
        close_time timestamptz NOT NULL,
        count integer NOT NULL
);

CREATE INDEX index_history_int_close_time ON %1.history_int (close_time);

CREATE TABLE %1.history_real
(
        id serial PRIMARY KEY,
        tag_id integer REFERENCES %1.tag(id),
        open double precision NOT NULL,
        close double precision NOT NULL,
        min double precision NOT NULL,
        max double precision NOT NULL,
        open_time timestamptz NOT NULL,
        close_time timestamptz NOT NULL,
        count integer NOT NULL
);

CREATE INDEX index_history_real_close_time ON %1.history_real (close_time);
